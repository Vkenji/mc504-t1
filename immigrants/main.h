#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>

/* Quantidade de cada thread */
#define N_IMG 3
#define N_SPEC 5
#define N_JDG 1

int futex_wait(void *addr, int val1){
	return syscall(SYS_futex, addr, FUTEX_WAIT, val1, NULL, NULL, 0);
}

int futex_wake(void *addr, int n){
	return syscall(SYS_futex, addr, FUTEX_WAKE, n, NULL, NULL, 0);
}

/* Mutex de entrada de imigrantes e espectadores */
pthread_mutex_t door, attendant;
pthread_cond_t all_checked_in;
volatile int entered, checkedin;

/* Barreira para que o judge possa dar confirm */
/* sem_t all_checked_in; */

/* Juíz está dentro?
	1: está dentro
	0: não está dentro */
int judge_inside;

/* Juíz confirmou?
	1: confirmou
	0: não confirmou */
int judge_confirmed;
