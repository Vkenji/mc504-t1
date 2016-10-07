void* f_img(void *v);
void enter_immigrant(int id);
void checkIn(int id);
void sitDown(int id);
void swear(int id);
void getCertificate(int id);
void leave_immigrant(int id);


void* f_img(void *v){
	int id = *(int*) v;

	enter_immigrant(id);
	checkIn(id);
	swear(id);
	sitDown(id);
	getCertificate(id);
	leave_immigrant(id);

	return NULL;
}

void enter_immigrant(int id){
	/* sleep(1); */
	futex_wait(&judge_inside, 1);
	__sync_add_and_fetch (&entered, 1);
	printf("Immigrant %d has entered.\n", id);
}

void checkIn(int id){
	sleep(1);

	__sync_add_and_fetch (&checkedin, 1);
	if (checkedin != entered) {
		pthread_cond_signal (&all_checked_in);
	}
	/* Barrier: quando o ultimo imigrante der check in,
				ele manda sinal para o judge poder dar confirm */

	printf("Immigrant %d has checked in.\n", id);
}

void swear(int id){
	printf("Immigrant %d has sworn.\n", id);
}

void sitDown(int id){
	printf("Immigrant %d has sat down.\n", id);
}

void getCertificate(int id){
	futex_wait(&judge_confirmed, 0);
	printf("Immigrant %d has gotten the certificate.\n", id);
}

void leave_immigrant(int id){
	futex_wait(&judge_inside, 1);
	printf("Immigrant %d has left.\n", id);
}
