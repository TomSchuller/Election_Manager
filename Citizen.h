/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on a citizen.
*****************************************************/
#pragma once
#include "Dynamic_Array.h"
#include "Sort.h"
class Citizen {
private:
	string _name;
	int _id;
	int _year;
	int _party_vote = UNDEFINED; // -1 means didn't vote

public:
	Citizen() noexcept;
	Citizen(const string name, int id, int year);
	Citizen(const Citizen& other) noexcept;
	~Citizen() noexcept;

	// Getters
	const string get_name(void) const noexcept { return _name; }
	int get_id(void) const noexcept { return _id; }
	int get_year(void) const noexcept { return _year; }
	int get_party_vote(void) const noexcept { return _party_vote; }

	// Setters
	bool set_name(const string name);
	bool set_id(int id) noexcept;
	bool set_year(int year) noexcept;
	bool set_party_vote(int party_vote) noexcept;

	// Operators
	const Citizen& operator=(const Citizen& other);
	bool operator>(const Citizen& other) const noexcept;
	bool operator<(const Citizen& other) const noexcept;
	bool operator==(const Citizen& other) const noexcept;

	friend ostream& operator<<(ostream& os, const Citizen& citizen) noexcept {
		os << "Name: " << citizen._name << ", ID: " << citizen._id << ", Year of birth: " << citizen._year << endl;
		return os;
	}

	// File operations
	void save(ostream& out) const;
	void load(istream& in);
};