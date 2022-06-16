#include "database.h"

//function for repeated user input validation
int database::validate_input(int lower_bound, int upper_bound)
{
	int user_input;
	std::cin >> user_input;
	while (user_input <= lower_bound || std::cin.fail() || user_input > upper_bound) {
		std::cout << "Input invalid. Enter an integer number between the range specified: ";
		// Clear fail bit and ignore bad input
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> user_input;
	}
	return user_input;
}

//Add all data to vector upon starting up
void database::add_data(std::vector<galaxy>& galaxy_vector, std::vector<star>& star_vector, std::vector<cepheid>& cepheid_vector, std::vector<neutron_star>& neutron_vector, std::vector<planet>& planet_vector, std::vector<gas_giant>& giant_vector)
{
	//clear previous shared pointers to re-add the vectors to shared pointer vector
	all_data.clear();
	//Try/catch for bad memory allocation
	try {
		//Assign each vector a shared pointer to add to the entire data set for memory efficiency 
		for (size_t k = 0; k < star_vector.size(); k++) {
			//allocate unique pointer to observed object
			std::shared_ptr<observed_object> pointer(new star(star_vector[k]));
			//pointer must be moved to insert into vector
			all_data.push_back(std::move(pointer));
		}
		for (size_t k = 0; k < galaxy_vector.size(); k++) {
			std::shared_ptr<observed_object> pointer(new galaxy(galaxy_vector[k]));
			all_data.push_back(std::move(pointer));
		}
		for (size_t k = 0; k < cepheid_vector.size(); k++) {
			std::shared_ptr<observed_object> pointer(new cepheid(cepheid_vector[k]));
			all_data.push_back(std::move(pointer));
		}
		for (size_t k = 0; k < neutron_vector.size(); k++) {
			std::shared_ptr<observed_object> pointer(new neutron_star(neutron_vector[k]));
			all_data.push_back(std::move(pointer));
		}
		for (size_t k = 0; k < planet_vector.size(); k++) {
			std::shared_ptr<observed_object> pointer(new planet(planet_vector[k]));
			all_data.push_back(std::move(pointer));
		}
		for (size_t k = 0; k < giant_vector.size(); k++) {
			std::shared_ptr<observed_object> pointer(new gas_giant(giant_vector[k]));
			all_data.push_back(std::move(pointer));
		}
	}
	catch (std::bad_alloc memfail) { std::cerr << "Memory allocation failure!" << std::endl; }
}

//output data to file
void database::file_output()
{
	std::fstream database_file;
	std::cout << "Enter name of text file you would like to output to (do not add .txt):" << std::endl;
	std::string file_name;
	std::cin >> file_name;
	database_file.open(file_name + ".txt", std::ios::out | std::ios_base::app);
	//Check file opened correctly
	if (database_file.fail()) std::cerr << "Error: file could be written to! Don't include characters like'/'. Please re-enter a file name:" << std::endl;
	while (!database_file.is_open()) {
		// Print error message and exit
		std::cin.clear();
		std::cin >> file_name;
		//Open file stream so the file may be confirmed to be open - use try/catch 
		try {
			database_file.open(file_name + ".txt", std::ios::out | std::ios_base::app);
			database_file.exceptions(database_file.exceptions() | std::ios::failbit | std::ifstream::badbit);
			std::ifstream database_file(file_name);
		}
		catch (std::ifstream::failure&) { std::cerr << "Error: file could be written to! Don't include characters like'/'. Please re-enter a file name:" << std::endl; };
	}
	//Iterate over all data and stream to file
	for (auto iter : all_data) {
		database_file << iter->get_all_data() << iter->branch_one_data() << iter->branch_two_data() << std::endl;
	}
	database_file.close();
	std::cout << "File created successfully. Check project file to see it with name " << file_name + ".txt" << std::endl;
}

//Compare each shared pointer to an input value
void database::search_database()
{
	int found_name{ 1 };
	int user_stop{ 1 };
	int type_question;
	while (user_stop == 1) {
		std::cout << "Search database by name or type? Enter (1) for name and (2) for type:" << std::endl;
		type_question = validate_input(0, 2);
		if(type_question ==1) std::cout << "Enter the name of the object you wish to see data for:" << std::endl;
		else std::cout << "Enter the type of the object you wish to see data for: e.g. 'spiral'" << std::endl;
		char find_user_name[100];
		std::string user_name_string;
		//Take in user input and stream into string
		std::cin >> find_user_name;
		std::istringstream(find_user_name) >> user_name_string;
		//Iterate over database
		for (auto iter : all_data) {
			//Search by name
			if (type_question == 1) {
				//iterate over all_data and if the name data type is the same as the input name then print it. Works for multiple names
				if (user_name_string.compare(iter->get_name()) == 0) {
					//Formatting lines
					std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << iter->get_all_data() << iter->branch_one_data() << iter->branch_two_data() << std::endl;
					std::cout << "with:" << std::endl;
					iter->print_first_vector();
					iter->print_second_vector();
					iter->print_third_vector();
					found_name = 2;
					//If the object is a galaxy then show the objects it contains
					if (iter->get_type_name() == "galaxy") { std::cout << iter->get_name() << " contains: " << std::endl; iter->print_contained_objects(); }
				}
			}
			//Search by type
			if (type_question == 2) {
				if (user_name_string.compare(iter->get_type()) == 0) {
					//Formatting lines
					std::cout << "------------------------------------------------------------------------------------------------------------------" << std::endl;
					//Print all data
					std::cout << iter->get_all_data() << iter->branch_one_data() << iter->branch_two_data() << std::endl;
					std::cout << "with:" << std::endl;
					iter->print_first_vector();
					iter->print_second_vector();
					iter->print_third_vector();
					found_name = 2;
					//If the object is a galaxy then show the objects it contains
					if (iter->get_type_name() == "galaxy") { std::cout << iter->get_name() << " contains: " << std::endl; iter->print_contained_objects(); }
				}
			}
		}
		if (found_name == 1) std::cout << "No such object in database!" << std::endl;
		std::cout << "Search again? Enter (1) to search again or (2) to go back:" << std::endl;
		user_stop = validate_input(0,2);
	}
}

//Print and sort database by a number of factors
void database::sort_database()
{
	int user_stop{ 1 };
	while (user_stop == 1) {
		std::cout << "How would you like to sort the data? By name (1), magnitude (2), ascension (3), declination (4), mass (5), distance (6) or type (7):" << std::endl;
		int user_input;
		//Validate input using the validate input function
		user_input = validate_input(0,7);
		//Sort data alphabetically by using lambda function that compares 2 shared pointers from the all_data vector
		if (user_input == 1) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, 
				std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_name() < object2->get_name(); });
		}
		//Sort in ascending order by magnitude in similar way - and repeat for each attribute
		if (user_input == 2) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_magnitude() > object2->get_magnitude(); });
		}
		if (user_input == 3) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_ascension() > object2->get_ascension(); });
		}
		if (user_input == 4) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_declination() > object2->get_declination(); });
		}
		if (user_input == 5) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_mass() > object2->get_mass(); });
		}
		if (user_input == 6) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_distance() > object2->get_distance(); });
		}
		if (user_input == 7) {
			std::sort(all_data.begin(), all_data.end(), [&](std::shared_ptr<observed_object> object1, std::shared_ptr<observed_object> object2) -> bool
				{return object1->get_type() < object2->get_type(); });
		}
		//Print entire data set
		for (auto iter : all_data) {
			//Formatting line
			std::cout << "----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
			//Print all stored data
			std::cout << iter->get_all_data() << iter->branch_one_data() << iter->branch_two_data() << std::endl;
			//If object is galaxy print what the objects the galaxy contains
			if (iter->get_type_name() == "galaxy") { std::cout << iter->get_name()<< " contains: " << std::endl; iter->print_contained_objects(); }
		}
		std::cout << "----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Get a print out to file of this list? Enter 1 to print to file or 2 to continue:" << std::endl;
		int user_choice{ validate_input(0,2) };
		if(user_choice == 1) file_output();
		std::cout << "Sort again or go back to go back? Enter (1) to sort and again or (2) to go back:" << std::endl;
		user_stop = validate_input(0,2);
	}
}

//Give user options on what to do
void database::database_menu()
{
	int user_stop{ 1 };
	while (user_stop == 1) {
		std::cout << "Welcome to the database menu. Print and sort entire database (1) or search database by name/ type (2)?" << std::endl;
		int user_input{ validate_input(0,2) };
		if (user_input == 1) sort_database();
		if (user_input == 2) search_database();
		std::cout << "Exit database? Enter (1) to pick another option or (2) to go back to menu:" << std::endl;
		user_stop = validate_input(0,2);
	}
}

