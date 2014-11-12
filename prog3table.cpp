//Miles Sanguinetti 2014
//Here we have the hash table functions.
//The constructor and destructor are in the
//other CPP file.
#include "prog3.h"
#include <iostream> //essential libraries and h file
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

//CONSTRUCTOR AND DESTRUCTOR
table::table(int size) //constructor
{
	if(!size)
		tablesize = 79; //good, large prime value
	else
		tablesize = size;
	hashtable = new songnode * [tablesize];
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
				songnode * temp = hashtable[i];
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
		wordnode * temp = rejectedhead;
		rejectedhead = rejectedhead -> next;
		delete temp;
	}
	rejectedhead = NULL; //then set its head pointer to null

	tablesize = 0;
}



//functions to make list of rejected words

int table::insertmanually(const char * toadd)
{ //add a new rejected word.
	if(!toadd) //can't insert nothing
		return 0;
	wordnode * temp = new wordnode; //allocate data for node and
				//its char data based on input
	temp -> data = new char[strlen(toadd) + 1];
	strcpy(temp -> data, toadd); //copy into the node
	temp -> data[0] = toupper(temp -> data[0]);
	//this ensures that we have no capitalization issues
	temp -> next = rejectedhead; //temp goes to front of list
	rejectedhead = temp; //temp becomes front of list
	return 1; //success
}



int table::insertautomatically()
{ //automatically reject common words
	insertmanually("The"); //honestly less code is used
	insertmanually("A");   //to just repeatedly call the
	insertmanually("An");  //function like this than to
	insertmanually("El");  //put the words in an array and
	insertmanually("La");  //run the array through a for loop
	insertmanually("I");   //given that it's a relatively short
	insertmanually("I'm"); //list and the arguments aren't
	insertmanually("It");  //something that I can reduce to a
	insertmanually("It's");//C++ algorithm easily
	insertmanually("My");
	insertmanually("We");
	insertmanually("You");
	return 1;
}	



//functions related to the hash table
int table::loadsongs()
{ //Here we load songs from an external file entitled "songs.txt"
	if(!hashtable)
		return 0; //awful hard to load songs onto nothing.
	
	ifstream songs;
	int size = 150; //an int for the maximum size of a song name

	char * songinput = new char[size]; //variable for file input
					 //50 chars for longer songs
	songs.open("songs.txt", ifstream::in);
	if(songs.is_open()) //check for file
	{
		while(!songs.eof())//go through file while we
		{		   //aren't at the end.
			songnode * temp = new songnode; //new song
			//songnode's data is added into the songnode
			//based on delimiters and the get function.
			songs.get(songinput, size, ';');
			songs.ignore(100,';');
			temp -> title = new char[strlen(songinput) + 1];
			strcpy(temp -> title, songinput); //title
			songs.get(songinput, size, ';');
			songs.ignore(100,';');
			temp -> artist = new char[strlen(songinput) + 1];
			strcpy(temp -> artist, songinput); //artist
			songs.get(songinput, size, ';');
			songs.ignore(100,';');
			temp -> album = new char[strlen(songinput) + 1];
			strcpy(temp -> album, songinput); //album
			songs.get(songinput, size, '\n');
			songs.ignore(100,'\n');
			temp -> minutes = new char[strlen(songinput) + 1];
			strcpy(temp -> minutes, songinput); //length
			songs.peek(); //triggers EOF
			int j = hash(temp -> title); //using a local var
			//keeps me from having to call hash twice
			//and hurt my runtime efficiency.
			temp -> next = hashtable[j];
			hashtable[j] = temp;
			//attach temp to table at hashed index
		}
		songs.close(); //close file
		delete songinput; //deallocate memory
		return 1; //success
	}
	delete songinput; //deallocate memory if the file wasn't open
	return 0; //failure to open
}



//searches the hash table for a passed title and--if found--displays
//the rest of the data.
int table::retrieve(const char * passedtitle)
{
	if(!passedtitle) //can't retrieve nothing
		return 0;
	songnode * current = hashtable[hash(passedtitle)];
	//set a pointer to a hashed index for traversal
	while(current)
	{
		if(strcmp(current -> title, passedtitle) == 0)
		{ //if a match is found:
			cout << "Artist: " << current -> artist
			<< endl; //we display the song's artist
			cout << "Album: " << current -> album
			<< endl; //and its album
			cout << "Song length: " << current -> minutes
			<< endl; //and its length.
			++current -> played; //Increment the variable
			//for the number of times the song has been
			//played.
			return current -> played; //return the number
			//of times that the song has been retrieved.
		}
		current = current -> next; //otherwise, keep looking
	}
	return 0; //If we get to this point, we did not find
		  //the node and should return 0.
}



//Displays every entry in the hash table, including all of its contents.
int table::displayall()
{
	if(!hashtable)
		return 0; //can't display a nonexistant hash table
	for(int i = 0; i < tablesize; ++i) //display every index
	{
		songnode * current = hashtable[i]; //set current to index i
		while(current) //display every node under said index
		{ cout << i << endl; //Display the index so that
				     //graders have an easier time
				     //seeing how few collisions I have
			cout << "Title: " << current -> title
			<< endl; //display the title.
			cout << "Artist: " << current ->  artist
			<< endl; //display artist
			cout << "Album: " << current -> album
			<< endl; //display album
			cout << "Song length: " << current -> minutes
			<< endl << endl; //display song length
			current = current -> next; //traverse
		}
	}
	return 1; //success
}



//A simple function for removal based on a passed title.
int table::remove(const char * passedtitle)
{
	if(!passedtitle || !hashtable)
		return 0; //can't delete nothing
	int j = hash(passedtitle); //again, we use a variable so we don't
			     //have to call hash twice.
	songnode * current = hashtable[j];
	songnode * prev = current; //traverse via two variables indexed
			       //to a head via our hash function.
	while(current)
	{
		if(strcmp(current -> title, passedtitle) == 0)
		{ //if we have a match
			if(prev == current) //special case at
			{		    //first node
				hashtable[j] = current -> next;
				delete current;
			}
			else //all other cases
			{	
				prev -> next = current -> next; //connect
				delete current; //and delete the match
			}
			return 1; //success
		}
		prev = current; //failing a match, we traverse.
		current = current -> next;
	}
	return 0; //if we get here, there's not match in the list
}



//My hash function uses standard additive scrambling algorithm to
//create a hash index based on the characters in the passed array.
//In order to comply with the requirement that we can omit rejected
//words from the hashing functionality, it copies individual words
//from the passed array, compares them with the LLL of rejected words
//and only changes the hash index variable if no matches are found.
//Afterward, the hash index (mod tablesize) is returned.
int table::hash(const char * title)
{
	if(!title)
		return 0; //can't hash an empty title
	char * wordcompare = new char[15]; //a variable to copy to
	//and compare with rejected words; few words are longer than 15
	int copywhere = 0; //basically an index variable for copying.
	//It differs from i because it needs to be reset after each word
	//is compared.
	int hashvalue = 0; //an int for storing the precursor to the
	//hash index that we ultimately return
	for(int i = 0; i < strlen(title); ++i) //traversing through
	//the title to get our hash index.
	{
		if(title[i] != ' ')
		{
			wordcompare[copywhere] = title[i];
			++copywhere; //copy that given letter
			//and then increment the index that we are
			//copying to.
		}
		if(title[i] == ' ' || i == strlen(title) - 1)
		{//basically an else statement with the addendum
		//of title[i] being the last character in the title
			wordcompare[0] = toupper(wordcompare[0]);
			//this ensures that we have no issues with
			//capitalization.
			for(int j = copywhere; j < 15; ++j)
				wordcompare[j] = '\0';
			//we reset the rest of our comparison variable
			//in the case that it still has char data from
			//a previous, longer word in it.
			bool match = false; //bool for a match w/ rejects
			wordnode * current = rejectedhead;
			while(current) //while there are more rejected words
			{
				if(strcmp(current -> data, wordcompare)
				== 0)//if it's a match
				{
					match = true; //change match var
					break; //break the while loop
					//to help runtime efficiency
				}
				current = current -> next; //otherwise traverse
			}
			if(match == false) //no matches w/ rejected words
			{//basically, we influence the hash index only
			 //if no matches were found.
				for(int k = 0; k < strlen(wordcompare); ++k)
					hashvalue += wordcompare[k];
			}	//Using every letter additively ensures
				 //a highly randomized hash index without
				 //any danger of getting a ridiculously
				 //high number
			copywhere = 0; //in any case, we reset our copying
				       //index to 0 so that future words
				       //aren't put in weird places.
		}
	}
	return hashvalue % tablesize; //return our finished hash value
	//after it has been ran through the modulus operator in relation
	//to our given table size.
}
