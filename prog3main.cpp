//Miles Sanguinetti 2014
//This is the main file, where we call all of our
//functions and conduct interfacing procedures.
#include "prog3.h"
#include <iostream> //essential libraries and h file
#include <cstring>
using namespace std;

int main()
{
	const int SIZE = 100; //constant var for input size

	char response1[SIZE]; //array for multi-character user input
	char response2[SIZE]; //another array for more input
	table mixtape(79);//Object declaration at size 79

	cout << "How would you like to enter ommitted words "
	<< "that songs will not be indexed by?" << endl <<
	"Enter 'manually' to enter words on your own." << endl
	<< "'automatically' will enter a preset list of common "
	<< "words." << endl << "Enter 'neither' to stop adding "
	<< "to or omit the list of filtered words." << endl;
	//Explains the filtered word interface.

	do{
		cin.get(response1, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		if(strcmp(response1, "manually") == 0)
		{ //manually add a word to omit then query user again
			cout << "Enter a word to omit." << endl;
			cin.get(response2, SIZE, '\n');
			cin.ignore(SIZE, '\n');
			mixtape.insertmanually(response2);
			cout << "Word added." << endl;
			cout << "Enter 'manually' to enter another word, or"
			<< endl << "'automatically' to add a preset list"
			" of common words to your own." << endl << 
			"Otherwise, 'neither' will finalize your list."
			<< endl;
		}
		else if(strcmp(response1, "automatically") == 0)
		{ //automatically add ommitted words
			cout << "Common words automatically ommitted."
			<< endl;
			mixtape.insertautomatically();
		}
		else if(strcmp(response1, "neither") != 0)
		{ //response is not recognized by the program
			cout << "Command not recognized." << endl;
			cout << "Please enter a suitable command." << endl;
		}
	}while(strcmp(response1, "neither") != 0 && strcmp(response1,
	"automatically") != 0);

	cout << "Press enter to load and display songs from an "
	<< "external file entitled 'songs.txt'" << endl;
	//helps make data display more comprehensible.
	cin.get(response1, SIZE, '\n');
	cin.clear();
	cin.ignore(SIZE, '\n');
	mixtape.loadsongs(); //Load the songs
	mixtape.displayall(); //Display them to the user.

	cout << "Would you like to remove any songs?" << endl
	<< "Enter 'yes' or 'no'" << endl;
	//prompt user for input.

	do{
		cin.get(response1, SIZE, '\n'); //store response
		cin.ignore(SIZE, '\n');

		if(strcmp(response1, "yes") == 0)
		{ //if the user entered yes.
			cout << "Enter a song name to be deleted" <<
			endl << "Song names are case-sensitive." << endl;
			cin.get(response2, SIZE, '\n');
			cin.ignore(SIZE, '\n');
			if(mixtape.remove(response2) == 0)
			{ //if the song is not found and thus
			  //cannot be deleted
				cout << "Song not found." << endl <<
				"Enter 'yes' to attempt to remove another "
				<< "song or 'no' to stop deleting songs."
				<< endl;
			}
			else
			{ //if the song is found and thus deleted.
				cout << "Song deleted." << endl <<
				"Enter 'yes' to delete another song" <<
				" or 'no' to stop deleting songs." << endl;
			}
		}
		
		else if(strcmp(response1, "no") != 0)
		{
			cout << "Command not recognized." << endl
			<< "Enter 'yes' or 'no'" << endl;
		}

	}while(strcmp(response1, "no") != 0); //continue while the user
			      		      //wants to delete stuff.

	cout << "Press enter to display songs that remain "
	<< "following the deletion process" << endl;
	//again, this helps make data display more comprehensible.
	cin.get(response1, SIZE, '\n');
	cin.clear();
	cin.ignore(SIZE, '\n');
	mixtape.displayall();

	cout << "Enter a song to play." << endl <<
	"Alternatively, enter 'poweroff' to exit the program." << endl;
	
	do{
		cin.get(response1, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		if(strcmp(response1, "poweroff") != 0)
		{ //Only search for a song if we're certain that
		  //the user doesn't just want to poweroff.
			int i = mixtape.retrieve(response1);
			//^ we store the return value to display it
			if(i == 0)
			{ //function returns 0 if song does not exist.
				cout << "Song name not found." << endl <<
				"Enter a different song to play" <<
				" or enter 'poweroff' to stop." <<
				endl;
			}
			else
			{//song found; display times that it has been
			 //played and ask for further queries
				cout << "Song has now been played " << i <<
	 			" times." << endl << "Enter another song"
				<< " or enter 'poweroff' to stop playing."
				<< endl;
			}
		}
	}while(strcmp(response1, "poweroff") != 0);
	//continue playing songs while the user has not "powered
	//off" the program.

return 0; //Program successful; return 0;
}
