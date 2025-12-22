

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


/* int pthread_create(pthread_t *restrict thread,
				const pthread_attr_t *restrict attr,
				void *(*start_routine)(void *),
				void *restrict arg);#include <stdio.h> */
				
/* 	#include <pthread.h>

	# define NC "\e[0m"
	# define YELLOW "\e[1;33m"

	// thread_routine is the function the thread invokes right after its
	// creation. The thread ends at the end of this function.
void *thread_routine(void *data)
{
	pthread_t tid;
	// The pthread_self() function provides
	// this thread's own ID.
	tid = pthread_self();
	printf("%sThread [%ld]: The heaviest burden is to exist without living.%s\n",
	YELLOW, tid, NC);
	return (NULL); // The thread ends here.
}

int main(void)
{
	pthread_t tid1; // First thread's ID
	pthread_t tid2; // Second thread's ID

	// Creating the first thread that will go
	// execute its thread_routine function.
	pthread_create(&tid1, NULL, thread_routine, NULL);
	printf("Main: Created first thread [%ld]\n", tid1);
	// Creating the second thread that will also execute thread_routine.
	pthread_create(&tid2, NULL, thread_routine, NULL);
	printf("Main: Created second thread [%ld]\n", tid2);
	// The main thread waits for the new threads to end
	// with pthread_join.
	pthread_join(tid1, NULL);
	printf("Main: Joining first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joining second thread [%ld]\n", tid2);
	return (0);
} */

#include <sys/time.h>


// un mutex par fork = il me faut un tab de fork / mutex ??
typedef struct s_locks
{
 pthread_mutex_t lock_1;
 pthread_mutex_t lock_2;
 unsigned int count;
} t_locks;

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

#define TIMES_TO_COUNT 20001

typedef struct s_counter
{
	pthread_mutex_t count_mutex;
	unsigned int count;
}	t_counter;

void *thread_routine(void *data)
{
	pthread_t tid;
	t_counter *count;
	unsigned int i;

	tid = pthread_self();
	count = (t_counter *)data;
	printf("tread [%1lu] = count at start = [%u]\n", tid, count->count);

	i =0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&count->count_mutex);
		count->count++;
		pthread_mutex_unlock(&count->count_mutex);
		i++;
	}

	pthread_mutex_lock(&count->count_mutex);
	printf("tread [%1lu] = count at end = [%u]\n", tid, count->count);
	pthread_mutex_unlock(&count->count_mutex);
	return (NULL);
}
#include <sys/time.h>
#include <stdio.h>

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	t_counter count;
	
	count.count = 0;
	struct timeval tv;

	long time_start = gettimeofday(&tv, NULL);

	//printf("mon temps est de = %ld", time);

	printf("secondes = %ld\n", tv.tv_sec);
	printf("microsecondes = %ld\n", tv.tv_usec);

	pthread_mutex_init(&count.count_mutex, NULL); // init l emutex

	// ce que j'attends
	printf("j'attend un count de [%d]\n", 2*TIMES_TO_COUNT);
	// threads creation
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("main = premier trhred cree [%1lu]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("main = seceond trhred cree [%1lu]\n", tid2);
	// thread joining
	
	pthread_join(tid1, NULL); // join le main a tid1
	printf("main = join 1 [%1lu]\n", tid1);
	pthread_join(tid2, NULL); // join le main a tid2
	printf("main = join 2 [%1lu]\n", tid2);
	// count final
	if (count.count != (2 * TIMES_TO_COUNT))
	{
		printf(RED"main = noo, total count = %u\n"NC, count.count);
	}
	else
		printf(GREEN"main = ok, total count = %u\n"NC, count.count);
	pthread_mutex_destroy(&count.count_mutex); //destroy a la fin
	return (0);
}
