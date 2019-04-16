/***************************************************************************
 *   Copyright (C) 2019 by Tim Stelz                                       *
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

#include "mmio6.h"
#include "netx_io_areas.h"
#include "systime.h"

void mmio6_setLED(LED_T tState)
{
	HOSTDEF(ptMmioCtrlArea);
	unsigned long ulValue;


	ulValue = 0;

	/* set uValue in case LED should turned on. */
	switch(tState)
	{
	case LED_OFF:
		break;

	case LED_ON:
		ulValue |= HOSTMSK(mmio6_cfg_pio_oe) | HOSTMSK(mmio6_cfg_pio_out);
		break;
	}

	ptMmioCtrlArea->aulMmio_cfg[6] = ulValue;
}

/*-------------------------------------*/


static const LED_T atLEDState[2] =
{
	LED_OFF,		/* 0: off */
	LED_ON			/* 1: on  */
};


void mmio6_init(MMIO6_BLINKI_HANDLE_T *ptHandle)
{
	ptHandle->uiCnt = 0;
	ptHandle->ulTimer = systime_get_ms();
}


void mmio6_blinki(MMIO6_BLINKI_HANDLE_T *ptHandle)
{
	unsigned int uiCnt;
  int iResult;

  /* wait for 500ms */
	iResult = systime_elapsed(ptHandle->ulTimer, 500U);
  while(iResult == 0){
    iResult = systime_elapsed(ptHandle->ulTimer, 500U);
  };

  /* get the Counter */
	uiCnt = ptHandle->uiCnt;

	/* get new systime */
	ptHandle->ulTimer = systime_get_ms();

	/* Show the LED state. */
	mmio6_setLED(atLEDState[uiCnt%2]);

	/* Increment Counter and save in Handle */
	uiCnt++;

	ptHandle->uiCnt = uiCnt;
}
