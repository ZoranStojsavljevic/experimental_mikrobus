/* SPDX-License-Identifier: GPL-2.0 */
/*
 * MikroBUS: mikrobus_info.c for data tracing
 *
 * Copyright 2020 Zoran Stojsavljevic (zoran.stojsavljevic@gmail.com)
 */

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/gpio/machine.h>
#include <linux/spi/spi.h>
#include <linux/serdev.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/greybus/greybus_manifest.h>

#include "mikrobus_core.h"

const char *const greybus_protocol_string[] =
{
	"GREYBUS_PROTOCOL_CONTROL",
	"UNUSED",
	"GREYBUS_PROTOCOL_GPIO",
	"GREYBUS_PROTOCOL_I2C",
	"GREYBUS_PROTOCOL_UART",
	"GREYBUS_PROTOCOL_HID",
	"GREYBUS_PROTOCOL_USB",
	"GREYBUS_PROTOCOL_SDIO",
	"GREYBUS_PROTOCOL_POWER_SUPPLY",
	"GREYBUS_PROTOCOL_PWM",
	"UNUSED",
	"GREYBUS_PROTOCOL_SPI",
	"GREYBUS_PROTOCOL_DISPLAY",
	"GREYBUS_PROTOCOL_CAMERA_MGMT",
	"GREYBUS_PROTOCOL_SENSOR",
	"GREYBUS_PROTOCOL_LIGHTS",
	"GREYBUS_PROTOCOL_VIBRATOR",
	"GREYBUS_PROTOCOL_LOOPBACK",
	"GREYBUS_PROTOCOL_AUDIO_MGMT",
	"GREYBUS_PROTOCOL_AUDIO_DATA",
	"GREYBUS_PROTOCOL_SVC",
	"GREYBUS_PROTOCOL_BOOTROM",
	"GREYBUS_PROTOCOL_CAMERA_DATA",
	"GREYBUS_PROTOCOL_FW_DOWNLOAD",
	"GREYBUS_PROTOCOL_FW_MANAGEMENT",
	"GREYBUS_PROTOCOL_AUTHENTICATION",
	"GREYBUS_PROTOCOL_LOG",
//	/ * ... * /			= 0x1b,
//	GREYBUS_PROTOCOL_RAW		= 0xfe,
//	GREYBUS_PROTOCOL_VENDOR		= 0xff,
};

#define GREYBUS_PROTOCOL_RAW    0xfe
#define GREYBUS_PROTOCOL_VENDOR 0xff

const char *const mikrobus_pin_string[] =
{
	"MIKROBUS_PIN_PWM",
	"MIKROBUS_PIN_INT",
	"MIKROBUS_PIN_RX",
	"MIKROBUS_PIN_TX",
	"MIKROBUS_PIN_SCL",
	"MIKROBUS_PIN_SDA",
	"MIKROBUS_PIN_MOSI",
	"MIKROBUS_PIN_MISO",
	"MIKROBUS_PIN_SCK",
	"MIKROBUS_PIN_CS",
	"MIKROBUS_PIN_RST",
	"MIKROBUS_PIN_AN",
	"MIKROBUS_PORT_PIN_COUNT",
};

inline void trace_mikrobus_port_scan_eeprom(void)
{
	printk(KERN_INFO "Entering mikrobus_port_scan_eeprom() function!\n");
}

inline void trace_mikrobus_device_register(void)
{
	printk(KERN_INFO "Entering mikrobus_device_register() function!\n");
}

inline void trace_mikrobus_port_probe(void)
{
	printk(KERN_INFO "Entering mikrobus_port_probe() function!\n");
}

inline void trace_mikrobus_port_register(void)
{
	printk(KERN_INFO "Entering mikrobus_port_register() function!\n");
}

inline void trace_mikrobus_manifest_parse_devices(void)
{
        printk(KERN_INFO "Entering mikrobus_manifest_parse_devices() function!\n");
}

void show_board_device_info(struct board_device_info *p)
{
	printk(KERN_INFO "--- show_board_device_info() ---\n");
	printk(KERN_INFO "board_device_info: num_gpio_resources = %u\n", p->num_gpio_resources);
	printk(KERN_INFO "board_device_info: num_properties = %u\n", p->num_properties);
	printk(KERN_INFO "board_device_info: num_regulators = %u\n", p->num_regulators);
	printk(KERN_INFO "board_device_info: num_clocks = %u\n", p->num_clocks);
	printk(KERN_INFO "board_device_info: protocol = %u, protocol string = %s\n", p->protocol, greybus_protocol_string[p->protocol]);
	printk(KERN_INFO "board_device_info: protocol string = %s\n", greybus_protocol_string[p->protocol]);
	printk(KERN_INFO "board_device_info: mode = %d\n", p->mode);
	printk(KERN_INFO "board_device_info: max_speed_hz = %u\n", p->max_speed_hz);
	printk(KERN_INFO "board_device_info: *drv_name = %s\n", p->drv_name);
	printk(KERN_INFO "board_device_info: irq_type = %d\n", p->irq_type);
	printk(KERN_INFO "board_device_info: irq = %d\n", p->irq);
	printk(KERN_INFO "board_device_info: id = %d\n", p->id);
	printk(KERN_INFO "--- end show_board_device_info() ---\n");
}

void show_addon_board_info(struct addon_board_info *p)
{
	int	i;

	printk(KERN_INFO "--- show_addon_board_info() ---\n");
	for(i = 0; i < MIKROBUS_PORT_PIN_COUNT; ++i)
		printk(KERN_INFO "addon_board_info: pin_state[%d] = %u, pin_state_string[%d] = %s\n", i, p->pin_state[i], i, mikrobus_pin_string[i]);

	printk(KERN_INFO "addon_board_info: *name = %s\n", p->name);
	printk(KERN_INFO "--- end show_addon_board_info() ---\n");
}

void show_mikrobus_port(struct mikrobus_port *p)
{
	printk(KERN_INFO "--- show_mikrobus_port() ---\n");
	// struct i2c_adapter *i2c_adap;
	if (NULL != p->i2c_adap) {
		printk(KERN_INFO "mikrobus_port: *i2c_adap->class = %d\n", p->i2c_adap->class);
		printk(KERN_INFO "mikrobus_port: *i2c_adap->timeout = %d\n", p->i2c_adap->timeout);
		printk(KERN_INFO "mikrobus_port: *i2c_adap->retries = %d\n", p->i2c_adap->retries);
		printk(KERN_INFO "mikrobus_port: *i2c_adap->nr = %d\n", p->i2c_adap->nr);
		printk(KERN_INFO "mikrobus_port: *i2c_adap->name = %s\n", p->i2c_adap->name);
	}
	else printk(KERN_INFO "mikrobus_port->i2c_adap is NULL\n");

	// struct spi_master *spi_mstr;
	if (NULL != p->spi_mstr) {
		printk(KERN_INFO "mikrobus_port: *spi_mstr->bus_num = %d\n", p->spi_mstr->bus_num);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->num_chipselect = %d\n", p->spi_mstr->num_chipselect);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->dma_alignment = %d\n", p->spi_mstr->dma_alignment);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->mode_bits = %d\n", p->spi_mstr->mode_bits);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->buswidth_override_bits = %d\n", p->spi_mstr->buswidth_override_bits);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->min_speed_hz = %d\n", p->spi_mstr->min_speed_hz);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->max_speed_hz = %d\n", p->spi_mstr->max_speed_hz);
		printk(KERN_INFO "mikrobus_port: *spi_mstr->flags = %d\n", p->spi_mstr->flags);
	}
	else printk(KERN_INFO "mikrobus_port->spi_mstr is NULL\n");

	// struct serdev_controller *ser_ctrl;
	if (NULL != p->ser_ctrl) {
		printk(KERN_INFO "mikrobus_port: *ser_ctrl->nr = %d\n", p->ser_ctrl->nr);
		if (NULL != p->ser_ctrl->serdev) {
			printk(KERN_INFO "mikrobus_port: *ser_ctrl->*serdev->nr = %d\n", p->ser_ctrl->serdev->nr);
			printk(KERN_INFO "mikrobus_port: *ser_ctrl->*serdev->modalias = %s\n", p->ser_ctrl->serdev->modalias);
		}
		else printk(KERN_INFO "mikrobus_port->ser_ctrl->serdev is NULL\n");
	}
	else printk(KERN_INFO "mikrobus_port->ser_ctrl is NULL\n");

	printk(KERN_INFO "mikrobus_port: name = %s\n", p->name);
	printk(KERN_INFO "mikrobus_port: *pinctrl_selected[%d] = %s\n",
		MIKROBUS_NUM_PINCTRL_STATE, p->pinctrl_selected[MIKROBUS_NUM_PINCTRL_STATE]);
	printk(KERN_INFO "mikrobus_port: chip_select[%d] = %u\n",
		MIKROBUS_NUM_CS, p->chip_select[MIKROBUS_NUM_CS]);
	printk(KERN_INFO "mikrobus_port: id = %d\n", p->id);

	printk(KERN_INFO "--- end show_mikrobus_port() ---\n");
}

void show_mikrobus_device(
			struct i2c_board_info *i2c,
			struct spi_device *spi,
			struct serdev_device *serdev,
			struct platform_device *pdev,
			char *devname)
{
	printk(KERN_INFO "--- show_mikrobus_device() ---\n");
	// struct i2c_board_info *i2c;
	if (NULL != i2c) {
		printk(KERN_INFO "mikrobus_device: i2c_board_info[type] = %s\n", i2c->type);
		printk(KERN_INFO "mikrobus_device: i2c_board_info[addr] = %u\n", i2c->addr);
		// printk(KERN_INFO "mikrobus_device: i2c_board_info[dev_name] = %s\n", i2c->dev_name);
		printk(KERN_INFO "mikrobus_device: i2c_board_info[num_resources] = %u\n", i2c->num_resources);
		printk(KERN_INFO "mikrobus_device: i2c_board_info[irq] = %d\n", i2c->irq);
	} else printk(KERN_INFO "mikrobus_device: i2c is NULL\n");

	// struct spi_device *spi;
	if (NULL != spi) {
		printk(KERN_INFO "mikrobus_device: spi_device[max_speed_hz] = %u\n", spi->max_speed_hz);
		printk(KERN_INFO "mikrobus_device: spi_device[chip_select] = %u\n", spi->chip_select);
		printk(KERN_INFO "mikrobus_device: spi_device[bits_per_word] = %u\n", spi->bits_per_word);
		printk(KERN_INFO "mikrobus_device: spi_device[mode] = %u\n", spi->mode);
		printk(KERN_INFO "mikrobus_device: spi_device[irq] = %d\n", spi->irq);
		printk(KERN_INFO "mikrobus_device: spi_device[modalias] = %s\n", spi->modalias);
		/* Driver name to force a match */
		printk(KERN_INFO "mikrobus_device: spi_device[*driver_override] = %s\n", spi->driver_override);
		printk(KERN_INFO "mikrobus_device: spi_device[cs_gpio] = %d\n", spi->cs_gpio);
	} else printk(KERN_INFO "mikrobus_device: spi is NULL\n");

	// struct serdev_device *serdev;
	if (NULL != serdev) {
		printk(KERN_INFO "mikrobus_device: serdev_device[nr] = %d\n", serdev->nr);
		printk(KERN_INFO "mikrobus_device: serdev_device[modalias] = %s\n", serdev->modalias);
	}
	else printk(KERN_INFO "mikrobus_device: serdev is NULL\n");

	// struct platform_device *pdev;
	if (NULL != pdev) {
		printk(KERN_INFO "mikrobus_device: platform_device[name] = %s\n", pdev->name);
		printk(KERN_INFO "mikrobus_device: platform_device[id] = %d\n", pdev->id);
		printk(KERN_INFO "mikrobus_device: platform_device[num_resources] = %u\n", pdev->num_resources);
		/* Driver name to force a match */
		printk(KERN_INFO "mikrobus_device: platform_device[*driver_override] = %s\n", pdev->driver_override);
	} else printk(KERN_INFO "mikrobus_device: pdev is NULL\n");

	printk(KERN_INFO "mikrobus_device: devname[MIKROBUS_NAME_SIZE] = %s\n", devname);

	printk(KERN_INFO "--- end show_mikrobus_device() ---\n");
}

void show_mikrobus_device_type(int protocol, void *p)
{
	struct i2c_board_info *i2c;
	struct spi_device *spi;
	struct serdev_device *serdev;
	struct platform_device *pdev;

	printk(KERN_INFO "--- show_mikrobus_device_type() ---\n");

	switch (protocol) {
		case GREYBUS_PROTOCOL_I2C:
			// struct i2c_board_info *i2c;
			i2c = (struct i2c_board_info *)p;
			printk(KERN_INFO "mikrobus_device: i2c_board_info[type] = %s\n", i2c->type);
			printk(KERN_INFO "mikrobus_device: i2c_board_info[addr] = %u\n", i2c->addr);
			// printk(KERN_INFO "mikrobus_device: i2c_board_info[dev_name] = %s\n", i2c->dev_name);
			printk(KERN_INFO "mikrobus_device: i2c_board_info[num_resources] = %u\n", i2c->num_resources);
			printk(KERN_INFO "mikrobus_device: i2c_board_info[irq] = %d\n", i2c->irq);
			break;
		case  GREYBUS_PROTOCOL_SPI:
			// struct spi_device *spi;
			spi = (struct spi_device *)p;
			printk(KERN_INFO "mikrobus_device: spi_device[max_speed_hz] = %u\n", spi->max_speed_hz);
			printk(KERN_INFO "mikrobus_device: spi_device[chip_select] = %u\n", spi->chip_select);
			printk(KERN_INFO "mikrobus_device: spi_device[bits_per_word] = %u\n", spi->bits_per_word);
			printk(KERN_INFO "mikrobus_device: spi_device[mode] = %u\n", spi->mode);
			printk(KERN_INFO "mikrobus_device: spi_device[irq] = %d\n", spi->irq);
			printk(KERN_INFO "mikrobus_device: spi_device[modalias] = %s\n", spi->modalias);
			/* Driver name to force a match */
			printk(KERN_INFO "mikrobus_device: spi_device[*driver_override] = %s\n", spi->driver_override);
			printk(KERN_INFO "mikrobus_device: spi_device[cs_gpio] = %d\n", spi->cs_gpio);
			break;
		case  GREYBUS_PROTOCOL_UART:
			// struct serdev_device *serdev;
			serdev = (struct serdev_device *)p;
			printk(KERN_INFO "mikrobus_device: serdev_device[nr] = %d\n", serdev->nr);
			printk(KERN_INFO "mikrobus_device: serdev_device[modalias] = %s\n", serdev->modalias);
			break;
		case  GREYBUS_PROTOCOL_RAW:
			// struct platform_device *pdev;
			pdev = (struct platform_device *)p;
			printk(KERN_INFO "mikrobus_device: platform_device[name] = %s\n", pdev->name);
			printk(KERN_INFO "mikrobus_device: platform_device[id] = %d\n", pdev->id);
			printk(KERN_INFO "mikrobus_device: platform_device[num_resources] = %u\n", pdev->num_resources);
			/* Driver name to force a match */
			printk(KERN_INFO "mikrobus_device: platform_device[*driver_override] = %s\n", pdev->driver_override);
			break;
		default:
			printk(KERN_INFO "mikrobus_device: UNKNOWN DEVICE TYPE!\n");
			break;
	}
	printk(KERN_INFO "--- end show_mikrobus_device_type() ---\n");
}

void show_device_name(char *devname) {
	printk(KERN_DEBUG "char devname[MIKROBUS_NAME_SIZE = %d] = %s\n", MIKROBUS_NAME_SIZE, devname);
}

void show_greybus_descriptor_device(struct greybus_descriptor_device *p)
{
	printk(KERN_INFO "--- show_greybus_descriptor_device() ---\n");
	printk(KERN_INFO "greybus_descriptor_device: id = %u\n", p->id);
	printk(KERN_INFO "greybus_descriptor_device: driver_stringid = %u\n", p->driver_stringid);
	printk(KERN_INFO "greybus_descriptor_device: protocol = %u, protocol string = %s\n", p->protocol, greybus_protocol_string[p->protocol]);
	printk(KERN_INFO "greybus_descriptor_device: protocol string = %s\n", greybus_protocol_string[p->protocol]);
	printk(KERN_INFO "greybus_descriptor_device: reg = %u\n", p->reg);
	printk(KERN_INFO "greybus_descriptor_device: max_speed_hz = %u\n", p->max_speed_hz);
	printk(KERN_INFO "greybus_descriptor_device: irq = %u\n", p->irq);
	printk(KERN_INFO "greybus_descriptor_device: irq_type = %u\n", p->irq_type);
	printk(KERN_INFO "greybus_descriptor_device: mode = %u\n", p->mode);
	printk(KERN_INFO "greybus_descriptor_device: prop_link = %u\n", p->prop_link);
	printk(KERN_INFO "greybus_descriptor_device: gpio_link = %u\n", p->gpio_link);
	printk(KERN_INFO "greybus_descriptor_device: reg_link = %u\n", p->reg_link);
	printk(KERN_INFO "greybus_descriptor_device: clock_link = %u\n", p->clock_link);
	printk(KERN_INFO "--- end show_greybus_descriptor_device() ---\n");
}

void show_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *p)
{
	int	i;

	printk(KERN_INFO "--- show_greybus_descriptor_mikrobus() ---\n");
	for(i = 0; i < MIKROBUS_PORT_PIN_COUNT; ++i)
		printk(KERN_INFO "greybus_descriptor_mikrobus: pin_state[%d] = %u, pin_state_string[%d] = %s\n", i, p->pin_state[i], i, mikrobus_pin_string[i]);
	printk(KERN_INFO "--- end show_greybus_descriptor_mikrobus() ---\n");
}
