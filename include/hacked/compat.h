/*
 * compat.h
 *
 * compat data types extracted from kernel intl-ll64.h, arm64/include/asm/compat.h
 * to be included in dronity ioctl drivers headers
 * DO NOT INCLUDE IT DIRECTLY unless you know what you do
 *
 *  Created on: Dec 4, 2014
 *      Author: vito rallo
 */

#ifndef KERNELHEADERS_HACKED_COMPAT_H_
#include "types.h"

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
//typedef unsigned long long u64; double definition of u64, shit!!


typedef u32		compat_size_t;
typedef s32		compat_ssize_t;
typedef s32		compat_time_t;
typedef s32		compat_clock_t;
typedef s32		compat_pid_t;
typedef u32		__compat_uid_t;
typedef u32		__compat_gid_t;
typedef u16		__compat_uid16_t;
typedef u16		__compat_gid16_t;
typedef u32		__compat_uid32_t;
typedef u32		__compat_gid32_t;
typedef u16		compat_mode_t;
typedef u32		compat_ino_t;
typedef u32		compat_dev_t;
typedef s32		compat_off_t;
typedef s64		compat_loff_t;
typedef s32		compat_nlink_t;
typedef u16		compat_ipc_pid_t;
typedef s32		compat_daddr_t;
typedef u32		compat_caddr_t;
typedef __kernel_fsid_t	compat_fsid_t;
typedef s32		compat_key_t;
typedef s32		compat_timer_t;

typedef s16		compat_short_t;
typedef s32		compat_int_t;
typedef s32		compat_long_t;
typedef s64		compat_s64;
typedef u16		compat_ushort_t;
typedef u32		compat_uint_t;
typedef u32		compat_ulong_t;
typedef u64		compat_u64;
typedef u32		compat_uptr_t;

//used only alarm.h
struct compat_timespec {
	compat_time_t	tv_sec;
	s32		tv_nsec;
};

#define KERNELHEADERS_HACKED_COMPAT_H_



#endif /* KERNELHEADERS_HACKED_COMPAT_H_ */
