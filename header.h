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

#include <iostream>
#include <cstring>

using namespace std;

//struct for the information about each topping
struct topping_info
{
	char * top_choice_name;
	char * category;
	char * surcharge;
};

// struct to keep track of the pizza topping
struct pizza_topping
{
	char * topping_name;
	//pointer of type topping info, so hold
	// the infomation in each topping
	topping_info info;
	
	pizza_topping * next;
};

//struct for the pizza types
struct pizza_type
{
	char * type_name;

	//pointer of type pizza_topping, for 
	//a head pointer for each pizza type
	pizza_topping * head_topping;
	pizza_type * next;	
};

// class for the overall list of pizza types
class pizzas
{
	public:
		pizzas(); //constructor for pizza class
		~pizzas(); // destructor for pizza class
		int add_pizza(char * & user_type); //fuunction to add a new pizza
		//type to list
		int add_topping(char * & user_type, topping_info & user_info);
		// function to add a pizza topping to a particular pizza type
		int remove_topping(char * & user_type, topping_info & user_info);
		// function to remove a particular pizza topping from particular
		//pizza type
		int display_pizza(int worked); // function to display all the pizza
		//types in the list
		int display_topping(char * & user_type); // function to display all 
		//all the pizza topping from a pizza type
		
	private:
		pizza_type * head; //variable of pizza type to keep track of the head
		// of the list
		pizza_type * current; // variable of type pizza type to keep track of the
		//current pizza type, for when we need to access of the pizza topping from
		// a particular type
		
		int find_pizza(char * & user_type);
		int display_pizza(pizza_type * head, int worked);
};

//prototypes
int menu(); //prototype for a menu to display options
int get_pizza_name(char * & user_type); // function to get name
// of a pizza type from user
int get_topping (char * & user_type, topping_info & user_info);
//function to get a topping/ topping information from user
