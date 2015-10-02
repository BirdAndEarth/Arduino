/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2015 Frank-Michael Krause
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/
#include "ringbuffer.h"

#ifdef WIN32

int tmcnt=10;

unsigned long millis()  { return tmcnt++; }
#define NULL 0

#else
#include <wirish/wirish.h>
#endif


RingBuffer::RingBuffer(int _size, int *_values, unsigned long *_timeStamps)
{
	size = _size;     // muss ZweierPotenz sein
   values = _values;  // Pointer auf Speicher f�r Werte
	timeStamps = _timeStamps; // optional Pointer auf Speicher f�r ms timestamps
    mask = 0;
    int t = size/2;
    while (t)
    {
    	mask = (mask<<1)|1;
    	t = t/2;
    }
    reset();
}


void RingBuffer::addValue(int value)
{
   values[wrIdx] = value;

   if (timeStamps != NULL)
	  timeStamps[wrIdx] = millis();

   if (anz < size)
      anz++;

   wrIdx++;
   wrIdx &= mask;
}


void RingBuffer::reset()
{
   anz = 0;
   wrIdx = 0;
   rdIdx = 0;

   for (int i=0; i<size; i++)
      values[i] = 0;
}


/*
 * setzt rdIdx auf distance Werte vor den aktuellen wrIdx
 * Mit getValue k�nnen die letzten Werte bis zum letzten Wert abgefragt werden
 *
 * Fuer Vorw�rtsauslesen:
 * 0 bzw. Size setzen auf den �ltesten vorhandenen Wert
 * 
 * gibt 1 zur�ck, wenn gen�gend Werte im Puffer sind
 * gibt 0 zur�ck, wenn noch nicht gen�gend Werte im Puffer sind oder distance
 *                gr��er als die Pufferl�nge ist
 */
int RingBuffer::setReadIdx(int distance)
{
	if (distance > anz)
	   return 0;

	rdIdx = (wrIdx - distance) & mask;

   lastRead = 0;

	return 1;
}


/*
 * Setzt rdIdx auf den ersten Wert, f�r den der zugeh�rige timeStamp mindestens <ms> zur�ckliegt,
 * Es wird das Alter des betreffenden Wertes in ms zur�ckgegeben
 * = wird zur�ckgegeben, wenn kein Wert mindestens so alt wie gefordert ist oder keine timestamps vorhanden sind
 */
int RingBuffer::setReadIdxDt(int ms)
{
    if (timeStamps == NULL)   // keine timeStamps vorhanden
       return 0;

    unsigned long  aktTime = millis();
    unsigned long  dt=0;
    int count = 0;
    rdIdx = (wrIdx - 1)&mask; // auf letzten eingetragenen Wert setzen

    lastRead = 0;

    while (count<anz)
    {
         dt = aktTime - timeStamps[rdIdx];
         if ((int)dt > ms)
            return dt;
         count++;

         rdIdx = (rdIdx-1)&mask;
    }
 
    return 0;
}


/*
 * gibt Wert f�r rdIdx zur�ck und incrementiert rdIdx, solange rdIdx < (wrIdx-1)
 * ACHTUNG: wird wrPtr erreicht, so wird immer wieder der letzte Wert zur�ckgegeben!
 */
int RingBuffer::getValue()
{
	int ret = values[rdIdx];
   
   if (((rdIdx+1)&mask) == wrIdx)
      lastRead = 1;
   else
      rdIdx = (rdIdx+1)&mask;

   return ret;
}

/*
 * gibt Wert f�r rdIdx zur�ck, tr�gt den zugeh�rigen timestamp
 * in time ein und incrementiert rdIdx, solange rdIdx < wrIdx
 * ACHTUNG: wird wrPtr erreicht, so wird immer wieder der letzte Wert zur�ckgegeben!
 */
int RingBuffer::getValue(unsigned long *time)
{
   int ret = values[rdIdx];
 	if ((time != NULL) && (timeStamps!=NULL))
	   *time = timeStamps[rdIdx];

   if (((rdIdx+1)&mask) == wrIdx)
      lastRead = 1;
   else
      rdIdx = (rdIdx+1)&mask;

   return ret;
}


/*
 * gibt den Wert von rdIdx-1 zur�ck und decrementiert rdIdx wenn  rdIdx-1 != wrIdx
 * 
 */
int RingBuffer::getPreviousValue()
{
   int idx = (rdIdx-1)&mask;
   int ret = values[idx];
   if (idx != wrIdx)         // rdIdx darf nicht kleiner als wrIdx werden   
      rdIdx = idx;
   else
      lastRead = 1;
   return ret;
}


/*
`* decrementiert rdPtr und gibt den zugeh�rigen Wert zur�ck
 */
int RingBuffer::getPreviousValue(unsigned long *time)
{
   int idx = (rdIdx-1)&mask;
   int ret = values[idx];
   rdIdx = (rdIdx-1)&mask;
  	if ((time != NULL) && (timeStamps!=NULL))
      *time = timeStamps[idx]; 
   if (idx != wrIdx)         // rdIdx darf nicht kleiner als wrIdx werden   
      rdIdx = idx;
   else
      lastRead = 1;
   return ret;
}


int RingBuffer::getPreviousValueDt(unsigned long *dt)
{
   int idx = (rdIdx-1)&mask;
   int ret = values[idx];
   if ((dt != NULL) && (timeStamps!=NULL)) 
   {
      unsigned long  aktTime = millis();
      *dt = aktTime - timeStamps[idx];
   }
   if (idx != wrIdx)         // rdIdx darf nicht kleiner als wrIdx werden   
      rdIdx = idx;
   else
      lastRead = 1;
   return ret;
}


/*
 *  gibt eins zur�ck, sobald der �lteste Wert mit einer PreviousValue-Funktion
 *  gelesen wurde
 *  wird durch jeden Aufruf einer SetReadIdx-Funktion zur�ckgesetzt
 */
int RingBuffer::lastValueRead()
{
   return lastRead;
}


/*
 * gibt 1 zur�ck, wenn rdPtr != wrPtr
 * gibt 0 zur�ck, wenn rdPtr == wrPtr
 *
 * --> funktioniert nur, wenn zuvor SetReadIdx() aufgerufen wurde
 */
int RingBuffer::valueAvailable()
{
   return !lastRead;
}


int RingBuffer::getValueAt(int idx)
{
   return values[(wrIdx+idx)&mask];
}


int RingBuffer::getValueAt(int idx, unsigned long *time)
{
   int valueIdx = (wrIdx+idx)&mask;
  	if ((time != NULL) && (timeStamps!=NULL))
      *time = timeStamps[valueIdx]; 
   return values[valueIdx];
}


int RingBuffer::getPreviousValueAt(int idx)
{
   return values[(wrIdx-1-idx)&mask];
}


int RingBuffer::getPreviousValueAt(int idx, unsigned long *time)
{
   int valueIdx = (wrIdx-1-idx)&mask;
  	if ((time != NULL) && (timeStamps!=NULL))
      *time = timeStamps[valueIdx]; 
   return values[valueIdx];
}

//*****************************************************************


RingBufferAverage::RingBufferAverage(int _size, int *_values, unsigned long *_timeStamps, int _averageSize):RingBuffer(_size, _values, _timeStamps)
{
    averageSize = _averageSize;
    averageSum  = 0;
}

void RingBufferAverage::addValue(int val)
{
   RingBuffer::addValue(val);
   averageSum += val;
   if (anz > averageSize)
      averageSum -= getPreviousValueAt(averageSize);
}


void RingBufferAverage::reset()
{
   RingBuffer::reset();
   averageSum = 0;
}


void RingBufferAverage::setAverageLen(int len)
{
	averageSize = len;
	reset();
}

int RingBufferAverage::getAverage()
{
   if (anz>averageSize)
      return averageSum/averageSize;
   return averageSum/anz;
}


int RingBufferAverage::getAverageSum()
{
   return averageSum;
}


