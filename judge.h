#include <stdatomic.h>

void* f_jdg (void *v);
void enter_judge();
void confirm_judge();
void leave_judge();


void* f_jdg (void *v){
	enter_judge();
	confirm_judge();
	leave_judge();

	return NULL;
}

void enter_judge(){
	sleep(1);
	atomic_exchange(&judge_inside, 1);
	printf("Judge entered.\n");
	sleep(2);
}

void confirm_judge(){
	/* Barreira: todos os imigrantes tem que fazer check in */

	pthread_mutex_lock (&attendant);

	while (entered != checkedin)
		pthread_cond_wait (&all_checked_in, &attendant);
	printf("Judge has confirmed.\n");
	atomic_exchange(&judge_confirmed, 1);

	futex_wake(&judge_confirmed, entered);
	sleep(2);

	pthread_mutex_unlock (&attendant);
}

void leave_judge(){
	judge_inside = 0;
	judge_confirmed = 0;
	printf("Judge has left.\n");
	futex_wake(&judge_inside, N_IMG + N_SPEC);
}
