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
	int size = 40; //an int for the maximum size of a song name

	char * songinput = new char[size]; //variable for file input
					 //40 chars for longer songs
	ifstream songs("songs.txt"); //link variable to file
	if(songs.is_open()) //check for file
	{
		while(!songs.eof())//go through file while we
		{		   //aren't at the end.
			for(int i = 0; i < size; ++i) //copy line
				songinput[i] = songs.get;
			node * temp = new node; //new node for song
			int j = hash(songinput); //using a local var
			//keeps me from having to call hash twice
			//and hurt my runtime efficiency.
			temp -> next = hashtable[hash(j)];
			hashtable[hash(j)] = temp;
			//attach temp to table at hashed index
			temp -> data = new char[strlen(songinput + 1)];
			strcpy(temp -> data, songinput);
			//copy song name into the node
		}
		songs.close(); //close file
		delete * songinput; //deallocate memory
		return 1; //success
	}
	delete * songinput; //deallocate memory if the file wasn't open
	return 0; //failure to open
}

int table::retrieve(char * title)
{

}

int table::displayall()
{

}

int table::remove(char * title)
{

}

//My hash function uses standard additive and multiplicative
//scrambling to ensure balanced distribution. If a word at the
//front of the passed title matches a rejected word like 'the,'
//I only pass characters AFTER the word into the hashing component
//of the function. I do this using a base index variable that I
//establish based on the length of the rejected word.
int table::hash(char * title)
{
	if(!title)
		return 0; //can't hash an empty title

	toupper(title[0]); //for comparison w/ rejected words
			   //0 is used to compare the first character
			   //if a rejected word is not found.

	int baseindex = 0; //we use this int to augment the
			   //parts of the title that we feed through
			   //the hash function if a rejected word is
			   //found.
	node * current = rejectedhead;
	while(current) //we traverse through the LLL of
	{ //rejected words and remove them from the title
		bool match = true;
		for(int i = strlen(current -> data) - 1;
		i <= 0; --i)
		{ //check each letter of the rejected word
		  //for difference with corresponding letter
		  //of the title.
			if(current -> data[i] == title[i] != 0)
			{ //if the characters aren't the same...
				match = false; //it's not a match
				break; //and we break the for loop
			}
		}
		if(match == true) //if we did find a match after all
		{	//we only account for characters after the
			//identified rejected word in the hash function
			baseindex = strlen(current -> data) - 1;
			break; //and we break the while loop to save time
		}      	//that would be spent needlessly traversing
		current = current -> next; //otherwise we go to the next
	}				   //node/rejected word.

	int i = title[baseindex]; //now we hash the simplified title
	if(title[baseindex + 1]) //careful randomizing
		i = i * title[baseindex + 1] - title[baseindex];
	if(title[baseindex + 2]) //more careful randomizing
		i = i * (title[baseindex + 2] + title[baseindex])
	return i%tablesize; //return the index after
			    //putting it through modulus operator
}
