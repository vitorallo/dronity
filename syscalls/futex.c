/*
 * SYSCALL_DEFINE6(futex, u32 __user *, uaddr, int, op, u32, val,
	 struct timespec __user *, utime, u32 __user *, uaddr2, u32, val3)
 */

//trying to fix missing def with android19
#ifndef FUTEX_WAIT_BITSET
#define FUTEX_WAIT_BITSET 9
#define FUTEX_WAKE_BITSET 10
#define FUTEX_WAIT_REQUEUE_PI 11 
#define FUTEX_CMP_REQUEUE_PI 12
//defining this macro AGAIN?! cause it's not known in android 19 and the futex.h cannot define untrusted pointers correctly
# define __user         __attribute__((noderef, address_space(1)))
#endif

#include <linux/futex.h>
#include "sanitise.h"

struct syscallentry syscall_futex = {
	.name = "futex",
	.num_args = 6,
	.arg1name = "uaddr",
	.arg1type = ARG_ADDRESS,
	.arg2name = "op",
	.arg2type = ARG_OP,
	.arg2list = {
		.num = 13,
		.values = { FUTEX_WAIT, FUTEX_WAKE, FUTEX_FD, FUTEX_REQUEUE,
			FUTEX_CMP_REQUEUE, FUTEX_WAKE_OP, FUTEX_LOCK_PI, FUTEX_UNLOCK_PI,
			FUTEX_TRYLOCK_PI, FUTEX_WAIT_BITSET, FUTEX_WAKE_BITSET, FUTEX_WAIT_REQUEUE_PI,
			FUTEX_CMP_REQUEUE_PI,
		},
	},
	.arg3name = "val",
	.arg4name = "utime",
	.arg4type = ARG_ADDRESS,
	.arg5name = "uaddr2",
	.arg5type = ARG_ADDRESS,
	.arg6name = "val3",
	.rettype = RET_FD,		// FIXME: Needs to mutate depending on 'op' value
	.flags = NEED_ALARM | IGNORE_ENOSYS,
};
