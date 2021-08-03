/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that gets input from user.
*****************************************************/
#pragma once
#include <ostream>
#include <istream>
#include "Print.h"

using namespace std;

class Input {
	public:
		Input() = default;
		Input(const Input& other) = default;
		~Input() = default;

		/****************************
        * new_election_input()
        * This function gets a new election input from user
        ****************************/
		void new_election_input(int& type, int& day, int& month, int& year) const;
		/****************************
        * new_simple_election_input()
        * This function gets a new simple election input from user
        ****************************/
		void new_simple_election_input(int& rep_count) const;
        /****************************
        * district_input()
        * This function gets a district input from user
        ****************************/
		void district_input(string& name, int& rep_count, int& type) const;
		/****************************
        * citizen_input()
        * This function gets a citizen input from user
        ****************************/
		void citizen_input(string& name, int& id, int&year, int& district) const;
		/****************************
        * party_input()
        * This function gets a party input from user
        ****************************/
		void party_input(string& name, int& id) const;
		/****************************
        * rep_input()
        * This function gets a representative input from user
        ****************************/
		void rep_input(int& id, int& party, int& district) const;
		/****************************
        * vote_input()
        * This function gets a vote input from user
        ****************************/
		void vote_input(int& id, int& party) const;
		/****************************
		 * is_valid_number()
		 * This function checks whether a number as a string contains letters. If not, it returns the number as an integer
		 ****************************/
		int is_valid_number(string number) const;
};