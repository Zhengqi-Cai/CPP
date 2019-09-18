#pragma once
/////////////////////////////////////////////////////////////////////
// DisplayFactory.h - Factory of Display(Project 3)                //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one factory class: DisplayFactory.
 * Its purpose is to avoid directly including of specific Display class.
 *
 *
 * Required Files:
 * ---------------
 * DisplayFactory.h
 * BaseDisplay.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include"BaseDisplay.h"
namespace CodePublisher {
	class DisplayFactory
	{
	public:
		DisplayFactory();
		~DisplayFactory();
		BaseDisplay* CreateCustom(std::string fDirIn, std::string fDirOut);
	};
}
