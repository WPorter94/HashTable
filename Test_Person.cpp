/** Test_Person is an application that tests class Person. */
#include <iostream>
#include <fstream>
#include "Hash_Table_Chain.h"
#include "Person.h"


using namespace std;

typedef KW::hash_map<Person, string> map_type;
typedef KW::hash_map<Person, string>::const_iterator const_iter;


// map_type map2;
// split comma delimited string
std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

int readfile(string infile) {
	string line;
	ifstream myfile(infile);
	istringstream ss;
	map_type map1, map2;
	int year;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << '\n';
			if (line.size() > 5) {
				vector<std::string> s = split(line, ',');
				istringstream ss(s[3]); // convert year to integer
				ss >> year;
				cout << year << endl;
				Person p1(s[0], s[1], s[2], year);
				// cout << p1.age(2019);
				if (p1.can_drink(2019)) {
					string drink = s[4];
					map1[p1] = drink;
				}
				else {
					map1[p1] = "Under age";
				}
			}
		}

		myfile.close();
	}
	else cout << "Unable to open file";


	myfile.open(infile);

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			// cout << line << '\n';
			if (line.size() > 5) {
				vector<std::string> s = split(line, ',');
				istringstream ss(s[3]); // convert year to integer
				ss >> year;
				// cout << year << endl;
				Person p1(s[0], s[1], s[2], year);

				if (p1.can_drink(2019)) {
					string drink = s[4];
					map2[p1] = drink;
				}
				else {
					map2[p1] = "Under age";
				}

//				if (map1.find(p1) != map1.end())
//					cout << "found!" << endl;
//				else
//					cout << "not found!" << endl;

				string drink1 = map1[p1];
				string drink2 = map2[p1];
				if (drink1 == drink2)
					cout << "pass" << endl;
				else
					cout << "fail" << endl;
			}
		}
	}



	  map_type::iterator itr = map1.begin();
	if (itr != map1.end()) {
		cout << "age:" << itr->first.age(2019) << endl;
		cout << "[" << itr->first << ", " << itr->second << "]";
		while (++itr != map1.end()) {
			cout << ", [" << itr->first << ", " << itr->second << "]";
		}
	}
	return 0;
}

int main() {


	readfile("persons.csv");




}
