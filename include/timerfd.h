#pragma once

#include "fd.h"

const struct fd_provider timerfd_fd_provider;

#define MAX_TIMERFD_FDS 8

//this is the sys/timerfd.h from the bionic 20 platform... 

#ifndef _SYS_TIMERFD_H_
#define _SYS_TIMERFD_H_

#include <fcntl.h> /* For O_CLOEXEC and O_NONBLOCK. */
#include <time.h>
#include <sys/types.h>

__BEGIN_DECLS

#define TFD_TIMER_ABSTIME (1 << 0)
#define TFD_TIMER_CANCEL_ON_SET (1 << 1)

#define TFD_CLOEXEC O_CLOEXEC
#define TFD_NONBLOCK O_NONBLOCK

extern int timerfd_create(clockid_t, int);
extern int timerfd_settime(int, int, const struct itimerspec*,
                           struct itimerspec*);
extern int timerfd_gettime(int, struct itimerspec*);

__END_DECLS

#endif /* _SYS_TIMERFD_H */
