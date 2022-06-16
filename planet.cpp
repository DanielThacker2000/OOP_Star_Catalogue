#include "planet.h"

void planet::file_output()
{
	std::fstream planet_file{validate_output_file()};
	//Discern size of biggest vector so missing values on each line may be filled with zeros
	//A slightly convoluted method is used to prevent unsafe unsigned integer comparisons
	size_t biggest_vector_size{ 0 };
	size_t flux_size{ static_cast<std::vector<int>::size_type>(stellar_brightness_vector.size()) };
	size_t wavelength_size{ static_cast<std::vector<int>::size_type>(time_vector.size()) };
	if (flux_size >= wavelength_size) biggest_vector_size = flux_size;
	else biggest_vector_size = wavelength_size;
	//Add data to the file. Missing data will be added as zeros
	stellar_brightness_vector.resize(biggest_vector_size, 0);
	time_vector.resize(biggest_vector_size, 0);
	planet_file << "brightness (cd per m squared)" << ",time (s)" << std::endl;
	for (size_t i = 0; i < biggest_vector_size; ++i) {
		planet_file << stellar_brightness_vector[i] << "," << time_vector[i] << std::endl;
	}
	planet_file.close();
	std::cout << "File created successfully. Check project file to see it!" << std::endl;
}

void planet::read_file()
{
	//Set variables to be filled by file
	char stellar_brightness_temp[100];
	char time_temp[100];
	std::ifstream csv_stream{validate_file_input()};
	while (csv_stream.peek() != EOF) {
		//Extract data from file
		csv_stream.getline(stellar_brightness_temp, 100, ',');
		csv_stream.getline(time_temp, 100);
		//Handle case in which there is an empty cell in the csv file
		double stellar_brightness = 0;
		double time = 0;
		//stream strings into ints
		std::istringstream(stellar_brightness_temp) >> stellar_brightness;
		std::istringstream(time_temp) >> time;
		//Add to vectors
		stellar_brightness_vector.push_back(stellar_brightness);
		time_vector.push_back(time);
	}
	csv_stream.close();
	std::cout  << "File read successfully!" << std::endl; 
}

void planet::keyboard_input()
{
	int user_continue{ 1 };
	while (user_continue == 1) {
		std::cout << "Would you like to add brightness in (cd per m squared) (1) or time (s) (2)  data? Type 1 or 2:" << std::endl;
		int user_input_choice{ 0 };
		//Call validate input to discern which vector to add to, then add_experimental_data to add the data
		user_input_choice = validate_input(0, 2);
		if(user_input_choice == 1){add_experimental_data(stellar_brightness_vector);};
		if(user_input_choice == 2){add_experimental_data(time_vector);};
		//Clear input in case of input after 's' character
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "Add more data to this object? Enter 1 to add more and 2 to go back to all object data:" << std::endl;
		user_continue = validate_input(0, 2);
	}
}

planet& planet::operator=(const planet& arr)
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
	day_length = arr.day_length;
	return *this;
}

std::istream& operator>>(std::istream& isstrm, planet& input_planet)
{
	char planet_name[100], planet_type[100];
	double planet_declination, planet_ascension, planet_magnitude, planet_mass, planet_distance, day_length;
	std::cout << "Enter planet name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then day length (Earth days)" << std::endl;
	std::cin >> planet_name >> planet_ascension >> planet_declination >> planet_magnitude >> planet_mass >> planet_distance >> planet_type >> day_length;
	//Validate
	while (std::cin.fail() || planet_ascension <= 0 || planet_ascension >= 360 || planet_magnitude <= 0 || planet_declination <= -90 || planet_declination >= 90 || planet_mass <= 0 || planet_distance <= 0 || day_length < 0) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively). All values must be physical." << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> planet_name >> planet_ascension >> planet_declination >> planet_magnitude >> planet_mass >> planet_distance >> planet_type >> day_length;
	}
	planet temp_planet(planet_ascension, planet_declination, planet_magnitude, planet_name, planet_mass, planet_distance, planet_type, day_length);
	//assigment operator called for a deep copy
	input_planet = temp_planet;
	return isstrm;
}

void planet::print_first_vector()
{
	if (stellar_brightness_vector.size() == 0) {
		std::cerr << "No brightness data for this planet!" << std::endl;
	}
	if (stellar_brightness_vector.size() > 0) {
		std::cout << "Brightness in (cd per m squared) for " << name << ":" << std::endl;
		for (auto i : stellar_brightness_vector) {
			std::cout << i << std::endl;
		}
	}
}

void planet::print_second_vector()
{
	if (time_vector.size() == 0) {
		std::cerr << "No velocity data for this planet!" << std::endl;
	}
	if (time_vector.size() > 0) {
		std::cout << "Time in (s) for " << name << ":" << std::endl;
		for (auto i : time_vector) {
			std::cout << i << std::endl;
		}
	}
}

void planet::print_third_vector()
{
	std::cout << "No third vector for planets!" << std::endl;
}

//returns name of class to be used in print statements
std::string planet::get_type_name()
{
	return "planet";
}

void planet::print_contained_objects() 
{
	std::cout << "No contained objects!" << std::endl;
};

std::string planet::branch_one_data()
{
	//Remove zeros using lambda function for print statements
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string day_length_string{ std::to_string(day_length) };
	remove_zeros(day_length_string);
	std::string data_statement{ " day length (Earth days): " + day_length_string + " | " };
	return data_statement;
}

