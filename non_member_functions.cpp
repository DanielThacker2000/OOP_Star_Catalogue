#include "non_member_functions.h"

//Validate input used in the main function
int validate_input_main(int lower_bound, int upper_bound)
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

//Create a telescope object with user input 
telescope initialise_telescope(std::vector<galaxy>& galaxy_vector, std::vector<star>& star_vector, std::vector<cepheid>& cepheid_vector, std::vector<neutron_star>& neutron_vector, std::vector<planet>& planet_vector, std::vector<gas_giant>& giant_vector)
{
	int number_col{ 35 }, number_row{ 35 };
	double upper_ac{ 60 }, upper_dec{ 60 }, lower_ac{ 40 }, lower_dec{ 40 };
	std::cout << "Chose to look through telescope!" << std::endl;
	std::cout << "Enter desired number of columns and rows, upper and lower ascension range, and upper and lower declination range (6 numbers separated by spaces). Upper range cannot be lower than lower range.\n"
		"For a reasonably sized monitor, it is recommended to use about 30 rows and columns e.g. '30 30 60 40 60 40' " << std::endl;
	std::cin >> number_col >> number_row >> upper_ac >> lower_ac >> upper_dec >> lower_dec;
	//Validate
	while (std::cin.fail() || number_row <= 0 || number_col <= 0 || lower_dec < -90 || upper_dec >= 90 || lower_ac <= 0 || upper_ac >= 360 || upper_ac <= lower_ac || upper_dec <= lower_dec) {
		std::cout << "Input invalid. Enter desired number of columns and rows, upper and lower ascension range, and upper and lower declination range (6 numbers separated by spaces). Ascension must be 0-360 and declination must be -90 - 90";
		// Clear fail bit and ignore bad input
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> number_col>> number_row >> upper_ac >> lower_ac >> upper_dec>> lower_dec;
	}
	telescope picked_telescope(galaxy_vector, star_vector, cepheid_vector, neutron_vector, planet_vector, giant_vector, upper_dec, lower_dec, upper_ac, lower_ac, number_col, number_row);
	return picked_telescope;
}

