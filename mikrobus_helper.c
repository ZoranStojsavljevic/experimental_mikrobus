/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mikroBUS helper.c for code tracing
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
	printk(KERN_INFO "mikrobus_port: name = %s\n", p->name);
	printk(KERN_INFO "mikrobus_port: *pinctrl_selected[%d] = %s\n",
		MIKROBUS_NUM_PINCTRL_STATE, p->pinctrl_selected[MIKROBUS_NUM_PINCTRL_STATE]);
	printk(KERN_INFO "mikrobus_port: chip_select[%d] = %u\n",
		MIKROBUS_NUM_CS, p->chip_select[MIKROBUS_NUM_CS]);
	printk(KERN_INFO "mikrobus_port: id = %d\n", p->id);
	printk(KERN_INFO "--- end show_mikrobus_port() ---\n");
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
