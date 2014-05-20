/*
 * SYSCALL_DEFINE4(rt_sigaction, int, sig,
	const struct sigaction __user *, act,
	struct sigaction __user *, oact,
	size_t, sigsetsize)
 */
#include <signal.h>
#include <stdlib.h>
#include "random.h"
#include "sanitise.h"
#include "shm.h"
#include "syscall.h"

void sanitise_rt_sigaction(int childno)
{
	struct syscallrecord *rec;

	rec = &shm->syscall[childno];

	if (rand_bool())
		rec->a2 = 0;

	if (rand_bool())
		rec->a3 = 0;

	rec->a4 = sizeof(sigset_t);
}

struct syscallentry syscall_rt_sigaction = {
	.name = "rt_sigaction",
	.num_args = 4,
	.sanitise = sanitise_rt_sigaction,
	.arg1name = "sig",
	.arg1type = ARG_RANGE,
	.low1range = 0,
	.hi1range = _NSIG,
	.arg2name = "act",
	.arg2type = ARG_ADDRESS,
	.arg3name = "oact",
	.arg3type = ARG_ADDRESS,
	.arg4name = "sigsetsize",
};
