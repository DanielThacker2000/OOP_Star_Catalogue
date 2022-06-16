#ifndef GAS_GIANT_H
#define GAS_GIANT_H
#include "planet.h"
/*
Class: gas giant

Author: Daniel Thacker

Brief: Child of planet. Has specifically classification which is between 1-6 for gas giants

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
class gas_giant : public planet
{
	friend std::istream& operator>>(std::istream& isstrm, gas_giant& input_giant);
private:
	//Data specific to gas giant
	int classification{ 1 };
public:

	gas_giant() : planet{} {};

	//'Plan' refers to planet specific data
	gas_giant(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty, double plan) : planet{ asc, dec, mag, na, mas, dis, ty , plan} {};

	//returns name of class to be used in print statements
	std::string get_type_name();

	std::string branch_two_data();

	void set_class(int clas);

	~gas_giant() {};
};
#endif
