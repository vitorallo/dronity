/*
 * ashmem.c
 *
 *  Created on: Dec 4, 2014
 *      Author: vito
 */

/* chose between compiler headers or hacked ones
#include <linux/ashmem.h>
*/

#include "config.h"
#include "trinity.h"
#include "ioctls.h"
#include "hacked/ashmem.h"
#include "utils.h"
#include <linux/ioctl.h>

static const struct ioctl ashmem_ioctls[] = {
        IOCTL(ASHMEM_SET_NAME),
        IOCTL(ASHMEM_GET_NAME),
        IOCTL(ASHMEM_SET_SIZE),
        IOCTL(ASHMEM_GET_SIZE),
        IOCTL(ASHMEM_SET_PROT_MASK),
        IOCTL(ASHMEM_GET_PROT_MASK),
        IOCTL(ASHMEM_PIN),
        IOCTL(ASHMEM_UNPIN),
        IOCTL(ASHMEM_GET_PIN_STATUS),
        IOCTL(ASHMEM_PURGE_ALL_CACHES),
#ifdef CONFIG_COMPAT
		IOCTL(COMPAT_ASHMEM_SET_SIZE),
		IOCTL(COMPAT_ASHMEM_SET_PROT_MASK),
#endif
};

static const char *const ashmem_devs[] = {
        "ashmem",
};

static const struct ioctl_group ashmem_grp = {
		.name = "ashmem",
        .devtype = DEV_MISC,
        .devs = ashmem_devs,
        .devs_cnt = ARRAY_SIZE(ashmem_devs),
        .sanitise = pick_random_ioctl,
        .ioctls = ashmem_ioctls,
        .ioctls_cnt = ARRAY_SIZE(ashmem_ioctls),
};

REG_IOCTL_GROUP(ashmem_grp)
