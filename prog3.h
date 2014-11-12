//Miles Sanguinetti CS163 2014
//This is a program that takes in a list of songs via
//input from an external file (.txt) and prints information
//via iostream, namely in the interfacing components in the
//main cpp file. 

//The principle data structures used are a hash table of
//linear linked lists and individual linear linked list.

struct wordnode //Common LLL node structure;
{		//used for the list of rejected words
	char * data; //character data
	wordnode * next; //pointer to next node
};

struct songnode //a LLL node for the hash table's entries.
{		//contains song information.
	songnode * next; //Pointer to the next node
	char * title; //different parts of a given song's data
	char * artist;
	char * album;
	char * minutes; //The song's length is kept as a char
			//because minutes operate in base 60
			//and floating points operate in base 10.
	int played; //how many times the song has been retrieved
};

class table //the class for all of our functions
{
	public:
		table(int size); //constructor that can use
				 //an input size
		~table(); //destructor

		//Functions for the list of rejected words
		int insertmanually(const char * toadd); 
					   //manually add words
		int insertautomatically(); //automatically add words

		//Functions for the hash table of songs
		int loadsongs(); //load songs from external file
		int retrieve(const char* title); //retrieve based on title
		int displayall(); //display all songs
		int remove(const char * title); //remove based on title
		int hash(const char * title);
		//^ this removes any rejected words from the front
		//of a song name and returns the hash table index
		//of the now-simplified song
	
	private:
		wordnode * rejectedhead; //Linear linked list head
				     //for the sake of easily
				     //adding new words to reject
				     //from song titles
		songnode ** hashtable; //Dynamically allocated
				   //array of node pointers
				   //for our chaining hash
				   //table.
		int tablesize; //for storing the size of
			       //the table.
};
