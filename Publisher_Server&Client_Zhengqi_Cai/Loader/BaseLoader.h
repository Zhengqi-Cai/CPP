#pragma once
/////////////////////////////////////////////////////////////////////
// BaseLoader.h - Abstract base class of Loader(Project 2)         //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Abstract base class: BaseLoader.
 * Its purpose is to provide interface and common data memeber derived
 * Loader class. It can accept a rootPath and load specific fileSpecs
 * (multimap is build-in data structure for result.)
 * It is implemented using multimap structure and standard IO.
 *
 *
 * Required Files:
 * ---------------
 * BaseLoader.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include<iostream>
#include<map>
namespace CodePublisher {
	class BaseLoader {
	public:
		BaseLoader(std::string fRootPath) ;
		virtual int loadFiles() = 0;
		virtual ~BaseLoader() {};
		//main interface to return searched result
		std::multimap<std::string, std::string>& matchedMap();
		std::string getRootPath();
		bool isFilesLoaded();

	protected:
		std::multimap<std::string, std::string> regexMatchMap_; //loaded without slash
		std::string fRootPath_; //full path
		bool filesLoaded;

	};


}

