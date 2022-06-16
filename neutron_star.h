#ifndef NEUTRON_STAR_H
#define NEUTRON_STAR_H
#include "star.h"

/*
Class: Nuetron star

Author: Daniel Thacker

Brief: Child of star. Has spin rate to set it apart from cepheid.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
class neutron_star : public star
{
	friend std::istream& operator>>(std::istream& isstrm, neutron_star& input_star);
private:
	//Spin rate is specific to neutron stars
	double spin_rate{ 0 };
public:

	neutron_star() : star{} {};

	neutron_star(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double star_dat) : star{ asc, dec, mag, na, mas, dis, ty , star_dat} {};

	//returns name of class to be used in print statements
	std::string get_type_name();

	std::string branch_two_data();

	void set_period(double spin);

	~neutron_star() {}
};
#endif
