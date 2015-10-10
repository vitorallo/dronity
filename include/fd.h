#pragma once

#include "list.h"
#include "types.h"

/* need to fix missing enum for output values not present in ftw.h header */
#ifndef FTW_CONTINUE
enum
{
FTW_CONTINUE = 0,	/* Continue with next sibling or for FTW_D with the
first child. */
# define FTW_CONTINUE FTW_CONTINUE
FTW_STOP = 1,	/* Return from `ftw' or `nftw' with FTW_STOP as return
value. */
# define FTW_STOP FTW_STOP
FTW_SKIP_SUBTREE = 2,	/* Only meaningful for FTW_D: Don't walk through the
subtree, instead just continue with its next
sibling. */
# define FTW_SKIP_SUBTREE FTW_SKIP_SUBTREE
FTW_SKIP_SIBLINGS = 3,/* Continue with FTW_DP callback for current directory
(if FTW_DEPTH) and then its siblings. */
# define FTW_SKIP_SIBLINGS FTW_SKIP_SIBLINGS
};
#endif

void setup_fd_providers(void);

unsigned int open_fds(void);

void process_fds_param(char *optarg, bool enable);

struct fd_provider {
        struct list_head list;
	const char *name;
        int (*open)(void);
        int (*get)(void);
	bool enabled;
};

#ifndef O_DSYNC
#define O_DSYNC 00010000
#endif
