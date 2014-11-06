//Miles Sanguinetti CS163 2014
//This is a program that neatly sorts songs
//input from an external file.

struct node //Common LLL node structure
{
	char * data; //character data
	node * next; //pointer to next node
};

class table //the class for all of our functions
{
	public:
		table(int size); //constructor that can use
				 //an input size
		~table(); //destructor

		//Functions for the list of rejected words
		int insertmanually(char const * toadd); 
					   //manually add words
		int insertautomatically(); //automatically add words

		//Functions for the hash table of songs
		int loadsongs(); //load songs from external file
		int retrieve(char * title); //retrieve based on title
		int displayall(); //display all songs
		int remove(char * title); //remove based on title
		int hash(char * title);
		//^ this removes any rejected words from the front
		//of a song name and returns the hash table index
		//of the now-simplified song
	
	private:
		node * rejectedhead; //Linear linked list head
				     //for the sake of easily
				     //adding new words to reject
				     //from song titles
		node ** hashtable; //Dynamically allocated
				   //array of node pointers
				   //for our chaining hash
				   //table.
		int tablesize; //for storing the size of
			       //the table.
};
