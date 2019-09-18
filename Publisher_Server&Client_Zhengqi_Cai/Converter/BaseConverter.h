#pragma once
/////////////////////////////////////////////////////////////////////
// BaseConverter.h - Abstract base class of Converter(Project 2)   //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Abstract base class: BaseConverter.
 * Its purpose is to provide interface and common data memeber derived 
 * Converter class. It can both convert one single file as well as a set 
 * of files(set is build-in data structure for receiving.)
 * It is implemented using set structure and standard IO.
 *
 *
 * Required Files:
 * ---------------
 * BaseConverter.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include<iostream>
#include <set>
namespace CodePublisher {
	//the base class hold essential input or result data, as well as public interface
	class BaseConverter {
	public:
		BaseConverter(std::string fDirOut, std::string targetExt);
		
		//I do not init set cuz converter can also convert one single file, same as display. In contrast dependencies have to hold the set all the time.
		virtual std::string doConversion(const std::string& fOriginFileSpec) = 0;
		virtual std::set<std::string> doConversionS(std::set<std::string>& pFOriginFileSpecs) = 0;

		void setFDirOut(std::string fDirOut);
		virtual ~BaseConverter() {};
	protected:
		std::string fDirOut_;
		std::string targetExt_;
	};

	
}

