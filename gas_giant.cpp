#include "gas_giant.h"

std::istream& operator>>(std::istream& isstrm, gas_giant& input_giant)
{
	char giant_name[100], giant_type[100];
	double giant_declination, giant_ascension, giant_magnitude, giant_mass, giant_distance, giant_class, planet_data;
	std::cout << "Enter giant name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then day length (earth days), then gas giant classification (1-6)" << std::endl;
	std::cin >> giant_name >> giant_ascension >> giant_declination >> giant_magnitude >> giant_mass >> giant_distance >> giant_type >> planet_data >> giant_class;
	//Validate
	while (std::cin.fail() || giant_ascension <= 0 || giant_ascension >= 360 || giant_magnitude <= 0 || giant_declination <= -90 || giant_declination >= 90 || giant_mass <= 0 || giant_distance <= 0 || giant_class <= 0 || giant_class > 6) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively). Gas giant classification must be below 7. All values must be real." << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> giant_name >> giant_ascension >> giant_declination >> giant_magnitude >> giant_mass >> giant_distance >> giant_type >> planet_data >> giant_class;
	}
	gas_giant temp_giant(giant_ascension, giant_declination, giant_magnitude, giant_name, giant_mass, giant_distance, giant_type, planet_data);
	temp_giant.set_class(giant_class);
	//assigment operator called for a deep copy
	input_giant = temp_giant;
	return isstrm;
}

//returns name of class to be used in print statements
std::string gas_giant::get_type_name()
{
	return "gas giant";
}

void gas_giant::set_class(int clas)
{
	classification = clas;
}

std::string gas_giant::branch_two_data()
{
	//Use lambda function to remove trailing zeros for print statement 
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string class_string{ std::to_string(classification) };
	remove_zeros(class_string);
	std::string data_statement{ " Classification: " + class_string + " | " };
	return data_statement;
}