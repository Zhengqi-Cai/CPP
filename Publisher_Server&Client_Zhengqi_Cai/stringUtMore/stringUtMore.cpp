/////////////////////////////////////////////////////////////////////
// stringUtMore.cpp - Supplement of StringUtilities tools          //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "stringUtMore.h"

using namespace Utilities;

// -----< test stub >-----------------------------------------------------

#ifdef TEST_STRINGUTMORE
int main() {
	std::multimap<int, std::string> my_map;
	my_map.insert(std::make_pair(50, "china"));
	my_map.insert(std::make_pair(100, "usa"));
	my_map.insert(std::make_pair(30, "english"));
	my_map.insert(std::make_pair(40, "hongkong"));
	showMultiMap(my_map);
}
#endif // TEST_STRINGUTMORE
