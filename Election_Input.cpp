/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that gets input from user.
*****************************************************/
#include "Election_Input.h"

void Input::new_election_input(int& type, int& day, int& month, int& year) const {
	string str_elec_type, str_elec_year, str_elec_month, str_elec_day;
	cout << "You've selected menu option 1." << endl << "Enter the date of the election: " << endl;
	cout << "Enter day: " << endl;

	getline(cin, str_elec_day);
	cout << "Enter month: " << endl;
	getline(cin, str_elec_month);
	cout << "Enter year: " << endl;
	getline(cin, str_elec_year);
	cout << "Enter election type (1 for simple or 0 for regular): " << endl;
	getline(cin, str_elec_type);

	try {
		type = is_valid_number(str_elec_type);
		year = is_valid_number(str_elec_year);
		month = is_valid_number(str_elec_month);
		day = is_valid_number(str_elec_day);
	}
	catch (invalid_argument& ex) {
		throw;
	}
}

void Input::new_simple_election_input(int& rep_count) const
{
	string str_rep_count;
	cout << "Enter number of representatives: ";
	getline(cin, str_rep_count);
	try {
		rep_count = is_valid_number(str_rep_count);
	}
	catch (invalid_argument& ex) {
		throw;
	}
}

void Input::district_input(string& name, int& rep_count, int& type) const
{
	string str_rep_count, str_type;
	cout << endl << "You've selected menu option 1." << endl << "Enter district name: ";
	getline(cin, name);
	cout << "Enter " << name << "'s number of representatives: ";
	getline(cin, str_rep_count);
	cout << "Enter " << name << "'s type:" << endl;
	cout << "0 - Unified" << endl;
	cout << "1 - Divided" << endl;
	getline(cin, str_type);

	try {
		rep_count = is_valid_number(str_rep_count);
		type = is_valid_number(str_type);
	}
	catch (invalid_argument& ex) {
		throw;
	}
}

void Input::citizen_input(string& name, int& id, int& year, int& district) const
{
	string str_id, str_year, str_district;
	cout << endl << "You've selected menu option 2." << endl << "Enter citizen's name: ";
	getline(cin, name);
	cout << "Enter " << name << "'s I.D. number: ";
	getline(cin, str_id);
	cout << "Enter " << name << "'s birth year: ";
	getline(cin, str_year);
	cout << "Enter " << name << "'s district number: ";
	getline(cin, str_district);

	try {
		id = is_valid_number(str_id);
		year = is_valid_number(str_year);
		district = is_valid_number(str_district);
	}
	catch (invalid_argument& ex){
		throw;
	}
}

void Input::party_input(string& name, int& id) const
{
	string str_candidate_id;
	cout << endl << "You've selected menu option 3." << endl << "Enter party's name: ";
	getline(cin, name);
	cout << "Enter " << name << "'s candidate I.D number: ";
	getline(cin, str_candidate_id);

	try {
		id = is_valid_number(str_candidate_id);
	}
	catch (invalid_argument& ex) {
		throw;
	}
}

void Input::rep_input(int& id, int& party, int& district) const
{
	string str_rep_id, str_party_num, str_dist_num;
	cout << endl << "You've selected menu option 4." << endl << "Enter representative's I.D: ";
	getline(cin, str_rep_id);
	cout << "Enter party number: ";
	getline(cin, str_party_num);
	cout << "Enter district number: ";
	getline(cin, str_dist_num);
	try {
		id = is_valid_number(str_rep_id);
		party = is_valid_number(str_party_num);
		district = is_valid_number(str_dist_num);
	}
	catch (invalid_argument& ex) {
		throw;
	}
}

void Input::vote_input(int& id, int& party) const
{
	string str_id, str_party_num;
	cout << endl << "You've selected menu option 8." << endl << "Please cast your vote: " << endl;
	cout << "Enter your I.D. number: ";
	getline(cin, str_id);
	cout << "Enter your party's serial number choice: ";
	getline(cin, str_party_num);
	try {
		id = is_valid_number(str_id);
		party = is_valid_number(str_party_num);
	}
	catch (invalid_argument& ex){
		throw;
	}
}

int Input::is_valid_number(string number) const
{
	try {
		int ans = stoi(number);
		return ans;
	}
	catch (invalid_argument& ex) {
		throw invalid_argument("Error! Please enter a valid number!");
	}
	catch (out_of_range& ex) {
		throw;
	}
	catch (exception& ex) {
		throw;
	}
	catch (...) {
		throw;
	}

}
