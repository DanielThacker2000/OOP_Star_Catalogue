// Star catalogue. This file contains the 'main' function. Program execution begins and ends here.
/*
Main cpp file

Author: Daniel Thacker

Brief: Runs a recurring switch case that allows the user to enter what
they want to do with the programme. Initialises all the vectors and menus.
When main ends the programme is shutdown.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */



//#include<iomanip>
#include "database.h"
#include "menu.h"
#include "telescope.h"
#include "non_member_functions.h"
using namespace menu_namespace;

//Add orbiting body to galaxy - accepts planets and stars as template arguments
//Was chosen to be a part of the main function to avoid having a header file just for one function
template<typename object>
void add_object_to_galaxy(std::vector<galaxy>& galaxy_vector, std::vector<object>& object_vector)
{
	if (object_vector.size() == 0) {std::cout << "None of these objects are stored yet! Add some!" << std::endl; return;}
	//Set object number to label and iterate over each object
	int object_number{ 1 };
	std::cout << "Here is a list of all the currently stored galaxies" << std::endl;
	for (auto iter : galaxy_vector) {
		std::cout << object_number << ":" << iter.get_all_data() << iter.branch_one_data() << std::endl;
		object_number++;
	}
	size_t which_object_input{ 0 };
	//Print all galaxies
	std::cout << "Which galaxy would you like to add objects to to?" << std::endl;
	which_object_input = validate_input_main(0, galaxy_vector.size());
	std::cout << "Selected " << galaxy_vector[which_object_input - 1].get_name() << "!" << std::endl;
	std::cout << "Here is a list of "<< object_vector[0].get_type_name() << "s"<<std::endl;
	//Reset object number to print all the data 
	object_number = 1;
	for (auto iter : object_vector) {
		std::cout << object_number << ":" << iter.get_all_data() << iter.branch_one_data() << iter.branch_two_data() << std::endl;
		object_number++;
	}
	size_t object_input{ 0 };
	//Print all objects
	int user_stop{ 1 };
	while (user_stop == 1) {
		std::cout << "Which "<< object_vector[0].get_type_name() << " would you like to add to " << galaxy_vector[which_object_input - 1].get_name() << "? " << std::endl;
		object_input = validate_input_main(0, object_vector.size());
		std::cout << "Selected " << object_vector[object_input - 1].get_name() << "!" << std::endl;
		galaxy_vector[which_object_input - 1].add_contained_star(object_vector[object_input - 1]);
		std::cout << "Add another "<< object_vector[0].get_type_name() << " to this galaxy? Enter 1 to add another and 2 to go back:" << std::endl;
		user_stop = validate_input_main(0, 2);
	}
}

int main()
{
	//Set up vectors to store each object data
	std::vector<galaxy> galaxy_vector;
	std::vector<cepheid> cepheid_vector;
	std::vector<neutron_star> neutron_vector;
	std::vector<star> star_vector;
	std::vector<planet> planet_vector;
	std::vector<gas_giant> giant_vector;
	//Initialise menu class for each vector
	menu<galaxy> galaxy_menu{ galaxy_vector };
	menu<neutron_star> neutron_menu{ neutron_vector };
	menu<cepheid> cepheid_menu{ cepheid_vector };
	menu<star> star_menu{ star_vector };
	menu<planet> planet_menu{ planet_vector };
	menu<gas_giant> giant_menu{ giant_vector };
	//Initialise database
	database catalogue_database;
	int input_stop{ 1 };
	while (input_stop == 1) {
		std::cout << "===========================================================\n" << std::endl;
		std::cout << "         \b\t\tMENU\t\n " << std::endl;
		std::cout << "===========================================================\n" << std::endl;
		std::cout << "Welcomes to the star catalogue!" << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1 Add/ read Galaxies" << std::endl;
		std::cout << "2 Add/ read Neutron Stars" << std::endl;
		std::cout << "3 Add/ read Cepheids" << std::endl;
		std::cout << "4 Add/ read Miscellaneous Stars" << std::endl;
		std::cout << "5 Add/ read Miscellaneous Planets" << std::endl;
		std::cout << "6 Add/ read Gas Giants" << std::endl;
		std::cout << "7 Look at star chart of currently held data" << std::endl;
		std::cout << "8 Open database" << std::endl;
		std::cout << "9 Add object to galaxy" << std::endl;
		std::cout << "10 Quit application" << std::endl;
		std::cout << "Enter your choice(1-10):";
		int your_choice;
		//Validate input
		your_choice = galaxy_menu.validate_input(0, 10);
		switch (your_choice)
		{
		case 1: galaxy_menu.object_menu();
			break;
		case 2: neutron_menu.object_menu();
			break;
		case 3: cepheid_menu.object_menu();
			break;
		case 4: star_menu.object_menu();
			break;
		case 5: planet_menu.object_menu();
			break;
		case 6: giant_menu.object_menu();
			break;
			//Initialise telescope so that it may be closed and reinitialised
		case 7: {telescope picked_telescope{ initialise_telescope(galaxy_vector, star_vector, cepheid_vector, neutron_vector, planet_vector, giant_vector) };
			picked_telescope.move_telescope();
			break;
		}
		case 8: {if (galaxy_vector.size() == 0 && star_vector.size() == 0 && cepheid_vector.size() == 0 && neutron_vector.size() == 0 && planet_vector.size() == 0 && giant_vector.size() == 0) { std::cout << "No data held yet! Add some!" << std::endl; break; }
			catalogue_database.add_data(galaxy_vector, star_vector, cepheid_vector, neutron_vector, planet_vector, giant_vector);
			catalogue_database.database_menu();
			break;
		}
		//Add objects to a galaxy. First check there is a galaxy and an object to add to it.
		case 9: {if (galaxy_vector.size() == 0) {std::cout << "No galaxies held yet! Add some!" << std::endl; break;}
			if (star_vector.size() == 0 && cepheid_vector.size() == 0 && neutron_vector.size() == 0 && planet_vector.size() == 0 && giant_vector.size() == 0) { std::cout << "No objects to add a galaxy to! Add some!" << std::endl; break; }
			std::cout << "Which type of object would you like to add to a galaxy? Enter 1 for cepheid, 2 for neutron star, 3 for star, 4 for planet and 5 for gas giant:" << std::endl;
			int user_choice;
			user_choice = galaxy_menu.validate_input(0, 5);
			//validate
			if (user_choice == 1) add_object_to_galaxy(galaxy_vector, cepheid_vector);
			if (user_choice == 2) add_object_to_galaxy(galaxy_vector, neutron_vector);
			if (user_choice == 3) add_object_to_galaxy(galaxy_vector, star_vector);
			if (user_choice == 4) add_object_to_galaxy(galaxy_vector, planet_vector);
			if (user_choice == 5) add_object_to_galaxy(galaxy_vector, giant_vector);
			break;
		}
		default: //Set default just in case validation fails
			std::cout << "Invalid input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cin >> your_choice;
		}
		std::cout << "Would you like to return to the menu? Enter 1 to return to menu and 2 to exit the application" << std::endl;
		input_stop = galaxy_menu.validate_input(0,2);
	}
	//Clear up data
	star_vector.clear();
	neutron_vector.clear();
	cepheid_vector.clear();
	galaxy_vector.clear();
	planet_vector.clear();
	giant_vector.clear();
	std::cout << "Shutting down..." << std::endl;
	return 0;
}


