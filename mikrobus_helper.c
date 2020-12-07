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

void print_board_device_info(struct board_device_info *pboard)
{
	printk(KERN_INFO "board_device_info: num_gpio_resources = %u\n", pboard->num_gpio_resources);
	printk(KERN_INFO "board_device_info: num_properties = %u\n", pboard->num_properties);
	printk(KERN_INFO "board_device_info: num_regulators = %u\n", pboard->num_regulators);
	printk(KERN_INFO "board_device_info: num_clocks = %u\n", pboard->num_clocks);
	printk(KERN_INFO "board_device_info: protocol = %u\n", pboard->protocol);
	printk(KERN_INFO "board_device_info: mode = %d\n", pboard->mode);
	printk(KERN_INFO "board_device_info: max_speed_hz = %u\n", pboard->max_speed_hz);
	printk(KERN_INFO "board_device_info: *drv_name = %s\n", pboard->drv_name);
	printk(KERN_INFO "board_device_info: irq_type = %d\n", pboard->irq_type);
	printk(KERN_INFO "board_device_info: irq = %d\n", pboard->irq);
	printk(KERN_INFO "board_device_info: id = %d\n", pboard->id);
}

void print_addon_board_info(struct addon_board_info *paddon)
{
	int	i;

	for(i = 0; i < MIKROBUS_PORT_PIN_COUNT; ++i)
		printk(KERN_INFO "addon_board_info: pin_state[%d] = %u\n", i, paddon->pin_state[i]);

	printk(KERN_INFO "addon_board_info: *name = %s\n", paddon->name);
}

void print_mikrobus_port(struct mikrobus_port *pmikrobus)
{
	printk(KERN_INFO "mikrobus_port: name = %s\n", pmikrobus->name);
	printk(KERN_INFO "mikrobus_port: *pinctrl_selected[%d] = %s\n",
		MIKROBUS_NUM_PINCTRL_STATE, pmikrobus->pinctrl_selected[MIKROBUS_NUM_PINCTRL_STATE]);
	printk(KERN_INFO "mikrobus_port: chip_select[%d] = %u\n",
		MIKROBUS_NUM_CS, pmikrobus->chip_select[MIKROBUS_NUM_CS]);
	printk(KERN_INFO "mikrobus_port: id = %d\n", pmikrobus->id);
}

void print_greybus_descriptor_device(struct greybus_descriptor_device *pgbddev)
{
	printk(KERN_INFO "greybus_descriptor_device: id = %u\n", pgbddev->id);
	printk(KERN_INFO "greybus_descriptor_device: driver_stringid = %u\n", pgbddev->driver_stringid);
	printk(KERN_INFO "greybus_descriptor_device: protocol = %u\n", pgbddev->protocol);
	printk(KERN_INFO "greybus_descriptor_device: reg = %u\n", pgbddev->reg);
	printk(KERN_INFO "greybus_descriptor_device: max_speed_hz = %u\n", pgbddev->max_speed_hz);
	printk(KERN_INFO "greybus_descriptor_device: irq = %u\n", pgbddev->irq);
	printk(KERN_INFO "greybus_descriptor_device: irq_type = %u\n", pgbddev->irq_type);
	printk(KERN_INFO "greybus_descriptor_device: mode = %u\n", pgbddev->mode);
	printk(KERN_INFO "greybus_descriptor_device: prop_link = %u\n", pgbddev->prop_link);
	printk(KERN_INFO "greybus_descriptor_device: gpio_link = %u\n", pgbddev->gpio_link);
	printk(KERN_INFO "greybus_descriptor_device: reg_link = %u\n", pgbddev->reg_link);
	printk(KERN_INFO "greybus_descriptor_device: clock_link = %u\n", pgbddev->clock_link);
}

void print_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *pgbdmbus)
{
	int	i;

	for(i = 0; i < MIKROBUS_PORT_PIN_COUNT; ++i)
		printk(KERN_INFO "greybus_descriptor_mikrobus: pin_state[%d] = %u\n", i, pgbdmbus->pin_state[i]);
}
