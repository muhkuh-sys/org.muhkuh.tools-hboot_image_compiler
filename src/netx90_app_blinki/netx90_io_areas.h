/***************************************************************************
 *   Copyright (C) 2016 by Hilscher GmbH                                   *
 *                                                                         *
 *   Author: Christoph Thelen (cthelen@hilscher.com)                       *
 *                                                                         *
 *   Redistribution or unauthorized use without expressed written          *
 *   agreement from the Hilscher GmbH is forbidden.                        *
 ***************************************************************************/

#ifndef __NETX90_IO_AREAS_H__
#define __NETX90_IO_AREAS_H__


#include "netx90_regdef.h"
#include "netx90_mmio.h"


#define NX90_DEF_ptCm4MiscAsicCtrlArea NX90_CM4_MISC_CTRL_AREA_T * const ptCm4MiscAsicCtrlArea = (NX90_CM4_MISC_CTRL_AREA_T * const)Addr_NX90_cm4_misc_ctrl;

#define NX90_DEF_ptDmacComCh0Area NX90_DMAC_CH_AREA_T * const ptDmacComCh0Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_com_ch0;
#define NX90_DEF_ptDmacComCh1Area NX90_DMAC_CH_AREA_T * const ptDmacComCh1Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_com_ch1;
#define NX90_DEF_ptDmacComCh2Area NX90_DMAC_CH_AREA_T * const ptDmacComCh2Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_com_ch2;
#define NX90_DEF_ptDmacAppCh0Area NX90_DMAC_CH_AREA_T * const ptDmacAppCh0Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_app_ch0;
#define NX90_DEF_ptDmacAppCh1Area NX90_DMAC_CH_AREA_T * const ptDmacAppCh1Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_app_ch1;
#define NX90_DEF_ptDmacAppCh2Area NX90_DMAC_CH_AREA_T * const ptDmacAppCh2Area = (NX90_DMAC_CH_AREA_T * const)Addr_NX90_dmac_app_ch2;

#define NX90_DEF_ptDmacComRegArea NX90_DMAC_REG_AREA_T * const ptDmacComRegArea = (NX90_DMAC_REG_AREA_T * const)Addr_NX90_dmac_com_reg;
#define NX90_DEF_ptDmacAppRegArea NX90_DMAC_REG_AREA_T * const ptDmacAppRegArea = (NX90_DMAC_REG_AREA_T * const)Addr_NX90_dmac_app_reg;

#define NX90_DEF_ptUartArea NX90_UART_AREA_T * const ptUartArea = (NX90_UART_AREA_T * const)Addr_NX90_uart;
#define NX90_DEF_ptUartAppArea NX90_UART_AREA_T * const ptUartAppArea = (NX90_UART_AREA_T * const)Addr_NX90_uart_app;
#define NX90_DEF_ptUartXpicAppArea NX90_UART_AREA_T * const ptUartXpicAppArea = (NX90_UART_AREA_T * const)Addr_NX90_uart_xpic_app;

#define NX90_DEF_ptSlaveFirewallCtrlArea NX90_SLAVE_FIREWALL_CTRL_AREA_T * const ptSlaveFirewallCtrlArea = (NX90_SLAVE_FIREWALL_CTRL_AREA_T * const)Addr_NX90_slave_firewall_ctrl;
#define NX90_DEF_ptModuleFirewallCtrlArea NX90_MODULE_FIREWALL_CTRL_AREA_T * const ptModuleFirewallCtrlArea = (NX90_MODULE_FIREWALL_CTRL_AREA_T * const)Addr_NX90_slave_firewall_ctrl;

#define NX90_DEF_ptI2c0ComArea NX90_I2C_AREA_T * const ptI2cArea = (NX90_I2C_AREA_T * const)Addr_NX90_i2c0_com;
#define NX90_DEF_ptI2c1ComArea NX90_I2C_AREA_T * const ptI2cArea = (NX90_I2C_AREA_T * const)Addr_NX90_i2c1_com;
#define NX90_DEF_ptI2cAppArea NX90_I2C_AREA_T * const ptI2cArea = (NX90_I2C_AREA_T * const)Addr_NX90_i2c_app;
#define NX90_DEF_ptI2cXpicAppArea NX90_I2C_AREA_T * const ptI2cArea = (NX90_I2C_AREA_T * const)Addr_NX90_i2c_xpic_app;

#define NX90_DEF_ptMledCtrlComArea NX90_MLED_CTRL_AREA_T * const ptMledCtrlComArea = (NX90_MLED_CTRL_AREA_T * const)Addr_NX90_mled_ctrl_com;
#define NX90_DEF_ptMledCtrlAppArea NX90_MLED_CTRL_AREA_T * const ptMledCtrlAppArea = (NX90_MLED_CTRL_AREA_T * const)Addr_NX90_mled_ctrl_app;

#define NX90_DEF_ptEccCtrlComArea NX90_ECC_CTRL_COM_AREA_T * const ptEccCtrlComArea = (NX90_ECC_CTRL_COM_AREA_T * const)Addr_NX90_ecc_ctrl_com;
#define NX90_DEF_ptEccCtrlArea NX90_ECC_CTRL_AREA_T * const ptEccCtrlArea = (NX90_ECC_CTRL_AREA_T * const)Addr_NX90_ecc_ctrl;
#define NX90_DEF_ptEccCtrlAppArea NX90_ECC_CTRL_AREA_T * const ptEccCtrlAppArea = (NX90_ECC_CTRL_AREA_T * const)Addr_NX90_ecc_ctrl_app;

#define NX90_DEF_ptGpioArea NX90_GPIO_AREA_T * const ptGpioArea = (NX90_GPIO_AREA_T * const)Addr_NX90_gpio_com;

#define NX90_DEF_ptBlinkArea NX90_BLINK_AREA_T * const ptBlinkArea = (NX90_BLINK_AREA_T * const)Addr_NX90_blink_com;

#define NX90_DEF_ptIntlogicSystimeLtComArea NX90_INTLOGIC_SYSTIME_LT_AREA_T * const ptIntlogicSystimeLtComArea = (NX90_INTLOGIC_SYSTIME_LT_AREA_T * const)Addr_NX90_systime_lt_com;
#define NX90_DEF_ptIntlogicSystimeLtAppArea NX90_INTLOGIC_SYSTIME_LT_AREA_T * const ptIntlogicSystimeLtAppArea = (NX90_INTLOGIC_SYSTIME_LT_AREA_T * const)Addr_NX90_systime_lt_app;
#define NX90_DEF_ptIntlogicSystimeLtXpicComArea NX90_INTLOGIC_SYSTIME_LT_AREA_T * const ptIntlogicSystimeLtXpicComArea = (NX90_INTLOGIC_SYSTIME_LT_AREA_T * const)Addr_NX90_systime_lt_xpic_com;
#define NX90_DEF_ptIntlogicSystimeLtXpicAppArea NX90_INTLOGIC_SYSTIME_LT_AREA_T * const ptIntlogicSystimeLtXpicAppArea = (NX90_INTLOGIC_SYSTIME_LT_AREA_T * const)Addr_NX90_systime_lt_xpic_app;

#define NX90_DEF_ptArmTimerComArea NX90_ARM_TIMER_AREA_T * const ptArmTimerComArea = (NX90_ARM_TIMER_AREA_T * const)Addr_NX90_timer_com;
#define NX90_DEF_ptArmTimerAppArea NX90_ARM_TIMER_AREA_T * const ptArmTimerAppArea = (NX90_ARM_TIMER_AREA_T * const)Addr_NX90_timer_app;
#define NX90_DEF_ptArmTimerXpicComArea NX90_ARM_TIMER_AREA_T * const ptArmTimerXpicComArea = (NX90_ARM_TIMER_AREA_T * const)Addr_NX90_timer_xpic_com;
#define NX90_DEF_ptArmTimerXpicAppArea NX90_ARM_TIMER_AREA_T * const ptArmTimerXpicAppArea = (NX90_ARM_TIMER_AREA_T * const)Addr_NX90_timer_xpic_app;

#define NX90_DEF_ptSystimeComArea NX90_SYSTIME_AREA_T * const ptSystimeComArea = (NX90_SYSTIME_AREA_T * const)Addr_NX90_systime_com;
#define NX90_DEF_ptSystimeUcComArea NX90_SYSTIME_AREA_T * const ptSystimeUcComArea = (NX90_SYSTIME_AREA_T * const)Addr_NX90_systime_uc_com;
#define NX90_DEF_ptSystimeAppArea NX90_SYSTIME_AREA_T * const ptSystimeAppArea = (NX90_SYSTIME_AREA_T * const)Addr_NX90_systime_app;

#define NX90_DEF_ptHsIrqRegComArea NX90_HS_IRQ_REG_AREA_T * const ptHsIrqRegComArea = (NX90_HS_IRQ_REG_AREA_T * const)Addr_NX90_mpc_com;
#define NX90_DEF_ptHsIrqRegAppArea NX90_HS_IRQ_REG_AREA_T * const ptHsIrqRegAppArea = (NX90_HS_IRQ_REG_AREA_T * const)Addr_NX90_mpc_app;
#define NX90_DEF_ptHsIrqRegXpicComArea NX90_HS_IRQ_REG_AREA_T * const ptHsIrqRegXpicComArea = (NX90_HS_IRQ_REG_AREA_T * const)Addr_NX90_mpc_xpic_com;
#define NX90_DEF_ptHsIrqRegXpicAppArea NX90_HS_IRQ_REG_AREA_T * const ptHsIrqRegXpicAppArea = (NX90_HS_IRQ_REG_AREA_T * const)Addr_NX90_mpc_xpic_app;

#define NX90_DEF_ptWatchdogComArea NX90_WATCHDOG_AREA_T * const ptWatchdogComArea = (NX90_WATCHDOG_AREA_T * const)Addr_NX90_wdg_com;
#define NX90_DEF_ptWatchdogAppArea NX90_WATCHDOG_AREA_T * const ptWatchdogAppArea = (NX90_WATCHDOG_AREA_T * const)Addr_NX90_wdg_app;

#define NX90_DEF_ptIntPhyCfgComArea NX90_INT_PHY_CFG_AREA_T * const ptIntPhyCfgComArea = (NX90_INT_PHY_CFG_AREA_T * const)Addr_NX90_int_phy_cfg_com;

#define NX90_DEF_ptAsicCtrlComArea NX90_ASIC_CTRL_COM_AREA_T * const ptAsicCtrlComArea = (NX90_ASIC_CTRL_COM_AREA_T * const)Addr_NX90_asic_ctrl_com;

#define NX90_DEF_ptLvds2mii0ComArea NX90_LVDS2MII_AREA_T * const ptLvds2mii0ComArea = (NX90_LVDS2MII_AREA_T * const)Addr_NX90_lvds2mii0_com;
#define NX90_DEF_ptLvds2mii1ComArea NX90_LVDS2MII_AREA_T * const ptLvds2mii1ComArea = (NX90_LVDS2MII_AREA_T * const)Addr_NX90_lvds2mii1_com;

#define NX90_DEF_ptDpm0ComArea NX90_DPM_AREA_T * const ptDpm0ComArea = (NX90_DPM_AREA_T * const)Addr_NX90_dpm0_com;
#define NX90_DEF_ptDpm1ComArea NX90_DPM_AREA_T * const ptDpm1ComArea = (NX90_DPM_AREA_T * const)Addr_NX90_dpm1_com;

#define NX90_DEF_ptIdpmComArea NX90_IDPM_AREA_T * const ptIdpmComArea = (NX90_IDPM_AREA_T * const)Addr_NX90_idpm_com;

#define NX90_DEF_ptIflashCfg0ComArea NX90_IFLASH_CFG_AREA_T * const ptIflashCfg0ComArea = (NX90_IFLASH_CFG_AREA_T * const)Addr_NX90_iflash_cfg0_com;
#define NX90_DEF_ptIflashCfg1ComArea NX90_IFLASH_CFG_AREA_T * const ptIflashCfg1ComArea = (NX90_IFLASH_CFG_AREA_T * const)Addr_NX90_iflash_cfg1_com;
#define NX90_DEF_ptIflashCfg2Area NX90_IFLASH_CFG_AREA_T * const ptIflashCfg2Area = (NX90_IFLASH_CFG_AREA_T * const)Addr_NX90_iflash_cfg2;

#define NX90_DEF_ptHandshakeCtrlComArea NX90_HANDSHAKE_CTRL_AREA_T * const ptHandshakeCtrlComArea = (NX90_HANDSHAKE_CTRL_AREA_T * const)Addr_NX90_handshake_ctrl_com;

#define NX90_DEF_ptBistCtrlComArea NX90_BIST_CTRL_AREA_T * const ptBistCtrlComArea = (NX90_BIST_CTRL_AREA_T * const)Addr_NX90_bist_ctrl_com;

#define NX90_DEF_ptCrcComArea NX90_CRC_AREA_T * const ptCrcComArea = (NX90_CRC_AREA_T * const)Addr_NX90_crc_com;

#define NX90_DEF_ptIflashGlobalTimingsArea NX90_IFLASH_GLOBAL_TIMINGS_AREA_T * const ptIflashGlobalTimingsArea = (NX90_IFLASH_GLOBAL_TIMINGS_AREA_T * const)Addr_NX90_flash_global_timings_com;

#define NX90_DEF_ptHashArea NX90_HASH_AREA_T * const ptHashArea = (NX90_HASH_AREA_T * const)Addr_NX90_hash;

#define NX90_DEF_ptAesArea NX90_AES_AREA_T * const ptAesArea = (NX90_AES_AREA_T * const)Addr_NX90_aes;

#define NX90_DEF_ptRandomArea NX90_RANDOM_AREA_T * const ptRandomArea = (NX90_RANDOM_AREA_T * const)Addr_NX90_random;

#define NX90_DEF_ptMtgyArea NX90_MTGY_AREA_T * const ptMtgyArea = (NX90_MTGY_AREA_T * const)Addr_NX90_mtgy;

#define NX90_DEF_ptXpecArea NX90_XPEC_AREA_T * const ptXpecArea = (NX90_XPEC_AREA_T * const)Adr_NX90_;

#define NX90_DEF_ptXc0Xmac0RegsArea NX90_XMAC_AREA_T * const ptXc0Xmac0RegsArea = (NX90_XMAC_AREA_T * const)Addr_NX90_xc0_xmac0_regs;
#define NX90_DEF_ptXc0Xmac1RegsArea NX90_XMAC_AREA_T * const ptXc0Xmac1RegsArea = (NX90_XMAC_AREA_T * const)Addr_NX90_xc0_xmac1_regs;

#define NX90_DEF_ptXmacArea NX90_XMAC_AREA_T * const ptXmacArea = (NX90_XMAC_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptPointerFifoArea NX90_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX90_POINTER_FIFO_AREA_T * const)Addr_NX90_xc0_pointer_fifo;
#define NX90_DEF_ptFmmusmArea NX90_FMMUSM_AREA_T * const ptFmmusmArea = (NX90_FMMUSM_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptTriggerSampleUnitArea NX90_TRIGGER_SAMPLE_UNIT_AREA_T * const ptTriggerSampleUnitArea = (NX90_TRIGGER_SAMPLE_UNIT_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXcExternalConfigArea NX90_XC_EXTERNAL_CONFIG_AREA_T * const ptXcExternalConfigArea = (NX90_XC_EXTERNAL_CONFIG_AREA_T * const)Addr_NX90_xc_external_config;
#define NX90_DEF_ptBufManArea NX90_BUF_MAN_AREA_T * const ptBufManArea = (NX90_BUF_MAN_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXpecIrqRegistersArea NX90_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX90_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX90_xc_xpec_irq_registers;
#define NX90_DEF_ptXcDebugArea NX90_XC_DEBUG_AREA_T * const ptXcDebugArea = (NX90_XC_DEBUG_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXcStartStopArea NX90_XC_START_STOP_AREA_T * const ptXcStartStopArea = (NX90_XC_START_STOP_AREA_T * const)Addr_NX90_xc_start_stop;
#define NX90_DEF_ptXc0PhyCtrl0Area NX90_PHY_CTRL_AREA_T * const ptXc0PhyCtrl0Area = (NX90_PHY_CTRL_AREA_T * const)Addr_NX90_xc0_phy_ctrl0;
#define NX90_DEF_ptXc0PhyCtrl1Area NX90_PHY_CTRL_AREA_T * const ptXc0PhyCtrl1Area = (NX90_PHY_CTRL_AREA_T * const)Addr_NX90_xc0_phy_ctrl1;
#define NX90_DEF_ptXcSystimeConfigArea NX90_XC_SYSTIME_CONFIG_AREA_T * const ptXcSystimeConfigArea = (NX90_XC_SYSTIME_CONFIG_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXpicArea NX90_XPIC_AREA_T * const ptXpicArea = (NX90_XPIC_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXpicDebugArea NX90_XPIC_DEBUG_AREA_T * const ptXpicDebugArea = (NX90_XPIC_DEBUG_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXpicVicArea NX90_XPIC_VIC_AREA_T * const ptXpicVicArea = (NX90_XPIC_VIC_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXpicWgdArea NX90_XPIC_WDG_AREA_T * const ptXpicWgdArea = (NX90_XPIC_WDG_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptSrArea NX90_SR_AREA_T * const ptSrArea = (NX90_SR_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXcStatcfgSharedArea NX90_XC_STATCFG_SHARED_AREA_T * const ptXcStatcfgSharedArea = (NX90_XC_STATCFG_SHARED_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptNfifoArea NX90_NFIFO_AREA_T * const ptNfifoArea = (NX90_NFIFO_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptPadCtrlArea NX90_PAD_CTRL_AREA_T * const ptPadCtrlArea = (NX90_PAD_CTRL_AREA_T * const)Addr_NX90_pad_ctrl;

#define NX90_DEF_ptAsicCtrlArea NX90_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX90_ASIC_CTRL_AREA_T * const)Addr_NX90_asic_ctrl;

#define NX90_DEF_ptMmioCtrlArea NX90_MMIO_CTRL_AREA_T * const ptMmioCtrlArea = (NX90_MMIO_CTRL_AREA_T * const)Addr_NX90_mmio_ctrl;
#define NX90_DEF_ptGlobalBufManArea NX90_GLOBAL_BUF_MAN_AREA_T * const ptGlobalBufManArea = (NX90_GLOBAL_BUF_MAN_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptHifIoCtrlArea NX90_HIF_IO_CTRL_AREA_T * const ptHifIoCtrlArea = (NX90_HIF_IO_CTRL_AREA_T * const)Addr_NX90_hif_io_ctrl;
#define NX90_DEF_ptHifAsyncmemCtrlArea NX90_EXT_ASYNCMEM_CTRL_AREA_T * const ptHifAsyncmemCtrlArea = (NX90_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX90_hif_asyncmem_ctrl;
#define NX90_DEF_ptHifSdramCtrlArea NX90_EXT_SDRAM_CTRL_AREA_T * const ptHifSdramCtrlArea = (NX90_EXT_SDRAM_CTRL_AREA_T * const)Addr_NX90_hif_sdram_ctrl;
#define NX90_DEF_ptHifmemPriorityCtrlArea NX90_EXTMEM_PRIORITY_CTRL_AREA_T * const ptHifmemPriorityCtrlArea = (NX90_EXTMEM_PRIORITY_CTRL_AREA_T * const)Addr_NX90_hifmem_priority_ctrl;

#define NX90_DEF_ptSqiArea NX90_SQI_AREA_T * const ptSqiArea = (NX90_SQI_AREA_T * const)Addr_NX90_sqi;

#define NX90_DEF_ptSampleAtPornStatArea NX90_SAMPLE_AT_PORN_STAT_AREA_T * const ptSampleAtPornStatArea = (NX90_SAMPLE_AT_PORN_STAT_AREA_T * const)Addr_NX90_sample_at_porn_stat;
#define NX90_DEF_ptAdcSeqArea NX90_ADC_SEQ_AREA_T * const ptAdcSeqArea = (NX90_ADC_SEQ_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptMiimuArea NX90_MIIMU_AREA_T * const ptMiimuArea = (NX90_MIIMU_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptEthArea NX90_ETH_AREA_T * const ptEthArea = (NX90_ETH_AREA_T * const)Addr_NX90_eth;
#define NX90_DEF_ptDmacMuxArea NX90_DMAC_MUX_AREA_T * const ptDmacMuxArea = (NX90_DMAC_MUX_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptGpioAppArea NX90_GPIO_APP_AREA_T * const ptGpioAppArea = (NX90_GPIO_APP_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptEndatArea NX90_ENDAT_AREA_T * const ptEndatArea = (NX90_ENDAT_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptEndatCtrlArea NX90_ENDAT_CTRL_AREA_T * const ptEndatCtrlArea = (NX90_ENDAT_CTRL_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptCanctrlArea NX90_CANCTRL_AREA_T * const ptCanctrlArea = (NX90_CANCTRL_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptSpiArea NX90_SPI_AREA_T * const ptSpiArea = (NX90_SPI_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptPioArea NX90_PIO_AREA_T * const ptPioArea = (NX90_PIO_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptBissArea NX90_BISS_AREA_T * const ptBissArea = (NX90_BISS_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptBissCtrlArea NX90_BISS_CTRL_AREA_T * const ptBissCtrlArea = (NX90_BISS_CTRL_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXlinkArea NX90_XLINK_AREA_T * const ptXlinkArea = (NX90_XLINK_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptIoLinkIeqArea NX90_IO_LINK_IRQ_AREA_T * const ptIoLinkIeqArea = (NX90_IO_LINK_IRQ_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptXcExtbusSelArea NX90_XC_EXTBUS_SEL_AREA_T * const ptXcExtbusSelArea = (NX90_XC_EXTBUS_SEL_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptParityArea NX90_PARITY_AREA_T * const ptParityArea = (NX90_PARITY_AREA_T * const)Adr_NX90_;
#define NX90_DEF_ptArmBootVectorArea NX90_ARM_BOOT_VECTOR_AREA_T * const ptArmBootVectorArea = (NX90_ARM_BOOT_VECTOR_AREA_T * const)Adr_NX90_;


#endif  /* __NETX90_IO_AREAS_H__ */

