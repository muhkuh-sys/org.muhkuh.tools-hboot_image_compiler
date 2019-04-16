/**************************************************************************//**
 * @file    main.c
 * @brief   Main program body
 * $Revision: 4507 $
 * $Date: 2018-11-20 13:25:13 +0100 (Di, 20 Nov 2018) $
 * \copyright Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
 * \note Exclusion of Liability for this demo software:
 * The following software is intended for and must only be used for reference and in an
 * evaluation laboratory environment. It is provided without charge and is subject to
 * alterations. There is no warranty for the software, to the extent permitted by
 * applicable law. Except when otherwise stated in writing the copyright holders and/or
 * other parties provide the software "as is" without warranty of any kind, either
 * expressed or implied.
 * Please refer to the Agreement in README_DISCLAIMER.txt, provided together with this file!
 * By installing or otherwise using the software, you accept the terms of this Agreement.
 * If you do not agree to the terms of this Agreement, then do not install or use the
 * Software!
 ******************************************************************************/

/*
 * PROJECT STRUCTURE:
 * all Imports are in the Component Folder
 * all Project related Files are in the Target Folder
 * all build related Files are in the build Folder
 * Folder-Structure:
 * - blinki_rams
 *  |- build
 *  |- Components
 *     |- netx
 *        |- Includes (general Includes for all netx types)
 *        |- netx90 (specific netx90 Includes and Sources)
 *        |- Sources (general Sources for all netx types)
 *  |- Targets
 *     |- APP
 *        |- Includes
 *        |- Linker (Linker and XML Files)
 *        |- Sources
 *     |- COM
 *        |- Includes
 *        |- Linker (Linker and XML Files)
 *        |- Sources
 */

#include "main.h"
#include "systime.h"
#include "netx90_io_areas.h"
#include "mmio6.h"
#include "mmio7.h"

/*
 * PROJECT DESCRIPTION APP:
 * Name: BlinkiTest
 * Requirements for APP:
 *  - activate SDRAM with HWC
 *  - activate MMIO's with HWC
 *  - enable APP-CPU in general options
 *  - SDRAM (tested with: 7703.080 1) must be plugged in
 *  - enable on LED (Switch S701-4 LED/ADC LED -> ON)
 * Description: Mini Blinki to test all RAM's. The Program will be linked to SDRAM, INTRAM and INTFLASH.
 * The Program will be executed in INTFLASH
 *  - all mmio6 function will be stored in IFLASH Section
 *  - all mmio7functions will be stored in IFLASH Section
 * if everything went correct MMIO6 and MMIO7 will blink
 */

void blinki_main(void *pvBootBlock __attribute__((unused)), unsigned long ulBootSource)
{
  MMIO6_BLINKI_HANDLE_T tMmio6Handle;
  MMIO7_BLINKI_HANDLE_T tMmio7Handle;

  /* initialize the systemtime */
  systime_init();

  /* Switch all LEDs off. */
  mmio6_setLED(LED_OFF);
  mmio7_setLED(LED_OFF);

  /* initialize all LED Handle's
   * MMIO6 and MMIO7 Handle's are just Counter to toggle the LED's
   */
  mmio6_init(&tMmio6Handle);
  mmio7_init(&tMmio7Handle);

  /*
   * Blinki routine
   */
  while(1)
  {
    mmio6_blinki(&tMmio6Handle);
    mmio7_blinki(&tMmio7Handle);
  };

}
