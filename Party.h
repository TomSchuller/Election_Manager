/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on a party
*****************************************************/

#pragma once
#include "Representative.h"

class Party {
private:
	string _name;
	int _id;
	int _total_votes = 0;
	int _total_representatives = 0;
	Citizen _candidate;
	list <Representative> _representatives;
public:
	Party();
	Party(const string name, const Citizen& candidate_id, int serial_number);
	Party(const Party& other);
	~Party();

	// Getters
	const string get_name(void) const { return _name; }
	int get_id(void) const { return _id; }
	int get_total_votes(void) const { return _total_votes; }
	int get_total_representatives(void) const { return _total_representatives; }
	const Citizen& get_candidate(void) const { return _candidate; }
	const list <Representative>& get_representatives(void) const { return _representatives; }

	// Setters
	bool set_name(const string name);
	bool set_candidate(const Citizen& candidate);
	bool set_serial_number(int serial_number);
	bool set_total_votes(int total_votes);
	bool add_representative(Representative& representative);
	bool set_total_representatives(int representatives);

	// Operators
	Party& operator=(const Party& other);
	bool operator>(const Party& other) const;
	bool operator<(const Party& other) const;
	bool operator==(const Party& other) const;

	friend ostream& operator<<(ostream& os, const Party& party) {
		cout << "Name: " << party._name << " Serial Number: " << party._id << " Candidate: " << party._candidate.get_name();
		return os;
	}

	// File operations
	void save(ostream& out) const;
	void load(istream& in);
};