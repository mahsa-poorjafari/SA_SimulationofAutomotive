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

#include <stdbool.h>
//#include <cstdlib>
#include <pthread.h>

//using namespace std;

// Mutex
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

// Global vars
int speed=0;
int red=1;
int yellow=2;
int green=3;
bool blockAcc= false;
int varA=1;
int varB=1;
int varC=1;
int varD=1;
int lightColor=0;
int obstacleDistance=0;
// autoSide => 1:FrontTop, 2:FrontBottom, 3:BackBottom, 4:BackTop, 5:LeftFront, 6:RightFront, 7:LeftBack, 8:RightBack 
int autoSide = 0;
int numofcpus = 4;
bool alarmOn = false;
int autoAlarmSound = 0;
int autoBrake = 0;
int autoSpeed = 0;
int speedSign = 0;
int gearLevers = 0;

int FrontTopSensorsA = 0;
int FrontTopSensorsB = 0;
int FrontTopSensorsC = 0;
int FrontBottomSensorsA = 0;
int FrontBottomSensorsB = 0;
int FrontBottomSensorsC = 0;
int BackBottomSensorsA = 0;
int BackBottomSensorsB = 0;
int BackBottomSensorsC = 0;
int BackTopSensorsA = 0;
int BackTopSensorsB = 0;
int BackTopSensorsC = 0;
int LeftFrontSensorsA = 0;
int LeftFrontSensorsB = 0;
int LeftFrontSensorsC = 0;
int RightFrontSensorsA = 0;
int RightFrontSensorsB = 0;
int RightFrontSensorsC = 0;
int LeftBackSensorsA = 0;
int LeftBackSensorsB = 0;
int LeftBackSensorsC = 0;
int RightBackSensorsA = 0;
int RightBackSensorsB = 0;
int RightBackSensorsC = 0;


// Function declarations
void *sensorsRandomValue(int);
void *stop();
void brake();
void *fasterSpeed();
void *ringTheAlarm();
void readStreetSigns();
void *getSpeedSign();
void readTraficLight();
void goBack();

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;


// CheckObstacleBack 8 sides
void *CheckObstacleFrontTop()
{
	printf("\n This is CheckObstacleFrontTop Function");
	pthread_t threadChObFT[4];
	int rc[4];
	pthread_mutex_lock(&lock);	
	autoSide = 1;
	//Random values for sensors 0 or 10
	rc[0] = pthread_create(&threadChObFT[0], NULL, sensorsRandomValue(autoSide), NULL);
	
	//sensorsRandomValue(autoSide);
	
	if (FrontTopSensorsA < 20 && FrontTopSensorsB < 20 && FrontTopSensorsC < 20){
		rc[1] = pthread_create(&threadChObFT[1], NULL, stop, NULL);
		//stop();
	}else if (FrontTopSensorsA < 30 || FrontTopSensorsB < 30 || FrontTopSensorsC < 30){
		alarmOn = true;
		rc[2] = pthread_create(&threadChObFT[2], NULL, ringTheAlarm, NULL);
		//ringTheAlarm();	
	}else{
		rc[3] = pthread_create(&threadChObFT[3], NULL, fasterSpeed, NULL);
		//fasterSpeed();
	}
	pthread_mutex_unlock(&lock);
	for (int i = 0; i < 4; i++){
		if (rc[i]) {
		 printf("\n Error in creation of thread %d.\n", i);
		 exit(-1);
		}
	}
	for (int j = 0; j < 4; ++j){
		pthread_join(threadChObFT[j],NULL);
	}

}

void *CheckObstacleBackBottom()
{
	printf("\n This is CheckObstacleBackBottom Function");
	pthread_t threadChObBB[4];
	int rc[4];
	pthread_mutex_lock(&lock);
	autoSide = 3;
	//sensorsRandomValue(autoSide);
	rc[0] = pthread_create(&threadChObBB[0], NULL, sensorsRandomValue(autoSide), NULL);
	
	if (BackBottomSensorsA < 20 && BackBottomSensorsB < 20 && BackBottomSensorsC < 20){
		rc[1] = pthread_create(&threadChObBB[1], NULL, stop, NULL);
		//stop();
	}else if (BackBottomSensorsA < 30 || BackBottomSensorsB < 30 || BackBottomSensorsC < 30){
		alarmOn = true;
		rc[2] = pthread_create(&threadChObBB[2], NULL, ringTheAlarm, NULL);
		//ringTheAlarm();	
	}else{
		rc[3] = pthread_create(&threadChObBB[3], NULL, fasterSpeed, NULL);
		//fasterSpeed();
	}
	
	pthread_mutex_unlock(&lock);
	for (int i = 0; i < 4; i++){
		if (rc[i]) {
		 printf("\n Error in creation of thread %d.\n", i);
		 exit(-1);
		}
	}
	for (int j = 0; j < 4; ++j){
		pthread_join(threadChObBB[j],NULL);
	}

}
void *CheckObstacleFrontBottom()
{
	printf("\n This is CheckObstacleFrontBottom Function");
	pthread_t threadChObFB[4];
	int rc[4];
	pthread_mutex_lock(&lock);
	autoSide = 2;
	rc[0] = pthread_create(&threadChObFB[0], NULL, sensorsRandomValue(autoSide), NULL);
	//sensorsRandomValue(autoSide);
	if (FrontBottomSensorsA < 20 && FrontBottomSensorsB < 20 && FrontBottomSensorsC < 20){
		rc[1] = pthread_create(&threadChObFB[1], NULL, stop, NULL);
		//stop();
	}else if (FrontBottomSensorsA < 30 || FrontBottomSensorsB < 30 || FrontBottomSensorsC < 30){
		alarmOn = true;
		rc[2] = pthread_create(&threadChObFB[2], NULL, ringTheAlarm, NULL);
		//ringTheAlarm();	
	}else{
		rc[3] = pthread_create(&threadChObFB[3], NULL, fasterSpeed, NULL);
		//fasterSpeed();
	}
	pthread_mutex_unlock(&lock);
	for (int i = 0; i < 4; i++){
		if (rc[i]) {
		 printf("\n Error in creation of thread %d.\n", i);
		 exit(-1);
		}
	}
	for (int j = 0; j < 4; ++j){
		pthread_join(threadChObFB[j],NULL);
	}

}
void *CheckObstacleBackTop()
{
	printf("\n This is CheckObstacleBackTop Function");
	pthread_t threadChObBT[4];
	int rc[4];
	pthread_mutex_lock(&lock);
	autoSide = 4;
	rc[0] = pthread_create(&threadChObBT[0], NULL, sensorsRandomValue(autoSide), NULL);
	//sensorsRandomValue(autoSide);
	if (BackTopSensorsA < 20 && BackTopSensorsB < 20 && BackTopSensorsC < 20){
		rc[1] = pthread_create(&threadChObBT[1], NULL, stop, NULL);
		//stop();
	}else if (BackTopSensorsA < 30 || BackTopSensorsB < 30 || BackTopSensorsC < 30){
		alarmOn = true;
		rc[2] = pthread_create(&threadChObBT[2], NULL, ringTheAlarm, NULL);
		//ringTheAlarm();	
	}else{
		rc[3] = pthread_create(&threadChObBT[3], NULL, fasterSpeed, NULL);
		//fasterSpeed();
	}
	pthread_mutex_unlock(&lock);
	for (int i = 0; i < 4; i++){
		if (rc[i]) {
		 printf("\n Error in creation of thread %d.\n", i);
		 exit(-1);
		}
	}
	for (int j = 0; j < 4; ++j){
		pthread_join(threadChObBT[j],NULL);
	}

}
void *CheckObstacleLeftFront()
{
	printf("\n This is CheckObstacleLeftFront Function");
	pthread_mutex_lock(&lock);
	autoSide = 5;
	sensorsRandomValue(autoSide);
	if (LeftFrontSensorsA < 20 && LeftFrontSensorsB < 20 && LeftFrontSensorsC < 20){
		stop();
	}else if (LeftFrontSensorsA < 30 || LeftFrontSensorsB < 30 || LeftFrontSensorsC < 30){
		alarmOn = true;
		ringTheAlarm();	
	}else{
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);

}
void *CheckObstacleLeftBack()
{
	printf("\n This is CheckObstacleLeftBack Function");
	pthread_mutex_lock(&lock);
	autoSide = 7;
	sensorsRandomValue(autoSide);
	if (LeftBackSensorsA < 20 && LeftBackSensorsB < 20 && LeftBackSensorsC < 20){
		stop();
	}else if (LeftBackSensorsA < 30 || LeftBackSensorsB < 30 || LeftBackSensorsC < 30){
		alarmOn = true;
		ringTheAlarm();	
	}else{
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);

}

void *CheckObstacleRightFront()
{
	printf("\n This is CheckObstacleRightFront Function");
	pthread_mutex_lock(&lock);
	autoSide = 6;
	sensorsRandomValue(autoSide);
	if (RightFrontSensorsA < 20 && RightFrontSensorsB < 20 && RightFrontSensorsC < 20){
		stop();
	}else if (RightFrontSensorsA < 30 || RightFrontSensorsB < 30 || RightFrontSensorsC < 30){
		alarmOn = true;
		ringTheAlarm();	
	}else{
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);

}

void *CheckObstacleRightBack()
{
	printf("\n This is CheckObstacleRightBack Function");
	pthread_mutex_lock(&lock);
	autoSide = 8;
	sensorsRandomValue(autoSide);
	if (RightBackSensorsA < 20 && RightBackSensorsB < 20 && RightBackSensorsC < 20){
		stop();
	}else if (RightBackSensorsA < 30 || RightBackSensorsB < 30 || RightBackSensorsC < 30){
		alarmOn = true;
		ringTheAlarm();	
	}else{
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);

}

// readStreetSigns 4 sides
void *readStreetSignsFront()
{
	printf("\n This is readStreetSignsFront Function");
	pthread_t speedThread;
	int rc;
	pthread_mutex_lock(&lock);
	rc = pthread_create(&speedThread, NULL, getSpeedSign, NULL);
	//getSpeedSign();
	varD = varC + 6;
	speedSign = 50;
	pthread_mutex_unlock(&lock);
	if (rc) {
		printf("Error in thread readStreetSignsFront creation.\n");
		exit(-1);
	 }
	 pthread_join(speedThread,NULL);

}
void *readStreetSignsBack()
{
	printf("\n This is readStreetSignsBack Function");
	pthread_t speedThread;
	int rc;
	pthread_mutex_lock(&lock);
	//getSpeedSign();
	rc = pthread_create(&speedThread, NULL, getSpeedSign, NULL);
	varD = varA + 5;
	pthread_mutex_unlock(&lock);
	if (rc) {
		printf("Error in thread readStreetSignsBack creation.\n");
		exit(-1);
	 }
	 pthread_join(speedThread,NULL);

}
void *readStreetSignsLeft()
{
	printf("\n This is readStreetSignsLeft Function");
	pthread_t speedThread;
	int rc;
	pthread_mutex_lock(&lock);
	// getSpeedSign();
	rc = pthread_create(&speedThread, NULL, getSpeedSign, NULL);
	varD = varB + 3;
	pthread_mutex_unlock(&lock);
	if (rc) {
		printf("Error in thread readStreetSignsBack creation.\n");
		exit(-1);
	 }
	 pthread_join(speedThread,NULL);

}
void *readStreetSignsRight()
{
	printf("\n This is readStreetSignsRight Function");
	pthread_t speedThread;
	int rc;
	pthread_mutex_lock(&lock);
	//getSpeedSign();
	rc = pthread_create(&speedThread, NULL, getSpeedSign, NULL);
	varD = varC + 4;
	speedSign = 10;
	pthread_mutex_unlock(&lock);
	if (rc) {
		printf("Error in thread readStreetSignsBack creation.\n");
		exit(-1);
	 }
	 pthread_join(speedThread,NULL);

}

void *goFurther()
{
	printf("\n This is goFurther Function \n");	
	pthread_mutex_lock(&lock);
	autoSpeed = 20;
	printf("speedSign is %d in goFurther Function 1", speedSign);
	getSpeedSign();
	printf("speedSign is %d in goFurther Function 2", speedSign);
	if (speedSign > 10){
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);
		
}


void *CheckTrafficLight()
{
	printf("\n This is CheckTrafficLight Function \n");
	autoSpeed = 5;
	readTraficLight();

}

int main(void) {
	// numofcpus = sysconf(_SC_NPROCESSORS_ONLN);	
	printf("sysconf %d \n", numofcpus);
	int numOfThread = 15;
	printf("numOfThread %d", numOfThread); 
	pthread_t threads[numOfThread];
	int rc;
	int CheckObstacleRc [10];
	int streetSignsRc [5];	
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	
	autoSpeed = 10;
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
	
	streetSignsRc[0] = pthread_create(&threads[8], NULL, readStreetSignsFront, NULL);
	streetSignsRc[1] = pthread_create(&threads[9], NULL, readStreetSignsBack, NULL);
	streetSignsRc[2] = pthread_create(&threads[10], NULL, readStreetSignsLeft, NULL);
	streetSignsRc[3] = pthread_create(&threads[11], NULL, readStreetSignsRight, NULL);
	for (int rc = 0; rc < 4; rc++){
		if (streetSignsRc[rc]) {
		 printf("\n Error in creation of thread %d.\n", rc);
		 exit(-1);
		}
	}
						
	rc = pthread_create(&threads[12], NULL, (void * (*)(void *))(goFurther), NULL);
	if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }	
	rc = pthread_create(&threads[13], NULL, (void * (*)(void *))(CheckTrafficLight), NULL);
	if (rc) {
		printf("Error in thread creation.\n");
		exit(-1);
	  }
		
	for (int i = 0; i < numOfThread; ++i){
		pthread_join(threads[i],NULL);
	}
	
	return EXIT_SUCCESS;
}


void *sensorsRandomValue(int side){
	printf("\n This is sensorsRandomValue Function");
	printf("\n side is %d in sensorsRandomValue \n", side);
	pthread_mutex_lock(&lock);
	switch(side) {
		case 1:							
			FrontTopSensorsA = rand() % 40;		
			printf("\n -- FrontTopSensorsA %d", FrontTopSensorsA);				
			FrontTopSensorsB = rand() % 40;		
			printf("\n -- FrontTopSensorsB %d", FrontTopSensorsB);
			FrontTopSensorsC = rand() % 40;		
			printf("\n -- FrontTopSensorsC %d", FrontTopSensorsC);					
			break;
		case 2:							
			FrontBottomSensorsA = rand() % 50;		
			printf("\n -- FrontBottomSensorsA %d", FrontBottomSensorsA);				
			FrontBottomSensorsB = rand() % 50;		
			printf("\n -- FrontBottomSensorsB %d", FrontBottomSensorsB);
			FrontBottomSensorsC = rand() % 50;		
			printf("\n -- FrontBottomSensorsC %d", FrontBottomSensorsC);					
			break;
		case 3:							
			BackBottomSensorsA = rand() % 30;		
			printf("\n -- BackBottomSensorsA %d", BackBottomSensorsA);				
			BackBottomSensorsB = rand() % 30;		
			printf("\n -- BackBottomSensorsB %d", BackBottomSensorsB);
			BackBottomSensorsC = rand() % 30;		
			printf("\n -- BackBottomSensorsC %d", BackBottomSensorsC);					
			break;
		case 4:							
			BackTopSensorsA = rand() % 50;		
			printf("\n -- BackTopSensorsA %d", BackTopSensorsA);				
			BackTopSensorsB = rand() % 50;		
			printf("\n -- BackTopSensorsB %d", BackTopSensorsB);
			BackTopSensorsC = rand() % 50;		
			printf("\n -- BackTopSensorsC %d", BackTopSensorsC);					
			break;
		case 5:							
			LeftFrontSensorsA = rand() % 30;		
			printf("\n -- LeftFrontSensorsA %d", LeftFrontSensorsA);				
			LeftFrontSensorsB = rand() % 30;		
			printf("\n -- LeftFrontSensorsB %d", LeftFrontSensorsB);
			LeftFrontSensorsC = rand() % 30;		
			printf("\n -- LeftFrontSensorsC %d", LeftFrontSensorsC);					
			break;
		case 6:							
			RightFrontSensorsA = rand() % 30;		
			printf("\n -- RightFrontSensorsA %d", RightFrontSensorsA);				
			RightFrontSensorsB = rand() % 30;		
			printf("\n -- RightFrontSensorsB %d", RightFrontSensorsB);
			RightFrontSensorsC = rand() % 30;		
			printf("\n -- RightFrontSensorsC %d", RightFrontSensorsC);					
			break;
		case 7:							
			LeftBackSensorsA = rand() % 30;		
			printf("\n -- LeftBackSensorsA %d", LeftBackSensorsA);				
			LeftBackSensorsB = rand() % 30;		
			printf("\n -- LeftBackSensorsB %d", LeftBackSensorsB);
			LeftBackSensorsC = rand() % 30;		
			printf("\n -- LeftBackSensorsC %d", LeftBackSensorsC);					
			break;
		case 8:							
			RightBackSensorsA = rand() % 30;		
			printf("\n -- RightBackSensorsA %d", RightBackSensorsA);				
			RightBackSensorsB = rand() % 30;		
			printf("\n -- RightBackSensorsB %d", RightBackSensorsB);
			RightBackSensorsC = rand() % 30;		
			printf("\n -- RightBackSensorsC %d", RightBackSensorsC);					
			break;
		
		default: printf("\n sensorsRandomValue Function"); break;
	}	
	pthread_mutex_unlock(&lock);
}
void *stop()
{
	gearLevers = 1;
	printf("\n This is stop Function \n");
	brake();

}

void brake()
{
	printf("\n BR__________AAAAAAAA_____________KE \n");
	blockAcc = true;
	autoBrake = 1;

}

void *getSpeedSign()
{
	printf("\n This is readStreetSigns Function \n");
	//pthread_mutex_lock(&lock);		
	speedSign = rand() % 100;	
	//pthread_mutex_unlock(&lock);
}

void *fasterSpeed()
{
	printf("\n This is fasterSpeed Function \n");
	varA = 2;
	varC = varA + varC;
	varD = varC * 2;	 
	pthread_mutex_lock(&lock);
	autoSpeed = speedSign - varD;
	gearLevers = 3;
	gearLevers = gearLevers + 1;
	printf("\n autoSpeed is %d in fasterSpeed", autoSpeed);
	pthread_mutex_unlock(&lock);	

}

void *ringTheAlarm(){
	if (alarmOn){
		autoAlarmSound = 1;
		printf("\n ALARM => B_______________EEEEEEEEE___________B \n");		
	}
	printf("\n This is ringTheAlarm Function \n");
}

void slowDown()
{
	printf("\n This is slowDown Function");
	pthread_mutex_lock(&lock);
	autoSpeed = autoSpeed - 20;
	varD = varD - 3;
	gearLevers = 1;
	pthread_mutex_unlock(&lock);

}

void goBack()
{
	printf("\n This is goBack Function");
	pthread_mutex_lock(&lock);
	autoSpeed = autoSpeed - 20;
	gearLevers = -1;
	pthread_mutex_unlock(&lock);

}

void readTraficLight(){
	pthread_mutex_lock(&lock);
	lightColor = rand() % 3;
	if (lightColor == red){
		blockAcc = true;
		stop();
	}else if (lightColor == yellow){
		blockAcc = true;
		slowDown();
	}else if (lightColor == green){
		blockAcc = false;
		fasterSpeed();
	}
	pthread_mutex_unlock(&lock);
	
}



