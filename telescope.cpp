#include "telescope.h"

void telescope::create_grid()
{
	//Set constant variables for acencion and declination so they can be reset when iterated over
	double acencion_higher_bin{ ac_higher_bin };
	double acencion_lower_bin{ ac_lower_bin };
	double declination_lower_bin{ dec_lower_bin };
	double declination_higher_bin{ dec_higher_bin };
	//'changed' variable used as marker to determine if a celestial object has been placed
	int changed{ 0 };
	//y axis label
	std::cout << std::endl;
	std::cout <<  "Declination (deg)" <<std::endl;
	//Iterate over columns and rows, adding to the ac and dec bin lengths. Determining at each iteration if there is a celestial object there. If there is, place marker
	for (int i{ 0 }; i < number_rows; i += 1) {
		declination_higher_bin -= dec_spacing;
		declination_lower_bin -= dec_spacing;
		acencion_higher_bin = ac_higher_bin;
		acencion_lower_bin = ac_lower_bin;
		for (int j{ 0 }; j < number_cols; j += 1) {
			acencion_higher_bin += ac_spacing;
			acencion_lower_bin += ac_spacing;
			changed = 0;
			std::cout.precision(2);
			//Set y-axis scale - number represents higher bin of the celestial object
			if (j == 0) std::cout << std::fixed << declination_higher_bin << "|";
			//Begin iteration over stored objects - checking each bin range to see if an object is present. If an object is placed, don't place any more
			for (size_t k = 0; k < galaxy_vector.size(); k++) {
				if (galaxy_vector[k].get_ascension() < acencion_higher_bin && galaxy_vector[k].get_ascension() >= acencion_lower_bin &&
					galaxy_vector[k].get_declination() < declination_higher_bin && galaxy_vector[k].get_declination() >= declination_lower_bin) {
					std::cout << " G ";
					changed = 1;
					break;
				}
			}
			for (size_t k = 0; k < star_vector.size(); k++) {
				if (star_vector[k].get_ascension() < acencion_higher_bin && star_vector[k].get_ascension() >= acencion_lower_bin &&
					star_vector[k].get_declination() < declination_higher_bin && star_vector[k].get_declination() >= declination_lower_bin
					&& changed == 0) {
					std::cout << " * ";
					changed = 1;
					break;
				}
			}
			for (size_t k = 0; k < cepheid_vector.size(); k++) {
				if (cepheid_vector[k].get_ascension() < acencion_higher_bin && cepheid_vector[k].get_ascension() >= acencion_lower_bin &&
					cepheid_vector[k].get_declination() < declination_higher_bin && cepheid_vector[k].get_declination() >= declination_lower_bin
					&& changed == 0) {
					std::cout << " C ";
					changed = 1;
					break;
				}
			}
			for (size_t k = 0; k < neutron_vector.size(); k++) {
				if (neutron_vector[k].get_ascension() < acencion_higher_bin && neutron_vector[k].get_ascension() >= acencion_lower_bin &&
					neutron_vector[k].get_declination() < declination_higher_bin && neutron_vector[k].get_declination() >= declination_lower_bin
					&& changed == 0) {
					std::cout << " N ";
					changed = 1;
					break;
				}
			}
			for (size_t k = 0; k < planet_vector.size(); k++) {
				if (planet_vector[k].get_ascension() < acencion_higher_bin && planet_vector[k].get_ascension() >= acencion_lower_bin &&
					planet_vector[k].get_declination() < declination_higher_bin && planet_vector[k].get_declination() >= declination_lower_bin
					&& changed == 0) {
					std::cout << " P ";
					changed = 1;
					break;
				}
			}
			for (size_t k = 0; k < giant_vector.size(); k++) {
				if (giant_vector[k].get_ascension() < acencion_higher_bin && giant_vector[k].get_ascension() >= acencion_lower_bin &&
					giant_vector[k].get_declination() < declination_higher_bin && giant_vector[k].get_declination() >= declination_lower_bin
					&& changed == 0) {
					std::cout << " O ";
					changed = 1;
					break;
				}
			}
			//If no marker was placed, add a dot
			if (changed == 0) std::cout << " . ";
			//set y scale on right side
			if (j == number_cols - 1) std::cout << std::fixed <<"|"<< declination_higher_bin;
			std::cout << "   ";
			if (j == number_cols - 1) std::cout << std::endl;
		}
	}
	//Reset value to reiterate
	acencion_higher_bin = ac_higher_bin;
	std::cout << "     ";
	//Set x-axis - and estimate spacing
	for (int i{ 0 }; i < number_cols; i += 1) {
		std::cout << acencion_higher_bin << " ";
		acencion_higher_bin += ac_spacing;
	}
	//Set x axis label
	std::cout << std::endl;
	std::cout <<  "     Ascension (deg) " <<std::endl;
	//formatting space
	std::cout << std::endl;
}

bool telescope::check_bounds()
{
	//Check if x and y scale are out of bounds 
	if (dec_higher_bound - dec_spacing * number_cols <= -90) { std::cout << "Hit the bottom! You must go up!" << std::endl; return true; }
	if (dec_higher_bound >= 90) { std::cout << "Hit the top! You must go down!" << std::endl; return true; }
	if (ac_higher_bin + ac_spacing * number_rows >= 360) { std::cout << "Telescope cannot turn any further! You must go left!" << std::endl; return true; }
	if (ac_higher_bin  <= 0) { std::cout << "Telescope cannot turn any further! You must go right!" << std::endl; return true; }
	return false;
}

//Add or subtract the x and y scale by 5 so user can 'move' the telescope
void telescope::move_telescope()
{
	std::cin.clear();
	int user_choice{ 1 };
	while (user_choice != 5) {
		//Don't print grid if out of bounds
		bool out_of_bounds{ check_bounds() };
		if(out_of_bounds == false) create_grid();
		std::cout << "Would you like to move the telescope up (1), down (2), left (3) or right (4). Enter (5) to exit telescope.";
		std::cin >> user_choice;
		while (user_choice <= 0 || std::cin.fail() || user_choice > 5) {
			std::cout << "Input invalid. Enter an integer number between the range specified: ";
			// Clear fail bit and ignore bad input
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cin >> user_choice;
		}
		if (user_choice == 1) {
			dec_higher_bound += 5;
			dec_higher_bin += 5;
			dec_lower_bin += 5;
		}
		if (user_choice == 2) {
			dec_higher_bound -= 5;
			dec_higher_bin -= 5;
			dec_lower_bin -= 5;
		}
		if (user_choice == 3) {
			ac_higher_bound -= 5;
			ac_higher_bin -= 5;
			ac_lower_bin -= 5;
		}
		if (user_choice == 4) {
			ac_higher_bound += 5;
			ac_higher_bin += 5;
			ac_lower_bin += 5;
		}
		if (user_choice == 5) break;
	}
}

