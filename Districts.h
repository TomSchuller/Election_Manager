/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on districts.
*****************************************************/

#pragma once
#include "Divided_District.h"

const int INITIAL = 1;

class Districts {

private:
	Dynamic_Array<District*> _arr;

public:
	explicit Districts(int length = INITIAL);
	Districts(istream& in);
	Districts(const Districts& other) = delete;
	~Districts();

	// Getters
	const District& get(int index) const { return *_arr[index]; }
	int getLength(void) const;

	// Setters
	bool setLength(int newLen);
	void add_district(const string name, int representatives_count, int type);
	
	/****************************
	* find_district_by_serial_number()
	* This function finds a district by its serial number
	****************************/
	District* find_district_by_serial_number(int district_num);
	/****************************
	* district_exists()
	* This function checks if the district exists in the array already
	****************************/
	void district_exists(const District& other);

    // Operators
	Districts& operator=(const Districts& other) = delete;

	friend ostream& operator<<(ostream& os, const Districts& districts) {
		for (int i = 0; i < districts.getLength(); i++) {
			os << districts.get(i);
		}
		return os;
	}

	// File operations
	void save(ostream& out) const;
	void load(istream& in);
};