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

//constructor for my pizza class- so I can 
// initalize all my data members 
pizzas::pizzas()
{
	head=NULL;
	current=NULL;
}

//destructor for my pizza class- so I can 
// set all my data members to NULL/ 0
pizzas::~pizzas()
{
	// if there is memoryt allocated for head
	if (head)
	{
		//create a temp pizza type to help traverse
		pizza_type * temp_type= new pizza_type;
		// while head is not NULL...
		while(head)
		{
			//if head's head_topping has memory allocated..
			if (head->head_topping)
			{
				//create temp pointer of pizza_topping, to help
				// traverse
				pizza_topping * temp_top=head->head_topping;
				//while heads head_topping is not NULL...
				while(head->head_topping)
				{
				//delete from beggining and traverse to next
					//set temp to temps next
					temp_top=temp_top->next;
					//delete heads head topping
					delete head->head_topping;
					//set heads head topping to NULL
					head->head_topping=temp_top;
				}
				//set heads topping to NULL	
				head->head_topping=NULL;
				//delete temp top
				delete temp_top;
			}
			//do the same for pizza type ^^
			
			//set temp to temps next
			temp_type=temp_type->next;
			//delete head
			delete head;
			//set head to temp (the next node)
			head=temp_type;
		}
		//set head to NULL
		head=NULL;
		//delete temp
		delete temp_type;
	}
	// if there is memory allocated for current..	
	if (current)
	{
		//delete current
		delete current;
		//set to NULL
		current= NULL;
	}

}

//function used for when I need to traverse through my pizza_type
// LLL to find a specific pizza
int pizzas::find_pizza(char * & user_type)
{
	pizza_type * temp= new pizza_type; 
	// create a pointer of type 'piza_type' for the new
	//pizza we're adding to list

	temp->type_name= new char[strlen(user_type)+1];
	//allocate data for the type_name ( for temp )
	// of length 'name +1'
	strcpy(temp->type_name, user_type);
	// copy name into temp's type_name

	//if there is nothing in list...
	if (!head)
		return 0;	

	//if I have 1+ things in my list...
	else
	{
		//set current to the head of my list
		current= head;

		//while current is not NULL, and while the temp's pizza name is not
		//matching current... traverse current
		while (current && strcmp(temp->type_name, current->type_name) != 0 )
		{
			current=current->next;
		}

		//once we're done traversing..
		//if head is NULL- it means there was no match.
		if (!current)
			return 0;
		//otherwise, there was a match.
		else
			return 1;		
	}			
}

//function to add a new pizza_type to our list of pizza types
int pizzas::add_pizza(char * & user_type)
{

	//create a temp pointer for the value passed in, and set its next to NULL
	pizza_type * temp= new pizza_type; 
	temp->next=NULL;
	// create a pointer of type 'piza_type' for the new
	//pizza we're adding to list

	temp->type_name= new char[strlen(user_type)+1];
	//allocate data for the type_name ( for temp )
	// of length 'name +1'
	strcpy(temp->type_name, user_type);
	// copy name into temp's type_name

	//if nothing is in head, add to beggining
	if (!head)
	{
		head=temp;
		head->next=NULL;	
		return 1;
	}

	//if temp is < then head, then add before head	
	else if (head && strcmp(temp->type_name, head->type_name) < 0)
	{	
		temp->next=head;
		head=temp;
		return 1;
	}	

	//otherwise...
	else
	{	
		//create temp pointers to keep track of the current and 
		//previous value
		pizza_type * previous =head;
		current = head->next;

		//traverse current/previous until either current is NULL or the 
		//temp is < then head	
		while ( current!=NULL && strcmp(current->type_name, temp->type_name) < 0 )
		{
			current= current ->next;
			previous= previous -> next;
		}	

		if (!current)
		{
			previous->next=temp;
			temp->next=NULL;
			return 1;
		}

		else
		{
			temp->next=current;
			previous->next=temp;
			return 1;
		}		


	}		
	return 0;
}

//recursivly display the all the pizza types from out pizza_type list
int pizzas::display_pizza(pizza_type * head, int worked)
{
	// if head is NULL, we're done!
	if (!head)
		return worked;

	//output head's 'type_name'
	cout<<head->type_name<<endl;
	//call this function using head's next value, and incease
	// the number for 'worked' (which is equivalent to a count)
	display_pizza(head->next, ++worked);
}

// function to add toppings to a specific pizza
int pizzas::add_topping(char * & user_type, topping_info & user_info)
{
	if(find_pizza(user_type) == 0)
		return 0;

	//saving value passed in from user into the particular
	// pizzas information 
	//topping name
	pizza_topping * temp= new pizza_topping;
	temp->topping_name= new char[strlen(user_info.top_choice_name)+1];
	strcpy(temp->topping_name, user_info.top_choice_name);

	//topping category
	temp->info.category= new char[strlen(user_info.category)+1];
	strcpy(temp->info.category, user_info.category);

	//topping surcharge
	temp->info.surcharge= new char[strlen(user_info.surcharge)+1];
	strcpy(temp->info.surcharge, user_info.surcharge);


	//if out current pizza has no toppings, add temp as topping
	if (!current->head_topping)
	{
		current->head_topping=temp;
		temp->next=NULL;		
		return 1;
	}

	//if temps topping name is < then heads topping name, add to begginging
	if ( current->head_topping && strcmp(temp->topping_name,current->head_topping->
				topping_name) < 0)
	{
		temp->next=current->head_topping;
		current->head_topping=temp;
		return 1;
	}

	//otherwise	...
	else
	{
		//create temp pointers for the current topping and previous topping
		pizza_topping * current_top = current->head_topping->next;
		pizza_topping * previous_top =current->head_topping;

		//traverse current and previous until either current is NULL or 
		// temps topping name is < currents topping name
		while ( current_top && strcmp(temp->topping_name, current_top->topping_name) > 0)
		{
			current_top= current_top ->next;
			previous_top= previous_top -> next;
		}	

		//if current is NULL, add to end
		if (!current_top)
		{
			previous_top->next=temp;
			temp->next=NULL;
			return 1;
		}

		// add between previous and current
		else
		{
			temp->next=current_top;
			previous_top->next=temp;
			return 1;
		}		
	}
}

//function to remove a topping from a specific pizza type
int pizzas::remove_topping(char * & user_type, topping_info  & user_info)
{
	int worked;

	//call the find function, to find the specific pizza we're gonna 
	// remove from
	find_pizza(user_type);	

	// create temp pointer for the topping we're removing
	pizza_topping * temp = new pizza_topping;
	//allocate memory of the size of 'user_topping', which we've
	//gotten from the user
	temp->topping_name= new char[strlen(user_info.top_choice_name)+1];
	//copy 'user_topping'into temp's 'topping_name
	strcpy(temp->topping_name, user_info.top_choice_name);

	//if the current pizza_type (the one we stopped at from FIND)'s
	// head_topping is NULL...
	if (!current->head_topping)
		return 0;

	//if out current pizza_type's topping is not NULL and the next
	// head_topping is NULL	...
	if (current->head_topping && !current->head_topping->next)
	{
		//set that head_toppings information to NULL
		current->head_topping-> topping_name=NULL;

		//and delete that topping	
		delete current->head_topping;

		return 1;
	}

	//if current's head topping is not NULL	( 1<x) 
	if (current->head_topping)
	{
		//create pointers for the current topping and the previous
		//topping
		pizza_topping * current_top= current->head_topping->next;
		pizza_topping * previous_top= current->head_topping;

		//while the current topping is not NULL 
		while(current_top && strcmp(current_top->topping_name, temp->topping_name) != 0 )
		{
			current_top=current_top->next;
			previous_top=previous_top->next;
		}

		//if current is NULL, send back 0
		if (!current)
			return 0;	

		//otherwise delete current
		else
		{	
			previous_top->next=current_top->next;		
			delete current_top;
			return 1;
		}
	}
}


//wrapper function to call my recursive function for displaying pizza
int pizzas::display_pizza(int worked)
{
	worked=0;
	return display_pizza(head, worked);
}

//function to display the toppings of a particular pizza type
int pizzas::display_topping(char * & user_type)
{

	//if there was no matching pizza type..
	if(find_pizza(user_type) == 0)
		return 0;

	// if there is a head pointer ..		
	if (current->head_topping)
	{
		// create a pointer for the current pizza topping
		pizza_topping * current_top=current->head_topping;
		//traverse current until weve gone through the whole list
		while(current_top)
		{
			//output...
			cout<<current_top->topping_name<<" : "<< 
				current_top->info.category<<" : "<<
				current_top->info.surcharge<<endl<<endl;

			current_top=current_top->next;
		}
		return 1;	
	}
	return 0;
}
