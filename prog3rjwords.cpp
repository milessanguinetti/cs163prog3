//Miles Sanguinetti 2014
//This file contains functions that manipulate my
//linear linked list of rejected words. This file is
//separated from the other one, which deals with the hash
//table itself, for the sake of cleanliness and ease of
//debugging.

//Additionally, I will include the constructor and
//destructor below.
#include "prog3.h"
#include <cstring> //including essential libraries and h file
using namespace std;

table::table(int size) //constructor
{
	if(!size)
		tablesize = 79; //good, large prime value
	else
		tablesize = size;
	hashtable = new node * [tablesize];
	//^ allocate a table of input size
	for(int i = 0; i < tablesize; ++i)
		hashtable[i] = NULL;
	//set all indices of hashtable to null
	rejectedhead = NULL;
	//set the rejected word list head to null.
}

table::~table() //destructor 
{
	if(hashtable)
	{ //can't delete nothing
		for(int i = 0; i < tablesize; ++i)
		{ //for each index of the table
			while(hashtable[i])
			{ //if the index contains data 
				node * temp = hashtable[i];
				hashtable[i] = hashtable[i]
				-> next; //delete all of it
				delete temp;
			}
			hashtable[i] = NULL;
		}
		delete hashtable; //delete the table
		hashtable = NULL; //set its pointer to null
	}

	while(rejectedhead)
	{ //delete the entire LLL of rejected words
		node * temp = rejectedhead;
		rejectedhead = rejectedhead -> next;
		delete temp;
	}
	rejectedhead = NULL; //then set its head pointer to null

	tablesize = 0;
}

//functions to make list of rejected words
int table::insertmanually(char const * toadd)
{ //add a new rejected word.
	if(!toadd) //can't insert nothing
		return 0;
	node * temp = new node; //allocate data for node and
				//its char data based on input
	temp -> data = new char[strlen(toadd) + 1];
	strcpy(temp -> data, toadd); //copy into the node
	temp -> next = rejectedhead; //temp goes to front of list
	rejectedhead = temp; //temp becomes front of list
	return 1; //success
}

int table::insertautomatically()
{ //automatically reject common words
	insertmanually("The "); //honestly less code is used
	insertmanually("A ");   //to just repeatedly call the
	insertmanually("An ");  //function like this than to
	insertmanually("El ");  //put the words in an array and
	insertmanually("La ");  //run the array through a for loop
	insertmanually("I ");   //given that it's a relatively short
	insertmanually("I'm "); //list and the arguments aren't
	insertmanually("It ");  //something that I can reduce to a
	insertmanually("It's ");//C++ algorithm easily
	insertmanually("My ");
	insertmanually("We ");
	insertmanually("You ");
	return 1;
}	

