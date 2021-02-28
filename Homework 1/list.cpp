/* @BEYZA
Student Name: Beyza OZAN
Student ID: 150180056
Date: 15/10/2019 */

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include "list.h"

using namespace std;

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
        head =temp;
    
        return;
    }
    else if(x== head->shoe_size){//yeni no head'dekine eşitse-> head'in sayısı 1 arttırılır.
        head->quantity++;
        return;
    }
    else{ // yeni no head'dekinden büyükse->yerini bulana kadar listede dolaşacak.
        shoe_node * traverse, *temp ;
        traverse =head;
        while(traverse->next){
            if(traverse->next->shoe_size>=x)
                break;
            traverse= traverse->next;
        }
        if(traverse->next && x==traverse->next->shoe_size)
            traverse->next->quantity++;
        else{ // yeni gelen numaradan daha önce yoksa->yeni kutu oluşturulur.
            temp=new shoe_node;
            temp->shoe_size = x;
            temp->quantity=1;
            temp->next = traverse->next;
            traverse->next = temp;
        }
    }
    
}
//not finished
void stock::sell(int x)
{
    shoe_node *traverse, *tail;
    traverse =head;
    if (head ==NULL){
        cout<<"invalid value"<< endl;
        return ;
    }
        if(abs(x)==traverse->shoe_size and traverse->quantity==1){//silmek istediği no ilk kutudaysa ve 1 taneyse -> kutuyu sil.
            head = head->next;
            delete traverse;
            return;
        }
        else if (abs(x)==traverse->shoe_size and traverse->quantity>1)){//silmek istediği no ilk kutudaysa ve 1den fazlaysa -> sayıyı 1 azalt.
            traverse->quantity--;
            return ;}
        while(abs(x)!=traverse->shoe_size and traverse){//silmek istediği no ilk kutuda değilse ve traverse null değilse ->bu koşullardan biri gerçekleşene kadar tail ve traverse ilerlesin.
            tail->next= traverse;
            traverse=traverse->next;
        }
        if(traverse and traverse->quantity==1){//silmek istediği no'ya ulaştığında kutuda 1 tane varsa ->kutuyu sil.
            tail->next = traverse->next;
            traverse->next = NULL;
            delete traverse;
            return;
        
        }
        else if(traverse and traverse->quantity>1){//silmek istediği no'ya ulaştığında kutudan 1den fazla varsa -> sayıyı 1 azalt.
            traverse->quantity--;
        }
        else if(abs(x)!=traverse->shoe_size){// istediği no'ya ulaşamadan list bittiyse-> stokta yok demektir.
            cout >>"NO_STOCK">>endl;
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
        head= head->next;
        delete p;
    }
    
    
}
//not finished
void stock::ReadFromFile()
{
    int num;// her seferinde alınan sayıları bu değişkene ata
    ifstream myfile ("input.txt");
    if(myfile.is_open()){
    
    while(myfile>>num ){ //dosya sonuna gelene kadar
        
        if(num>0)
            add_stock(num);
    
        else if(num==0)
            current_stock();
    
        else// when the number is negative
            sell(num);
    }
        
    myfile.close();
    }
}

