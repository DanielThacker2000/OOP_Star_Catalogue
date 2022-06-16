#include<sstream>
#include "cepheid.h"

std::istream& operator>>(std::istream& isstrm, cepheid& input_star)
{
	char star_name[100], star_type[100];
	double star_declination, star_ascension, star_magnitude, star_mass, star_distance, metallicity, luminosity_period;
	std::cout << "Enter star name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then metallicity (0-1), then luminosity period (hours):" << std::endl;
	std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type >> metallicity >> luminosity_period;
	//validate
	while (std::cin.fail() || star_ascension <= 0 || star_ascension >= 360 || star_magnitude <= 0 || star_declination <= -90 || star_declination >= 90 || star_mass <= 0 || star_distance <= 0 || luminosity_period < 0) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively) All values must be physical. Metallicity must be less than 1" << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type >> metallicity >> luminosity_period;
	}
	cepheid temp_star(star_ascension, star_declination, star_magnitude, star_name, star_mass, star_distance, star_type, metallicity);
	//assigment operator called for a deep copy
	temp_star.set_luminosity_period(luminosity_period);
	input_star = temp_star;
	return isstrm;
}

//returns name of class to be used in print statements
std::string cepheid::get_type_name()
{
	return "cepheid";
}

void cepheid::set_luminosity_period(double cepheid_dat)
{
	luminosity_period = cepheid_dat;
}

//For print statements
std::string cepheid::branch_two_data()
{
	//Use lambda function to remove zeros for print statements
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string luminosity_period_string{ std::to_string(luminosity_period) };
	remove_zeros(luminosity_period_string);
	std::string data_statement{ " luminosity_period (hours): " + luminosity_period_string + " | " };
	return data_statement;
}