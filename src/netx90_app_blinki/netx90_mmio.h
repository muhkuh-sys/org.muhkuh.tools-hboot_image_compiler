////////////////////////////////////////////////////////////
//
// Automatically generated by GEN_MULTIPLEXMATRIX script
// from:      /home/netx/doc/netXtiny/pinning/netxtiny_pinning_180227_1640.xlsx
//
////////////////////////////////////////////////////////////
//
// Hilscher SoCT
//
////////////////////////////////////////////////////////////
//
// Multiplexmatrix MMIO-signal selections
//
////////////////////////////////////////////////////////////



#ifndef __mmio_ctrl_h
#define __mmio_ctrl_h

#define MMIO_SEL_XC_SAMPLE0         0x00
#define MMIO_SEL_XC_SAMPLE1         0x01
#define MMIO_SEL_XC_TRIGGER0        0x02
#define MMIO_SEL_XC_TRIGGER1        0x03
#define MMIO_SEL_CAN0_APP_RX        0x04
#define MMIO_SEL_CAN0_APP_TX        0x05
#define MMIO_SEL_CAN1_APP_RX        0x06
#define MMIO_SEL_CAN1_APP_TX        0x07
#define MMIO_SEL_I2C_XPIC_APP_SCL   0x08
#define MMIO_SEL_I2C_XPIC_APP_SDA   0x09
#define MMIO_SEL_I2C_APP_SCL        0x0a
#define MMIO_SEL_I2C_APP_SDA        0x0b
#define MMIO_SEL_SPI_XPIC_APP_CLK   0x0c
#define MMIO_SEL_SPI_XPIC_APP_CS0N  0x0d
#define MMIO_SEL_SPI_XPIC_APP_CS1N  0x0e
#define MMIO_SEL_SPI_XPIC_APP_CS2N  0x0f
#define MMIO_SEL_SPI_XPIC_APP_MISO  0x10
#define MMIO_SEL_SPI_XPIC_APP_MOSI  0x11
#define MMIO_SEL_SPI1_APP_CLK       0x12
#define MMIO_SEL_SPI1_APP_CS0N      0x13
#define MMIO_SEL_SPI1_APP_CS1N      0x14
#define MMIO_SEL_SPI1_APP_CS2N      0x15
#define MMIO_SEL_SPI1_APP_MISO      0x16
#define MMIO_SEL_SPI1_APP_MOSI      0x17
#define MMIO_SEL_UART_XPIC_APP_RXD  0x18
#define MMIO_SEL_UART_XPIC_APP_TXD  0x19
#define MMIO_SEL_UART_XPIC_APP_RTSN 0x1a
#define MMIO_SEL_UART_XPIC_APP_CTSN 0x1b
#define MMIO_SEL_UART_APP_RXD       0x1c
#define MMIO_SEL_UART_APP_TXD       0x1d
#define MMIO_SEL_UART_APP_RTSN      0x1e
#define MMIO_SEL_UART_APP_CTSN      0x1f
#define MMIO_SEL_GPIO0              0x20
#define MMIO_SEL_GPIO1              0x21
#define MMIO_SEL_GPIO2              0x22
#define MMIO_SEL_GPIO3              0x23
#define MMIO_SEL_GPIO4              0x24
#define MMIO_SEL_GPIO5              0x25
#define MMIO_SEL_GPIO6              0x26
#define MMIO_SEL_GPIO7              0x27
#define MMIO_SEL_WDG_ACT            0x28
#define MMIO_SEL_EN_IN              0x29
#define MMIO_SEL_ETH_MDC            0x2a
#define MMIO_SEL_ETH_MDIO           0x2b
#define MMIO_SEL_PIO                0x3f

typedef enum
{
	MMIO_CFG_XC_SAMPLE0         = 0x00,
	MMIO_CFG_XC_SAMPLE1         = 0x01,
	MMIO_CFG_XC_TRIGGER0        = 0x02,
	MMIO_CFG_XC_TRIGGER1        = 0x03,
	MMIO_CFG_CAN0_APP_RX        = 0x04,
	MMIO_CFG_CAN0_APP_TX        = 0x05,
	MMIO_CFG_CAN1_APP_RX        = 0x06,
	MMIO_CFG_CAN1_APP_TX        = 0x07,
	MMIO_CFG_I2C_XPIC_APP_SCL   = 0x08,
	MMIO_CFG_I2C_XPIC_APP_SDA   = 0x09,
	MMIO_CFG_I2C_APP_SCL        = 0x0a,
	MMIO_CFG_I2C_APP_SDA        = 0x0b,
	MMIO_CFG_SPI_XPIC_APP_CLK   = 0x0c,
	MMIO_CFG_SPI_XPIC_APP_CS0N  = 0x0d,
	MMIO_CFG_SPI_XPIC_APP_CS1N  = 0x0e,
	MMIO_CFG_SPI_XPIC_APP_CS2N  = 0x0f,
	MMIO_CFG_SPI_XPIC_APP_MISO  = 0x10,
	MMIO_CFG_SPI_XPIC_APP_MOSI  = 0x11,
	MMIO_CFG_SPI1_APP_CLK       = 0x12,
	MMIO_CFG_SPI1_APP_CS0N      = 0x13,
	MMIO_CFG_SPI1_APP_CS1N      = 0x14,
	MMIO_CFG_SPI1_APP_CS2N      = 0x15,
	MMIO_CFG_SPI1_APP_MISO      = 0x16,
	MMIO_CFG_SPI1_APP_MOSI      = 0x17,
	MMIO_CFG_UART_XPIC_APP_RXD  = 0x18,
	MMIO_CFG_UART_XPIC_APP_TXD  = 0x19,
	MMIO_CFG_UART_XPIC_APP_RTSN = 0x1a,
	MMIO_CFG_UART_XPIC_APP_CTSN = 0x1b,
	MMIO_CFG_UART_APP_RXD       = 0x1c,
	MMIO_CFG_UART_APP_TXD       = 0x1d,
	MMIO_CFG_UART_APP_RTSN      = 0x1e,
	MMIO_CFG_UART_APP_CTSN      = 0x1f,
	MMIO_CFG_GPIO0              = 0x20,
	MMIO_CFG_GPIO1              = 0x21,
	MMIO_CFG_GPIO2              = 0x22,
	MMIO_CFG_GPIO3              = 0x23,
	MMIO_CFG_GPIO4              = 0x24,
	MMIO_CFG_GPIO5              = 0x25,
	MMIO_CFG_GPIO6              = 0x26,
	MMIO_CFG_GPIO7              = 0x27,
	MMIO_CFG_WDG_ACT            = 0x28,
	MMIO_CFG_EN_IN              = 0x29,
	MMIO_CFG_ETH_MDC            = 0x2a,
	MMIO_CFG_ETH_MDIO           = 0x2b,
	MMIO_CFG_PIO                = 0x3f,
} MMIO_CFG_T;

#define MMIO_CFG_DISABLE MMIO_CFG_PIO

#endif

////////////////// autogenerated file end //////////////////
