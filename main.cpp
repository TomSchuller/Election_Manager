/********************************
 * Name: Tom Schuller, I.D: 205928146
 * Name: Ofek Shavit, I.D: 207330671
 * Date: 24/01/2021
 * Exercise 3
 * This program contains functions that manage elections.
 ********************************/
#include "Election_Input.h"

/*************** MENU VARIABLES ***************/

enum class Menu_options {
    ADD_DISTRICT = 1, ADD_CITIZEN, ADD_PARTY, ADD_REPRESENTATIVE, PRINT_DISTRICTS, PRINT_CITIZENS,
    PRINT_PARTIES, CAST_VOTE, PRINT_RESULTS, EXIT, SAVE_ELEC_ROUND, LOAD_ELEC_ROUND
};


enum class First_Menu_options {
    NEW_ELECTION = 1, LOAD_ELECTION, END_ELECTION
};


int main()
{
    // Initialize election
    bool menu = true;
    bool first_menu = false;
    Elections* election = nullptr;
    Print print(election);
    Input input;
    string str_menu;
    int ch = UNDEFINED;
    Menu_options opp;

    // First menu
    while (!first_menu)
    {
        print.main_menu();
        getline(cin, str_menu);
        try {
            ch = input.is_valid_number(str_menu);
            if (ch < 1 || ch > 3) throw invalid_argument("Error! Please enter a valid number!");
        }
        catch (invalid_argument& ex) {
            ch = UNDEFINED;
            cout << ex.what() << endl;
        }

        if (static_cast<First_Menu_options>(ch) == First_Menu_options::NEW_ELECTION)
        {
            int elec_type, election_year, election_month, election_day;
            try {
                input.new_election_input(elec_type, election_day, election_month, election_year);
                if (elec_type < 0 || elec_type > 1) throw invalid_argument("Error! Please enter a valid number!");
                // create election by type
                if (static_cast<ELECTION_TYPE>(elec_type) == ELECTION_TYPE::REGULAR) { 
                    election = new Elections(election_year, election_month, election_day);
                    print.set_elections(election);
                    first_menu = true;
                    menu = false;
                }
                else if (static_cast<ELECTION_TYPE>(elec_type) == ELECTION_TYPE::SIMPLE)// simple elections
                {
                    int representatives_count;
                    input.new_simple_election_input(representatives_count);
                    if (representatives_count <= 0) {
                        cout << "Error! You've entered an invalid number of representatives!" << endl
                            << "Must be an integer above 0!" << endl << endl;
                    }
                    else {
                        election = new Simple_Elections(election_year, election_month, election_day, representatives_count);
                        print.set_elections(election);
                        first_menu = true;
                        menu = false;
                    }
                }

            }
            catch (invalid_argument& ex) {
                cout << ex.what() << endl;
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            catch (...) {
            }
        }

        else if (static_cast<First_Menu_options>(ch) == First_Menu_options::LOAD_ELECTION)
        {
            ELECTION_TYPE type;
            string name;
            try {
                cout << endl << "You've selected menu option 2." << endl << "Enter file name you wish to load: ";
                getline(cin, name);
                ifstream infile(name, ios::binary);
                if (!infile) {
                    throw runtime_error("ERROR! File doesn't exists!");
                }

                infile.read(rcast(&type), sizeof(type));

                if (!infile.good()) {
                    throw runtime_error("ERROR! Couldn't read from file!");
                }

                if (type == ELECTION_TYPE::REGULAR) {
                    election = new Elections(infile);
                    first_menu = true;
                    menu = false;
                }

                else {
                    election = new Simple_Elections(infile);
                    first_menu = true;
                    menu = false;
                }

                print.set_elections(election);

                infile.close();
                cout << name << " has been loaded successfully!" << endl;

            }
            catch (runtime_error& ex) {
                cout << ex.what() << endl;
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            catch (...) {
            }
        }

        else if (static_cast<First_Menu_options>(ch) == First_Menu_options::END_ELECTION)// Selected option 3 - exit
        {
            cout << "You've selected menu option 3." << endl << "Thank you for using our program!" << endl;
            first_menu = true;
            menu = true;
        }
    }

    // Second Menu
    while (!menu && election != nullptr)
    {
        print.instructions();
        getline(cin, str_menu);
        try {
            ch = input.is_valid_number(str_menu);
            if (ch <= 0 || ch > 12) throw invalid_argument("Error! Please enter a valid number!");
        }
        catch (invalid_argument& ex) {
            ch = UNDEFINED;
            cout << ex.what() << endl;
        }
        opp = static_cast<Menu_options>(ch);
        switch (opp) {
            case Menu_options::ADD_DISTRICT: {
                string district_name;
                int representatives_count, type;
                if (election->get_type() == ELECTION_TYPE::SIMPLE) {
                    cout << "Error! You cannot add districts in a simple elections!" << endl;
                } else {
                    try {
                        input.district_input(district_name, representatives_count, type);
                        election->add_district(district_name, representatives_count, type);
                        if (static_cast<DISTRICT_TYPE>(type) == DISTRICT_TYPE::UNIFIED)
                            cout << "Unified District Added Successfully!" << endl << endl;
                        if (static_cast<DISTRICT_TYPE>(type) == DISTRICT_TYPE::DIVIDED)
                            cout << "Divided District Added Successfully!" << endl << endl;
                    }
                    catch (invalid_argument &ex) {
                        cout << ex.what() << endl;
                    }
                    catch (exception &ex) {
                        cout << ex.what() << endl;
                    }
                    catch (...) {
                    }
                }
                break;
            }
            case Menu_options::ADD_CITIZEN: {
                int citizen_id, year, district_number;
                string name;
                try {
                    input.citizen_input(name, citizen_id, year, district_number);
                    election->add_citizen(name, citizen_id, year, district_number);
                    cout << "Citizen Added Successfully!" << endl << endl;
                }
                catch (invalid_argument &ex) {
                    cout << ex.what() << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }

                break;
            }
            case Menu_options::ADD_PARTY: {
                string name;
                int candidate_id;
                try {
                    input.party_input(name, candidate_id);
                    election->add_party(name, candidate_id);
                    cout << "Party Added Successfully!" << endl << endl;
                }
                catch (invalid_argument &ex) {
                    cout << ex.what() << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }

                break;
            }
            case Menu_options::ADD_REPRESENTATIVE: {
                int representative_id, party_number, district_number;
                try {
                    input.rep_input(representative_id, party_number, district_number);
                    election->add_representative(representative_id, party_number, district_number);
                    cout << "Representative Added Successfully!" << endl << endl;
                }
                catch (invalid_argument &ex) {
                    cout << ex.what() << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }

                break;
            }
            case Menu_options::PRINT_DISTRICTS: {
                cout << endl << "You've selected menu option 5." << endl << "Displaying all districts:" << endl;
                try {
                    print.districts();
                    cout << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            case Menu_options::PRINT_CITIZENS: {
                cout << endl << "You've selected menu option 6." << endl << "Displaying all citizens:" << endl;
                try {
                    print.citizens();
                    cout << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            case Menu_options::PRINT_PARTIES: {
                cout << endl << "You've selected menu option 7." << endl << "Displaying all parties:" << endl;
                try {
                    print.parties();
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            case Menu_options::CAST_VOTE: {
                int citizen_id, party_number;
                try {
                    input.vote_input(citizen_id, party_number);
                    election->cast_vote(citizen_id, party_number);
                    cout << "You've successfully casted your vote! Thank you for influencing!" << endl << endl;
                }
                catch (invalid_argument &ex) {
                    cout << ex.what() << endl;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {

                }

                break;
            }
            case Menu_options::PRINT_RESULTS: {
                cout << endl << "You've selected menu option 9." << endl << "Displaying election results: " << endl;
                try {
                    election->results_ready();
                    print.results();
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            case Menu_options::EXIT: {
                cout << "Thank you for using our program!" << endl;
                delete election;
                election = nullptr;
                menu = true;
                break;
            }
            case Menu_options::SAVE_ELEC_ROUND: {
                string name;
                cout << endl << "You've selected menu option 11." << endl << "Enter saved file name: ";
                getline(cin, name);
                ofstream outfile(name, ios::binary | ios::trunc);
                try {
                    if (!outfile) {
                        throw runtime_error("ERROR! File doesn't exists!");
                    }
                    election->save(outfile);
                    cout << name << " has been saved successfully!" << endl;
                    outfile.close();
                }
                catch (runtime_error &ex) {
                    cout << ex.what() << endl;
                    menu = true;
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            case Menu_options::LOAD_ELEC_ROUND: {
                ELECTION_TYPE type;
                string name;
                cout << endl << "You've selected menu option 12." << endl << "Enter file name you wish to load: ";
                getline(cin, name);
                ifstream infile(name, ios::binary);
                try {
                    if (!infile) {
                        throw runtime_error("ERROR! Couldn't load file!");
                    }

                    infile.read(rcast(&type), sizeof(type));
                    if (!infile.good()) {
                        throw runtime_error("ERROR! Couldn't read from file!");
                    }

                    delete election;
                    election = nullptr;

                    if (type == ELECTION_TYPE::REGULAR) {
                        election = new Elections(infile);
                    }
                    else {
                        election = new Simple_Elections(infile);
                    }

                    print.set_elections(election);

                    infile.close();
                    cout << name << " has been loaded successfully!" << endl;
                }
                catch (runtime_error &ex) {
                    cout << ex.what() << endl;
                    menu = true; 
                }
                catch (exception &ex) {
                    cout << ex.what() << endl;
                }
                catch (...) {
                }
                break;
            }
            default: {
                break;
            }
        }
    }
    return 0;
}
