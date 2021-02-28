/* @ozan18
Student Name: Beyza Ozan
Student ID: 150180056
Date: 19.10.2019 */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

struct shoe_node
{
    int shoe_size;
    int quantity;
    shoe_node *next; // pointer to other object
};

struct stock
{
    shoe_node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
    void ReadFromFile(char* );
};

//creating stock list
void stock::create()
{
    head = NULL;
}
//get new shoes into stock
void stock::add_stock(int x){
    if(head==NULL){// henüz kutu yok. head oluşturduk ve içini doldurduk.
        head = new shoe_node;
        head->next =NULL;
        head->quantity=1;
        head->shoe_size = x;
        return;
    }
    if(x < head->shoe_size){//yeni numara head'den küçükse->listenin en başına eklenir
        shoe_node *temp;
        temp = new shoe_node;
        temp->next =head;
        temp->quantity =1;
        temp->shoe_size = x;
        head=temp;
    
        return;
    }
    else if(x== head->shoe_size){//yeni no head'dekine eşitse-> head'in sayısı 1 arttırılır.
        head->quantity++;
        return;
    }
    else{ // yeni no head'dekinden büyükse->yerini bulana kadar listede dolaşacak.
        shoe_node * traverse, *temp ;
        traverse =head;
       
        while(traverse->next && traverse->next->shoe_size<x )
            traverse= traverse->next; // ekleme yapilacak konuma erismek
        if(!traverse->next ){
            temp=new shoe_node;
            temp->shoe_size = x;
            temp->quantity=1;
            traverse->next=temp;
            temp->next= NULL;
            return ;
        }
            
        
        if( x == traverse->next->shoe_size ){
            traverse->next->quantity++;
            return;
        }
        if(x<traverse->next->shoe_size){ // yeni gelen numaradan daha önce yoksa->yeni kutu oluşturulur.
            temp=new shoe_node;
            temp->shoe_size = x;
            temp->quantity=1;
            temp->next = traverse->next;
            traverse->next = temp;
            return;
        }
    }
    
}

void stock::sell(int x)
{
    shoe_node *traverse, *tail;
    traverse = head;
    tail=head;
    if(!head){
        cout<<"NO_STOCK"<<endl;
        return;
    }
    if(abs(x)<head->shoe_size){
        cout<<"NO_STOCK"<<endl;
        return;
    }
    if( abs(x) == traverse->shoe_size and traverse->quantity == 1 ){//silmek istediği no ilk kutudaysa ve 1 taneyse -> kutuyu sil.
            head=head->next;
            delete traverse;
            return;
    }
    else if ( abs(x) == traverse->shoe_size and traverse->quantity > 1 ){//silmek istediği no ilk kutudaysa ve 1den fazlaysa -> sayıyı 1 azalt.
            traverse->quantity--;
            return ;
    }
    while( abs(x) != traverse->shoe_size and traverse ){//silmek istediği no ilk kutuda değilse ve traverse null değilse ->bu koşullardan biri gerçekleşene kadar tail ve traverse ilerlesin.
            tail=traverse;
            traverse=traverse->next;
            tail->next = traverse;
        }
        
    if( traverse and traverse->quantity==1 ){//silmek istediği no'ya ulaştığında kutuda 1 tane varsa ->kutuyu sil.
            traverse->quantity--;
            tail->next = traverse->next;
            //cout<<abs(x)<<"oooo";
            delete traverse;
            return;
            
    }
     else if( traverse and traverse->quantity>1 ){//silmek istediği no'ya ulaştığında kutudan 1den fazla varsa -> sayıyı 1 azalt.
            traverse->quantity--;
            return ;
            }
        
        
    else if( abs(x) != traverse->shoe_size ){// istediği no'ya ulaşamadan list bittiyse-> stokta yok demektir.
            cout <<"NO_STOCK" << endl;
            return;
    }
   
    
    
}
//print current stock of the shoes in the shop
void stock::current_stock(){
    shoe_node *traverse;
    traverse =head;
    while(traverse){
        cout << traverse->shoe_size <<":"<< traverse->quantity<<endl;
        traverse = traverse->next;
    }
    
    
}

//Deletes all of the nodes of the list.
void stock::clear(){
    shoe_node *p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
    
    
}
//not finished
void stock::ReadFromFile(char* f)
{
    int num;// her seferinde alınan sayıları bu değişkene ata
    FILE* file;
    file = fopen(f,"r+");
    fseek(file,0,SEEK_SET);
    if(!file){
        cout <<"file don't open"<<endl;
        return;
    }
        while(!feof(file)){
            
            fscanf(file,"%d",&num);
            if(num>0)
                add_stock(num);
    
            else if(num==0)
                current_stock();
    
            else// when the number is negative
                sell(num);
            
   
    }
}
stock my_stock;

int main(int argc,char*argv[]){
    char* my_file;
    my_file =argv[1];
    my_stock.create();
    my_stock.ReadFromFile(my_file);
    my_stock.clear();
    return 0;
}
