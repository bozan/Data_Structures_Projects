/* @ozan18
Student Name: Beyza Ozan
Student ID : 150180056
Date: 27.10.2019
 
PLEASE DO NOT CHANGE THIS FILE 
*/


#define NAME_LENGTH 2

struct Task{
	char *name;
	int day;
	int time;
	int priority;

	Task *previous;
	Task *next;
	Task *counterpart;
};
