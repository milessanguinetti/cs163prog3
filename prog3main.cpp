//Miles Sanguinetti 2014
//This is the main file, where we call all of our
//functions and conduct interfacing procedures.
#include "prog3.h"
#include <iostream> //essential libraries and h file
#include <cstring>
using namespace std;

int main()
{
table mixtape(79);//Will YOU try my new mixtape?
mixtape.insertautomatically();
mixtape.loadsongs();
//mixtape.displayall();
if(mixtape.retrieve("jimmy n da potatos") == 1)
	cout << "It says that's there, but it shouldn't be." << endl;
if(mixtape.retrieve("karma police") == 0)
	cout << "That's actually there." << endl; 
mixtape.remove("om");
mixtape.displayall();
return 0;
}
