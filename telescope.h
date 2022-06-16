#ifndef TELESCOPE_H
#define TELESCOPE_H
#include <vector>
#include<iomanip>
#include "cepheid.h"
#include "neutron_star.h"
#include "galaxy.h"
#include "gas_giant.h"

/*
Class: Telescope

Author: Daniel Thacker

Brief: Allows user to see a grid-based image of the sky. Accepts all object vectors and iterates over each one. 

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
class telescope
{
private:
	//References to object containers for iteration
	std::vector<galaxy>& galaxy_vector;
	std::vector<star>& star_vector;
	std::vector<cepheid>& cepheid_vector;
	std::vector<neutron_star>& neutron_vector;
	std::vector<planet>& planet_vector;
	std::vector<gas_giant>& giant_vector;
	int number_cols{ 20 };
	int number_rows{ 25 };
	double ac_higher_bin{ 42 };
	double ac_lower_bin{ 40 };
	//Set higher bounds for the max y/x scale value
	double ac_higher_bound{ 60 };
	double dec_higher_bound{ 60 };
	double dec_higher_bin{ 42 };
	double dec_lower_bin{ 40 };
	double dec_spacing{ 2 };
	double ac_spacing{ 2 };
public:
	telescope(std::vector<galaxy>& gal_vec, std::vector<star>& star_vec, std::vector<cepheid>& ceph_vec, std::vector<neutron_star>& neut_vec, std::vector<planet>& planet_vec, std::vector<gas_giant>& giant_vec, double upper_dec, double lower_dec, double upper_ac, double lower_ac, int num_col, int num_row) :
		galaxy_vector{ gal_vec }, star_vector{ star_vec }, cepheid_vector{ ceph_vec }, neutron_vector{ neut_vec }, planet_vector{ planet_vec }, giant_vector{ giant_vec }, dec_higher_bound{ upper_dec }, dec_lower_bin{ lower_dec }, ac_higher_bound{ upper_ac }, ac_lower_bin{ lower_ac }, number_cols{ num_col }, number_rows{ num_row }
	{
		//dec_lower_bin first used to set limits of dec_spacing then reassigned to be the first bin range
		dec_spacing = (dec_higher_bound - dec_lower_bin) / number_rows;
		ac_spacing = (ac_higher_bound - ac_lower_bin) / number_cols;
		dec_higher_bin = dec_higher_bound;
		dec_lower_bin = dec_higher_bound - dec_spacing;
		ac_higher_bin = ac_lower_bin + ac_spacing;
	}

	void create_grid();

	void move_telescope();

	bool check_bounds();

	~telescope() {}
};
#endif