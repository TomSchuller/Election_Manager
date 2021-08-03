/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on a simple election round.
*****************************************************/

#include "Simple_Elections.h"

Simple_Elections::Simple_Elections(int year, int month, int day, int representatives_count) : Elections(year, month, day)
{
	// only one district so make it with an empty name
	this->Elections::add_district("", representatives_count, DIVIDED);
}

Simple_Elections::Simple_Elections(istream& in) : Elections(in)
{
}

Simple_Elections::~Simple_Elections()
{
}

void Simple_Elections::save(ostream& out) const
{
	Elections::save(out);
}

void Simple_Elections::load(istream& in)
{
	Elections::load(in);
}