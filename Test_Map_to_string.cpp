/** Simple program to test map */

#include <iostream>
#include <string>

#include "Hash_Table_Chain.h"

typedef KW::hash_map<std::string, int> map_type;


using std::string;
using std::cout;
using std::endl;

int main()
{
	
	//Test map insert and indexing operations
	map_type map;
	map["Hello"] = 1;
	cout << map.to_string() << endl;
	map["Good bye"] = 100;
	cout << map.to_string() << endl;
	map["Hello"] = map["Hello"] + 1;
	cout << map.to_string() << endl;
	//Test erase
	map.erase("Hello");
	cout << "Map contents after erase of \"Hello\"\n";
	cout << map.to_string() << endl;


	return 0;
}
