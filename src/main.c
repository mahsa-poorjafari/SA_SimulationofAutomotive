/*
 ============================================================================
 Name        : SA_SimulationofAutomotive.c
 Author      : Monireh Pourjafarian
 Version     :
 Copyright   : Benchamek for cocurrent multithreded C program
 Description : Simple Autonomous multithreaded program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
int numofcpus = 0;
int 


void *CheckObstacleFrontTop()
{
	printf("\n This is CheckObstacleFrontTop Function");

}
void *CheckObstacleBackBottom()
{
	printf("\n This is CheckObstacleBackBottom Function");

}
void *CheckObstacleFrontBottom()
{
	printf("\n This is CheckObstacleFrontBottom Function");

}
void *CheckObstacleBackTop()
{
	printf("\n This is CheckObstacleBackTop Function");

}
void *CheckObstacleLeftFront()
{
	printf("\n This is CheckObstacleLeftFront Function");

}
void *CheckObstacleLeftBack()
{
	printf("\n This is CheckObstacleLeftBack Function");

}

void *CheckObstacleRightFront()
{
	printf("\n This is CheckObstacleRightFront Function");

}

void *CheckObstacleRightBack()
{
	printf("\n This is CheckObstacleRightBack Function");

}

void stop()
{
	printf("This is stop Function \n");

}

void *slowDown()
{
	printf("This is slowDown Function \n");

}

void *goFurther()
{
	printf("This is goFurther Function \n");

}

void fasterSpeed()
{
	printf("This is fasterSpeed Function \n");

}

void *CheckTrafficLight()
{
	printf("This is CheckTrafficLight Function \n");

}

int main(void) {
	numofcpus = sysconf(_SC_NPROCESSORS_ONLN);	
	printf("sysconf %d \n", numofcpus);
	int numOfThread = numofcpus * 10;
	printf("numOfThread %d", numOfThread); 
	pthread_t threads[numOfThread];
	int rc;
	int CheckObstacleRc [10];
	int i;
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	
	// Group of 8 threads for CheckObstacle  
	CheckObstacleRc[0] = pthread_create(&threads[0], NULL, CheckObstacleFrontTop, NULL);
	CheckObstacleRc[1] = pthread_create(&threads[1], NULL, CheckObstacleFrontBottom, NULL);
	CheckObstacleRc[2] = pthread_create(&threads[2], NULL, CheckObstacleBackBottom, NULL);
	CheckObstacleRc[3] = pthread_create(&threads[3], NULL, CheckObstacleBackTop, NULL);
	CheckObstacleRc[4] = pthread_create(&threads[4], NULL, CheckObstacleLeftFront, NULL);
	CheckObstacleRc[5] = pthread_create(&threads[5], NULL, CheckObstacleLeftBack, NULL);
	CheckObstacleRc[6] = pthread_create(&threads[6], NULL, CheckObstacleRightFront, NULL);
	CheckObstacleRc[7] = pthread_create(&threads[7], NULL, CheckObstacleRightBack, NULL);
	
	for (int rc = 0; rc < 8; rc++){
		if (CheckObstacleRc[rc]) {
		 printf("\n Error in creation of thread %d.\n", rc);
		 exit(-1);
		}
	}
		
	rc = pthread_create(&threads[8], NULL, slowDown, NULL);
	if (rc) {
	 printf("Error in thread creation.\n");
	 exit(-1);
	}		
	rc = pthread_create(&threads[9], NULL, (void * (*)(void *))(goFurther), NULL);
	if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }	
	rc = pthread_create(&threads[10], NULL, (void * (*)(void *))(CheckTrafficLight), NULL);
	if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }
		
	for (int i = 0; i < numOfThread; ++i){
		pthread_join(threads[i],NULL);
	}
	
	return EXIT_SUCCESS;
}
