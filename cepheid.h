#ifndef CEPHEID_H
#define CEPHEID_H
#include "star.h"

/*
Class: Cepheid

Author: Daniel Thacker

Brief: Child of star. Has a luminosity period.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
class cepheid : public star
{
	friend std::istream& operator>>(std::istream& isstrm, cepheid& input_star);
private:
	//data specific to cepheid
	double luminosity_period{ 1 };
public:

	cepheid() : star{} {};

	//star_dat refers to specific star data (metallicity)
	cepheid(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double star_dat) : star{ asc, dec, mag, na, mas, dis, ty , star_dat} {};

	//returns name of class to be used in print statements
	std::string get_type_name();

	std::string branch_two_data();

	void set_luminosity_period(double cepheid_dat);

	~cepheid() {}
};
#endif