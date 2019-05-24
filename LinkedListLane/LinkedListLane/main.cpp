//
//  main.cpp
//  LinkedListLane
//
//  Created by Sarvesh Bhatnagar on 03/05/19.
//  Copyright © 2019 introtoalgo.com. All rights reserved.
//

#include <iostream>
#include <cmath>
#define out std::cout
#define endl std::endl

int count = 1;
int tempValue = 1;
int cVal = 1;


//A simple linked list with elements id, and next node.
//Following methods are defined for the object of linked list :
//getId , returns int id
//setID used for setting id to a new value.
//3 pointers are also declared  : temp , first and last.
class List{
    int id;
    List *next;
public:
    List() : id(count),next(NULL){count+=1;}
    void setNext(List *n){next = n;}
    List * getNext(){return next;}
    int getId(){return id;}
    void setId(int myid){id = myid;}
    ~List(){out<<"Destroyed "<<id<<endl;}
}*temp(NULL),*first(NULL),*last(NULL);



//A simple linked list for the lane consisting of next and up
// next for next node in lane and up for going to the main linked list.
//following methods are defined in Lane DS, : setNext and setUp
class Lane{
    Lane * next;
    List * up;
public:
    Lane() : next(NULL),up(NULL){}
    Lane * getNext(){return next;}
    List * getUp(){return up;}
    void setNext(Lane *n){next = n;}
    void setUp(List *u){up = u;}
}*lastL(NULL),*tempL(NULL),*firstL(NULL);





//namespace lane contains add(List *u), destroy(), search(int n)((id)), printLane()
namespace lane {
    //Adds a lane node with list u.
    void add(List *u){
        tempL = new Lane();
        tempL->setUp(u);
        if (firstL != NULL) {
            lastL->setNext(tempL);
        }else{
            firstL = tempL;
        }
        lastL = tempL;
    }
    
    //Destroys lane.
    void destroy(){
        tempL = firstL;
        lastL = NULL;
        while (tempL != NULL) {
            firstL = tempL->getNext();
            delete tempL;
            tempL = firstL;
        }
    }
    
    //Searches for a lane element which is just less than the id we are looking for.
    Lane* search(int n){
        if (firstL != NULL) {
            tempL = firstL;
            Lane * back = tempL;
            while (tempL != lastL) {
                if (tempL->getUp()->getId() >= n) {
                    return back;
                }
                back = tempL;
                tempL= tempL->getNext();
            }
            return tempL;
        }else{return NULL;}
    }
    
    
    //Prints the lane elements id's to which they are connected.
    void printLane(){
        if (firstL != NULL) {
            tempL = firstL;
            while (tempL != NULL) {
                out<<"Lane node id "<<tempL->getUp()->getId()<<endl;
                tempL = tempL->getNext();
            }
        }
    }
    
}


//namespace linkedList contains :
// print(), add(), add(n), destroy(), search()((returns list pointer)),
//destroy(n)((destroy element with id n)) checkIfNextIsLane(), square(int a),cube(int a), quad(int a)
//addWithLaneMakeList(int n)((tells which function to use for adding with lane i.e. square,
//makeList(int n)
namespace linkedList {
    
    //Some basic Mathematical functions.
    int square(int a){return pow(a, 2);}
    int cube(int a){return pow(a, 3);}
    int quad(int a){return pow(a, 4);}
    int pent(int a){return pow(a, 5);}
    int hex(int a){return pow(a, 6);}
    int hept(int a){return pow(a, 7);}
    int oct(int a){return pow(a, 8);}
    
    
    int callFunction(int n,int val){
        switch (n) {
            case 1:
                return square(val);
            case 2:
                return cube(val);
            case 3:
                return quad(val);
            case 4:
                return pent(val);
            case 5:
                return hex(val);
            case 6:
                return hept(val);
            case 7:
                return oct(val);
            default:
                return square(val);
                break;
        }
    }
    
    
    //We assume tempValue contains the math functions next value.
    bool checkIfNextIsLane(){
        if (count == tempValue) {
            return true;
        }else{
            return false;
        }
    }
    
    
    /* Prints the linked list if it exists.*/
    void print(){
        temp = first;
        if (temp != NULL) {
            while (temp != NULL) {
                out<<temp->getId()<<endl;
                temp = temp->getNext();
            }
        }
    }
    
    /* Adds a node in Linked List */
    void add(){
        List *a = new List();
        if (first == NULL) {
            first = a;
        }else{
            last->setNext(a);
        }
        last = a;
    }
    
    //Adds a node in Linked list with lane element attached to it.
    void addWithLane(){
        List *a = new List();
        lane::add(a);
        if (first == NULL) {
            first = a;
        }else{
            last->setNext(a);
        }
        last = a;
    }
    
    void addWithLaneMakeList(int n){
        List *a = new List();
        lane::add(a);
        if (first == NULL) {
            first = a;
        }else{
            last->setNext(a);
        }
        last = a;
        cVal = cVal+1;
        tempValue = callFunction(n, cVal);
    }
    
    /* Adds N nodes in Linked List */
    void add(int n){
        for (int i = 0; i<n; i++) {
            add();
        }
    }
    
    /* Destroys the created List if any. */
    void destroy(){
        List *temp1 = NULL;
        temp = first;
        if (first != NULL) {
            while (temp != NULL) {
                temp1 = temp;
                temp = temp->getNext();
                delete temp1;
            }
        }
    }
    
    
    /* Simple Search which returns the List pointer of a particular id & saves previous
     element's pointer in temp. */
    List * search(int n){
        List* temp1 = first;
        temp = NULL;
        while (temp1 != NULL) {
            if (temp1->getId() == n) {
                return temp1;
            }
            temp = temp1;
            temp1 = temp1->getNext();
        }
        return NULL;
    }
    
    
    /*Destroys the element where id = n ; */
    void destroy(int n){
        List* temp1 = search(n);
        if (temp1 == first) {
            first = temp1->getNext();
        }else if (temp1 == last){
            last = temp;
            temp->setNext(NULL);
        }else{
            temp->setNext(temp1->getNext());
        }
        delete temp1;
    }
    
    
    
    void makeList(int n){
        linkedList::addWithLaneMakeList(1);
        while (count <= n ) {
            if (checkIfNextIsLane()) {
                addWithLaneMakeList(1);
            }else{
                add();
            }
        }
    }
    
}


int main(int argc, const char * argv[]) {
    linkedList::makeList(20);
    out<<"printing lane nodes"<<endl;
    lane::printLane();
    lane::destroy();
    linkedList::destroy();
    out<<"Destroyed"<<endl;
    return 0;
}
