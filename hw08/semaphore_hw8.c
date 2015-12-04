/*
 * semaphore.c HW08
 * Isaac Fernandez
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define true 1
#define false 0

//Semaphore code
//Follows the pattern given in OSTEP C31, replacing the pthread_cond_signal
//logic with a boolean to achieve the same signaling mechanism
struct sem_t {
	int count; //pending requests
	int access; //Can the resource be accessed? BOOLEAN
	pthread_mutex_t mutex; //lock this semaphore down
};

int sem_post(struct sem_t * sem);
int sem_wait(struct sem_t * sem);
int sem_init(struct sem_t * sem, int start_access, int init);
void wait(struct sem_t * sem);
int rem();
void add(int val);
void printbuf();


//[Semaphore pointer , any int, initial count]
int sem_init(struct sem_t * sem, int start_access, int init) {
	sem->count = init;
	sem->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sem->access = start_access; //allows producer to start available
	//while allowing us to start consumer on hold 
}

//Increment the semaphore / notify others that its opened up
int sem_post(struct sem_t * sem) {
	pthread_mutex_lock(&sem->mutex);
	sem->count += 1;
	sem->access = true; //signal to all others that resource can be access
	pthread_mutex_unlock(&sem->mutex);
}

//decrement the semaphore / notify others it is being used
int sem_wait(struct sem_t * sem) {
	pthread_mutex_lock(&sem->mutex);
	sem->count -= 1; //Add ourselves to the count of attempting access
	if (sem-> count <= 0) { //Let's pthread_cond_wait sortof
		wait(sem);
	}
	sem->access = false; //let others know they cannot access this
	pthread_mutex_unlock(&sem->mutex);
}

//not_quite pthread_cond_wait 
void wait(struct sem_t * sem) {
	while (!sem->access) { //Wait for a 'signal' to continue
		pthread_mutex_unlock(&sem->mutex);
		sleep(1);
		pthread_mutex_lock(&sem->mutex);
	}
}

//buffer semaphores and such
#define SLOTS 4
struct sem_t sem_pro;
struct sem_t sem_con;
pthread_mutex_t mut_buf;

//Initialize the semaphores to control access from prods & consumers
void init_buff_semas(struct sem_t * prod,
					 struct sem_t * con) {
	sem_init(prod, 1, 4);
	sem_init(con, 0, 0);
}

//buffer struts	
int buf[SLOTS];
int first_occupied_slot = 0;
int first_empty_slot = 0;
//Treat buf like a 4-element queue, access only thorugh:
//add(int element) and rem() --> int element
void add(int val) {
	buf[first_empty_slot] = val;
	first_empty_slot = (first_empty_slot + 1) % SLOTS;
}
int rem() {
	int val = buf[first_occupied_slot];
	first_occupied_slot = (first_occupied_slot + 1) % SLOTS;
	return val;
}

//Producer
void *producer(void *arg) {
  int work_item = 0;
  while (1) {
    sleep( rand() % 5 );
    sem_wait(&sem_pro);  // Wait for empty slots
    pthread_mutex_lock(&mut_buf);
      work_item = work_item + 1;
      add(work_item);  // inside critical section with mut_buf lock
    pthread_mutex_unlock(&mut_buf);
    sem_post(&sem_con);  // Tell the consumer there's a new work item
  }
}

// Exactly the same, but the inverse:
void *consumer(void *arg) {
  while (1) {
	int work_item;
	sleep( rand() % 5 );
	sem_wait(&sem_con); // wait for new consumable
	pthread_mutex_lock(&mut_buf);
	  work_item = rem();
	  //printbuf();
	pthread_mutex_unlock(&mut_buf);
	sem_post(&sem_pro); // let producer know theres an empty slot
	printf("%d ", work_item);
	fflush(stdout);  // Force printing now; don't wait for the newline
  }
}

//Print out the buffer to visualize what it looks like
//For test and giggles
void printbuf() {
	printf("[");
	for (int i = 0; i < SLOTS; i++) {
		printf(",%d", buf[i]);
	}
	printf("]");
}

int main() {
	init_buff_semas(&sem_pro, &sem_con);
	mut_buf = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	int threads = 3;
	pthread_t tproducers[threads];
	pthread_t tconsumers[threads];
	//spawn the threads
	for (int i = 0; i < threads; i++) {
	  pthread_create(&tproducers[i], NULL, producer, NULL);
	  pthread_create(&tconsumers[i], NULL, consumer, NULL);
	}
	//join them all to main
	for (int i = 0; i < threads; i++) {
	  pthread_join(tproducers[i], NULL);
	  pthread_join(tconsumers[i], NULL);
	}
	return 0;
}

