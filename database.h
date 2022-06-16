#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include<algorithm>
#include<iomanip>
#include<memory>
#include "cepheid.h"
#include "neutron_star.h"
#include "galaxy.h"
#include "planet.h"
#include "gas_giant.h"


// Star catalogue
/*
Class: database

Author: Daniel Thacker

Brief: Holds shared pointers to all data after recieving vectors of objects.
Does not need a constructor. Is simply a container to store shared pointers and functions.

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */

class database
{
private:
	//Vector to store all objects for ease when iterating through
	std::vector<std::shared_ptr<observed_object>> all_data;
public:
	//No constructor required
	void add_data(std::vector<galaxy>& galaxy_vector, std::vector<star>& star_vector, std::vector<cepheid>& cepheid_vector, std::vector<neutron_star>& neutron_vector, std::vector<planet>& planet_vector, std::vector<gas_giant>& giant_vector);

	int validate_input(int lower_bound, int upper_bound);

	void search_database();

	void sort_database();

	void database_menu();

	void file_output();

	~database() {}
};
#endif