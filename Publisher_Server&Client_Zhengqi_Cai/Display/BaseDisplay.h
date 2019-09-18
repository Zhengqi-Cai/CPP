#pragma once
/////////////////////////////////////////////////////////////////////
// BaseDisplay.h - Abstract base class of Display                  //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Abstract base class: BaseDisplay.
 * Its purpose is to provide interface and common data memeber derived
 * Display class. It can add visibility of comments, function, class of
 *  a set of files(set is build-in data structure for receiving.)
 * It is implemented using set structure and standard IO.
 *
 *
 * Required Files:
 * ---------------
 * BaseDisplay.h
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
namespace CodePublisher {
	
	class BaseDisplay {
	public:
		BaseDisplay(std::string fDirIn, std::string fDirOut);
		virtual std::set<std::string> handleDisplays(std::set<std::string>& fOriginFileSpecs) = 0;
		virtual std::string handleOneFileDisp(std::string fFileSpec) = 0;
		void setFDirIn(std::string fDirIn);
		void setFDirOut(std::string fDirOut);
		virtual ~BaseDisplay() {};
	protected:
		std::string fDirIn_;
		std::string fDirOut_;
	};
}

