/*
 * SYSCALL_DEFINE3(ioctl, unsigned int, fd, unsigned int, cmd, unsigned long, arg)
 */
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/major.h>
#include "ioctls.h"
#include "maps.h"
#include "random.h"
#include "sanitise.h"
#include "shm.h"
#include "syscall.h"
#include "trinity.h"
#include "log.h"
#include "params.h"

static void ioctl_mangle_cmd(struct syscallrecord *rec)
{
	unsigned int i;

	/* mangle the cmd by ORing up to 4 random bits */
	for (i=0; i < (unsigned int)(rand() % 4); i++)
		rec->a2 |= 1L << (rand() % 32);

	/* mangle the cmd by ANDing up to 4 random bits */
	for (i=0; i < (unsigned int)(rand() % 4); i++)
		rec->a2 &= 1L << (rand() % 32);
}

static void ioctl_mangle_arg(struct syscallrecord *rec)
{
	/* the argument could mean anything, because ioctl sucks like that. */
	if (rand_bool())
		rec->a3 = rand32();
	else
		rec->a3 = (unsigned long) get_non_null_address();
}

static void ioctl_fixed_arg(struct syscallrecord *rec)
{
	/* this meanse we don't want to fuzz but choose a fixed page for arg. only deadbeaf at the moment */
	//unsigned long *p=(unsigned long*)deadbeef(64);
	//printf("0x%lx\n",p[1]);
	rec->a3 = deadbeef(64); //the size should be handled better!!!
}

static void generic_sanitise_ioctl(struct syscallrecord *rec)
{
	if ((rand() % 50)==0)
		ioctl_mangle_cmd(rec);

	if (!fixed_arg) ioctl_mangle_arg(rec); // mangle arg randomly only if fixed arg is not requested
			else ioctl_fixed_arg(rec);
}

static void sanitise_ioctl(struct syscallrecord *rec)
{
	const struct ioctl_group *grp;

	/* FIXME: investigate possible bug
	 * found a bug in this function, when going random and hitting the else, branching
	 * to find_ioctl_group(rec->a1) this will return most of the time null, even if the device
	 * is there, cause when we specify the target i.e. -V /dev/binder the fd is never found in the
	 * list of if (strcmp(devname, grps[i]->devs[j]) == 0) devices defined in _devs[] array, unless
	 * it does hit a dev defined with the full name like /dev/tty (suppose). Never works with /dev/binder
	 * did "lucky" branching test and it worked :(
	 */

	if (ioctlgroup==NULL) {
		if (rand() % 100 == 0)
			grp = get_random_ioctl_group();
		else
			grp = find_ioctl_group(rec->a1);
	} else {
		// we have a group to work with
		grp = find_ioctl_group_by_name(ioctlgroup);
		if (!grp) output (0,"** invalid group specified (check name with -I), bail back to random\n");
			//else output (0,"selected group: %s\n",grp->name);
	}

	if (grp)
	{
		if (!fixed_arg) ioctl_mangle_arg(rec); // mangle arg randomly only if fixed arg is not requested
		else ioctl_fixed_arg(rec);
		grp->sanitise(grp, rec); // pick a random ioctl from the group defined in the driver .sanitise = pick_random_ioctl
		if (rand() % 100 == 0) // in one real rare case only mangle cmd
			ioctl_mangle_cmd(rec);
		grp->sanitise(grp, rec);

	} else
		generic_sanitise_ioctl(rec); //otherwise do mangle generically both
}

struct syscallentry syscall_ioctl = {
	.name = "ioctl",
	.num_args = 3,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "cmd",
	.arg3name = "arg",
	.sanitise = sanitise_ioctl,
	.flags = NEED_ALARM | IGNORE_ENOSYS,
};
