#pragma once
/////////////////////////////////////////////////////////////////////
// ConverterFactory.h - Factory of Converter(Project 3)            //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one factory class: ConverterFactory.
 * Its purpose is to avoid directly including of specific converter class.
 *
 *
 * Required Files:
 * ---------------
 * ConverterFactory.h
 * BaseConverter.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */
#include"BaseConverter.h"
namespace CodePublisher {
	class ConverterFactory
	{
	public:
		ConverterFactory();
		~ConverterFactory();
		BaseConverter* CreateCustom(std::string fDirOut, std::string targetExt);
	};
}

