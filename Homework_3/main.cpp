/* @ozan18
Student Name: BEYZA OZAN
Student ID: 150180056
Date: 16.12.2019 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

struct HS { // mobile host's struct
    int mobile_number;
    HS *next;
};
struct BS { // base station's struct
    int base_number ;
    BS *brother;
    BS *child;
    HS *MobileH;
    BS* previous;
    BS* previous_p;
};
struct network {
    BS *Central_Controller;
    
    void create();
    void close();
    void sclose(BS* base_station);
    void add_BS(int base_station,int parent);
    void add_MH(int mobile_host,int parent);
    bool traverse(BS*,int mobile_host);
    int find_parent_of_mh(BS* Traverse ,int mobile_host);
    BS* find_parent_of_bs(BS*);
    BS* search(BS* Central_Controller,int base_station); // search and find given base number then return this base station struct
    void print_stack(int parent);
    void add_from_file(char*);
    void take_message_from_file_and_deliver(char* f);
};
network MyNetwork;
// CREATE STACK TO PRINT SHORTEST PATH
struct node{
    int data;
    node* next;
};
struct stack{ // need stack structure to find shorthest path
    node* head;
    void create();
    void close();
    void push(int);
    int pop();
    bool isempty();
};
stack my_stack;

void stack::create(){
    head = NULL;
}
void stack::close(){ // delete all node one by one in stack
    node* p;
    while(head){
    p= head;
    head = head->next;
    delete p;
    }
}
void stack::push(int parent){ // base station is added to top of stack
    node* newnode = new node;
    newnode->data = parent;
    newnode->next = head;
    head = newnode;
}
int stack::pop(){ // base station which is top of stack is taken from there
    int x;
    node* topnode = new node;
    topnode = head;
    head = head->next;
    x = topnode->data;
    delete topnode;
    return x;
}
bool stack::isempty(){ //it checks stack is empty or not
    return head == NULL;
}

void network::create(){ // create first node which is not have any ID (Cenral Controller)
    Central_Controller = new BS;
    Central_Controller->child = NULL;
    Central_Controller->brother = NULL;
    Central_Controller->base_number = 0;
}
void network::sclose(BS* base_station){ //delete mh and bs one by one with recursive
    if(base_station==NULL)
        return ;
    sclose(base_station->child); // firstl go to bs child until there are no children
    sclose(base_station->brother); // after bs->child is null, go to bs brother until there are no bs
       if(base_station->MobileH){ // delete mobile hosts
            HS * hs_1;
            HS * hs_2 = base_station->MobileH;
            do {
                hs_1 = hs_2->next;
                HS * hs_3 = hs_2;
//                cout<<"deleting mh : "<<hs_3->mobile_number<<endl; for checking
                delete hs_3;
                hs_2=hs_1;
            }while(hs_2);
       }
//    cout <<"deleting bs : "<<base_station->base_number<<endl; for checking
    delete base_station; // delete base stations

}
void network::close(){ // i need second close because i had to use a function which is not take a parameter in the main funciton
    sclose(Central_Controller);
}
// ENDING STACK ISSUES

void network::add_BS(int base_station,int parent){ // adding base stations(new nodes) to my doubly and multi-linked list
    BS *temp = Central_Controller;
    BS *newbase;
    newbase = new BS; // create a new struct node
    newbase->base_number = base_station; // base station number(taken parameter) is assigned to new struct node
    newbase->brother = NULL;
    newbase->child = NULL;
    newbase->MobileH = NULL;
    newbase->previous = NULL;
    newbase->previous_p = NULL;
    if(Central_Controller -> child == NULL){ // if cc not have any child then new node is added as cc' first child
        Central_Controller -> child = newbase;
        newbase->previous_p = Central_Controller;
        temp = temp->brother;
        return ;
    }
    temp = temp->child;
    if( parent == 0 ){ // if cc have even one child and also the new node's parent is cc then,the new node is added as brother.
        while(temp->brother)
            temp = temp->brother;
        temp->brother = newbase;
        newbase->previous = temp;
        return ;
    }
    if(parent != 0){ //if the new node is lower than cc level then, firstly find parent(through pointer) then add
       temp = search(Central_Controller,parent); // return pointer which is point to parent's location
        if(temp->child == NULL){
            temp->child = newbase;
            newbase->previous_p = temp;
        }
        else {
            temp = temp->child;
            while(temp->brother)
                temp = temp->brother;
            temp->brother = newbase;
            newbase->previous = temp;
        }
    }
}
void network::add_MH(int mobile_host,int parent){ // add mobile hosts into doubly and multi-linked list
    BS *temp = Central_Controller;
    HS *newhost;
    newhost = new HS;
    newhost->mobile_number = mobile_host; // new phone number is assigned to struct node
    newhost->next = NULL;
    temp = search(Central_Controller,parent);// find pointer which is point to mh's parent
    
    if(temp->MobileH == NULL) // if parent dont have any mh then add first mh number to the base station(temp)
        temp->MobileH = newhost;
    else { // if parent already have even one mobile host then
        HS* temp2 = temp->MobileH;
        while(temp2->next) // repeat until find null location
            temp2 = temp2->next;
        temp2->next = newhost; // reached null , add there
    }
}
bool network::traverse(BS* Traverse ,int mobile_host){// print base stations which is traversed with recursive
    if(Traverse==NULL)
        return false;
    cout << Traverse->base_number <<" ";
    HS * hs = Traverse->MobileH;
    while(hs){
        if(hs->mobile_number == mobile_host){
            return true;
        }
        hs = hs-> next;
    }
    if(traverse(Traverse->child,mobile_host))
        return true;
    
    return traverse(Traverse->brother,mobile_host);
}
int network::find_parent_of_mh(BS* Traverse ,int mobile_host){// find parent of mobile host which is parameter with recursive
    if(Traverse==NULL)
        return -1;
    HS * hs = Traverse->MobileH;
    while(hs){
        if(hs->mobile_number == mobile_host){
            return Traverse->base_number;
        }
        hs = hs-> next;
    }
    int a= find_parent_of_mh(Traverse->child,mobile_host);
    if(a!=-1)
        return a;
    return find_parent_of_mh(Traverse->brother,mobile_host);
}

BS* network::find_parent_of_bs(BS* baz){ // find parent of base stations by using two previous pointer which is point back
    BS* traverse = baz;
    while(traverse->previous)
        traverse = traverse-> previous;
    return traverse->previous_p;
    
    
}

BS* network::search(BS * traverse,int base_station){ //find and return the pointer which points to taken parameter

    if(traverse== NULL)
        return NULL;
    
    if(traverse->base_number == base_station)
        return traverse;

    BS * x = search(traverse->child,base_station);
    if(x == NULL)
        x = search(traverse->brother,base_station);
    return x;
}
void network::print_stack(int mh){ // print shortest path with using stack
    int parent = find_parent_of_mh(Central_Controller,mh);
    BS * returned = search(Central_Controller,parent);
    my_stack.create();
    my_stack.push(parent);
    while(parent !=0){
        returned = find_parent_of_bs(returned);
        parent = returned->base_number;
        my_stack.push(parent);
    }
    
    while(!(my_stack.isempty())){ // while stack is not empty, this funciton prints the stack's elements top to bottom
        cout<<my_stack.pop()<<" ";
        
    }
    my_stack.close();
    
}

void network::add_from_file(char* f){  // read from first(network.txt) file
    FILE * my_file;
    my_file = fopen(f,"r");
    char cinput1,cinput2;
    int input2,input3;
    while(!feof(my_file)){
        fscanf(my_file," %c%c",&cinput1,&cinput2);
        fscanf(my_file,"%d",&input2);
        fscanf(my_file,"%d",&input3);
        if(cinput1 == 'B'){ // if node is wanted to add as base station,
            add_BS(input2,input3);
        }
        else if(cinput1 == 'M') // if node is wanted to add as mobile host,
            add_MH(input2,input3);
    }
    fclose(my_file);
}
int to_int(string a) //convert string to integer value
{
    
    int i=a.size()-1,ans=0,t=1;
    while(i>=0)
    {
        if(a[i]>'9' or a[i]<'0')
        {
            i--;
            continue;
        }
        ans+=t*(a[i]-'0');
        t*=10;
        i--;
    }
    return ans;
}

void network::take_message_from_file_and_deliver(char* f){ // take message from second(message.txt) file and print all output
    FILE * my_file;
    my_file = fopen(f,"r");
    string input;
    int MHost;
    int i=0;
    

    while(!feof(my_file)){
        input="";
        char ch;
        fscanf(my_file,"%c",&ch);
        while(ch!='\n' && !feof(my_file)){
            input += ch;
            fscanf(my_file,"%c",&ch);
        }
        i=0;
    
        while(input[i]!='>'){
            i++;
        }
        string message,wanted;
        message = input.substr(0,i);
        wanted = input.substr(i+1,input.size()-i-1);
        MHost = to_int(wanted); // convert string to integer.
        cout<<"Traversing:";
        traverse(Central_Controller,MHost); // print traverse's path.
        cout<<endl;
        int parent = find_parent_of_mh(Central_Controller,MHost);
        if(parent == -1) // if the entered mobile host's number is not belong to any base station
            cout <<"Can not be reached the mobile host mh_"<<MHost<<" at the moment"<<endl;
        else {
            cout<<"Message:"<<message<<" To:";
            print_stack(MHost);
            cout<<"mh_"<<MHost<<endl;
        }
    }
    fclose(my_file); // remove all nodes(clear memory)
}



int main(int argc,char*argv[]){
    char* first_file;
    char* second_file;
    first_file = argv[1];
    second_file = argv[2];
    MyNetwork.create();
    MyNetwork.add_from_file(first_file);
    MyNetwork.take_message_from_file_and_deliver(second_file);
    MyNetwork.close();
    
return 0;
}
