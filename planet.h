#ifndef PLANET_H
#define PLANET_H
#include "observed_object.h"

/*
Class: Planet

Author: Daniel Thacker

Brief: Child of observed object. Branch one. Parent to gas giant.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */

class planet : public observed_object
{
	friend std::istream& operator>>(std::istream& isstrm, planet& input_planet);
protected:
	std::vector<double> stellar_brightness_vector;
	std::vector<double> time_vector;
	//Day lengths distinguishes planets from other branch 1 objects
	double day_length{ 0 };
public:
	planet() : observed_object{}, day_length{}{};

	planet(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double plan) : observed_object{ asc, dec, mag, na, mas, dis, ty }, day_length{ plan } {};

	void print_first_vector();

	void print_second_vector();

	void print_third_vector();

	//returns name of class to be used in print statements
	std::string get_type_name();

	std::string branch_one_data();

	void keyboard_input();

	planet& operator=(const planet& arr);

	void read_file();

	void file_output();

	void print_contained_objects();

	~planet() {}
};
#endif
