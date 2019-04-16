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

#include "rdy_run.h"

#include "netx_io_areas.h"
#include "systime.h"


#if ASIC_TYP==ASIC_TYP_NETX500 || ASIC_TYP==ASIC_TYP_NETX50
//-------------------------------------
// some defines for the mysterious HIF registers
// taken from the "netX Program Reference Guide Rev0.3", page 16

#define MSK_sta_netx_rdy                        0x00000001U
#define SRT_sta_netx_rdy                        0
#define MSK_sta_netx_run                        0x00000002U
#define SRT_sta_netx_run                        1
#define MSK_sta_netx_netx_state                 0x0000000cU
#define SRT_sta_netx_netx_state                 2
#define MSK_sta_netx_host_state                 0x000000f0U
#define SRT_sta_netx_host_state                 4
#define MSK_sta_netx_netx_sta_code              0x0000ff00U
#define SRT_sta_netx_netx_sta_code              8
#define MSK_sta_netx_rdy_in                     0x00010000U
#define SRT_sta_netx_rdy_in                     16
#define MSK_sta_netx_run_in                     0x00020000U
#define SRT_sta_netx_run_in                     17
#define MSK_sta_netx_rdy_pol                    0x00040000U
#define SRT_sta_netx_rdy_pol                    18
#define MSK_sta_netx_run_pol                    0x00080000U
#define SRT_sta_netx_run_pol                    19
#define MSK_sta_netx_rdy_drv                    0x01000000U
#define SRT_sta_netx_rdy_drv                    24
#define MSK_sta_netx_run_drv                    0x02000000U
#define SRT_sta_netx_run_drv                    25

#endif

/*-------------------------------------*/

#if ASIC_TYP==ASIC_TYP_NETX500
void rdy_run_setLEDs(RDYRUN_T tState)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulValue;


	ulValue = 0;

	/* Add the active LED. */
	switch(tState)
	{
	case RDYRUN_OFF:
		break;

	case RDYRUN_GREEN:
		ulValue  = MSK_sta_netx_rdy_drv | MSK_sta_netx_run_drv;
		ulValue |= MSK_sta_netx_rdy;
		break;

	case RDYRUN_YELLOW:
		ulValue  = MSK_sta_netx_rdy_drv | MSK_sta_netx_run_drv;
		ulValue |= MSK_sta_netx_run;
		break;
	}
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
}
#elif ASIC_TYP==ASIC_TYP_NETX50
void rdy_run_setLEDs(RDYRUN_T tState)
{
	HOSTDEF(ptNetxControlledGlobalRegisterBlock1Area);
	unsigned long ulSCLNew;
	unsigned long ulSDANew;
	unsigned long ulSDAOld;
	unsigned long ulValue;


	/* Initialize the new SCL and SDA parts. */
	ulSCLNew = MSK_sta_netx_rdy_drv;
	ulSDANew = MSK_sta_netx_run_drv;

	/* Add the active LED. */
	switch(tState)
	{
	case RDYRUN_OFF:
		break;

	case RDYRUN_YELLOW:
		ulSCLNew |= MSK_sta_netx_run;
		break;

	case RDYRUN_GREEN:
		ulSDANew |= MSK_sta_netx_rdy;
		break;
	}

	/* Get the old SDA part. */
	ulSDAOld = ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx & MSK_sta_netx_run_drv;

	/* Set SCL to low. This allows modifications of the SDA line without
	 * the risk of generating a start condition.
	 * The signals look like this:
	 * 
	 * Off:      __     _____
	 * RDY (SCL) __|___|     
	 *           ____ _______
	 * RUN (SDA) ____|        
	 *
	 * Green:    __
	 * RDY (SCL) __|_________
	 *           ____ _______
	 * RUN (SDA) ____|
	 * 
	 * Yellow:   __         _
	 * RDY (SCL) __|_______|
	 *           ____
	 * RUN (SDA) ____|_______
	 * 
	 */
	ulValue = MSK_sta_netx_rdy_drv | ulSDAOld;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	/* Delay a bit. */
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;

	/* Output the new SDA part while SCL is still low. */
	ulValue = MSK_sta_netx_rdy_drv | ulSDANew;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	/* Delay a bit. */
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;

	/* Output the new SCL part. Now the new value is complete. */
	ulValue = ulSCLNew | ulSDANew;
	ptNetxControlledGlobalRegisterBlock1Area->ulSta_netx = ulValue;
}
#elif ASIC_TYP==ASIC_TYP_NETX4000_RELAXED || ASIC_TYP==ASIC_TYP_NETX4000 || ASIC_TYP==ASIC_TYP_NETX10 || ASIC_TYP==ASIC_TYP_NETX56 || ASIC_TYP==ASIC_TYP_NETX6
void rdy_run_setLEDs(RDYRUN_T tState)
{
	HOSTDEF(ptAsicCtrlArea)
	unsigned long ulSCLNew;
	unsigned long ulSDANew;
	unsigned long ulSDAOld;
	unsigned long ulValue;


	/* Initialize the new SCL and SDA parts. */
	ulSCLNew = 0;
	ulSDANew = 0;

	/* Add the active LED. */
	switch(tState)
	{
	case RDYRUN_OFF:
		break;

	case RDYRUN_GREEN:
		ulSDANew |= HOSTMSK(rdy_run_cfg_RUN_DRV);
		break;

	case RDYRUN_YELLOW:
		ulSCLNew |= HOSTMSK(rdy_run_cfg_RDY_DRV);
		break;
	}

	/* Get the old SDA part. */
	ulSDAOld = ptAsicCtrlArea->ulRdy_run_cfg & HOSTMSK(rdy_run_cfg_RUN_DRV);

	/* Set SCL to low. This allows modifications of the SDA line without
	 * the risk of generating a start condition.
	 * The signals look like this:
	 *
	 * Off:      __     _____
	 * RDY (SCL) __|___|
	 *           ____ _______
	 * RUN (SDA) ____|
	 *
	 * Green:    __
	 * RDY (SCL) __|_________
	 *           ____ _______
	 * RUN (SDA) ____|
	 *
	 * Yellow:   __         _
	 * RDY (SCL) __|_______|
	 *           ____
	 * RUN (SDA) ____|_______
	 *
	 */
	ulValue = HOSTMSK(rdy_run_cfg_RDY_DRV) | ulSDAOld;
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	/* Delay a bit. */
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;

	/* Output the new SDA part while SCL is still low. */
	ulValue = HOSTMSK(rdy_run_cfg_RDY_DRV) | ulSDANew;
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	/* Delay a bit. */
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;

	/* Output the new SCL part. Now the new value is complete. */
	ulValue = ulSCLNew | ulSDANew;
	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
}
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90_MPW_APP
void rdy_run_setLEDs(RDYRUN_T tState)
{
	HOSTDEF(ptAsicCtrlArea);
	unsigned long ulValue;


	/* Initialize the new SCL and SDA parts. */
	ulValue = 0;

	/* Add the active LED. */
	switch(tState)
	{
	case RDYRUN_OFF:
		break;

	case RDYRUN_GREEN:
		ulValue |= HOSTMSK(rdy_run_cfg_RUN_DRV);
		break;

	case RDYRUN_YELLOW:
		ulValue |= HOSTMSK(rdy_run_cfg_RDY_DRV);
		break;
	}

	ptAsicCtrlArea->ulRdy_run_cfg = ulValue;
}
#elif ASIC_TYP==ASIC_TYP_NETX90 || ASIC_TYP==ASIC_TYP_NETX90_APP
void rdy_run_setLEDs(RDYRUN_T tState)
{
	HOSTDEF(ptAsicCtrlComArea);
	unsigned long ulValue;


	/* Initialize the new SCL and SDA parts. */
	ulValue = 0;

	/* Add the active LED. */
	switch(tState)
	{
	case RDYRUN_OFF:
		break;

	case RDYRUN_GREEN:
		ulValue |= HOSTMSK(rdy_run_cfg_RUN_DRV);
		break;

	case RDYRUN_YELLOW:
		ulValue |= HOSTMSK(rdy_run_cfg_RDY_DRV);
		break;
	}

	ptAsicCtrlComArea->ulRdy_run_cfg = ulValue;
}
#endif

/*-------------------------------------*/


static const RDYRUN_T atLEDState[4] =
{
	RDYRUN_OFF,		/* 0: off */
	RDYRUN_OFF,		/* 1: off */
	RDYRUN_YELLOW,		/* 2: yellow */
	RDYRUN_GREEN		/* 3: green */
};


void rdy_run_blinki_init(BLINKI_HANDLE_T *ptHandle, unsigned long ulMask, unsigned long ulState)
{
	ptHandle->uiCnt = 0;
	ptHandle->ulTimer = systime_get_ms();
	ptHandle->ulMask = ulMask;
	ptHandle->ulState = ulState;
}


void rdy_run_blinki(BLINKI_HANDLE_T *ptHandle)
{
	int iResult;
	unsigned int uiCnt;
	unsigned int uiMaskBit;
	unsigned int uiStateBit;
	unsigned int uiBlinkiBit;
	int f_doRestart;


	/* wait until 500ms passed */
	iResult = systime_elapsed(ptHandle->ulTimer, 500U);
	while(iResult == 0){
		iResult = systime_elapsed(ptHandle->ulTimer, 500U);
	};

	if( iResult!=0 )
	{
		/* Get a new timer value. */
		ptHandle->ulTimer = systime_get_ms();

		/* Get the counter from the handle. */
		uiCnt = ptHandle->uiCnt;

		do
		{
			/* Show the next LED state. */
			uiMaskBit = (ptHandle->ulMask>>uiCnt)&1U;
			uiStateBit = (ptHandle->ulState>>uiCnt)&1U;

			/* Reset the counter if the LED state is a masked 1. */
			/* NOTE: do not do this for the first bit (uiHandle==0), this would be an endless loop! */
			f_doRestart = ( uiCnt!=0U && uiMaskBit==0U && uiStateBit!=0U );
			if( f_doRestart==0 )
			{
				/* Increase the counter. */
				++uiCnt;
				uiCnt &= 0x1fU;
			}
			else
			{
				/* Restart the LED sequence. */
				uiCnt = 0U;
			}
		} while( f_doRestart!=0 );

		/* Show the LED state. */
		uiBlinkiBit = (uiMaskBit<<1) | uiStateBit;
		rdy_run_setLEDs(atLEDState[uiBlinkiBit]);

		/* Write back the new counter value. */
		ptHandle->uiCnt = uiCnt;
	}
}


