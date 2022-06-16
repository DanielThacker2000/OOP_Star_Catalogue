#ifndef OBSERVED_OBJECT_H
#define OBSERVED_OBJECT_H
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <sstream>

/*
Class: Observed_object

Author: Daniel Thacker

Brief: Abstract base class for all observed objects. Contains pure virtual and virtual functions used by every child class.
Contains 7 atributes common to all the children. 

Contact: daniel.thacker-3@student.manchester.ac.uk

Created: 15/05/22
 */
class observed_object
{
protected:
	//Set parameters for all observed objects
	double ascension{ 0 };
	double declination{ 0 };
	double magnitude{ 0 };
	double mass{ 0 };
	double distance{ 0 };
	std::string type{ "no type" };
	std::string name{ "No Name" };
public:
	observed_object() = default;
	//Set constructor for all observed objects 
	observed_object(double asc, double dec, double mag, std::string na, double mas, double dis, std::string ty) : ascension{ asc }, declination{ dec }, magnitude{ mag }, name{ na }, mass{ mas }, distance{ dis }, type{ ty }{}
	//Pure virtual functions - different for every child - each child contains different vectors of information
	virtual std::string get_type_name() = 0;
	virtual void print_contained_objects() = 0;
	virtual void file_output() = 0;
	virtual void keyboard_input() = 0;
	virtual void read_file() = 0;
	virtual void print_first_vector() = 0;
	virtual void print_second_vector() = 0;
	virtual void print_third_vector() = 0;
	virtual std::string branch_one_data() = 0;
	//Class specific functions (only used in branch two)
	virtual std::string branch_two_data();
	virtual void set_period(double spin);
	virtual void set_luminosity_period(double cepheid_dat);
	virtual void set_class(double clas);
	//Functions that act the same way for all celestial objects
	virtual std::string get_all_data();
	virtual std::string get_name();
	virtual double get_magnitude();
	virtual double get_ascension();
	virtual double get_declination();
	virtual double get_mass();
	virtual double get_distance();
	virtual std::string get_type();
	virtual int validate_input(int lower_bound, int upper_bound);
	virtual std::ifstream validate_file_input();
	virtual std::fstream validate_output_file();
	virtual std::vector<double>& add_experimental_data(std::vector<double>& input_vector);
	virtual ~observed_object() {};
};
#endif
