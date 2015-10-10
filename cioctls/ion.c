#include <unistd.h>  /* size_t */
#include <hacked/ion.h>
#include <linux/ioctl.h>
#include "trinity.h"
#include "ioctls.h"
#include "utils.h"
#include "config.h"

static const struct ioctl ion_ioctls[] = {
	IOCTL(ION_IOC_ALLOC),
        IOCTL(ION_IOC_FREE),
        IOCTL(ION_IOC_SHARE),
	IOCTL(ION_IOC_MAP),
        IOCTL(ION_IOC_IMPORT),
        IOCTL(ION_IOC_SYNC),
        IOCTL(ION_IOC_CUSTOM),
#ifdef CONFIG_COMPAT
		IOCTL(COMPAT_ION_IOC_ALLOC),
		IOCTL(COMPAT_ION_IOC_FREE),
		IOCTL(COMPAT_ION_IOC_CUSTOM),
#endif
};

static const char *const ion_devs[] = {
        "ion",
};

static const struct ioctl_group ion_grp = {
		.name = "ion",
        .devtype = DEV_MISC,
        .devs = ion_devs,
        .devs_cnt = ARRAY_SIZE(ion_devs),
        .sanitise = pick_random_ioctl,
        .ioctls = ion_ioctls,
        .ioctls_cnt = ARRAY_SIZE(ion_ioctls),
};

REG_IOCTL_GROUP(ion_grp)
