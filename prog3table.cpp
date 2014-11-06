//Miles Sanguinetti 2014
//Here we have the hash table functions.
//The constructor and destructor are in the
//other CPP file.
#include "prog3.h"
#include <iostream> //essential libraries and h file
#include <cstring>
#include <fstream>
using namespace std;

//functions related to the hash table
int table::loadsongs()
{ //Here we load songs from an external file.
	if(!hashtable)
		return 0; //awful hard to load songs onto nothing.
	
	ifstream songs;
	int size = 50; //an int for the maximum size of a song name

	char * songinput = new char[size]; //variable for file input
					 //50 chars for longer songs
	songs.open("songs.txt", ifstream::in);
	if(songs.is_open()) //check for file
	{
		while(!songs.eof())//go through file while we
		{		   //aren't at the end.
			/*for(int i = 0; i < size; ++i) //copy line
				songinput[i] = songs.get();*/
			songs.getline(songinput, size, '\n');
			node * temp = new node; //new node for song
			int j = hash(songinput); //using a local var
			//keeps me from having to call hash twice
			//and hurt my runtime efficiency.
			temp -> next = hashtable[j];
			hashtable[j] = temp;
			//attach temp to table at hashed index
			temp -> data = new char[strlen(songinput + 1)];
			strcpy(temp -> data, songinput);
			//copy song name into the node
		}
		songs.close(); //close file
		delete songinput; //deallocate memory
		return 1; //success
	}
	delete songinput; //deallocate memory if the file wasn't open
	return 0; //failure to open
}

//Given that the nodes don't have anything in them besides the title,
//it's impossible to retrieve anything (useful) from the song entries.
//Therefor, my retrieve function just returns an integer that states
//whether or not the song exists in my table.
int table::retrieve(const char * title)
{
	if(!title) //can't retrieve nothing
		return 0;
	node * current = hashtable[hash(title)];
	//set a pointer to a hashed index for traversal
	while(current)
	{
		if(strcmp(current -> data, title) == 0)
			return 1; //we found it!
		current = current -> next; //otherwise, keep looking
	}
	return 0; //If we get to this point, we did not find
		  //the node and should return 0.
}

int table::displayall()
{
	if(!hashtable)
		return 0; //can't display a nonexistant hash table
	for(int i = 0; i < tablesize; ++i) //display every index
	{
		node * current = hashtable[i]; //set current to index i
		while(current)
		{
			cout << "index: " << i << endl;
			cout << current -> data << endl; //display song
			current = current -> next; //traverse
		}
	}
	return 1; //success
}

int table::remove(const char * title)
{
	if(!title || !hashtable)
		return 0; //can't delete nothing
	int j = hash(title); //again, we use a variable so we don't
			     //have to call hash twice.
	node * current = hashtable[j];
	node * prev = current; //traverse via two variables indexed
			       //to a head via our hash function.
	while(current)
	{
		if(strcmp(current -> data, title) == 0)
		{ //if we have a match
			if(prev == current) //special case at
			{		    //first node
				hashtable[j] = current -> next;
				delete current;
			}	
			prev -> next = current -> next; //connect
			delete current; //and delete the match
			return 1; //success
		}
		prev = current; //failing a match, we traverse.
		current = current -> next;
	}
	return 0; //if we get here, there's not match in the list
}

//My hash function uses standard additive and multiplicative
//scrambling to ensure balanced distribution. If a word at the
//front of the passed title matches a rejected word like 'the,'
//I only pass characters AFTER the word into the hashing component
//of the function. I do this using a base index variable that I
//establish based on the length of the rejected word.
int table::hash(const char * title)
{
	if(!title)
		return 0; //can't hash an empty title
	
	int baseindex = 0; //we use this int to augment the
			   //parts of the title that we feed through
			   //the hash function if a rejected word is
			   //found.
	node * current = rejectedhead;
	while(current) //we traverse through the LLL of
	{ //rejected words and remove them from the title
		bool match = true;
		for(int i = strlen(current -> data) - 1;
		i >= 0; --i)
		{ //check each letter of the rejected word
		  //for difference with corresponding letter
		  //of the title.
			if(tolower(current -> data[i])
			 != tolower(title[i]))
			{ //if the characters aren't the same...
				match = false; //it's not a match
				break; //and we break the for loop
			}
		}
		if(match == true) //if we did find a match after all
		{	//we only account for characters after the
			//identified rejected word in the hash function
			baseindex = strlen(current -> data);
			break; //and we break the while loop to save time
		}      	//that would be spent needlessly traversing
		current = current -> next; //otherwise we go to the next
	}				   //node/rejected word.

	int i = title[baseindex]; //now we hash the simplified title
	if(title[baseindex + 1]) //careful randomizing
		i = i * title[baseindex + 1] - title[baseindex];
	if(title[baseindex + 2]) //more careful randomizing
		i = i * (title[baseindex + 2] + title[baseindex]);
	return i%tablesize; //return the index after
			    //putting it through modulus operator
}
