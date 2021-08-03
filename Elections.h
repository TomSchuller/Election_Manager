/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on an election round
*****************************************************/

#pragma once
#include "Districts.h"

class Elections {
protected:
	int _year, _month, _day;
	Districts _districts;
	map <int, Citizen*> _voters_notebook;
	Dynamic_Array <Party> _parties;
	ELECTION_TYPE _type = ELECTION_TYPE::REGULAR;
public:
	Elections(int year, int month, int day);
	Elections(istream& in);
	Elections(const Elections& other) = delete;
	~Elections();

	bool set_date(int year, int month, int day);

	// Getters
	int get_year(void) const { return _year; }
	int get_month(void) const { return _month; }
	int get_day(void) const { return _day; }
	const Districts& get_district_array(void) const { return _districts; }
	const map <int, Citizen*>& get_voters_notebook(void) const { return _voters_notebook; }
	const Dynamic_Array <Party>& get_party_array(void) const { return _parties; }
	virtual ELECTION_TYPE get_type(void) const { return ELECTION_TYPE::REGULAR; }

	void add_district(const string name, int representatives_count, int type);
	void add_party(const string name, int candidate_id);
	virtual void add_citizen(const string name, int citizen_id, int year, int district_number);
	virtual void add_representative(int representative_id, int party_num, int district_num);

	/****************************
	* is_valid()
	* This function returns true if a citizen's birth year makes him valid to vote
	****************************/
	void is_valid_age(int birth_year);

	/****************************
	* set_results()
	* This function sets the results totals to the districts and parties
	****************************/
	bool set_results(void);

	/****************************
	* results_ready()
	* This function makes sure there's enough data to show election results
	****************************/
	bool results_ready(void);

	/****************************
	* get_district_winner()
	* This function returns the party that won in the desired district
	****************************/
	Party* get_district_winner(int district_number);

	/****************************
	* set_parties_total_reps()
	* This function sets the total representatives each party won from each district
	****************************/
	void set_parties_total_reps(void);

	int find_district_by_citizen(int citizen_id);
	virtual District* find_district(int district_num);
	Party* find_party(int party_num);
	Party* find_party(const string name);
	Representative* find_representative(int citizen_id);

	void cast_vote(int citizen_id, int party_number);

	Elections& operator=(const Elections& other) = delete;

	// File operations
	virtual void save(ostream& out) const;
	virtual void load(istream& in);

	void save_parties(ostream& out) const;
	void load_parties(istream& in);

	void load_voters_notebook();

	void save_representatives(ostream& out) const;
	void load_representatives(istream& in);

};