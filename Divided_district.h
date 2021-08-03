/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on divided districts.
*****************************************************/

#pragma once
#include "District.h"

class Divided_District : public District
{
public:
	Divided_District();
	Divided_District(const string name, int serial_number, int representatives);
	Divided_District(const  Divided_District& other);
	virtual ~Divided_District();

	virtual DISTRICT_TYPE get_type(void) const override { return DISTRICT_TYPE::DIVIDED; }

	virtual void save(ostream& out) const override;
	virtual void load(istream& in) override;

};