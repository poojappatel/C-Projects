Project Overview: For my threads and synchronization project, I am simulating scenarios when n amount of phone calls are being received by our 
local health care center, and each caller wants to create an appointment to get the COVID-19 test. The problem is the health care center is 
receiving n amount of callers all at the same time, and there are certain restrictions in place to complete the process of scheduling the test. 
First each caller must go through specific steps to complete the process. A caller must attempt to connect to the center’s phone line. If the caller 
succeeds, meaning there is an open line at the center, then the caller must speak to an operator. If there is an available operator, then the 
caller must speak to operator and schedule the appointment for a test. Finally, the caller leaves the operator, and hangs up the phone, effectively 
disconnecting the phone line. Other restrictions that hold are: the center only has seven available lines, so only up to seven callers can connect to 
the center’s phone line at a time. Also, the center only has four available operators at a time that can speak to the callers to set up the appointments, 
so only up to four callers can speak to an operator at a time.

Overview of implementation: There are two functions in my program that create the simulation of phonecalls to a health care center.

I created seven global variables. These global variables are necessary and should be declared as global variables because each thread needs to share 
access of these variables. 

Phonecall function: The phonecall function has one parameter void* vargp which allows a generic type to be passed within this function. This function 
implements the simulation above with threads. First, I create a caller_ID variable and set it to next_ID. The caller_ID variable represents the id of 
each thread (caller) that is created. The variable next_ID is a global variable that I increment inside   this function. Because each thread should have 
a unique caller id, the threads should be synchronized at this part. I use sem_wait(&ID_lock) and sem_post(&ID_lock); to protect the critical region and 
avoid the race condition that arises when the threads try to increment next_ID. Next, I go on to implement when a thread can connect to a line. Because 
we have to update the global variable connected every time a thread connects to an open line, this section of code is a critical section since 
multiple threads are accessing the shared variable connected. We have to increment connected one thread at a time, so I used sem_wait(&connected_lock) 
to only allow one thread in this section at a time. If there are currently no available lines, meaning 7 other threads are connected to a line, then 
the current thread that is trying to connect to a line goes into  the loop, while (connected == NUM_LINES). This loop only lets a thread go inside when t
he connected is 7 (lines are busy). Once a thread is inside  the while loop, I unlock the connected semaphore with sem_post(&connected_lock) because I am 
not working with critical variables inside the while loop. I have a condition inside the while loop that prints the current thread trying to connect to a 
line cannot connect to the line because lines are currently busy. I put the print statement in an if statement because I want the print statement to 
print only once for each unique thread that encounter s a busy line connection scenario. Without my condition the print statement is very expensive in 
the program when we have 50+ callers because there were  too many busy lines printing in the program, so I had to create a way that the line should only 
print once for the unique thread that encounters busy lines. After the if statement, I sleep the threads in the while loop as to simulate the callers 
waiting for a line to free up. The sleep function also staggers the threads, allowing time for other threads to finish scheduling their appointments and 
hang   up. Then, I use sem_wait(&connected_lock) at the end of the while loop to block the threads once more because, if a thread ends up leaving the 
while loop, the next thing I do is increment connected, a   critical variable, otherwise the thread goes through the while loop once again if lines have 
not freed up. Next, I use a counting semaphore to implement the threads speaking to an operator and making an appointment. This is a counting semaphore, 
so I allow four threads to go in this critical section at a time. The counting semaphore simulates four callers speaking with an operator simultaneously. 
The   difference with this critical region in my code is that I included print statements because these print statements simulate speaking to an operator 
and making an appointment all of which can only happen with max four unique threads at a time. Within the lock, I sleep to simulate time taken to make 
an appointment. Lastly, in this function I have one more critical region when we have to decrement connected because the threads are finished making an 
appointment and the threads hang up, freeing up lines for more threads to connect.

Main function: The purpose of the main function is to pass command line arguments. The function has two parameters, int agrc and char*argv[ ]. 
int argc represents the number of arguments a user can pass. char *argv[] is an array of strings representing the individual arguments given on the 
command line. The user can input a command line argument to the function, and  this function reads and executes the argument. I, first, initialize the 
three semaphores within this function. Then, I have an if-else statement that checks if the argument counter is not two or the argument vector is less 
than 0. If that is not true, then  I go on to initialize um_phonecalls as the integer that the user passes in the command line argument. Then I use 
pthread_t to uniquely identify n number of threads. Then I use one for loop to create n  threads, and another for loop to terminate n threads using 
pthread_join.
