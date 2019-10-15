/*
 ============================================================================
 Name        : SA_SimulationofAutomotive.c
 Author      : Monireh Pourjafarian
 Version     :
 Copyright   : Benchamek for cocurrent multithreded C program
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//#include <cstdlib>
#include <pthread.h>

//using namespace std;

// Mutex
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

// Global vars
int speed=0;
int red=1;
int blue=2;
int green=3;
int blockAcc=0;
int varA=1;
int varB=1;
int varC=1;
int varD=1;
int lightColor=0;
int obstacleDistance=0;
int side=0;



void CheckObstacle(int side)
{

}

void stop()
{

}

void slowDown()
{

}

void goFurther()
{

}

void fasterSpeed()
{

}

void CheckTrafficLight()
{

}


int main(void) {
   cout << "Number of Physical cores " << thread::hardware_concurrency() << endl;
   pthread_t thread1 , thread2, thread3, thread4;
   int rc;
   int i;
   pthread_mutex_init(&mutex1, NULL);
   pthread_mutex_init(&mutex2, NULL);
   printf("MAIN::result = %d.\n", result);
   rc = pthread_create(&thread1, NULL, sum, NULL);
   if (rc) {
	 printf("Error in thread creation.\n");
	 exit(-1);
   }
   pthread_join(thread1,NULL);

   rc = pthread_create(&thread3, NULL, sumPlus, NULL);
   if (rc) {
	 printf("Error in thread creation.\n");
	 exit(-1);
   }
   pthread_join(thread3,NULL);


   rc = pthread_create(&thread2, NULL, (void * (*)(void *))(diff), NULL);
   if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }
   pthread_join(thread2,NULL);
   rc = pthread_create(&thread4, NULL, (void * (*)(void *))(incrementSharedVars), NULL);
   if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }
   pthread_join(thread4,NULL);

	   //pthread_exit(NULL);

	return EXIT_SUCCESS;
}
