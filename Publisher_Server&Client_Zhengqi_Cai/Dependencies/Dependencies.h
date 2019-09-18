#pragma once
/////////////////////////////////////////////////////////////////////
// Dependencies.h - constructs for adding Dependencies(Project 2)  //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one derived dependency-adding class: Dependencies.
 * It is mainly designed as components of CodePublisher(Project 2).
 * Its duty is to receive a set of fileSpecs and searchRoot, analyze and add
 * dependency links at the top of converted files.
 * It is implemented mainly using ParseMgr Class for dependency extration
 * and writing them in coordinating with pre-components provided by Converter.
 *
 *
 *
 * Required Files:
 * ---------------
 * Dependencies.h
 * BaseDependencies.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */

#include <iostream>
#include <set>
#include <vector>
#include "BaseDependencies.h"


namespace CodePublisher {
	
	class Dependencies : public BaseDependencies
	{
	public:
		Dependencies(std::string fDirIn, std::string fDirOut, std::string searchRootPath);
		std::set<std::string> handleDependcies(std::set<std::string>& fOriginFileSpecs) override;
		~Dependencies();
	private: 
		std::string handleOneFileDep(std::string fFileSpec);
		std::string writeOneFileDep(std::string targetFileName);

		bool logOpen_ = false;
		std::string searchRootPath_;
		std::set<std::string> fOriginFileSpecs_;
		//temp vector for each file
		std::vector<std::string> notInTrees_;
		std::vector<std::string> notBeChosens_;
		std::vector<std::string> valids_;
	};
}

