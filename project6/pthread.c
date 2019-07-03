//Name: Junda An
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;
int task[2] = {0, 0};
int total_tasks;

//If the first slot is empty, generate a task at the first slot.
//If the first slot is full and the second is empty, generate a task at the second slot.
//If both slots are full, do nothing
void *producer(){
  while(total_tasks > 0){

    //define the critical setion
    pthread_mutex_lock(&lock);
    if(task[0] == 0 && task[1] == 0){
      task[0] = 1;
      total_tasks --;
      printf("Producer 1 inserts a task\n");
    }
    else if(task[0] == 1 && task[1] == 0){
      task[1]=1;
      total_tasks --;
      printf("Producer 1 inserts a task\n");
    }

    pthread_mutex_unlock(&lock);
  }
  pthread_exit(0);
}

//If the second slot is full, extract a task at the second slot.
//If the first slot is full and the second is empty, extract a task at the second slot.
//If both slots are empty, do nothing
void *consumer(void *consumer_thread_data){

  int my_tasks = 0;
  int *consumer_num = (int*)consumer_thread_data;
  while(task[0]==1 || total_tasks > 0){
    //define the critical section
    pthread_mutex_lock(&lock);
    if(task[0] == 1 && task[1] == 1){
      task[0] = 1;
      task[1] = 0;
      my_tasks ++;
      printf("Consumer %d extracts a task\n", *consumer_num);
    }
    else if (task[0] == 1 && task[1] == 0){
      task[0] = 0;
      my_tasks ++;
      printf("Consumer %d extracts a task\n", *consumer_num);
    }

    pthread_mutex_unlock(&lock);
  }
  printf("Consumer %d extracts %d tasks in total\n", *consumer_num, my_tasks);
  pthread_exit(0);
}

int main(int argc, char *argv[]){
  total_tasks = atoi(argv[1]);

  pthread_t p_thread[3];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_mutex_init(&lock, NULL);
  int consumer_num[2] = {1, 2};

  //generate one thread for producer, two thread for consumers
  pthread_create(&p_thread[0], &attr, producer, NULL);
  pthread_create(&p_thread[1], &attr, consumer, (void*)&consumer_num[0]);
  pthread_create(&p_thread[2], &attr, consumer, (void*)&consumer_num[1]);

  pthread_join(p_thread[0], NULL);
  pthread_join(p_thread[1], NULL);
  pthread_join(p_thread[2], NULL);
  return 0;
}
