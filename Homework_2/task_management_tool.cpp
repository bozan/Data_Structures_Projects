/* @ozan18
Student Name: Beyza Ozan
Student ID : 150180056
Date: 27.10.2019 */

/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}

//done
void WorkPlan::create()
{   head = NULL;
	//THIS FUNCTION WILL BE CODED BY YOU
}
void WorkPlan::close()
{
    Task *x, *y;
    
    while(head){ // head and x provide to delete horizontal nodes
        x = head;
        head = head->next;
        x->next =NULL;
        while(x){ // x and y provide to delete vertical nodes
            y = x;
            x = x->counterpart;
            delete y;
            }
    }
    
	//THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::add(Task *task)
{
    Task *tasknew;
    tasknew = new Task; // create new node and relay all information about task into new node
    tasknew->day = task->day;
    tasknew->time = task->time;
    tasknew->name = new char[strlen(task->name)];
    strcpy(tasknew->name,task->name);
    tasknew->priority = task->priority;
    tasknew->counterpart = NULL;
    
    if(head == NULL){ // there is no node yet -1
        head = tasknew;
        head->next = head ;
        head->previous = head;
        return;
    }
    
    else if(tasknew->day < head->day){ // if task is a day smaller than head -> task is added horizontally before head -2
        tasknew-> next = head;
        tasknew-> previous = head->previous;
        head->previous->next = tasknew;
        head->previous =tasknew;
		head = tasknew;
        return;
    
    }
    else if(tasknew->day == head->day){// if task and head on the same day -3
        Task *temp ,*traverse;
        Task *other;
        other = new Task;
        temp = head;
        if(tasknew->time < temp->time || (temp->time == tasknew->time &&  tasknew->priority > temp->priority)){// and if task's time less than head's ->task is added vertically before head 3.1
            tasknew->counterpart = temp;
            tasknew->previous =head->previous;
            head->previous->next = tasknew;
            tasknew->next= head->next;
            head->next->previous =tasknew;
            head->next = NULL;
            head->previous = NULL;
            head = tasknew;
            return;
        }
        else if(temp->time == tasknew->time){ //and if task's time and head's time at the same time 3.2
            other =getTask(tasknew->day,tasknew->time);
            if(temp->priority >= tasknew->priority){ //if head's priority bigger than task's-> search new place for task and add
                checkAvailableNextTimesFor(tasknew);
                tasknew->day=getUsableDay();
                tasknew->time=getUsableTime();
                add(tasknew);
            }
            else if(tasknew->priority > temp->priority){//if task's priority bigger than head's-> swap task and head's information.then search new place for head.
                temp->priority = tasknew->priority;
                strcpy(temp->name,tasknew->name);
                checkAvailableNextTimesFor(other);
                other->day=getUsableDay();
                other->time=getUsableTime();
                add(other);
            
            }
        }
        else if(getTask(tasknew->day,tasknew->time)!= NULL && tasknew->time > temp->time ){// if task's time bigger than head's time and the location is not aviable 3.3
            other =getTask(tasknew->day,tasknew->time);
            while(temp->time != tasknew->time ){ // temp is traversing until it find task's time.
                temp = temp->counterpart;
            }
            if(tasknew->priority > temp->priority ){// if task's priority bigger than temp's priority
                temp->priority = tasknew->priority;
                strcpy(temp->name,tasknew->name);
                checkAvailableNextTimesFor(other);
                other->day=getUsableDay();
                other->time=getUsableTime();
                add(other);
                return;
            }
            else if(tasknew->priority <= temp->priority){// if temp's priority bigger than task's priority
                checkAvailableNextTimesFor(tasknew);
                tasknew->day=getUsableDay();
                tasknew->time=getUsableTime();
                add(tasknew);
            }
            return;
        }
        else if(getTask(tasknew->day,tasknew->time)==NULL && tasknew->time > temp->time ){//if task's time bigger than head's time and the location is aviable 3.4
    
            while(temp != NULL && tasknew->time > temp->time ){ // temp is traversing until it find task's time
                traverse = temp;
                temp = temp->counterpart;
                traverse->counterpart = temp;
            }// the task is inserted between traverse and temp
            if(temp == NULL){ // if traverse reach the last node(time) of day
                traverse->counterpart = tasknew;
                tasknew->counterpart = NULL;
            }
            else{
                tasknew->counterpart = temp;
                traverse->counterpart = tasknew;
                
            }
        
       }
    }
    else if(tasknew->day > head->day){// the task'day bigger than head's day -4
        Task *temp;
        temp =head;
        while(head->previous != temp && tasknew->day > temp->day){
            temp = temp->next;
        }
        if(tasknew->day > temp->day && head->previous == temp) { // when adding the task second day
            if(tasknew->day > temp->day){// temp traversed all list and reached the last day.
                temp->next = tasknew; // task is inserted between the last day and head
                tasknew->previous = temp;
                tasknew->next = head;
                head->previous = tasknew;
                return;
            }
        }
        
        if(tasknew->day == temp->day){ // when the day which is task's day is found (temp is point to appointment that starting of day)
            Task * traverse;
            Task *other;
            other = new Task;
            if(tasknew->time < temp->time ){// if temp's time bigger than task's time  1
                tasknew->counterpart = temp;
                temp->next->previous = tasknew;
                tasknew->next = temp->next;
                temp->next = NULL;
                temp->previous->next = tasknew;
                tasknew->previous = temp->previous;
                temp->previous =NULL;
                return;
            }
            else if(tasknew->time == temp->time){ // if task's time equal to temp's time 2
                if(tasknew->priority <= temp->priority){ // temp's priority bigger than task's priority
                    checkAvailableNextTimesFor(tasknew);
                    tasknew->day=getUsableDay();
                    tasknew->time=getUsableTime();
                    add(tasknew);
                    return;
                }
                else if(tasknew->priority > temp->priority){ // task's priority bigger than temp's priority
                    other =getTask(tasknew->day,tasknew->time);
                    temp->priority = tasknew->priority;
                    strcpy(temp->name,tasknew->name);
                    checkAvailableNextTimesFor(other);
                    other->day=getUsableDay();
                    other->time=getUsableTime();
                    add(other);
                    return;                }
            }
            else if(getTask(tasknew->day,tasknew->time)==NULL && tasknew->time > temp->time ){//if task's time bigger than temp's time and the location is aviable 3
            
                    while(temp != NULL && tasknew->time > temp->time ){ //temp is traversing until it find task's time
                        traverse = temp;
                        temp = temp->counterpart;
                        traverse->counterpart = temp;
                    }// the task is inserted between traverse and temp
                    if(temp == NULL){
                        traverse->counterpart = tasknew;
                        tasknew->counterpart = NULL;
                    }
                    else{
                        tasknew->counterpart = temp;
                        traverse->counterpart = tasknew;
                    }
                
               }
            else if(getTask(tasknew->day,tasknew->time)!=NULL && tasknew->time > temp->time){ //  if task's time bigger than temp's time and the location is not aviable 4
                other =getTask(tasknew->day,tasknew->time);
                if(tasknew->priority > other->priority ){// if task's priority bigger than other's priority
                    while(temp->time != tasknew->time ){
                        temp = temp->counterpart;
                    }
                    temp->priority = tasknew->priority;
                    strcpy(temp->name,tasknew->name);
                    checkAvailableNextTimesFor(other);
                    other->day=getUsableDay();
                    other->time=getUsableTime();
                    add(other);
                    return;
                }
                else if(tasknew->priority <= other->priority){ // if other's priority bigger than task's priority
                    checkAvailableNextTimesFor(tasknew);
                    tasknew->day=getUsableDay();
                    tasknew->time=getUsableTime();
                    add(tasknew);
                    return;
                }
            }
        }
        else if(tasknew->day < temp->day && tasknew->day > head->day){ //if task's day is not created before. insert task's day before temp
            temp-> previous->next = tasknew;
            tasknew->previous =temp->previous;
            temp-> previous =tasknew;
            tasknew-> next = temp;
        }
    }
    
} 

Task * WorkPlan::getTask(int day, int time) // check which appointments consistent in that day and time
{
    Task *target ,*ptarget;// node target and pointer target
    target = new Task;
    ptarget = head;
    if(day < head->day) // wanted day smaller than head's day -> there is no appointments
        return NULL;
    
    else if(head->day == day){ // wanted day equal to head's day -> search time
        if(head->time == time){ // wanted time equal to head's time
            *target = *head;
            return target; // target == head
        }
        else if(time < head->time) // wanted time less than head's time -> there is no appointments
            return NULL;
        else if(time > head->time){ // wanted time bigger than head's time -> traverse until find that time
            while(ptarget != NULL && ptarget->time != time){
                ptarget = ptarget->counterpart;
            }
            if(ptarget ==NULL){ // reached end of day and not found any appointments
                return NULL;
            }
            else if(ptarget->time == time){ // if that time is found
                target->day = ptarget->day;
                target->time = ptarget->time;
                target->priority =ptarget->priority;
                target->name = new char[strlen(ptarget->name)];
                strcpy(target->name,ptarget->name);
                return target;
            }
        }
    }
    else if(day > head->day){ // wanted day bigger than head's day
        while(ptarget->day != day && ptarget->next != head){
            ptarget = ptarget->next;
        }
        if(ptarget->day == day){ // when wanted day is found
            if(time < ptarget->time){ //if wanted time less than starting of day's time -> there is no appointments
                return NULL;
            }
            else if(time == ptarget->time){ // if wanted time equal to starting of day's time
                target->day = ptarget->day;
                target->time = ptarget->time;
                target->priority =ptarget->priority;
                target->name = new char[strlen(ptarget->name)];
                strcpy(target->name,ptarget->name);
                return target;
            }
            else if(time > ptarget->time){ // if wanted time bigger than starting of day's time -> traversing other times
                while(ptarget != NULL && ptarget->time != time){
                    ptarget = ptarget->counterpart;
                    
                }
                if(ptarget ==NULL){ // wanted time is not found
                    return NULL;
                }
                else if(ptarget->time == time){ // wanted time is found
                    target->day = ptarget->day;
                    target->time = ptarget->time;
                    target->priority =ptarget->priority;
                    target->name = new char[strlen(ptarget->name)];
                    strcpy(target->name,ptarget->name);
                    return target;
                }
            }
        }
        else if(ptarget->day != day && ptarget->next ==head){ // traversed all list and returned head of list. Not found day
            return NULL;
        }
    }
    return NULL;
	//THIS FUNCTION WILL BE CODED BY YOU
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{
    
    Task *temp,*tail ;
    temp = new Task;
    temp = head;
    tail = head;
    while(temp->day != delayed->day){ // accessing day which is delayed
        temp = temp->next;
        tail = temp->next;
    }
    while(temp->time < delayed->time){ // accesing time which is delayed
        temp = temp->counterpart;
    } // temp is equal to delayed
    while(temp->time != ShowLastHourOn(temp->day)){ //findig next available time after delayed's time in same day
        if(temp->counterpart->time - temp->time >1){ //if found null time-> insert that time
            usable_time = temp->time + 1;
            usable_day = delayed->day;
            return ;
        }
        temp = temp->counterpart;
    }//the loop is over however not found appropriate time
    if(temp->time == ShowLastHourOn(temp->day)){//if temp equal to last of the days
        while(tail != head){
            for(int i=8;i<ShowLastHourOn(tail->day);i++){ // search new place inside the other days for  delayed
                if( getTask(tail->day,i)==NULL){
                    usable_day = tail->day;
                    usable_time = i;
                    return;
                }
            }
            tail = tail->next;
        }
        if(tail == head){ // if tail reached end of list and not found aviable time
            while(tail->next->day - tail->day <= 1 && tail->next !=head){ // traverse until find null day between existing days
                tail = tail->next;
            }
            delayed->day = tail->day + 1;
            delayed->time = 8;
            usable_day = delayed->day;
            usable_time = delayed->time;
        }
        
    }
    //THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::delayAllTasksOfDay(int day)
{
    Task *traverse,*temp;
    temp = new Task;
    traverse = head;
    
    while(traverse->day != day){ // traverse until access day which is delayed
        traverse = traverse->next;
    }
    temp->day = traverse->day;
    temp->time = traverse->time;
    temp->priority = traverse->priority;
    temp->name = new char[strlen(traverse->name)];
    strcpy(temp->name,traverse->name);
    
    checkAvailableNextTimesFor(temp);
    temp->day=getUsableDay();
    temp->time=getUsableTime();
    add(temp);
    if(traverse->counterpart != NULL){ // until finish appointments which is delayed
        remove(traverse);
        delayAllTasksOfDay(day); //her randevuyu tek tek sil sonra o günü tekrar erteleme fonksiyonuna al ta ki gün sonuna gelene kadar
    }
    else{
        remove(traverse); //finally if traverse->counterpart is null , remove the last time of that day
        return;
    }
        
}
   
void WorkPlan::remove(Task *target)
{
    Task *tail, *temp;
    temp = head;
    tail = temp;
    while(temp->day != target->day){ // find day which want to remove
        temp = temp->next;
    }
    while(temp->time != target->time){ // find time which want to remove
        tail = temp;
        temp = temp->counterpart;
    }
    
    
    if(temp->day == head->day){ // temp == target
        if(temp->counterpart ==NULL && temp->time == head->time){ //if we want to remove head and there is no task after (below) head
            temp->next->previous =head->previous;
            head->previous->next =temp->next;
            head = head->next;
            temp->previous =NULL;
            temp->next = NULL;
            delete temp;
            return;
    
        
        }
        else if(temp->counterpart != NULL && temp->time == head->time ){// if we want to remove head and one task exist after (below) head
            head = head->counterpart;
            head->next =temp->next;
            temp->next->previous =head;
            temp->previous->next =head;
            head->previous =temp->previous;
            temp->next = NULL;
            temp->counterpart = NULL;
            temp->previous =NULL;
            delete temp;
            return;
        }
    }
    else if(temp->counterpart == NULL && temp->next !=NULL){//if we want to remove task except head and there is no task below temp
        temp->previous->next =temp->next;
        temp->next->previous = temp->previous;
        delete temp;
        return;
    }
    else if(temp->counterpart != NULL && temp->next !=NULL){//if we want to remove task except head and one task exist below the temp
        temp->counterpart->next =temp->next;
        temp->counterpart->previous = temp->previous;
        temp->previous->next =temp->counterpart;
        temp->next->previous = temp->counterpart;
        temp->counterpart = NULL;
        temp->next = NULL;
        temp->previous = NULL;
        delete temp;
        return;
    }
    else if (temp->next ==NULL){ //the task which want to remove is not starting of any day
        tail->counterpart = temp->counterpart;
        delete temp;
        return;
        
        
    }

    
	//THIS FUNCTION WILL BE CODED BY YOU
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
                    
int WorkPlan::ShowLastHourOn(int day){ // girilen gundeki son saati dondurur.
  Task *traverse;
  traverse = new Task;
  traverse = head;
  while(traverse->day != day){
  traverse = traverse->next;
  } // döngü sonunda günü bulmuş oluruz.
  while(traverse->counterpart != NULL){
      
        traverse = traverse->counterpart;
  }// döngü sonunda traverse o günki son randevuyu göstermiş olur
                    
  return traverse->time;
}
