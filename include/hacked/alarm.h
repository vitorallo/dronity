/*
 * alarm.h
 *
 *  Created on: Dec 5, 2014
 *      Author: vito
 */

#include "config.h"

#ifndef KERNELHEADERS_HACKED_ALARM_H_



/* support for compat */



#define KERNELHEADERS_HACKED_ALARM_H_

#ifdef CONFIG_COMPAT

#include "hacked/compat.h"

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

#endif

#endif /* KERNELHEADERS_HACKED_ALARM_H_ */
