/*
 * alarm.c
 *
 *  Created on: Dec 5, 2014
 *      Author: vito
 */

#include "config.h"
#include "trinity.h"
#include "ioctls.h"
#include "hacked/alarm.h"
#include "utils.h"
#include <linux/ioctl.h>
#include <linux/android_alarm.h>


/*
ANDROID_ALARM_CLEAR(type) _IO('a', 0 | ((type) << 4))
#define ANDROID_ALARM_WAIT _IO('a', 1)
#define ALARM_IOW(c, type, size) _IOW('a', (c) | ((type) << 4), size)
#define ANDROID_ALARM_SET(type) ALARM_IOW(2, type, struct timespec)
#define ANDROID_ALARM_SET_AND_WAIT(type) ALARM_IOW(3, type, struct timespec)
#define ANDROID_ALARM_GET_TIME(type) ALARM_IOW(4, type, struct timespec)
#define ANDROID_ALARM_SET_RTC _IOW('a', 5, struct timespec)
#define ANDROID_ALARM_BASE_CMD(cmd) (cmd & ~(_IOC(0, 0, 0xf0, 0)))
#define ANDROID_ALARM_IOCTL_TO_TYPE

#define ANDROID_ALARM_SET_COMPAT(type)		ALARM_IOW(2, type, \
							struct compat_timespec)
#define ANDROID_ALARM_SET_AND_WAIT_COMPAT(type)	ALARM_IOW(3, type, \
							struct compat_timespec)
#define ANDROID_ALARM_GET_TIME_COMPAT(type)	ALARM_IOW(4, type, \
							struct compat_timespec)
#define ANDROID_ALARM_SET_RTC_COMPAT		_IOW('a', 5, \
							struct compat_timespec)
#define ANDROID_ALARM_IOCTL_NR(cmd)		(_IOC_NR(cmd) & ((1<<4)-1))
#define ANDROID_ALARM_COMPAT_TO_NORM(cmd)  \
				ALARM_IOW(ANDROID_ALARM_IOCTL_NR(cmd), \
					ANDROID_ALARM_IOCTL_TO_TYPE(cmd), \
					struct timespec)
*/

static const struct ioctl alarm_ioctls[] = {
        //IOCTL(ANDROID_ALARM_CLEAR(type)),
        IOCTL(ANDROID_ALARM_WAIT),
        //IOCTL(ALARM_IOW),
        //IOCTL(ANDROID_ALARM_SET),
        //IOCTL(ANDROID_ALARM_SET_AND_WAIT),
        //IOCTL(ANDROID_ALARM_GET_TIME),
        IOCTL(ANDROID_ALARM_SET_RTC),
        //IOCTL(ANDROID_ALARM_BASE_CMD(cmd)),
#ifdef CONFIG_COMPAT
		//IOCTL(ANDROID_ALARM_SET_COMPAT),
		//IOCTL(ANDROID_ALARM_SET_AND_WAIT_COMPAT),
		//IOCTL(ANDROID_ALARM_GET_TIME_COMPAT),
		IOCTL(ANDROID_ALARM_SET_RTC_COMPAT),
		//IOCTL(ANDROID_ALARM_IOCTL_NR),
#endif
};

static const char *const alarm_devs[] = {
        "alarm",
};

static const struct ioctl_group alarm_grp = {
		.name = "alarm",
        .devtype = DEV_MISC,
        .devs = alarm_devs,
        .devs_cnt = ARRAY_SIZE(alarm_devs),
        .sanitise = pick_random_ioctl,
        .ioctls = alarm_ioctls,
        .ioctls_cnt = ARRAY_SIZE(alarm_ioctls),
};

REG_IOCTL_GROUP(alarm_grp)

