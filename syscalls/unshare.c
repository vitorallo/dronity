/*
 * SYSCALL_DEFINE1(unshare, unsigned long, unshare_flags)
 */
#include <linux/sched.h>
#include "sanitise.h"

//fix missing def in case... androdi 19
#ifndef CLONE_NEWUTS
#define CLONE_NEWUTS 0x04000000
#define CLONE_NEWIPC 0x08000000
#define CLONE_NEWUSER 0x10000000
#define CLONE_NEWPID 0x20000000
#define CLONE_NEWNET 0x40000000
#define CLONE_IO 0x80000000
#endif


struct syscallentry syscall_unshare = {
	.name = "unshare",
	.num_args = 1,
	.arg1name = "unshare_flags",
	.arg1type = ARG_LIST,
	.arg1list = {
		.num = 12,
		.values = { CLONE_THREAD, CLONE_FS, CLONE_NEWNS, CLONE_SIGHAND,
			    CLONE_VM, CLONE_FILES, CLONE_SYSVSEM, CLONE_NEWUTS,
			    CLONE_NEWIPC, CLONE_NEWNET, CLONE_NEWUSER, CLONE_NEWPID,
		},
	},
};
