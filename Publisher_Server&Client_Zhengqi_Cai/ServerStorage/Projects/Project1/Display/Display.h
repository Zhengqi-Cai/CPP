#pragma once
///////////////////////////////////////////////////////////////
// Display.h - process starter for pop-up dispaly(Proj 1)    //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * This package contains one process starter class: Display.
 * Its purpose is to create a process and pop-up the html files
 * in targetPath one by one.
 * It is implemented using standard IO to interact, and some tools
 * in Utilities and FileSystem like ProcessCmdLine to analyze inputs.
 *
 *
 *
 * Required Files:
 * ---------------
 * Display.h
 * ../DirectoryNavigator/FileSystem/FileSystem.h
 * ../Process/Process/Process.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 04 Feb 2019
 * - first release
 *
 */

#include <iostream>
#include <vector>
//#include <windows.h>
#include <conio.h>

#include "../DirectoryNavigator/FileSystem/FileSystem.h"

namespace SrcPublisher {

	class Display
	{
	public:
		Display(const std::string fullPath, const std::string appPath, int max);
		void doDisplay();

	private:

		std::string fullPath_;
		std::string appPath_;
		unsigned int max_ = 50;

	};
}










