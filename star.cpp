
#include "star.h"

void star::file_output()
{
	std::fstream star_file{validate_output_file()};
	//Discern size of biggest vector so missing values on each line may be filled with zeros
	//A slightly convoluted method is used to prevent unsafe unsigned integer comparisons
	size_t biggest_vector_size{ 0 };
	size_t flux_size{ static_cast<std::vector<int>::size_type>(flux_vector.size()) };
	size_t wavelength_size{ static_cast<std::vector<int>::size_type>(wavelength_vector.size()) };
	if (flux_size >= wavelength_size) biggest_vector_size = flux_size;
	else biggest_vector_size = wavelength_size;
	//Add data to the file, separated by commas. Missing data will be added as zeros
	flux_vector.resize(biggest_vector_size, 0);
	wavelength_vector.resize(biggest_vector_size, 0);
	star_file << "flux (W per m squared)" << ",wavelength (nm)" << std::endl;
	for (size_t i = 0; i < biggest_vector_size; ++i) {
		star_file << flux_vector[i] << "," << wavelength_vector[i] << std::endl;
	}
	star_file.close();
	std::cout << "File created successfully. Check project file to see it" << std::endl;
}

void star::read_file()
{
	//Set variables to be filled by file
	char distance_temp[100];
	char velocity_temp[100];
	std::ifstream csv_stream{validate_file_input()};
	while (csv_stream.peek() != EOF) {
		//Extract data from file
		csv_stream.getline(distance_temp, 100, ',');
		csv_stream.getline(velocity_temp, 100);
		//Handle case in which there is an empty cell in the csv file
		double distance = 0;
		double velocity = 0;
		//stream strings into ints
		std::istringstream(distance_temp) >> distance;
		std::istringstream(velocity_temp) >> velocity;
		//Add to vectors
		flux_vector.push_back(distance);
		wavelength_vector.push_back(velocity);
	}
	csv_stream.close();
	std::cout  << "File read successfully!" << std::endl; 
}

void star::keyboard_input()
{
	int user_continue{ 1 };
	while (user_continue == 1) {
		std::cout << "Would you like to add flux (W per m squared) (1) or wavelength (nm) (2)  data? Type 1 or 2:" << std::endl;
		int user_input_choice{ 0 };
		//Call validate input to discern which vector to add to, then add_experimental_data to add the data
		user_input_choice = validate_input(0, 2);
		if(user_input_choice == 1){add_experimental_data(flux_vector);};
		if(user_input_choice == 2){add_experimental_data(wavelength_vector);};
		//Clear input in case of input after 's' character
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "Add more data to this object? Enter 1 to add more and 2 to go back to all object data:" << std::endl;
		user_continue = validate_input(0, 2);
	}
}

star& star::operator=(const star& arr)
{
	//No self assignment
	if (&arr == this) {
		return *this;
	}
	name = arr.name;
	declination = arr.declination;
	ascension = arr.ascension;
	magnitude = arr.magnitude;
	mass = arr.mass;
	distance = arr.distance;
	type = arr.type;
	metallicity = arr.metallicity;
	return *this;
}

std::istream& operator>>(std::istream& isstrm, star& input_star)
{
	char star_name[100], star_type[100];
	double star_declination, star_ascension, star_magnitude, star_mass, star_distance, metallicity;
	std::cout << "Enter star name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then metallicity (0-1)" << std::endl;
	std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type >> metallicity;
	//Validate
	while (std::cin.fail() || star_ascension <= 0 || star_ascension >= 360 || star_magnitude <= 0 || star_declination <= -90 || star_declination >= 90 || star_mass <= 0 || star_distance <=0|| metallicity < 0 || metallicity > 1) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively). All values must be physical. Metallicity must be less than 1" << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> star_name >> star_ascension >> star_declination >> star_magnitude >> star_mass >> star_distance >> star_type >> metallicity;
	}
	star temp_star(star_ascension, star_declination, star_magnitude, star_name, star_mass, star_distance, star_type, metallicity);
	//assigment operator called for a deep copy
	input_star = temp_star;
	return isstrm;
}

//If vector is not empty, print
void star::print_first_vector()
{
	if (flux_vector.size() == 0) {
		std::cerr << "No distance data for this star!" << std::endl;
	}
	if (flux_vector.size() > 0) {
		std::cout << "Flux in (W per m squared) for " << name << ":" << std::endl;
		for (auto iter : flux_vector) {std::cout << iter << std::endl;}
	}
}

//If vector is not empty, print
void star::print_second_vector()
{
	if (wavelength_vector.size() == 0) {
		std::cerr << "No velocity data for this star!" << std::endl;
	}
	if (wavelength_vector.size() > 0) {
		std::cout << "Wavelength in (nm) for " << name << ":" << std::endl;
		for (auto iter : wavelength_vector) {std::cout << iter << std::endl;}
	}
}

//No third vector for star
void star::print_third_vector(){}

//returns name of class to be used in print statements
std::string star::get_type_name()
{
	return "star";
}

void star::print_contained_objects()
{
	std::cout << "No 3rd vector for stars!" << std::endl;
};

std::string star::branch_one_data()
{
	//Use lambda function to remove zeros from streaming into string for print statements
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string metallicity_string{ std::to_string(metallicity) };
	remove_zeros(metallicity_string);
	std::string data_statement{ " metallicity: " + metallicity_string + " | " };
	return data_statement;
}
