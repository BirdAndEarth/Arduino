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
 /*
 *  Das Timer-Modul stellt Funktionen bereit, mit denen andere Funktionen
 *  sp�ter aufgerufen werden k�nnen. Diese Funktionen sollten eine
 *  kurze Laufzeit haben, da sie im Interrupt aufgerufen werden.
 *
 *  - Die Timer arbeiten mit einer Aufl�sung von 5 ms.
 *  - Es k�nnen maximal 10 Timer gleichzeitig aktiv sein.
 *  - Stoppen eines Timers ist m�glich
 *
 */

#ifndef FUNCTION_TIMER_H_
#define FUNCTION_TIMER_H_

#define TIMER_ANZAHL 10

typedef void (*tmrFuncPtr)(int arg);

extern void timerInit();
extern void timerStart(int id, int ms, tmrFuncPtr handler, int arg);
extern void timerStop(int id);




#endif /* TIMER_H_ */
