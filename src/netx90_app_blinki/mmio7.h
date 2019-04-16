/***************************************************************************
 *   Copyright (C) 2012 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __MMIO7_H__
#define __MMIO7_H__

/*-----------------------------------*/

#include "mmio6.h"

typedef struct
{
	unsigned long ulTimer;
	unsigned int uiCnt;
	unsigned long ulMask;
	unsigned long ulState;
} MMIO7_BLINKI_HANDLE_T;


void mmio7_setLED(LED_T tState);
void mmio7_init(MMIO7_BLINKI_HANDLE_T *ptHandle);
void mmio7_blinki(MMIO7_BLINKI_HANDLE_T *ptHandle);

/*-----------------------------------*/

#endif  /* __MMIO7_H__ */
