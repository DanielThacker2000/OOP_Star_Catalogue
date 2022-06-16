
#ifndef STAR_H
#define STAR_H
#include "observed_object.h"

/*
Class: Star

Author: Daniel Thacker

Brief: Branch one. Parent class of cepheid and neutron star and inherits functions from observed_object.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */

class star : public observed_object
{
	friend std::istream& operator>>(std::istream& isstrm, star& input_star);
protected:
	//Experimental data containers
	std::vector<double> flux_vector;
	std::vector<double> wavelength_vector;
	//Metallicity to distinguish star from observed object
	double metallicity{ 0 };

public:
	star() : observed_object{}, metallicity{}{};

	star(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double star_dat) : observed_object{ asc, dec, mag, na, mas, dis, ty }, metallicity{ star_dat } {};

	void print_first_vector();

	void print_second_vector();

	void print_third_vector();

	//returns name of class to be used in print statements
	std::string get_type_name();

	void keyboard_input();

	void print_contained_objects();

	std::string branch_one_data();

	star& operator=(const star& arr);

	void read_file();

	void file_output();

	~star() {}
};
#endif
