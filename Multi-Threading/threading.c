#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// creating global variables
static sem_t ID_lock; //id semaphore
static sem_t connected_lock; //connected semaphore
static sem_t operators; //operators semaphore
static int NUM_OPERATORS = 4; // total number of operators available
static int NUM_LINES = 7; // total number of lines available
static int connected = 0; // keeps track of number of callers connected
static int next_ID = 0; // incremented by 1, used to set caller ids for threads

void* phonecall(void* vargp) {

  // caller_ID initalized and set to next_ID
  //caller_ID is not a static variable because each thread needs to have a unique ID not the same ID
  int caller_ID = next_ID;
  
  // first critical section begins, next_ID needs to be incremented for every thread                                                                         
  sem_wait(&ID_lock);
  next_ID++;
  // unlocks semaphore, exits first critical region
  sem_post(&ID_lock);
  
  printf("Thread %d is attempting to connect...\n", caller_ID);

  // variable used to print busy message, not a static variable because I need to modify it
  int busy = 0;
  // second critical section begins
  sem_wait(&connected_lock);
  // checks if all lines are currently in use, if yes, then goes into the while loop
  while (connected == NUM_LINES) {
    // unlocks semaphore here because no critical variables are being updated, also maximizes efficiency because print statement shouldn't be inside of critical section 
    sem_post(&connected_lock);
    // this condition ensures that my program will only print unavailability message once to increase efficiency of program
    if (busy == 0) {
      printf("Thread %d cannot connect! No available lines, try again later.\n", caller_ID);
      busy = 1;
      }
    sleep(1);
    sem_wait(&connected_lock);
  }

  // connected incremented when there is an available line
  connected++;
  // unlocks connected sempahore, second critical section finished
  sem_post(&connected_lock); 
    
  printf("Thread %d connects to an available line, call ringing...\n", caller_ID);
  
  // counting semphore for operator, third critical section starts
  sem_wait(&operators);
  printf("Thread %d is speaking to an operator in the local health center.\n", caller_ID);
  // program sleeps to simulate an appointment being made
  sleep(3);
  printf("Thread %d has made an appointment for the test! The operator has left...\n", caller_ID);
  // operator semaphore is unlocked, critical section is finished
  sem_post(&operators);
  
  // last critical section, decrements connected because the thread disconnected from line
  sem_wait(&connected_lock);
  connected--;
  sem_post(&connected_lock);
  
  printf("Thread %d has hung up!\n", caller_ID);
}

/* main function that has two parameters. Purpose is to pass command line arguments. 
Parameters: int argc represents the number of arguments user can pass. char *argv[] is an array of strings representing the individual arguments given on the command line.
Purpose: User inputs command line argument, that this function reads and executes.*/
int main(int argc, char *argv[]) {
  // initializing semaphores
  sem_init(&ID_lock, 0, 1);
  sem_init(&connected_lock, 0, 1);
  sem_init(&operators, 0, NUM_OPERATORS);

  if (argc != 2 || argv[1] == NULL) {
    printf("Invalid number of arguments, please try again. Should have two arguments passed.\n");
    return 0;
  } else if (atoi(argv[1]) < 0) {
    printf("Invalid integer inputted for second argument. Try again.\n");
    return 0;
  } else {
    // variable that is set to the number user inputs in command line
    int num_phonecalls = atoi(argv[1]);
    pthread_t tid[num_phonecalls];

    // creates threads for number of phonecall user passes in command line 
    for (int i = 0; i < num_phonecalls; i++) {
      pthread_create(&tid[i], 0, phonecall, NULL);
    }
    // waits for each thread that was created to termiante
    for (int i = 0; i < num_phonecalls; ++i) {
      pthread_join(tid[i], NULL);
    }
    printf("\n");
    printf("No more callers trying to connect.\n");
  }

  //Destroying created semaphores
  sem_destroy(&connected_lock);
  sem_destroy(&ID_lock);
  sem_destroy(&operators);
  
  return 0;
}
