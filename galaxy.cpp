#include "galaxy.h"
#include<string>
#include<fstream>
#include<sstream>

void galaxy::file_output()
{
	std::fstream galaxy_file{validate_output_file()};
	//Discern size of biggest vector so missing values on each line may be filled with zeros
	//A slightly convoluted method is used to prevent unsafe unsigned integer comparisons
	size_t biggest_vector_size{ 0 };
	size_t distance_size{ static_cast<std::vector<int>::size_type>(distance_vector.size()) };
	size_t velocity_size{ static_cast<std::vector<int>::size_type>(velocity_vector.size()) };
	size_t velocity_error_size{ static_cast<std::vector<int>::size_type>(velocity_error_vector.size()) };
	if ((distance_size >= velocity_size) && (distance_size >= velocity_error_size)) {
		biggest_vector_size = distance_size;
	}
	else if ((velocity_size >= distance_size) && (velocity_size >= velocity_error_size)) {
		biggest_vector_size = velocity_size;
	}
	else {
		biggest_vector_size = velocity_error_size;
	}
	//Add data to the file. Missing data will be added as zeros
	distance_vector.resize(biggest_vector_size, 0);
	velocity_vector.resize(biggest_vector_size, 0);
	velocity_error_vector.resize(biggest_vector_size, 0);
	galaxy_file << "distance (m)" << ",velocity (m per s)" << ",velocity error (m per s)" << std::endl;
	for (size_t i = 0; i < biggest_vector_size; ++i) {
		galaxy_file << distance_vector[i] << "," << velocity_vector[i] << "," << velocity_error_vector[i] << std::endl;
	}
	galaxy_file.close();
	std::cout << "File created successfully. Check project file to see it!" << std::endl;
}

void galaxy::read_file()
{
	//Initialise containers to store data
	char distance_temp[100];
	char velocity_error_temp[100];
	char velocity_temp[100];
	//Check file opened correctly 
	std::ifstream csv_stream{validate_file_input()};
	while (csv_stream.peek() != EOF) {
		//Extract course score, code and name from file 
		csv_stream.getline(distance_temp, 100, ',');
		csv_stream.getline(velocity_temp, 100, ',');
		csv_stream.getline(velocity_error_temp, 100);
		//Handle case in which there is an empty cell in the csv file
		double distance = 0;
		double velocity = 0;
		double velocity_error = 0;
		//stream strings into ints
		std::istringstream(distance_temp) >> distance;
		std::istringstream(velocity_temp) >> velocity;
		std::istringstream(velocity_error_temp) >> velocity_error;
		//If the value has not changed from zero, a zero will be saved in the vector, showing an empty cell
		distance_vector.push_back(distance);
		velocity_vector.push_back(velocity);
		velocity_error_vector.push_back(velocity_error);
	}
	csv_stream.close();
	std::cout  << "File read successfully!" << std::endl; 
}

//Add to galaxy data by keyboard input
void galaxy::keyboard_input()
{
	int user_continue{ 1 };
	while (user_continue == 1) {
		std::cout << "Would you like to add distance (m) (1), velocity (m per s) (2) or velocity error (m per s) (3) data? Type 1,2 or 3:" << std::endl;
		int user_input_choice{ 0 };
		//Call validate input to discern which vector to add to, then add_experimental_data to add the data
		user_input_choice = validate_input(0, 3);
		if(user_input_choice == 1){add_experimental_data(distance_vector);};
		if(user_input_choice == 2){add_experimental_data(velocity_vector);};
		if(user_input_choice == 3){add_experimental_data(velocity_error_vector);};
		//Clear input in case of input after 's' character
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "Add more data to this object? Enter 1 to add more and 2 to go back to all object data:" << std::endl;
		user_continue = validate_input(0, 2);
	}
}

galaxy& galaxy::operator=(const galaxy& arr)
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
	rotation_speed = arr.rotation_speed;
	return *this;
}

//Overload insertion operator for keyboard input
std::istream& operator>>(std::istream& isstrm, galaxy& input_galaxy)
{
	char galaxy_name[100], galaxy_type[100];
	double galaxy_declination, galaxy_ascension, galaxy_magnitude, galaxy_mass, galaxy_distance, rotation_speed;
	std::cout << "Enter galaxy name, then ascension (deg), then declination (deg), then magnitude, then mass (solar masses), then distance (pc), then type, then rotation speed (rps)" << std::endl;
	std::cin >> galaxy_name >> galaxy_ascension >> galaxy_declination >> galaxy_magnitude >> galaxy_mass >> galaxy_distance >> galaxy_type >> rotation_speed;
	//Validate
	while (std::cin.fail() || galaxy_ascension <= 0 || galaxy_ascension >= 360 || galaxy_magnitude <= 0 || galaxy_declination <= -90 || galaxy_declination >= 90 || galaxy_mass <= 0 || galaxy_distance <= 0 || rotation_speed < 0) {
		std::cout << "Invalid input! Magnitude must be positive. Ascension and declination cannot be out of bounds (0-360 and -90-90 respectively). All values must be physical." << std::endl;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> galaxy_name >> galaxy_ascension >> galaxy_declination >> galaxy_magnitude >> galaxy_mass >> galaxy_distance >> galaxy_type >> rotation_speed;
	}
	galaxy temp_galaxy(galaxy_ascension, galaxy_declination, galaxy_magnitude, galaxy_name, galaxy_mass, galaxy_distance, galaxy_type, rotation_speed);
	//assigment operator called for a deep copy
	input_galaxy = temp_galaxy;
	return isstrm;
}

void galaxy::print_first_vector()
{
	if (distance_vector.size() == 0) {
		std::cerr << "No distance data for this galaxy!" << std::endl;
	}
	if (distance_vector.size() > 0) {
		std::cout << "Distance in (m) for " << name << ":" << std::endl;
		for (auto iter : distance_vector) {
			std::cout << iter << std::endl;
		}
	}
}

void galaxy::print_second_vector()
{
	if (velocity_vector.size() == 0) {
		std::cerr << "No velocity data for this galaxy!" << std::endl;
	}
	if (velocity_vector.size() > 0) {
		std::cout << "Velocity in (m per s) for " << name << ":" << std::endl;
		for (auto iter : velocity_vector) {
			std::cout << iter << std::endl;
		}
	}
}

void galaxy::print_third_vector()
{
	if (velocity_error_vector.size() == 0) {
		std::cerr << "No velocity error data for this galaxy!" << std::endl;
	}
	if (velocity_error_vector.size() > 0) {
		std::cout << "Velocity error in (m per s) for " << name << ":" << std::endl;
		for (auto iter : velocity_error_vector) {
			std::cout << iter << std::endl;
		}
	}
}

//returns name of class to be used in print statements
std::string galaxy::get_type_name()
{
	return "galaxy";
}

//Overload function for adding different added classes
void galaxy::add_contained_star(star& add_star)
{
	std::shared_ptr<observed_object> pointer(new star(add_star));
	//pointer must be moved to insert into vector
	contained_objects.push_back(std::move(pointer));
}

void galaxy::add_contained_star(planet& add_star)
{
	std::shared_ptr<observed_object> pointer(new planet(add_star));
	//pointer must be moved to insert into vector
	contained_objects.push_back(std::move(pointer));
}

void galaxy::print_contained_objects()
{
	if (contained_objects.size() == 0) std::cout << "Zero objects" << std::endl;
	for (auto iter : contained_objects) {
		std::cout << iter->get_name() << std::endl;
	}
}

std::string galaxy::branch_one_data()
{
	auto remove_zeros = [&](std::string& str) { return str.erase(str.find_last_not_of('0') + 1, std::string::npos); };
	std::string rotation_speed_string{ std::to_string(rotation_speed) };
	remove_zeros(rotation_speed_string);
	std::string data_statement{ " rotation speed (rps): " + rotation_speed_string + " | " };
	return data_statement;
}