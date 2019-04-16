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


#ifndef __RDY_RUN_H__
#define __RDY_RUN_H__

/*-----------------------------------*/

typedef enum
{
	RDYRUN_OFF      = 0,
	RDYRUN_GREEN    = 1,
	RDYRUN_YELLOW   = 2
} RDYRUN_T;


typedef struct
{
	unsigned long ulTimer;
	unsigned int uiCnt;
	unsigned long ulMask;
	unsigned long ulState;
} BLINKI_HANDLE_T;


void rdy_run_setLEDs(RDYRUN_T tState);
void rdy_run_blinki_init(BLINKI_HANDLE_T *ptHandle, unsigned long ulMask, unsigned long ulState);
void rdy_run_blinki(BLINKI_HANDLE_T *ptHandle);

/*-----------------------------------*/

#endif  /* __RDY_RUN_H__ */

