/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on divided districts.
*****************************************************/

#include "Divided_District.h"

Divided_District::Divided_District() : District()
{
}

Divided_District::Divided_District(const string name, int serial_number, int representatives) : District(name, serial_number, representatives)
{
}

Divided_District::Divided_District(const Divided_District& other) : District(other)
{
}

Divided_District::~Divided_District()
{
}

void Divided_District::save(ostream& out) const
{
	District::save(out);
}

void Divided_District::load(istream& in)
{
	District::load(in);
}