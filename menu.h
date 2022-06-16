#ifndef MENU_H
#define MENU_H
#include<vector>
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>

#include "cepheid.h"
#include "neutron_star.h"
#include "galaxy.h"
#include "planet.h"
#include "gas_giant.h"

/*
Class: menu
 
Author: Daniel Thacker
 
Brief: Template class menu to read and add to specific classes such as galaxy, cepheid etc to the object vectors. 
Accepts many object input by screen or file and outputs all objects and data
Template args: galaxy, star, cepheid, neutron star, planet, gas giant
 
Contact: daniel.thacker-3@student.manchester.ac.uk
 
Created: 15/05/22
 */
//Use a namespace because it's a class template
namespace menu_namespace
{
	template <class stellar_object>
	class menu
	{
	private:
	//Vector to store all objects of the same type
	std::vector<stellar_object>& object_vector;
	// a default stellar object to be used for calling for print statements
	stellar_object object_name;
	public:
		menu() = default;

		//Takes in a vector that stores stellar objects 
		menu(std::vector<stellar_object>& object_vec) : object_vector{ object_vec } {}

		//function to add object to its designated vector
		void add_object();

		void read_all_objects();

		void object_menu();

		void add_object_data();

		void many_object_input();

		//Function to get user input and validate - used across the menu
		int validate_input(int lower_bound, int upper_bound);

		~menu() {}
	};
}
using namespace menu_namespace;

//Used throughout menu for input number validation
template<class stellar_object>
int menu<stellar_object>::validate_input(int lower_bound, int upper_bound)
{
	int user_input;
	std::cin >> user_input;
	while (user_input <= lower_bound || std::cin.fail() || user_input > upper_bound) {
		std::cout << "Input invalid. Enter an integer number between the range specified: ";
		// Clear fail bit and ignore bad input
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> user_input;
	}
	return user_input;
}

//Input many objects by file
template<class stellar_object>
void menu<stellar_object>::many_object_input()
{
	//Set variables to be filled by file
	char file_name[100];
	std::cout << "Enter the file you would like to read data from." << std::endl;
	std::cin >> file_name;
	std::ifstream csv_stream(file_name);
	//Check file opened correctly 
	if(csv_stream.fail()) std::cerr << "Error: file could not be opened! Please re-enter a csv file name." << std::endl;
	//Make sure write fails with appropriate exception if error occurs
	while (!csv_stream.is_open()) {
		// Print error message and exit
		std::cin.clear();
		std::cin >> file_name;
		//Open file stream so the file may be confirmed to be open
		try {
			csv_stream.open(file_name);
			csv_stream.exceptions(csv_stream.exceptions() | std::ios::failbit | std::ifstream::badbit);
			std::ifstream csv_stream(file_name);
		}
		catch(std::ifstream::failure&) { std::cerr << "Error: file could not be opened! Please re-enter a csv file name." << std::endl; };
	}
	char magnitude_temp[100], ascension_temp[100], declination_temp[100], name_temp[100], mass_temp[100], distance_temp[100], type_temp[100], extra_var_1_temp[100], extra_var_2_temp[100];
	//If class is a neutron star, read in the file with a set_period function as well
	while (csv_stream.peek() != EOF) {
		//Handle case in which there is an empty cell in the csv file
		double magnitude = 0, ascension = 0, declination = 0, mass = 0, distance = 0, extra_var_1 = 0, extra_var_2 = 0;
		csv_stream.getline(name_temp, 100, ',');
		csv_stream.getline(ascension_temp, 100, ',');
		csv_stream.getline(declination_temp, 100, ',');
		csv_stream.getline(magnitude_temp, 100,',');
		csv_stream.getline(mass_temp, 100, ',');
		csv_stream.getline(distance_temp, 100, ',');
		csv_stream.getline(type_temp, 100, ',');
		//Accept an extra column for specific child data
		if (std::is_same<stellar_object, neutron_star>::value || std::is_same<stellar_object, cepheid>::value || std::is_same<stellar_object, gas_giant>::value) {
			csv_stream.getline(extra_var_1_temp, 100, ',');
			csv_stream.getline(extra_var_2_temp, 100);
		}
		//galaxy/star/planet does not have an additional column
		else csv_stream.getline(extra_var_1_temp, 100);
		//stream strings into ints
		std::istringstream(magnitude_temp) >> magnitude;
		std::istringstream(ascension_temp) >> ascension;
		std::istringstream(declination_temp) >> declination;
		std::istringstream(magnitude_temp) >> magnitude;
		std::istringstream(mass_temp) >> mass;
		std::istringstream(distance_temp) >> distance;
		std::istringstream(extra_var_1_temp) >> extra_var_1;
		//If the class has an additional feature, stream it to int
		if (std::is_same<stellar_object, neutron_star>::value || std::is_same<stellar_object, cepheid>::value || std::is_same<stellar_object, gas_giant>::value) std::istringstream(extra_var_2_temp) >> extra_var_2;
		//Initialise object
		stellar_object temp_object(ascension, declination, magnitude, name_temp, mass, distance, type_temp, extra_var_1);
		//Set specific attributes if object is branch two
		if (std::is_same<stellar_object, cepheid>::value) (temp_object.set_luminosity_period(extra_var_2));
		if (std::is_same<stellar_object, neutron_star>::value) (temp_object.set_period(extra_var_2));
		if (std::is_same<stellar_object, gas_giant>::value) (temp_object.set_class(extra_var_2));
		//Add to vector
		object_vector.push_back(temp_object);
	}
	std::cout << "File recieved" << std::endl;
}

//Add data to an existing object
template<class stellar_object>
void menu<stellar_object>::add_object_data()
{
	int object_number{ 1 };
	std::cout << "Here is a list of all the currently stored " << object_name.get_type_name() << " objects:" << std::endl;
	for (auto iter : object_vector) {
		std::cout << object_number << ":" << iter.get_name() << std::endl;
		object_number++;
	}
	int user_stop{ 1 };
	//Give option to add more data until user says stop
	while (user_stop == 1) {
		int user_input_question;
		int which_object_input{ 0 };
		//Give user option for what to add. distance/ lumin etc
		std::cout << "Which " << object_name.get_type_name() << " would you like to add data to? (Enter a number from the list above):" << std::endl;
		which_object_input = validate_input(0, object_vector.size());
		std::cout << "Selected " << object_vector[which_object_input - 1].get_name() << "!" << std::endl;
		std::cout << "Enter data via csv file or by keyboard? Enter '1' for csv file and '2' for keyboard " << std::endl;
		user_input_question = validate_input(0,2);
		//Call the object read file or keyboard input
		if (user_input_question == 1) {
			object_vector[which_object_input - 1].read_file();
		}
		if (user_input_question == 2) {
			object_vector[which_object_input - 1].keyboard_input();
		}
		std::cout << "Add more " << object_name.get_type_name() << " data? Enter 1 to add more data and 2 to go back to menu:" << std::endl;
		user_stop = validate_input(0,2);
	}
}

//Add a new object to the vector
template<class stellar_object>
void menu<stellar_object>::add_object() 
{
	//Call overloaded extraction operator for each input class
	stellar_object user_created_object;
	std::cin >> user_created_object;
	std::cout << "Created a " << user_created_object.get_type_name() << " called " << user_created_object.get_name() << std::endl;
	std::cout << "Would you like to add some data to this " << user_created_object.get_type_name() << "? Enter 1 to add data or 2 to go back: " << std::endl;
	int user_input_question;
	if (validate_input(0,2) == 1) {
		std::cout << "Enter data via csv file or by keyboard? Enter '1' for csv file and '2' for keyboard " << std::endl;
		user_input_question = validate_input(0,2);
		if (user_input_question == 1) {
			user_created_object.read_file();
		}
		if (user_input_question == 2) {
			user_created_object.keyboard_input();
		}
	}
	object_vector.push_back(user_created_object);
}

//Iterate over object vector and print all stored objects
template<class stellar_object>
void menu<stellar_object>::read_all_objects()
{
	int object_number{ 1 };
	std::cout << "Here is a list of all the currently stored " << object_name.get_type_name() << " objects:" << std::endl;
	for (auto iter : object_vector) {
		//Formatting line
		std::cout << "-----------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		//Iterate over object vector and print
		std::cout << object_number << ":" << iter.get_all_data() << iter.branch_one_data() << iter.branch_two_data() << std::endl;
		if (iter.get_type_name() == "galaxy") { std::cout << "Contains:" << std::endl; iter.print_contained_objects(); }
		object_number++;
	}
	std::cout << "-----------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	int user_stop{ 1 };
	while (user_stop == 1) {
		int user_data_choice;
		size_t which_object_input{ 0 };
		//Give user option for what to print. distance/ lumin etc
		std::cout << "Which " << object_name.get_type_name() << " would you like to read data for? Enter a number corresponding to the list:" << std::endl;
		which_object_input = validate_input(0, object_vector.size());
		std::cout << "Selected " << object_vector[which_object_input - 1].get_name() << "!" << std::endl;
		std::cout << object_vector[which_object_input - 1].get_all_data() << object_vector[which_object_input - 1].branch_one_data() << object_vector[which_object_input - 1].branch_two_data() << std::endl;
		std::cout << "View currently held data for " << object_vector[which_object_input - 1].get_name() << "? Enter '1' to go back or '2' to see data:" << std::endl;
		if (validate_input(0,2) == 1) break;
		std::cout << "Print data to screen or file? Enter '1' for screen or '2' for file:" << std::endl;
		user_data_choice = validate_input(0,2);
		//File output
		if (user_data_choice == 2) {
			object_vector[which_object_input - 1].file_output();
		}
		//Screen output 
		if (user_data_choice == 1) {
			//Give user option to print different data based on what they picked
			if (std::is_same<stellar_object, galaxy>::value) std::cout << "Print distance (1) values, velocity (2) or velocity error (3)? Type 1, 2 or 3:" << std::endl;
			if (std::is_same<stellar_object, star>::value || std::is_same<stellar_object, neutron_star>::value || std::is_same<stellar_object, cepheid>::value) std::cout << "Print flux (1) values or wavelength (2)? Type 1 or 2:" << std::endl;
			if (std::is_same<stellar_object, planet>::value || std::is_same<stellar_object, gas_giant>::value) std::cout << "Print stellar brightness (1) values or time (2)? Type 1 or 2:" << std::endl;
			user_data_choice = validate_input(0, 3);
			switch (user_data_choice)
			{
				//Call print functions from object classes
			case 1: object_vector[which_object_input - 1].print_first_vector();
				break;
			case 2: object_vector[which_object_input - 1].print_second_vector();
				break;
			case 3: object_vector[which_object_input - 1].print_third_vector();
				break;
			default:
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(1024, '\n');
				std::cin >> user_data_choice;
			}
		}
		//Ask if should repeat
		std::cout << "Print another " << object_name.get_type_name() << "? Enter 1 to see more data and 2 to go back to menu:" << std::endl;
		user_stop = validate_input(0,2);
	}
}

//Give user options on where to go in the menu by calling other menu functions
template<class stellar_object>
void menu<stellar_object>::object_menu()
{
	int object_choice;
	std::cout << "Picked " << object_name.get_type_name()<< "! Would you like to add a " << object_name.get_type_name() << ", read current " << object_name.get_type_name() << " data or add to an existing " << object_name.get_type_name() << "?" << std::endl;
	std::cout << "1 Add a " << object_name.get_type_name() << std::endl;
	std::cout << "2 Read current " << object_name.get_type_name() << " data" << std::endl;
	std::cout << "3 Add to existing " << object_name.get_type_name() << std::endl;
	std::cout << "Enter your choice(1-3):";
	object_choice = validate_input(0, 3);
	switch (object_choice)
	{
	//Run add_object function
	case 1:
		std::cout << "Do you want to add many objects at once via a file? Enter 1 to add many objects by file or 2 to add a single object:" << std::endl;
		if (validate_input(0,2) == 1) {
			many_object_input();
			break;
		}
		else add_object();
		break;
		//Print list of all objects for this class
	case 2:
		if (object_vector.size() == 0) {
			std::cout << "No " << object_name.get_type_name() << " data stored yet! " << std::endl;
			break;
		}
		read_all_objects();
		break;
	case 3:
		if (object_vector.size() == 0) {
			std::cout << "No " << object_name.get_type_name() << " data stored yet! " << std::endl;
			break;
		}
		add_object_data();
		break;
	//Add default just in case validate_input fails
	default: 
		std::cout << "Invalid input!";
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> object_choice;
	}
}
#endif
