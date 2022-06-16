#include "observed_object.h"

//Output all contained data for print statements
std::string observed_object::get_all_data()
{
	//remove trailing zeros from string output caused by to_string. Using lambda function
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string mag_string{ std::to_string(magnitude) };
	std::string asc_string{ std::to_string(ascension) };
	std::string dec_string{ std::to_string(declination) };
	std::string mass_string{ std::to_string(mass) };
	std::string distance_string{ std::to_string(distance) };
	remove_zeros(mag_string);
	remove_zeros(asc_string);
	remove_zeros(dec_string);
	remove_zeros(mass_string);
	remove_zeros(distance_string);
	std::string data_statement{ name + " ->  |Magnitude: " + mag_string + " |Ascension (deg): " + asc_string + " |Declination (deg): " + dec_string + " | Mass (solar masses): " + mass_string + " | Distance (pc): " + distance_string + " | Type: " + type  + " | " };
	return data_statement;
}

std::string observed_object::get_name()
{
	return name;
}

double observed_object::get_magnitude()
{
	return magnitude;
}

double observed_object::get_ascension()
{
	return ascension;
}

double observed_object::get_declination()
{
	return declination;
}

double observed_object::get_mass()
{
	return mass;
}
double observed_object::get_distance()
{
	return distance;
}
std::string observed_object::get_type()
{
	return type;
}

//function for repeated user input validation
int observed_object::validate_input(int lower_bound, int upper_bound)
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

//set_period function to be overwridden by neutron star and repeat for all branch twos
void observed_object::set_period(double spin){}

void observed_object::set_luminosity_period(double cepheid_dat) {}

void observed_object::set_class(double clas) {}

std::string observed_object::branch_two_data() { return { "" }; }

//Use try/ except to validate a file csv input
std::ifstream observed_object::validate_file_input()
{
	char file_name[100];
	std::cout << "Enter the file you would like to read data from." << std::endl;
	std::cin >> file_name;
	std::ifstream csv_stream(file_name);
	//Check file opened correctly 
	if(csv_stream.fail()) std::cerr << "Error: file could not be opened! Please re-enter a csv file name." << std::endl;
	//Make sure write fails with appropriate exception if error occurs
	while (!csv_stream.is_open()) {
		// Print error message and exit
		std::cin.clear();
		std::cin >> file_name;
		//Open file stream so the file may be confirmed to be open
		try {
			csv_stream.open(file_name);
			csv_stream.exceptions(csv_stream.exceptions() | std::ios::failbit | std::ifstream::badbit);
			std::ifstream csv_stream(file_name);
		}
		catch(std::ifstream::failure&) { std::cerr << "Error: file could not be opened! Please re-enter a csv file name." << std::endl; };
	}
	return csv_stream;
}

//Function to add data to vector by ref - called when adding experimental data
std::vector<double>& observed_object::add_experimental_data(std::vector<double>& input_vector)
{
	std::cout << "Enter data as numbers separated by spaces, then enter 's' when you are done e.g. 100 200 300s" << std::endl;
	int number;
	std::string test_string;
	std::string input_number;
	getline(std::cin, input_number, 's');
	std::istringstream numbers_iss(input_number);
	while (numbers_iss >> number || !numbers_iss.eof()) {
		//Validate input in case of string input - attempt to stream int into string
		if (numbers_iss.fail()) {
			numbers_iss.clear();
			std::string dummy;
			numbers_iss >> dummy;
			continue;
		}
		//Once checked the input is not a string, add to vector
		input_vector.push_back(number);
	}
	//Clear input in case of input after 's' character
	numbers_iss.clear();
	return input_vector;
}

//Called when a file is created by user
std::fstream observed_object::validate_output_file()
{
	std::fstream input_file;
	std::cout << "Enter name of text file you would like to output to (do not add .txt):" << std::endl;
	std::string file_name;
	std::cin >> file_name;
	input_file.open(file_name + ".txt", std::ios::out | std::ios_base::app);
	//Check file opened correctly
	if (input_file.fail()) std::cerr << "Error: file could be written to! Don't include characters like'/'. Please re-enter a file name:" << std::endl;
	while (!input_file.is_open()) {
		// Print error message and exit
		std::cin.clear();
		std::cin >> file_name;
		//Open file stream so the file may be confirmed to be open
		try {
			input_file.open(file_name + ".txt", std::ios::out | std::ios_base::app);
			input_file.exceptions(input_file.exceptions() | std::ios::failbit | std::ifstream::badbit);
			std::ifstream input_file(file_name);
		}
		catch (std::ifstream::failure&) { std::cerr << "Error: file could be written to! Don't include characters like'/'. Please re-enter a file name:" << std::endl; };
	}
	return input_file;
}