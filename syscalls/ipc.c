/*
 * SYSCALL_DEFINE6(ipc, unsigned int, call, int, first, unsigned long, second,
                  unsigned long, third, void __user *, ptr, long, fifth)
 */
#include <linux/ipc.h>
#include "sanitise.h"

//fix missing def in android19
#ifndef SEMOP
#define SEMOP 1
#define SEMGET 2
#define SEMCTL 3
#define SEMTIMEDOP 4
#define MSGSND 11
#define MSGRCV 12
#define MSGGET 13
#define MSGCTL 14
#define SHMAT 21
#define SHMDT 22
#define SHMGET 23
#define SHMCTL 24
#endif

struct syscallentry syscall_ipc = {
	.name = "ipc",
	.num_args = 6,
	.arg1name = "call",
	.arg1type = ARG_OP,
	.arg1list = {
		.num = 12,
		.values = {
			SEMOP, SEMGET, SEMCTL, SEMTIMEDOP,
			MSGSND, MSGRCV, MSGGET, MSGCTL,
			SHMAT, SHMDT, SHMGET, SHMCTL,
		},
	},
	.arg2name = "first",
	.arg3name = "second",
	.arg4name = "third",
	.arg5name = "ptr",
	.arg5type = ARG_ADDRESS,
	.arg6name = "fifth",
	.flags = IGNORE_ENOSYS,
};
