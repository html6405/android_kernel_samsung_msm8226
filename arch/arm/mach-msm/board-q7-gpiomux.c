/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>

#define WLAN_CLK       44
#define WLAN_SET       43
#define WLAN_DATA0     42
#define WLAN_DATA1     41
#define WLAN_DATA2     40

static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hsic_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm_hsic_configs[] = {
	{
		.gpio = 115,               /* HSIC_STROBE */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 116,               /* HSIC_DATA */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};

#define KS8851_IRQ_GPIO 115

#if defined(CONFIG_MACH_MS01_CHN_CTC) || defined(CONFIG_MACH_CRATERVE_CHN_CTC) || \
	defined(CONFIG_MACH_MS01_EUR_3G) || defined(CONFIG_MACH_CRATERQ) || \
	defined(CONFIG_MACH_MS01_LTE) || defined(CONFIG_MACH_CS03_SGLTE) || \
	defined(CONFIG_MACH_MS01_LTE_KOR) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || \
	defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || \
	defined(CONFIG_MACH_S3VE_CHN_CTC) || defined(CONFIG_MACH_Q7_CHN_CU) || \
	defined(CONFIG_MACH_Q7LTE_KOR)|| defined(CONFIG_MACH_MEGAPLUSLTE_CHN_CMCC)
#define NC_GPIO_CONFIG(gpio_num) { \
		.gpio = gpio_num, \
		.settings = { [GPIOMUX_SUSPENDED] = &nc_suspend_cfg, } \
	}

static struct gpiomux_setting nc_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)
#define GPIO_IN_NP_CONFIG(gpio_num) { \
		.gpio = gpio_num, \
		.settings = { [GPIOMUX_SUSPENDED] = &gpio_in_np_suspend_cfg, } \
	}

static struct gpiomux_setting gpio_in_np_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

#if 0
#define NC_GPIO_PD_CONFIG(gpio_num) { \
	.gpio = gpio_num, \
	.settings = { [GPIOMUX_ACTIVE] = &nc_pd_cfg, }, \
	.settings = { [GPIOMUX_SUSPENDED] = &nc_pd_cfg, } \
}

static struct gpiomux_setting nc_pd_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

#define NC_GPIO_PU_CONFIG(gpio_num) { \
		.gpio = gpio_num, \
		.settings = { [GPIOMUX_SUSPENDED] = &nc_pu_suspend_cfg, } \
	}

static struct gpiomux_setting nc_pu_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
#endif
#endif


#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)|| defined(CONFIG_MACH_MEGAPLUSLTE_CHN_CMCC)
static struct gpiomux_setting uart_boot_on_gpio_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif



static struct gpiomux_setting synaptics_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting synaptics_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting synaptics_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting synaptics_reset_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)
static struct gpiomux_setting chg_pm8226_gpio_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
#endif


static struct gpiomux_setting gpio_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting gpio_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
static struct gpiomux_setting gpio_home_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting gpio_home_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};
#else
static struct gpiomux_setting gpio_home_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_home_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

#if !defined(CONFIG_MACH_MILLET3G_EUR) && \
!defined(CONFIG_MACH_VICTOR_CHN_CMCC) && !defined(CONFIG_MACH_VICTOR_CHN_CU)

static struct gpiomux_setting gpio_spi_act_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gpio_spi_cs_act_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct gpiomux_setting gpio_spi_susp_config = {

	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif
static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting wcnss_5gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_i2c_tsp_active_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct gpiomux_setting gpio_i2c_tsp_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

	/* define PROX EN GPIO SETTING */
#if defined(CONFIG_MACH_CS03_SGLTE)||defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)
static struct gpiomux_setting prox_en_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_prox_gpio_configs[] __initdata = {
	{
		.gpio = 12,
		.settings = {
			[GPIOMUX_ACTIVE]	= &prox_en_cfg,
		},
	},
};
static struct msm_gpiomux_config msm_prox_en_2nd_gpio_configs[] __initdata = {
	{
		.gpio = 34,
		.settings = {
			[GPIOMUX_ACTIVE]	= &prox_en_cfg,
		},
	},
};
#endif

#if defined(CONFIG_YAS_ACC_DRIVER_BMA250) || defined(CONFIG_INPUT_MPU6500) || \
defined(CONFIG_PROXIMITY_SENSOR) || defined (CONFIG_SENSORS_HSCDTD008A) || defined (CONFIG_BMA250_ACC_DRIVER) || \
defined(CONFIG_SENSORS_INVENSENSE) || defined(CONFIG_SENSORS_TMD27723) || \
defined(CONFIG_SENSORS_AK09911C)
#if defined(CONFIG_MACH_CS03_SGLTE)	 || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
static struct gpiomux_setting sensor_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
#else
static struct gpiomux_setting sensor_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif
static struct gpiomux_setting accel_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting prox_irq_config = {
    .func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
#if defined(CONFIG_MACH_MS01_LTE_KOR) || defined(CONFIG_MACH_CS03_SGLTE)|| defined (CONFIG_MACH_HLITE_CHN_SGLTE) || \
defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU)|| \
defined(CONFIG_MACH_CRATERVE_CHN_CTC) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
	.pull = GPIOMUX_PULL_NONE,
#else
	.pull = GPIOMUX_PULL_DOWN,
#endif
	.dir = GPIOMUX_IN,
};
static struct gpiomux_setting mag_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
static struct gpiomux_setting prox_en_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting prox_en_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif
static struct gpiomux_setting grip_sensor_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting grip_irq_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
static struct gpiomux_setting nfc_gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting nfc_ven_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting nfc_tx_en_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting nfc_irq_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
	.pull = GPIOMUX_PULL_DOWN,
#else
	.pull = GPIOMUX_PULL_NONE,
#endif
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting nfc_firmware_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting hall_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hall_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_hall_configs[] __initdata = {
	{
		.gpio = 63,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hall_active_cfg,
			[GPIOMUX_SUSPENDED] = &hall_suspend_cfg,
		},
	},
};


static struct msm_gpiomux_config msm_keypad_configs[] __initdata = {
	{
		.gpio = 106,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_keys_suspend,
		},
	},
	{
		.gpio = 108,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_home_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_home_keys_suspend,
		},
	},
};
static struct gpiomux_setting lcd_rst_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
static struct msm_gpiomux_config msm_lcd_configs[] __initdata = {
	{
		.gpio = 110,
		.settings = {
			[GPIOMUX_SUSPENDED] = &lcd_rst_sus_cfg,
		},
	},
};

static struct gpiomux_setting gpio_uart_rx_sleep_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_HIGH,

};

static struct gpiomux_setting gpio_uart_sleep_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};



static struct msm_gpiomux_config msm_blsp_configs[] __initdata = {
	{
		.gpio      = 0,		/* BLSP1 QUP1 SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 1,		/* BLSP1 QUP1 SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 2,		/* BLSP1 QUP1 SPI_CS1 */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_cs_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 3,		/* BLSP1 QUP1 SPI_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 8,	/* BLSP1 UART2 TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_sleep_config,
		},
	},
	{
		.gpio      = 9,	/* BLSP1 UART2 RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_rx_sleep_config,
		},
	},
#if 0 /*Need to enable these gpios for the 4 PIN UART system*/
	{
		.gpio      = 6,	/* BLSP1 UART2 CTS */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 7,	/* BLSP1 QUART2 RFR */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	}
#endif
	{
		.gpio      = 14,	/* BLSP1 QUP4 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 15,	/* BLSP1 QUP4 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 18,		/* BLSP1 QUP5 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_tsp_active_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_tsp_suspend_config,
		},
	},
	{
		.gpio      = 19,		/* BLSP1 QUP5 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_tsp_active_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_tsp_suspend_config,
		},
	},
#if !defined(CONFIG_MACH_MILLET3G_EUR) && !defined(CONFIG_MACH_CS03_SGLTE) && !defined(CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && \
!defined(CONFIG_MACH_VICTOR_CHN_CMCC) && !defined(CONFIG_MACH_VICTOR_CHN_CU)&& !defined(CONFIG_MACH_CRATERVE_CHN_CTC) && \
!defined(CONFIG_MACH_Q7_CHN_CU) && !defined(CONFIG_MACH_Q7LTE_KOR)
	{
		.gpio      = 22,		/* BLSP1 QUP6 SPI_CS_ETH */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#endif
#if !defined(CONFIG_MACH_MILLET3G_EUR) && !defined(CONFIG_MACH_S3VE_CHN_OPEN) && !defined(CONFIG_MACH_CS03_SGLTE) && \
!defined(CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && !defined(CONFIG_MACH_VICTOR_CHN_CMCC) && !defined(CONFIG_MACH_VICTOR_CHN_CU) && \
!defined(CONFIG_MACH_Q7_CHN_CU) && !defined(CONFIG_MACH_Q7LTE_KOR)
	{
		.gpio      = 23,		/* BLSP1 QUP6 SPI_CS_ETH */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#endif
	{					/*  NFC   */
		.gpio      = 10,		/* BLSP1 QUP3 I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &nfc_gpio_i2c_config,
		},
	},
	{					/*  NFC   */
		.gpio      = 11,		/* BLSP1 QUP3 I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &nfc_gpio_i2c_config,
		},
	},

#if defined(CONFIG_YAS_ACC_DRIVER_BMA250) || defined(CONFIG_INPUT_MPU6500) || \
defined(CONFIG_PROXIMITY_SENSOR) || defined (CONFIG_SENSORS_HSCDTD008A) || defined (CONFIG_BMA250_ACC_DRIVER) || \
defined(CONFIG_SENSORS_INVENSENSE) || defined(CONFIG_SENSORS_TMD27723) || \
defined(CONFIG_SENSORS_AK09911C)
    {
		.gpio      = 6,		/* BLSP1 QUP2 I2C_SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 7,		/* BLSP1 QUP2 I2C_SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &sensor_gpio_i2c_config,
		},
	},
#endif

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU)|| defined(CONFIG_MACH_CRATERVE_CHN_CTC) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)|| defined(CONFIG_MACH_MEGAPLUSLTE_CHN_CMCC)
	{
		.gpio	   = 109,		/* UART boot on gpio */
		.settings = {
			[GPIOMUX_ACTIVE] = &uart_boot_on_gpio_config,
			[GPIOMUX_SUSPENDED] = &uart_boot_on_gpio_config,
		},
	},
#endif	

};


static struct msm_gpiomux_config msm_synaptics_configs[] __initdata = {
	{
		.gpio = 16,
		.settings = {
			[GPIOMUX_ACTIVE] = &synaptics_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &synaptics_reset_sus_cfg,
		},
	},
	{
		.gpio = 17,
		.settings = {
			[GPIOMUX_ACTIVE] = &synaptics_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &synaptics_int_sus_cfg,
		},
	},
};

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)
static struct msm_gpiomux_config chg_pm8226_configs[] __initdata = {
	{
		.gpio = 51,
		.settings = {
			[GPIOMUX_ACTIVE] = &chg_pm8226_gpio_cfg,
			[GPIOMUX_SUSPENDED] = &chg_pm8226_gpio_cfg,
		},
	},
};
#endif



static struct gpiomux_setting gpio_nc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting goodix_ldo_en_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_ldo_en_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting goodix_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting goodix_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_reset_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm_qrd_blsp_configs[] __initdata = {
	{
		.gpio      = 4,		/* NC */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio      = 14,	/* NC */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
};

static struct msm_gpiomux_config msm_qrd_goodix_configs[] __initdata = {
	{
		.gpio = 15,		/* LDO EN */
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_ldo_en_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_ldo_en_sus_cfg,
		},
	},
	{
		.gpio = 16,		/* RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_reset_sus_cfg,
		},
	},
	{
		.gpio = 17,		/* INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_int_sus_cfg,
		},
	},
	{
		.gpio      = 18,		/* BLSP1 QUP5 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 19,		/* BLSP1 QUP5 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
};
static struct gpiomux_setting nfc_wake_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting nfc_wake_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_skuf_nfc_configs[] __initdata = {
	{					/*  NFC   WAKE */
		.gpio      = 5,
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_wake_act_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_wake_sus_cfg,
		},
	},
	{					/*  NFC   */
		.gpio      = 10,		/* BLSP1 QUP3 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{					/*  NFC   */
		.gpio      = 11,		/* BLSP1 QUP3 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
};

static struct gpiomux_setting sd_card_det_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting sd_card_det_sleep_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config sd_card_det __initdata = {
	.gpio = 38,
	.settings = {
		[GPIOMUX_ACTIVE]    = &sd_card_det_active_config,
		[GPIOMUX_SUSPENDED] = &sd_card_det_sleep_config,
	},
};

#if defined(CONFIG_YAS_ACC_DRIVER_BMA250) || defined(CONFIG_INPUT_MPU6500) || \
defined(CONFIG_PROXIMITY_SENSOR) || defined (CONFIG_SENSORS_HSCDTD008A)|| defined (CONFIG_BMA250_ACC_DRIVER)
static struct msm_gpiomux_config msm_sensors_configs[] __initdata = {
	{
		.gpio      = 65,		/* PROXY IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &prox_irq_config,
			[GPIOMUX_SUSPENDED] = &prox_irq_config,
		},
	},
#if defined(CONFIG_MACH_CS03_SGLTE)	|| defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
	{
  		.gpio	   = 67,		/* ACCEL IRQ */
  		.settings = {
  			[GPIOMUX_ACTIVE] = &accel_irq_config,
  			[GPIOMUX_SUSPENDED] = &accel_irq_config,
  		},
	},
#else
#endif
#if !defined (CONFIG_MACH_HLITE_CHN_SGLTE)  && !defined(CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && !defined(CONFIG_MACH_Q7_CHN_CU) && \
!defined(CONFIG_MACH_Q7LTE_KOR)
	{
		.gpio      = 66,		/* MAG IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &mag_irq_config,
			[GPIOMUX_SUSPENDED] = &mag_irq_config,
		},
	},
#endif
	{
		.gpio      = 49,		/* PROXY ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &prox_en_config,
			[GPIOMUX_SUSPENDED] = &prox_en_suspend_config,
		},
	},
#if 0 //defined (CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CU)
	{
		.gpio      = 56,		/* MAG IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &mag_irq_config,
			[GPIOMUX_SUSPENDED] = &mag_irq_config,
		},
	},
#endif

	{
		.gpio      = 56,		/* MAG IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &mag_irq_config,
			[GPIOMUX_SUSPENDED] = &mag_irq_config,
		},
	},

	{
		.gpio      = 22,		/* GRIP ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_sensor_gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &grip_sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 23,		/* GRIP ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_sensor_gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &grip_sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 49,		/* GRIP ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_sensor_gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &grip_sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 50,		/* GRIP ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_sensor_gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &grip_sensor_gpio_i2c_config,
		},
	},
	{
		.gpio      = 66,		/* GRIP ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_irq_config,
			[GPIOMUX_SUSPENDED] = &grip_irq_config,
		},
	},
	{
		.gpio      = 64,		/* GRIP_2G ENABLE */
		.settings = {
			[GPIOMUX_ACTIVE] = &grip_irq_config,
			[GPIOMUX_SUSPENDED] = &grip_irq_config,
		},
	},


};
#endif
static struct msm_gpiomux_config msm_nfc_configs[] __initdata = {
	{
		.gpio      = 21,		/* NFC IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_irq_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_irq_cfg,
		},
	},
	{
		.gpio		= 62,		/* NFC FIRMWARE */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_firmware_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_firmware_cfg,
		},
	},
	{
		.gpio		= 36,		/* NFC TX EN*/
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_tx_en_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_tx_en_cfg,
		},
	},
	{
		.gpio		= 20,		/* NFC VEN */
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_ven_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_ven_cfg,
		},
	},
};

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config wcnss_5gpio_interface[] = {
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
};

static struct gpiomux_setting gpio_suspend_config[] = {
	{
		.func = GPIOMUX_FUNC_GPIO,  /* IN-NP */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_GPIO,  /* O-LOW */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
};

static struct gpiomux_setting cam_settings[] = {
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 0 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 1 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

	{
		.func = GPIOMUX_FUNC_1, /*i2c suspend*/ /* 2 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*active 0*/ /* 3 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend 0*/ /* 4 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_OUT_LOW,
	},
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 0 */
		.drv = GPIOMUX_DRV_4MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 1 */
		.drv = GPIOMUX_DRV_4MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
	{
		.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */ //7 Haarika
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},
	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */ //8
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 9 */
		.drv = GPIOMUX_DRV_6MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 10 */
		.drv = GPIOMUX_DRV_6MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 11 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 12 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

};


static struct msm_gpiomux_config msm_sensor_configs[] __initdata = {

	{
		.gpio = 26, /* CAM_MCLK0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[5],
			[GPIOMUX_SUSPENDED] = &cam_settings[6],
		},
	},

	{
		.gpio = 27, /* CAM_MCLK1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[5],
			[GPIOMUX_SUSPENDED] = &cam_settings[6],
		},

	},
	{
		.gpio = 29, /* CCI_I2C_SDA0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 30, /* CCI_I2C_SCL0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 36, /* CAM1_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 37, /* CAM1_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#if !defined(CONFIG_MACH_MS01_CHN_CTC) && !defined(CONFIG_MACH_CRATERVE_CHN_CTC) && \
!defined( CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && !defined(CONFIG_MACH_Q7_CHN_CU) && !defined(CONFIG_MACH_Q7LTE_KOR) && !defined(CONFIG_MACH_MEGAPLUSLTE_CHN_CMCC)
	{
		.gpio = 34, /* CAM1 VCM_PWDN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#endif
#if !defined(CONFIG_MACH_CS03_SGLTE) && !defined(CONFIG_MACH_VICTOR_CHN_CMCC) && \
!defined(CONFIG_MACH_VICTOR_CHN_CU)
	{
		.gpio = 28, /* CAM2_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#endif
	{
		.gpio = 27, /* CAM1_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
/*
};

static struct msm_gpiomux_config msm_sensor_configs_skuf_plus[] __initdata = {*/
	{
		.gpio = 112, /* CAM_ANALOG_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 114, /* CAM_IO_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[7],
			[GPIOMUX_SUSPENDED] = &cam_settings[8],
		},
	},
	
		{
			.gpio	   = 34, /* AF_SDA */
			.settings = {
				/*[GPIOMUX_ACTIVE] = &gpio_i2c_config,*/
				[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
			},
		},
		{
			.gpio	   = 33, /* AF_SCL */
			.settings = {
				/*[GPIOMUX_ACTIVE] = &gpio_i2c_config,*/
				[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
			},
		},

};

static struct gpiomux_setting codec_int_gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting codec_int_gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_codec_int_gpio_configs[] __initdata = {
	{
		.gpio = 68, /* CODEC_INT_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &codec_int_gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &codec_int_gpio_suspend_cfg,
		},
	}
};

static struct gpiomux_setting earjack_detect_gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting earjack_detect_gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_earjack_detect_gpio_configs[] __initdata = {
	{
		.gpio = 69, /* EAR_3.5_DET */
		.settings = {
			[GPIOMUX_ACTIVE]    = &earjack_detect_gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &earjack_detect_gpio_suspend_cfg,
		},
	}
};

static struct gpiomux_setting earjack_sendend_gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*active 1*/ /* 0 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting earjack_sendend_gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO, /*suspend*/ /* 1 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_earjack_sendend_gpio_configs[] __initdata = {
	{
		.gpio = 35, /* EAR_SWITCH */
		.settings = {
			[GPIOMUX_ACTIVE]    = &earjack_sendend_gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &earjack_sendend_gpio_suspend_cfg,
		},
	}
};


#if !defined(CONFIG_MACH_HLITE_CHN_SGLTE) && ! defined (CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && !defined(CONFIG_MACH_Q7_CHN_CU) && \
!defined(CONFIG_MACH_Q7LTE_KOR)
static struct gpiomux_setting usb_otg_sw_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config usb_otg_sw_configs[] __initdata = {
	{
		.gpio = 67,
		.settings = {
			[GPIOMUX_SUSPENDED] = &usb_otg_sw_cfg,
		},
	},
};
#endif

static void msm_gpiomux_sdc3_install(void) {}





static struct msm_gpiomux_config msm8226_gpio_in_np_cfgs[] __initdata = {
	GPIO_IN_NP_CONFIG(14),
	GPIO_IN_NP_CONFIG(15),
	GPIO_IN_NP_CONFIG(51),
	GPIO_IN_NP_CONFIG(52),
};






static struct msm_gpiomux_config msm8226_nc_gpio_cfgs[] __initdata = {
	NC_GPIO_CONFIG(24),
	NC_GPIO_CONFIG(45),
	NC_GPIO_CONFIG(46),
	NC_GPIO_CONFIG(53),
	NC_GPIO_CONFIG(54),
	NC_GPIO_CONFIG(55),
	NC_GPIO_CONFIG(56),
	NC_GPIO_CONFIG(60),
	NC_GPIO_CONFIG(75),
	NC_GPIO_CONFIG(95),
	NC_GPIO_CONFIG(96),
	NC_GPIO_CONFIG(113),
	NC_GPIO_CONFIG(114),
	NC_GPIO_CONFIG(118),
	NC_GPIO_CONFIG(119),
	NC_GPIO_CONFIG(120),
};




#if defined(CONFIG_MACH_MS01_CHN_CTC) || defined(CONFIG_MACH_CRATERVE_CHN_CTC) || defined(CONFIG_MACH_Q7_CHN_CMCC) || \
	defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)
extern unsigned int system_rev;
#endif

void __init msm8226_init_gpiomux(void)
{
	int rc;

	rc = msm_gpiomux_init_dt();
	if (rc) {
		pr_err("%s failed %d\n", __func__, rc);
		return;
	}
#if defined(CONFIG_MACH_CS03_SGLTE)||defined(CONFIG_MACH_HLITE_CHN_SGLTE) || \
defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU)  || \
defined(CONFIG_MACH_Q7LTE_KOR)
	msm_gpiomux_install(msm_prox_gpio_configs,
				ARRAY_SIZE(msm_prox_gpio_configs));
	if (system_rev == 0)
		msm_gpiomux_install(msm_prox_en_2nd_gpio_configs,
					ARRAY_SIZE(msm_prox_en_2nd_gpio_configs));
#endif

	msm_gpiomux_install(msm_keypad_configs,
			ARRAY_SIZE(msm_keypad_configs));


	if (of_board_is_qrd())
		msm_gpiomux_install(msm_qrd_blsp_configs,
			ARRAY_SIZE(msm_qrd_blsp_configs));
	else
		msm_gpiomux_install(msm_blsp_configs,
			ARRAY_SIZE(msm_blsp_configs));

	msm_gpiomux_install(wcnss_5wire_interface,
				ARRAY_SIZE(wcnss_5wire_interface));

	msm_gpiomux_install(&sd_card_det, 1);



	if (of_board_is_qrd())
		msm_gpiomux_install(msm_qrd_goodix_configs,
				ARRAY_SIZE(msm_qrd_goodix_configs));

	else

		msm_gpiomux_install(msm_synaptics_configs,
			ARRAY_SIZE(msm_synaptics_configs));


	if (of_board_is_skuf())
		msm_gpiomux_install(msm_skuf_nfc_configs,
				ARRAY_SIZE(msm_skuf_nfc_configs));

	msm_gpiomux_install(msm_sensor_configs, ARRAY_SIZE(msm_sensor_configs));
/*
	if (of_board_is_skuf())
		msm_gpiomux_install(msm_sensor_configs_skuf_plus,
			ARRAY_SIZE(msm_sensor_configs_skuf_plus));
*/
	msm_gpiomux_install(msm_nfc_configs,
		ARRAY_SIZE(msm_nfc_configs));


#if defined(CONFIG_YAS_ACC_DRIVER_BMA250) || defined(CONFIG_INPUT_MPU6500) || \
defined(CONFIG_PROXIMITY_SENSOR) || defined (CONFIG_SENSORS_HSCDTD008A) || defined (CONFIG_BMA250_ACC_DRIVER)
	msm_gpiomux_install(msm_sensors_configs,
		ARRAY_SIZE(msm_sensors_configs));
#endif

#if !defined(CONFIG_MACH_HLITE_CHN_SGLTE) && ! defined (CONFIG_MACH_Q7_CHN_CMCC) && !defined(CONFIG_MACH_Q7_CHN_CTC) && !defined(CONFIG_MACH_Q7_CHN_CU) && \
!defined(CONFIG_MACH_Q7LTE_KOR)
	if (of_board_is_cdp() || of_board_is_mtp() || of_board_is_xpm())
		msm_gpiomux_install(usb_otg_sw_configs,
					ARRAY_SIZE(usb_otg_sw_configs));
#endif
	msm_gpiomux_sdc3_install();

	/*
	 * HSIC STROBE gpio is also used by the ethernet. Install HSIC
	 * gpio mux config only when HSIC is enabled. HSIC config will
	 * be disabled when ethernet config is enabled.
	 */
	if (machine_is_msm8926()) {
		msm_hsic_configs[0].gpio = 119; /* STROBE */
		msm_hsic_configs[1].gpio = 120; /* DATA */
	}
	msm_gpiomux_install(msm_hsic_configs, ARRAY_SIZE(msm_hsic_configs));

#if defined(CONFIG_MACH_MS01_CHN_CTC) || defined(CONFIG_MACH_CRATERVE_CHN_CTC) || \
defined(CONFIG_MACH_MS01_EUR_3G) || defined(CONFIG_MACH_CRATERQ) || defined(CONFIG_MACH_CS03_SGLTE) || \
defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC)|| defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || \
defined(CONFIG_MACH_S3VE_CHN_CTC) || defined(CONFIG_MACH_Q7_CHN_CU) || defined(CONFIG_MACH_Q7LTE_KOR)|| defined(CONFIG_MACH_MEGAPLUSLTE_CHN_CMCC)
	msm_gpiomux_install(msm8226_nc_gpio_cfgs, ARRAY_SIZE(msm8226_nc_gpio_cfgs));
#endif

	msm_gpiomux_install(msm_codec_int_gpio_configs, ARRAY_SIZE(msm_codec_int_gpio_configs));
	msm_gpiomux_install(msm_earjack_detect_gpio_configs, ARRAY_SIZE(msm_earjack_detect_gpio_configs));
	msm_gpiomux_install(msm_earjack_sendend_gpio_configs, ARRAY_SIZE(msm_earjack_sendend_gpio_configs));
#if defined(CONFIG_MACH_MS01_EUR_3G) || defined(CONFIG_MACH_MS01_LTE) || \
	defined(CONFIG_MACH_MS01_LTE_KOR)
	msm_gpiomux_install(ms01_nc_gpio_cfgs, ARRAY_SIZE(ms01_nc_gpio_cfgs));
#endif

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || defined(CONFIG_MACH_Q7_CHN_CTC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR)
	msm_gpiomux_install(chg_pm8226_configs, ARRAY_SIZE(chg_pm8226_configs));
#endif

#if defined(CONFIG_MACH_CS03_SGLTE) || defined(CONFIG_MACH_HLITE_CHN_SGLTE) || defined(CONFIG_MACH_Q7_CHN_CMCC) || \
defined(CONFIG_MACH_VICTOR_CHN_CMCC) || defined(CONFIG_MACH_VICTOR_CHN_CU) || defined(CONFIG_MACH_Q7_CHN_CU) || \
defined(CONFIG_MACH_Q7LTE_KOR) || defined(CONFIG_MACH_Q7_CHN_CTC)
	msm_gpiomux_install(msm8226_gpio_in_np_cfgs, ARRAY_SIZE(msm8226_gpio_in_np_cfgs));
#endif


}

static void wcnss_switch_to_gpio(void)
{
	/* Switch MUX to GPIO */
	msm_gpiomux_install(wcnss_5gpio_interface,
	ARRAY_SIZE(wcnss_5gpio_interface));

	/* Ensure GPIO config */
	gpio_direction_input(WLAN_DATA2);
	gpio_direction_input(WLAN_DATA1);
	gpio_direction_input(WLAN_DATA0);
	gpio_direction_output(WLAN_SET, 0);
	gpio_direction_output(WLAN_CLK, 0);
}

static void wcnss_switch_to_5wire(void)
{
	msm_gpiomux_install(wcnss_5wire_interface,
	ARRAY_SIZE(wcnss_5wire_interface));
}

u32 wcnss_rf_read_reg(u32 rf_reg_addr)
{
	int count = 0;
	u32 rf_cmd_and_addr = 0;
	u32 rf_data_received = 0;
	u32 rf_bit = 0;

	wcnss_switch_to_gpio();

	/* Reset the signal if it is already being used. */
	gpio_set_value(WLAN_SET, 0);
	gpio_set_value(WLAN_CLK, 0);

	/* We start with cmd_set high WLAN_SET = 1. */
	gpio_set_value(WLAN_SET, 1);

	gpio_direction_output(WLAN_DATA0, 1);
	gpio_direction_output(WLAN_DATA1, 1);
	gpio_direction_output(WLAN_DATA2, 1);

	gpio_set_value(WLAN_DATA0, 0);
	gpio_set_value(WLAN_DATA1, 0);
	gpio_set_value(WLAN_DATA2, 0);

	/* Prepare command and RF register address that need to sent out.
	 * Make sure that we send only 14 bits from LSB.
	 */
	rf_cmd_and_addr  = (((WLAN_RF_READ_REG_CMD) |
		(rf_reg_addr << WLAN_RF_REG_ADDR_START_OFFSET)) &
		WLAN_RF_READ_CMD_MASK);

	for (count = 0; count < 5; count++) {
		gpio_set_value(WLAN_CLK, 0);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA0, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA1, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA2, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		/* Send the data out WLAN_CLK = 1 */
		gpio_set_value(WLAN_CLK, 1);
	}

	/* Pull down the clock signal */
	gpio_set_value(WLAN_CLK, 0);

	/* Configure data pins to input IO pins */
	gpio_direction_input(WLAN_DATA0);
	gpio_direction_input(WLAN_DATA1);
	gpio_direction_input(WLAN_DATA2);

	for (count = 0; count < 2; count++) {
		gpio_set_value(WLAN_CLK, 1);
		gpio_set_value(WLAN_CLK, 0);
	}

	rf_bit = 0;
	for (count = 0; count < 6; count++) {
		gpio_set_value(WLAN_CLK, 1);
		gpio_set_value(WLAN_CLK, 0);

		rf_bit = gpio_get_value(WLAN_DATA0);
		rf_data_received |= (rf_bit << (count * 3 + 0));

		if (count != 5) {
			rf_bit = gpio_get_value(WLAN_DATA1);
			rf_data_received |= (rf_bit << (count * 3 + 1));

			rf_bit = gpio_get_value(WLAN_DATA2);
			rf_data_received |= (rf_bit << (count * 3 + 2));
		}
	}

	gpio_set_value(WLAN_SET, 0);
	wcnss_switch_to_5wire();

	return rf_data_received;
}
