
/** Implementation file for the class Person. */
#include "Person.h"
#include <ostream>
using std::ostream;

/** Calculates a person's age at this year's birthday.
   @param year The current year
   @return the year minus the birth year
*/
int Person::age(int year) const {
	return year - birth_year;
}

/** Determines whether a person can vote.
	@param year The current year
	@return true if the person's age is greater than or
				 equal to the voting age
*/

/** Determines whether a person can drink.
	@param year The current year
	@return true if the person's age is greater than or
				 equal to the drinking age
*/
bool Person::can_vote(int year) const {
	int the_age = age(year);
	return the_age >= VOTE_AGE;
}

bool Person::can_drink(int year) const {
	int the_age = age(year);
	return the_age >= DRINKING_AGE;
}

/** Determines whether a person is a senior citizen.
	@param year the current year
	@return true if person's age is greater than or
				 equal to the age at which a person is
			 considered to be a senior citizen
*/
bool Person::is_senior(int year) const {
	return age(year) >= SENIOR_AGE;
}

/** Compares two Person objects for equality.
	@param per The second Person object
	@return true if both the family_name
	and given_names are the same
*/

/*<exercise chapter="9" section="5" type="programming" number="2">*/
bool Person::operator==(const Person& per) const {
	return family_name == per.family_name
		&& given_name == per.given_name;
}
/*</exercise>*/


/** Compares two Person objects for inequality.
	@param per The second Person object
	@return The opposite of the equality operator
*/

bool Person::operator!=(const Person& per) const {
	return !(*this == per);
}


/** Retrieves the information in a Person object
	and formats it for output. The result is
	then inserted into the target ostream.
	@param os The target ostream
	@param per The source Person
	@return The modified ostream after the data has
			been inserted
*/

ostream& operator<<(ostream& os, const Person& per) {
	os << "Given name: " << per.given_name << '\n'
		<< "Family name: " << per.family_name << '\n'
		<< "ID number: " << per.ID_number << '\n'
		<< "Year of birth: " << per.birth_year << '\n';
	return os;
}


