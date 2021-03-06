/*
 * SYSCALL_DEFINE5(prctl, int, option, unsigned long, arg2, unsigned long, arg3,
	 unsigned long, arg4, unsigned long, arg5)
 */
#include "config.h"

#include <stdlib.h>
#include <linux/prctl.h>
#ifdef USE_SECCOMP
#ifndef P21
#include "hacked/seccomp.h" //using local headers as they are not there in android 19
#else
#include "linux/seccomp.h"
#endif
#endif
#include <sys/prctl.h>
#include <sys/socket.h>

#include "net.h"
#include "maps.h"
#include "sanitise.h"
#include "shm.h"
#include "syscall.h"
#include "trinity.h"
#include "utils.h"
#include "compat.h"

//fixing missing def for android 19
#ifndef PR_CAPBSET_READ
#define PR_GET_SECCOMP 21
#define PR_SET_SECCOMP 22
#define PR_CAPBSET_READ 23
#define PR_CAPBSET_DROP 24
#define PR_GET_SECUREBITS 27
#define PR_SET_SECUREBITS 28
#define PR_MCE_KILL 33
#define PR_GET_TSC 25
#define PR_SET_TSC 26
#endif

#define NR_PRCTL_OPTS 36
static int prctl_opts[NR_PRCTL_OPTS] = {
	PR_CAPBSET_READ, PR_CAPBSET_DROP, PR_SET_DUMPABLE, PR_GET_DUMPABLE,
	PR_SET_ENDIAN, PR_GET_ENDIAN, PR_SET_FPEMU, PR_GET_FPEMU,
	PR_SET_FPEXC, PR_GET_FPEXC, PR_SET_KEEPCAPS, PR_GET_KEEPCAPS,
	PR_SET_NAME, PR_GET_NAME, PR_SET_PDEATHSIG, PR_GET_PDEATHSIG,
	PR_SET_SECCOMP, PR_GET_SECCOMP, PR_SET_SECUREBITS, PR_GET_SECUREBITS,
	PR_SET_TIMING, PR_GET_TIMING, PR_SET_TSC, PR_GET_TSC,
	PR_SET_UNALIGN, PR_GET_UNALIGN, PR_MCE_KILL, PR_MCE_KILL_GET,
	PR_SET_MM, PR_SET_CHILD_SUBREAPER, PR_GET_CHILD_SUBREAPER, PR_SET_NO_NEW_PRIVS,
	PR_GET_NO_NEW_PRIVS, PR_GET_TID_ADDRESS, PR_SET_THP_DISABLE, PR_GET_THP_DISABLE,
};


#ifdef USE_SECCOMP
static void do_set_seccomp(struct syscallrecord *rec)
{
	unsigned long *optval = NULL, optlen = 0;

	bpf_gen_seccomp(&optval, &optlen);

	rec->a2 = SECCOMP_MODE_FILTER;
	rec->a3 = (unsigned long) optval;
	rec->a4 = 0;
	rec->a5 = 0;
}
#else
static void do_set_seccomp(__unused__ struct syscallrecord *rec) { }
#endif

/* We already got a generic_sanitise at this point */
static void sanitise_prctl(struct syscallrecord *rec)
{
	int option = prctl_opts[rand() % NR_PRCTL_OPTS];

// For now, just do SECCOMP, the other options need some attention.
	option = PR_SET_SECCOMP;

	rec->a1 = option;

	switch (option) {
	case PR_SET_SECCOMP:
		do_set_seccomp(rec);
		break;

	default:
		break;
	}
}

struct syscallentry syscall_prctl = {
	.name = "prctl",
	.num_args = 5,
	.arg1name = "option",
	.arg2name = "arg2",
	.arg3name = "arg3",
	.arg4name = "arg4",
	.arg5name = "arg5",
	.sanitise = sanitise_prctl,
};
