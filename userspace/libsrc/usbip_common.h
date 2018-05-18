/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#ifndef _USBIP_COMMON_H
#define _USBIP_COMMON_H

#include <stdint.h>
#include <stdio.h>

#ifndef USBIDS_FILE
#define USBIDS_FILE "/usr/share/hwdata/usb.ids"
#endif

#ifndef VHCI_STATE_PATH
#define VHCI_STATE_PATH "/var/run/vhci_hcd"
#endif

/* kernel module names */
#define USBIP_CORE_MOD_NAME	"usbip-core"
#define USBIP_HOST_DRV_NAME	"usbip-host"
#define USBIP_VHCI_DRV_NAME	"vhci_hcd"

/* FIXME: how to sync with drivers/usbip_common.h ? */
enum usbip_device_status{
	/* sdev is available. */
	SDEV_ST_AVAILABLE = 0x01,
	/* sdev is now used. */
	SDEV_ST_USED,
	/* sdev is unusable because of a fatal error. */
	SDEV_ST_ERROR,

	/* vdev does not connect a remote device. */
	VDEV_ST_NULL,
	/* vdev is used, but the USB address is not assigned yet */
	VDEV_ST_NOTASSIGNED,
	VDEV_ST_USED,
	VDEV_ST_ERROR
};

#define USBIP_DEV_PATH_MAX		256
#define USBIP_BUS_ID_SIZE		32

extern int usbip_use_stderr;
extern int usbip_use_debug ;

#define PROGNAME	"usbip"

#define err(fmt, ...)	do { \
	if (usbip_use_stderr) { \
		fprintf(stderr, "usbip err: %13s:%4d (%-12s) " fmt "\n", \
		__FILE__, __LINE__, __FUNCTION__,  ##__VA_ARGS__); \
	} \
} while (0)

#define notice(fmt, ...)	do { \
	if (usbip_use_stderr) { \
		fprintf(stderr, "usbip: " fmt "\n", ##__VA_ARGS__); \
	} \
} while (0)

#define info(fmt, ...)	do { \
	if (usbip_use_stderr) { \
		fprintf(stderr, fmt "\n", ##__VA_ARGS__); \
	} \
} while (0)

#define dbg(fmt, ...)	do { \
	if (usbip_use_debug) { \
		if (usbip_use_stderr) { \
			fprintf(stderr, "usbip dbg: %13s:%4d (%-12s) " fmt "\n", \
				__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
		} \
	} \
} while (0)

#define BUG()	do { err("sorry, it's a bug"); abort(); } while (0)

#pragma pack(push, 1)

struct usbip_usb_interface {
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t padding;	/* alignment */
};

struct usbip_usb_device {
	char path[USBIP_DEV_PATH_MAX];
	char busid[USBIP_BUS_ID_SIZE];

	uint32_t busnum;
	uint32_t devnum;
	uint32_t speed;

	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;

	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bConfigurationValue;
	uint8_t bNumConfigurations;
	uint8_t bNumInterfaces;
};

#pragma pack(pop)

#define to_string(s)	#s

void dump_usb_interface(struct usbip_usb_interface *);
void dump_usb_device(struct usbip_usb_device *);

const char *usbip_speed_string(int num);
const char *usbip_status_string(int32_t status);

int usbip_names_init(char *);
void usbip_names_free(void);
void usbip_names_get_product(char *buff, size_t size, uint16_t vendor, uint16_t product);
void usbip_names_get_class(char *buff, size_t size, uint8_t class, uint8_t subclass, uint8_t protocol);

#endif
