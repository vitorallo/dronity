/*
 * SYSCALL_DEFINE2(setns, int, fd, int, nstype)
 */
#include <sched.h>
#include "sanitise.h"

//fix missing def in case... androdi 19
#ifndef CLONE_NEWUTS
#define CLONE_NEWUTS 0x04000000
#define CLONE_NEWIPC 0x08000000
#define CLONE_NEWNET 0x40000000
#endif


struct syscallentry syscall_setns= {
	.name = "setns",
	.num_args = 2,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "nstype",
	.arg2type = ARG_LIST,
	.arg2list = {
		.num = 4,
		.values = { 0, CLONE_NEWIPC, CLONE_NEWNET, CLONE_NEWUTS, },
	},
	.flags = NEED_ALARM,
};
