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


#include "systime.h"

/* ASIC */
#define DEV_FREQUENCY 100000000

/* For netx 4000 FPGA */
//#define DEV_FREQUENCY 10000000

void systime_init(void)
{
#if ASIC_TYP==ASIC_TYP_NETX4000_RELAXED || ASIC_TYP==ASIC_TYP_NETX4000
	HOSTDEF(ptSystimeUcArea);

	/* Set the systime border to 1ms. */
	ptSystimeUcArea->ulSystime_border = (DEV_FREQUENCY/100U)-1U;
	ptSystimeUcArea->ulSystime_count_value = 10U<<28U;
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	HOSTDEF(ptSystimeUcComArea);

	/* Set the systime border to 1ms. */
	ptSystimeUcComArea->ulSystime_border = (DEV_FREQUENCY/100U)-1U;
	ptSystimeUcComArea->ulSystime_count_value = 10U<<28U;
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW_APP || ASIC_TYP==ASIC_TYP_NETX90_APP
	HOSTDEF(ptSystimeAppArea);

	/* Set the systime border to 1ms. */
	ptSystimeAppArea->ulSystime_border = (DEV_FREQUENCY/100U)-1U;
	ptSystimeAppArea->ulSystime_count_value = 10U<<28U;
#else
	HOSTDEF(ptSystimeArea);


	/* Set the systime border to 1ms. */
	ptSystimeArea->ulSystime_border = (DEV_FREQUENCY/100U)-1U;
	ptSystimeArea->ulSystime_count_value = 10U<<28U;

#       if ASIC_TYP==ASIC_TYP_NETX50
	/* Disable systime compare. */
	ptSystimeArea->ulSystime_s_compare_enable = 0;

	/* Reset any pending systime IRQs. */
	ptSystimeArea->ulSystime_s_compare_irq = 1;
#       endif
#endif
}



unsigned long systime_get_ms(void)
{
#if ASIC_TYP==ASIC_TYP_NETX4000_RELAXED || ASIC_TYP==ASIC_TYP_NETX4000
	HOSTDEF(ptSystimeUcArea);

	return ptSystimeUcArea->ulSystime_s;
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	HOSTDEF(ptSystimeUcComArea);

	return ptSystimeUcComArea->ulSystime_s;
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW_APP || ASIC_TYP==ASIC_TYP_NETX90_APP
	HOSTDEF(ptSystimeAppArea);

	return ptSystimeAppArea->ulSystime_s;
#else
	HOSTDEF(ptSystimeArea)


	return ptSystimeArea->ulSystime_s;
#endif
}


int systime_elapsed(unsigned long ulStart, unsigned long ulDuration)
{
#if ASIC_TYP==ASIC_TYP_NETX4000_RELAXED || ASIC_TYP==ASIC_TYP_NETX4000
	HOSTDEF(ptSystimeUcArea)
	unsigned long ulDiff;


	/* get the time difference */
	ulDiff = ptSystimeUcArea->ulSystime_s - ulStart;

	return (ulDiff>=ulDuration);
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90
	HOSTDEF(ptSystimeUcComArea);

	unsigned long ulDiff;


	/* get the time difference */
	ulDiff = ptSystimeUcComArea->ulSystime_s - ulStart;

	return (ulDiff>=ulDuration);
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW_APP || ASIC_TYP==ASIC_TYP_NETX90_APP
	HOSTDEF(ptSystimeAppArea);

	unsigned long ulDiff;


	/* get the time difference */
	ulDiff = ptSystimeAppArea->ulSystime_s - ulStart;

	return (ulDiff>=ulDuration);
#else
	HOSTDEF(ptSystimeArea)
	unsigned long ulDiff;


	/* get the time difference */
	ulDiff = ptSystimeArea->ulSystime_s - ulStart;

	return (ulDiff>=ulDuration);
#endif
}



void systime_delay_ms(unsigned long ulDuration)
{
	unsigned long ulStart;
	int iElapsed;


	ulStart = systime_get_ms();
	do
	{
		iElapsed = systime_elapsed(ulStart, ulDuration);
	} while( iElapsed==0 );
}



void systime_handle_start_ms(TIMER_HANDLE_T *ptHandle, unsigned long ulDuration)
{
	ptHandle->ulStart = systime_get_ms();
	ptHandle->ulDuration = ulDuration;
}



int systime_handle_is_elapsed(TIMER_HANDLE_T *ptHandle)
{
	return systime_elapsed(ptHandle->ulStart, ptHandle->ulDuration);
}
