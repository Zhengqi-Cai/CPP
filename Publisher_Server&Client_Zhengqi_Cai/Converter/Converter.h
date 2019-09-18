#pragma once
///////////////////////////////////////////////////////////////
// Converter.h - converter from txt to html(Proj 2)          //
// ver 1.2                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one derived file-conversion class: Converter.
 * It is mainly designed as components of CodePublisher(Project 2).
 * Its duty is mainly to receive a set of fileSpecs, and convert
 * them to equivalvant html file as well as some pre-components
 * for final products of CodePublisher. 
 * It is implemented using file IO streams defined in File class
 * as well as a predefined template.
 *
 *
 *
 * Required Files:
 * ---------------
 * Converter.h
 * BaseConverter.h
 *
 * Maintenance History:
 * --------------------
 * ver 1.2 : 10 Mar 2019
 * - modify the args of doCOnversions to a set
 * - make it inherited from BaseConverter.
 * ver 1.1 : 01 Mar 2019
 * - add doConversionS function to receive files from Loader
 * ver 1.0 : 04 Feb 2019
 * - first release
 *
 */

#include <iostream>
#include "BaseConverter.h"

namespace CodePublisher {
	class Converter : public BaseConverter
	{
	public:
		Converter(std::string fDirOut, std::string targetExt);
		std::string doConversion(const std::string& fOriginFileSpec) override;
		std::set<std::string> doConversionS(std::set<std::string>& pFOriginFileSpecs);
		~Converter();
		static std::string convertALine(std::string line);

	private:
		bool logOpen_=false;
	};
}



