/*
 * media.h
 *
 *  Created on: Dec 4, 2014
 *      Author: vito rallo
 */

#include <types.h>

#ifndef KERNELHEADERS_HACKED_MEDIA_H_

struct media_device_info {
	char driver[16];
	char model[32];
	char serial[40];
	char bus_info[32];
	__u32 media_version;
	__u32 hw_revision;
	__u32 driver_version;
	__u32 reserved[31];
};


struct media_entity_desc {
	__u32 id;
	char name[32];
	__u32 type;
	__u32 revision;
	__u32 flags;
	__u32 group_id;
	__u16 pads;
	__u16 links;

	__u32 reserved[4];

	union {
		/* Node specifications */
		struct {
			__u32 major;
			__u32 minor;
		} v4l;
		struct {
			__u32 major;
			__u32 minor;
		} fb;
		struct {
			__u32 card;
			__u32 device;
			__u32 subdevice;
		} alsa;
		int dvb;

		/* Sub-device specifications */
		/* Nothing needed yet */
		__u8 raw[184];
	};
};

#define MEDIA_PAD_FL_SINK		(1 << 0)
#define MEDIA_PAD_FL_SOURCE		(1 << 1)

struct media_pad_desc {
	__u32 entity;		/* entity ID */
	__u16 index;		/* pad index */
	__u32 flags;		/* pad flags */
	__u32 reserved[2];
};

#define MEDIA_LNK_FL_ENABLED		(1 << 0)
#define MEDIA_LNK_FL_IMMUTABLE		(1 << 1)
#define MEDIA_LNK_FL_DYNAMIC		(1 << 2)

struct media_link_desc {
	struct media_pad_desc source;
	struct media_pad_desc sink;
	__u32 flags;
	__u32 reserved[2];
};

struct media_links_enum {
	__u32 entity;
	/* Should have enough room for pads elements */
	struct media_pad_desc __user *pads;
	/* Should have enough room for links elements */
	struct media_link_desc __user *links;
	__u32 reserved[4];
};

#define MEDIA_IOC_DEVICE_INFO		_IOWR('|', 0x00, struct media_device_info)
#define MEDIA_IOC_ENUM_ENTITIES		_IOWR('|', 0x01, struct media_entity_desc)
#define MEDIA_IOC_ENUM_LINKS		_IOWR('|', 0x02, struct media_links_enum)
#define MEDIA_IOC_SETUP_LINK		_IOWR('|', 0x03, struct media_link_desc)

#define KERNELHEADERS_HACKED_MEDIA_H_



#endif /* KERNELHEADERS_HACKED_MEDIA_H_ */
