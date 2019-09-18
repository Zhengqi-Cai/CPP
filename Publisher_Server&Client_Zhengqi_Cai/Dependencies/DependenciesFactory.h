#pragma once
/////////////////////////////////////////////////////////////////////
// DependenciesFactory.h - Factory of Dependencies(Project 3)      //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one factory class: DependenciesFactory.
 * Its purpose is to avoid directly including of specific Dependencies class.
 *
 *
 * Required Files:
 * ---------------
 * DependenciesFactory.h
 * BaseDependencies.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include "BaseDependencies.h"
namespace CodePublisher {
	class DependenciesFactory
	{
	public:
		DependenciesFactory();
		~DependenciesFactory();
		BaseDependencies* CreateCustom(std::string fDirIn, std::string fDirOut, std::string searchRootPath);
	};
}

