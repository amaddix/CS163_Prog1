//Ashley Maddix, CS 163, Spring Q 2018

//*** header ***
// struct- topping info
// struct- pizza_topping
// struct- pizza_type
// class- pizzas

//*** main ***
// menu
// get_pizza_name
// get topping

//*** function ***
// constructor
// destructor
// find_pizza
// sort_pizza
// display_pizza (recursive)
// add_pizza
// add_topping
// remove_topping
// display_pizza (wrapper)
// display_topping   

#include "header.h"

int main()
{
	pizzas pizza; // variable for out pizzas class
	char * user_type= NULL;  // variable used to pass the type of pizza the user wants	
	topping_info user_info; // variable of type 'topping_info', to let user store
	// information into that struct and allow it to get passed 
	//over so it can be stored into my data structure.
	int choose=0; // function to allow user to choose an option 
	int worked=0; //variable to save value of whether something was successful

	do
	{
		//call menu
		choose=menu();
		if (choose == 1) // add new pizza
		{
			//call function to get the name of 
			//pizza type from user
			get_pizza_name(user_type);	
			
			//call function to add the pizza
			worked=pizza.add_pizza(user_type);

			if (!worked)
				cout<<"***You already have this pizza name!***"<<endl
					<<endl;
			else
				cout<<"***You've now made a new pizza***"<<endl
					<<endl;
		}

		if (choose == 2) // add topping
		{
			//call functiont to get the topping from the user
			worked=get_topping(user_type, user_info);
			
			//call function to add the topping
			worked=pizza.add_topping(user_type, user_info);
			if (worked == 0)
				cout<<"*** Sorry, we couldnt add that topping ***"<<endl<<endl;
			else
				cout<<"*** Topping added to " << user_type<<
				" ***"<<endl;	
		}
		if (choose == 3) // remove topping
		{	
			char temp [100];
			//call function to get the name of the pizza type
			get_pizza_name(user_type);
			cout<<"What topping would you like to delete?"<<endl;
			cin.get(temp, 100, '\n');
			cin.ignore (100, '\n');

			//create memory for the name of topping and save into 
			// the user_info struct
			user_info.top_choice_name= new char [strlen (temp)+1];
			strcpy (user_info.top_choice_name, temp);
			// call function to remove the topping
			worked=pizza.remove_topping(user_type, user_info);
			if (worked == 0)
				cout<<"*** Sorry that pizza topping "<<
					"couldnt be deleted ***"<<endl<<endl;
			else
				cout<<"*** Deleted "<<user_info.top_choice_name<<" ***"<<
					endl<<endl;
		}

		if (choose == 4) // display pizza
		{
			//call function to display the pizza type
			cout<<"*** List of Pizza Types ***"<<endl;
			worked=pizza.display_pizza(worked);
			if ( worked <= 0)
				cout<<"*** looks like there was nothing"<<
					" in your list! ***"<<endl;
		}
		if (choose == 5) //display topping
		{
			//call function to get the pizza type
			worked=get_pizza_name(user_type);	

			cout<<"*** List of Pizza Toppings from "<< user_type<<
			" ***"<<endl;
			//call function to display the piza toppings
			worked=pizza.display_topping(user_type);

			if ( worked <= 0)
				cout<<"*** looks like there was nothing"<<
					" to display! ***"<<endl;
		}


	}while (choose != 6);


	return 0;
}

//function to dipslay options to the user, and read in their choice
int menu ()
{ 
	int choose=0;

	cout<<"please choose an option!"<<endl;

	cout<< 
		"1.	add a new pizza type"<<endl<<
		"2.	add a new pizza topping to a specific pizza"<<endl<<
		"3.	remove a pizza topping from a pizza"<<endl<<
		"4. 	display list of pizza types"<<endl<<
		"5.	display list of pizza toppings"<<endl<<
		"6.	quit program"<<endl<<endl;

	cin>>choose;
	cin.ignore (100, '\n');

	return choose;
}

//function to get the name of the pizza type from user
int get_pizza_name(char * & user_type)
{
	char temp [100];
	cout<<"What's the name of the pizza?"<<endl<<endl;

	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');

	//allocate memory, and save temp into user_type
	user_type= new char[strlen(temp)+1];
	strcpy (user_type, temp);
	
}

//function to read in a topping, and the topping information from user
int get_topping( char * & user_type, topping_info & user_info)
{
	char temp [100];

	cout<<"what pizza type are we dealing with?"<<endl<<endl;
	cin.get (temp, 100, '\n');
	cin.ignore(100, '\n');

	//allocate memory, and save temp into user_type
	user_type=new char [strlen(temp)+1];
	strcpy (user_type, temp);

	//#########################################################//

	cout<<"what is the name of the topping you'd like to add?"<<endl<<endl;
	cin.get ( temp, 100, '\n');
	cin.ignore ( 100, '\n');

	//allocate memory, and save temp into info.category
	user_info.top_choice_name= new char [ strlen ( temp) +1];
	strcpy (user_info.top_choice_name, temp);

	cout<<"what category is your topping?"<<endl<<endl;
	cin.get ( temp, 100, '\n');
	cin.ignore ( 100, '\n');

	//allocate memory, and save temp into info.category
	user_info.category= new char [ strlen ( temp) +1];
	strcpy (user_info.category, temp);

	cout<<"What is the name of the topping you'd like to add?"<<endl<<endl;
	cout<<"  $     ";
	cin.get ( temp, 100, '\n');
	cin.ignore ( 100, '\n');

	//allocate memory, and save temp into info. surcharge
	user_info.surcharge= new char [ strlen ( temp) +1];
	strcpy (user_info.surcharge, temp);
}

