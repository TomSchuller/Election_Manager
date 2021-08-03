/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations of functions that print every output in the program.
*****************************************************/
#pragma once
#include "Simple_Elections.h"

class Print {
private:
    Elections* _pelections;
public:
    Print();
    Print(Elections* _pelections);
    ~Print();

    bool set_elections(Elections* pelections);

    /****************************
    * main_menu()
    * This function prints the main menu.
    ****************************/
    void main_menu(void);

    /****************************
    * instructions()
    * This function prints the second menu instructions.
    ****************************/
    void instructions(void);

    /****************************
    * citizens()
    * This function prints all citizens.
    ****************************/
    void citizens(void) const;

    /****************************
    * districts()
    * This function prints all districts.
    ****************************/
    void districts(void) const;

    /****************************
    * parties()
    * This function prints all parties.
    ****************************/
    void parties(void) const;

    /****************************
    * results()
    * This function prints the election results.
    ****************************/
    void results(void) const;

    /****************************
    * district_results()
    * This function prints the results for each district.
    ****************************/
    void district_results(void) const;

    /****************************
    * party_results()
    * This function prints the results for each party.
    ****************************/
    void party_results(void) const;

    /****************************
    * unified_district_candidates()
    * This function prints the district winner.
    ****************************/
    void unified_district_candidates(int district_number) const;

    /****************************
    * divided_district_candidates()
    * This function prints the the divided district candidates.
    ****************************/
    void divided_district_candidates(int district_number) const;

    /****************************
    * district_reps()
    * This function prints each party's elected representatives for the desired district
    ****************************/
    void district_reps(int district_number) const;

    /****************************
    * party_reps()
    * This function prints the desired party's representatives
    ****************************/
    void party_reps(int party_number) const;
};