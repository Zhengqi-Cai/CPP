#pragma once
///////////////////////////////////////////////////////////////
// Logger.h - Generic logger (Proj 1)                        //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one static generic class: Logger.
 * Its purpose is to provide generic tools for log and a switch to 
 * show or hide the log.
 * It is implemented using some tools in Utilities for format output.
 *
 *
 *
 * Required Files:
 * ---------------
 * Logger.h
 * ../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Feb 2019
 * - first release
 *
 */
#include <iostream>

namespace Utilities {

	class Logger
	{
	public:
		static void start();
		static void content(std::string cont);
		static void title(std::string tit);
		
	private:
		static bool loggerOn_ ;
	};

	


}