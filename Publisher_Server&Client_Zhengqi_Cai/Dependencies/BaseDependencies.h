#pragma once
/////////////////////////////////////////////////////////////////////
// BaseDependencies.h - Abstract base class of Dependencies        //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Abstract base class: BaseDependencies.
 * Its purpose is to provide interface and common data memeber derived
 * Dependencies class. It can analyze and add dependencies of a set
 * of files(set is build-in data structure for receiving.)
 * It is implemented using set structure and standard IO.
 *
 *
 * Required Files:
 * ---------------
 * BaseDependencies.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include<iostream>
#include<set>

namespace CodePublisher {
	class BaseDependencies {
	public:
		BaseDependencies(std::string fDirIn, std::string fDirOut);
		virtual std::set<std::string> handleDependcies(std::set<std::string>& fOriginFileSpecs) = 0;
		void setFDirIn(std::string fDirIn);
		void setFDirOut(std::string fDirOut);
		virtual ~BaseDependencies() {};
	protected:
		std::string fDirIn_;
		std::string fDirOut_;
	};

}
