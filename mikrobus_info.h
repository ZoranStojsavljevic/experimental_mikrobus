/* SPDX-License-Identifier: GPL-2.0 */
/*
 * MikroBUS: mikrobus_info.h for data tracing
 *
 * Copyright 2020 Zoran Stojsavljevic (zoran.stojsavljevic@gmail.com)
 */

#ifndef __MIKROBUS_INFO_H
#define __MIKROBUS_INFO_H

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

#define MIKROBUS_DEBUG 0

#if MIKROBUS_DEBUG
inline void trace_mikrobus_port_scan_eeprom(void);
inline void trace_mikrobus_device_register(void);
inline void trace_mikrobus_port_probe(void);
inline void trace_mikrobus_port_register(void);
inline void trace_mikrobus_manifest_parse_devices(void);
#else
static inline void trace_mikrobus_port_scan_eeprom(void) {}
static inline void trace_mikrobus_device_register(void) {}
static inline void trace_mikrobus_port_probe(void) {}
static inline void trace_mikrobus_port_register(void) {}
static inline void trace_mikrobus_manifest_parse_devices(void) {}
#endif

#if MIKROBUS_DEBUG
// mikrobus core data structures
void show_board_device_info(struct board_device_info *);
void show_addon_board_info(struct addon_board_info *);
void show_mikrobus_port(struct mikrobus_port *);
void show_mikrobus_device(
			struct i2c_board_info	*,
			struct spi_device	*,
			struct serdev_device	*,
			struct platform_device	*,
			char			*
			);
void show_mikrobus_device_type(int, void *);
void show_device_name(char *);

// mikrobus manifest data structures
void show_greybus_descriptor_device(struct greybus_descriptor_device *);
void show_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *);
#else
// mikrobus core dummy data structures
static inline void show_board_device_info(struct board_device_info *p) {}
static inline void show_addon_board_info(struct addon_board_info *p) {}
static inline void show_mikrobus_port(struct mikrobus_port *p) {}
static inline void show_mikrobus_device(
					struct	i2c_board_info	*p1,
					struct	spi_device	*p2,
					struct	serdev_device	*p3,
					struct	platform_device	*p4,
					char			*p5
					) {}
static inline void show_mikrobus_device_type(int protocol, void *p) {}
static inline void show_device_name(char *p) {}

// mikrobus manifest dummy data structures
static inline void show_greybus_descriptor_device(struct greybus_descriptor_device *p) {}
static inline void show_greybus_descriptor_mikrobus(struct greybus_descriptor_mikrobus *p) {}
#endif

#endif /* __MIKROBUS_INFO_H */
