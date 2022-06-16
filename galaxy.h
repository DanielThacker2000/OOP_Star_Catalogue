#ifndef GALAXY_H
#define GALAXY_H
#include "observed_object.h"
#include "star.h"
#include "planet.h"

/*
Class: Galaxy

Author: Daniel Thacker

Brief: Branch one. Child of observed object and can contain orbiting objects of star and planets

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */

class galaxy : public observed_object
{
	friend std::istream& operator>>(std::istream& isstrm, galaxy& input_galaxy);
private:
	//Experimental data goes here
	std::vector<double> distance_vector;
	std::vector<double> velocity_vector;
	std::vector<double> velocity_error_vector;
	//Container to store objects within the galaxy
	std::vector<std::shared_ptr<observed_object>> contained_objects;
	//Rotation speed is specific to galaxy
	double rotation_speed{ 0 };
public:
	galaxy() : observed_object{}, rotation_speed{}{};

	galaxy(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double gal) : observed_object{ asc, dec, mag, na, mas, dis, ty }, rotation_speed { gal } {};

	void read_file();

	//Do one for lumin and temp etc
	void print_first_vector();

	void print_second_vector();

	void print_third_vector();

	void keyboard_input();

	void file_output();

	std::string branch_one_data();

	//returns name of class to be used in print statements
	std::string get_type_name();

	void add_contained_star(star& add_star);

	void add_contained_star(planet& add_star);

	void print_contained_objects();

	galaxy& operator=(const galaxy& arr);

	~galaxy() {}
};
#endif
