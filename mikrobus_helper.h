/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mikroBUS helper.h for code tracing
 *
 * Copyright 2020 Zoran Stojsavljevic (zoran.stojsavljevic@gmail.com)
 */

#ifndef __MIKROBUS_HELPER_H
#define __MIKROBUS_HELPER_H

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

#define MIKROBUS_DEBUG 1

#if MIKROBUS_DEBUG
// mikrobus core data structures
void print_board_device_info(struct board_device_info *pboard);
void print_addon_board_info(struct addon_board_info *paddon);
void print_mikrobus_port(struct mikrobus_port *pmikrobus);

// mikrobus manifest data structures
void print_greybus_descriptor_device(struct greybus_descriptor_device *pgbddev);
void print_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *pgbdmbus);
# else
// mikrobus core dunmmy data structures
static inline void print_board_device_info(struct board_device_info *pboard) {}
static inline void print_addon_board_info(struct addon_board_info *paddon) {}
static inline void print_mikrobus_port(struct mikrobus_port *pmikrobus) {}

// mikrobus manifest dummy data structures
static inline void print_greybus_descriptor_device(struct greybus_descriptor_device *pgbddev) {}
static inline void print_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *pgbdmbus) {}
# endif

#endif /* __MIKROBUS_HELPER_H */
