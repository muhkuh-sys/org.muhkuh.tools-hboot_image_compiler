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


#include "netx_io_areas.h"


#ifndef __SYSTIME_H__
#define __SYSTIME_H__

typedef struct TIMER_HANDLE_STRUCT
{
	unsigned long ulStart;
	unsigned long ulDuration;
} TIMER_HANDLE_T;

void systime_init(void);

unsigned long systime_get_ms(void);

int systime_elapsed(unsigned long ulStart, unsigned long ulDuration);

void systime_delay_ms(unsigned long ulDuration);

void systime_handle_start_ms(TIMER_HANDLE_T *ptHandle, unsigned long ulDuration);
int systime_handle_is_elapsed(TIMER_HANDLE_T *ptHandle);


#endif  /* __SYSTIME_H__ */
