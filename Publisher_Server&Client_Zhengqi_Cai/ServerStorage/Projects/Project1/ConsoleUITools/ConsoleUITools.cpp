///////////////////////////////////////////////////////////////
// ConsolUITools.h - Tools for console interaction           //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////

#include "ConsoleUITools.h"


using namespace Utilities;
//----< test stub >---------------------------

#ifdef TEST_CONSOLEUITOOLS
int main() {
	// test readItems and showItems
	std::vector<int> items;
	ConsoleUITools::readItems("enter the items:", items);
	ConsoleUITools::showItems("here is the items:", items);
}
#endif // TEST_CONSOLEUITOOLS


//----< return string of currentTime >---------------------------

std::string ConsoleUITools::getCurrentTime() {
	time_t nowtime = time(NULL);
	struct tm *l = new tm;
	localtime_s(l, &nowtime);
	char buf[128];
	std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d_%02d_%02d_%02d", l->tm_year + 1900, l->tm_mon + 1, l->tm_mday, l->tm_hour, l->tm_min, l->tm_sec);
	delete l;
	std::string s(buf);
	return s;
}

//----< expose a Y/N question in the Console and return the input answer as a bool >----

bool ConsoleUITools::getTOrF(std::string question) {
	std::string feedback;
	while (true) {
		ConsoleUITools::readItem("\n" + question + "(Y/N)", feedback);
		if (feedback == "Y") {
			return true;
		}
		else if (feedback == "N") {
			return false;
		}
		else {
			preface("Invalid answer! Please reenter: ");
			std::cout << std::endl;
		}
	}
}
