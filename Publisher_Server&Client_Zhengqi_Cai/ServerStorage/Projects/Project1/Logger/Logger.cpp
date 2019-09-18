///////////////////////////////////////////////////////////////
// Logger.h - Generic logger (Proj 1)                        //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
#include "Logger.h"
#include <string>
#include "../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h"


using namespace Utilities;
bool Logger::loggerOn_ = false;

//----< start the logger to show >---------------------------
void Logger::start()
{
	loggerOn_ = true;
}
//----< write a title  >---------------------------
void Logger::title(std::string tit)
{
	if (loggerOn_) {
		Utilities::title("(" + tit + ")");
	}
}
//----< write content  >---------------------------
void Logger::content(std::string cont) {
	if (loggerOn_) {
		std::cout << "\n" << cont << std::endl;
	}
}

