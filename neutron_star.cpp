#include "neutron_star.h"

std::istream& operator>>(std::istream& isstrm, neutron_star& input_star)
{
	char star_name[100], star_type[100];
	double star_declination, star_ascension, star_magnitude, star_mass, star_distance, spin_period, star_data; //Star_data refers to specific data for star (metallicity)
	std::cout << "Enter star name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then metallicity (0-1), then spin period (rps)" << std::endl;
	std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type>> star_data >> spin_period;
	//Validate
	while (std::cin.fail() || star_ascension <= 0 || star_ascension >= 360 || star_magnitude <= 0 || star_declination <= -90 || star_declination >= 90 || star_mass <= 0 || star_distance <= 0 || spin_period <0) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively). All values must be physical. Metallicity must be less than 1" << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type >> star_data >> spin_period;
	}
	neutron_star temp_star(star_ascension, star_declination, star_magnitude, star_name, star_mass, star_distance, star_type, star_data);
	temp_star.set_period(spin_period);
	//assigment operator called for a deep copy
	input_star = temp_star;
	return isstrm;
}

//returns name of class to be used in print statements
std::string neutron_star::get_type_name()
{
	return "neutron star";
}

void neutron_star::set_period(double spin)
{
	spin_rate = spin;
}

std::string neutron_star::branch_two_data()
{
	//Use lambda function to remove trailing zeros
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string spin_string{ std::to_string(spin_rate) };
	remove_zeros(spin_string);
	std::string data_statement{ " Spin rate (rps): " + spin_string + " | " };
	return data_statement;
}