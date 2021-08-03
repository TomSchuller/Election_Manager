/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions of functions that print every output in the program.
*****************************************************/

#include "Print.h"

Print::Print() : Print(nullptr) {
}

Print::Print(Elections* pelections) : _pelections(pelections) {
}

Print::~Print() {
}

bool Print::set_elections(Elections* pelections) {
    _pelections = pelections;
    return true;
}

void Print::main_menu(void) {
    cout << endl << "Hello! Welcome to our program, these are the options you can select" << endl;
    cout << "1 - Create new election round" << endl;
    cout << "2 - Load an election round" << endl;
    cout << "3 - Exit" << endl << "Please enter your choice: ";
}

void Print::instructions(void) {
    cout << endl << "Hello, select one of the following:" << endl;
    cout << " 1 - Add new district" << endl;
    cout << " 2 - Add new citizen" << endl;
    cout << " 3 - Add new party" << endl;
    cout << " 4 - Add new representative" << endl;
    cout << " 5 - View all districts" << endl;
    cout << " 6 - View all citizens" << endl;
    cout << " 7 - View all parties" << endl;
    cout << " 8 - Cast vote" << endl;
    cout << " 9 - View results" << endl;
    cout << "10 - Exit the program" << endl;
    cout << "11 - Save election round" << endl;
    cout << "12 - Load election round" << endl;
    cout << "Please enter a digit: ";
}

void Print::districts(void) const {
    try {
        cout << _pelections->get_district_array();
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

void Print::citizens(void) const {
    int len = _pelections->get_district_array().getLength();
    // Go through every district and print the the citizen list
    for (int i = 0; i < len; i++) {
        cout << "District: " << _pelections->get_district_array().get(i).get_name() << endl;
        list<Citizen>::const_iterator itr = _pelections->get_district_array().get(i).get_citizens().begin();
        try {
            while (itr != _pelections->get_district_array().get(i).get_citizens().end()) {
                cout << *itr;
                ++itr;
            }
        }
        catch (out_of_range& ex) {
            throw;
        }
        catch (exception& ex) {
            throw;
        }
        cout << endl;
    }
}


void Print::parties(void) const {
    int len = _pelections->get_party_array().size();
    int party_num;
    // Go through each party and print its data and its representatives
    try {
        for (int i = 0; i < len; i++) {
            party_num = _pelections->get_party_array().at(i).get_id();
            cout << _pelections->get_party_array().at(i);
            cout << endl << "Representatives:" << endl;
            party_reps(party_num);
            cout << endl;
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }

}

void Print::results(void) const {
    cout << "WELCOME TO THE " << _pelections->get_year() << " ELECTIONS!" << endl;
    cout << "TODAY IS: " << _pelections->get_day() << "." << _pelections->get_month() << "." << _pelections->get_year() << endl;
    cout << "HERE ARE THE RESULTS: " << endl << endl;
    try {
        district_results();
        party_results();
        cout << endl << endl << "THE WINNER IS: " << endl << _pelections->get_party_array().at(0).get_candidate().get_name();
        cout << " FROM THE: " << _pelections->get_party_array().at(0).get_name() << " Party" << endl;
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }

}

void Print::district_results(void) const {
    int dist_len = _pelections->get_district_array().getLength();
    int dist_num;
    try {
        for (int i = 0; i < dist_len; i++) {
            cout << _pelections->get_district_array().get(i);
            dist_num = _pelections->get_district_array().get(i).get_serial_number();
            // Print winning candidate or all candidates according to the party's type
            if (_pelections->get_district_array().get(i).get_type() == DISTRICT_TYPE::UNIFIED) {
                unified_district_candidates(dist_num);
            }
            else if (_pelections->get_district_array().get(i).get_type() == DISTRICT_TYPE::DIVIDED) {
                divided_district_candidates(dist_num);
            }
            cout << "Total Votes: " << _pelections->get_district_array().get(i).get_total_votes();
            cout << ", Percentage: " << _pelections->get_district_array().get(i).get_percentage() << endl;
            cout << endl << "Elected Representatives: " << endl;
            // Print all parties' elected representatives
            district_reps(dist_num);
            cout << endl;
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

void Print::unified_district_candidates(int district_number) const {

    cout << "District Winner: " << _pelections->get_district_winner(district_number)->get_candidate() << endl;
}

void Print::divided_district_candidates(int district_number) const {
    int party_len = _pelections->get_party_array().size();
    int party_num, party_reps, print_index = 1;
    // Print every party's candidate if they won at least 1 representative
    try {
        for (int i = 0; i < party_len; i++) {
            party_num = _pelections->get_party_array().at(i).get_id();
            party_reps = _pelections->find_district(district_number)->get_party_reps(party_num);
            if (party_reps > 0) {
                cout << print_index << ". " << _pelections->find_party(party_num)->get_candidate();
                print_index++;
            }
        }
    }
     catch (out_of_range& ex) {
        throw;
    }
     catch (invalid_argument& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

void Print::district_reps(int district_number) const {
    int party_len = _pelections->get_party_array().size();
    int reps_won, total_votes, party_num, print_index;
    float percentage;
    try {
        for (int i = 0; i < party_len; i++) {
            // Go through each party's representative list
            cout << endl << "Party: " << _pelections->get_party_array().at(i).get_name() << endl;
            party_num = _pelections->get_party_array().at(i).get_id();
            // Get amount of representatives this party won
            reps_won = _pelections->get_district_array().get(district_number).get_party_reps(party_num);
            total_votes = _pelections->get_district_array().get(district_number).get_party_votes(party_num);
            percentage = _pelections->get_district_array().get(district_number).get_party_percentage(party_num);
            // If its at least 1 then print that amount of representatives
            if (reps_won > 0) {
                print_index = 1;
                // Go through representative list and print the elected representative of this district
                list <Representative>::const_iterator itr = _pelections->get_party_array().at(i).get_representatives().begin();
                while (itr != _pelections->get_party_array().at(i).get_representatives().end() && reps_won > 0) {
                    cout << print_index << ". ";
                    cout << *itr;
                    reps_won--;
                    print_index++;
                    ++itr;
                }
            }
            else {
                cout << "No representatives." << endl;
            }
            cout << "Total votes: " << total_votes << ", Percentage: " << percentage << endl;
        }
    }
     catch (out_of_range& ex) {
        throw;
    }
     catch (runtime_error& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

void Print::party_results(void) const {
    int party_len = _pelections->get_party_array().size();
    Dynamic_Array<Party>& pa = const_cast<Dynamic_Array<Party>&>(_pelections->get_party_array());
    try {
        Sort()(pa, [](Party x, Party y) {if (x.get_total_representatives() < y.get_total_representatives()) return true; else return false; }); //lambada
        for (int i = 0; i < party_len; i++) {
            cout << _pelections->get_party_array().at(i);
            cout << ", Total votes: " << _pelections->get_party_array().at(i).get_total_votes();
            cout << ", Total Representatives: " << _pelections->get_party_array().at(i).get_total_representatives() << endl;
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

void Print::party_reps(int party_number) const { 
    int dist_len = _pelections->get_district_array().getLength();
    int dist_num, print_index;
    // Go through districts and print the representatives by district
    for (int i = 0; i < dist_len; i++) {
        dist_num = _pelections->get_district_array().get(i).get_serial_number();
        if (_pelections->get_district_array().get(i).get_name()[0] != '\0') {
            cout << endl << "District " << _pelections->get_district_array().get(i).get_name() << endl;
        }
        print_index = 1;
        list <Representative>::const_iterator itr;
        try {
            for (itr = _pelections->find_party(party_number)->get_representatives().begin(); itr != _pelections->find_party(party_number)->get_representatives().end(); ++itr)
            {
                if (itr->get_district_number() == dist_num) {
                    cout << print_index << ". ";
                    cout << *itr;
                    print_index++;
                }
            }
        }
        catch (out_of_range& ex) {
            throw;
        }
        catch (exception& ex) {
            throw;
        }
    }
}