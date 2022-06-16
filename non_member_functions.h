#ifndef NON_MEMBER_FUNCTIONS_H
#define NON_MEMBER_FUNCTIONS_H

#include "cepheid.h"
#include "neutron_star.h"
#include "galaxy.h"
#include "planet.h"
#include "gas_giant.h"
#include "telescope.h"
/*
Misc non-member functions - added to not clutter up the main function

Author: Daniel Thacker

Brief: Contains function that initialises telescope and validate input function used in main 

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
telescope initialise_telescope(std::vector<galaxy>& galaxy_vector, std::vector<star>& star_vector, std::vector<cepheid>& cepheid_vector, std::vector<neutron_star>& neutron_vector, std::vector<planet>& planet_vector, std::vector<gas_giant>& giant_vector);

int validate_input_main(int lower_bound, int upper_bound);

#endif