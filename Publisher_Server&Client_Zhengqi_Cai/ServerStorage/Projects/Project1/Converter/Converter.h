#pragma once
///////////////////////////////////////////////////////////////
// Converter.h - converter mainly from txt to html(Proj 1)   //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one file-conversion class: Converter.
 * Its purpose is mainly to convert single source file to visible
 * html file with the same content.
 * It is implemented using file IO streams defined in File class
 * to read and write txt and use regex for translate '<' '>'.
 *
 *
 *
 * Required Files:
 * ---------------
 * Converter.h
 * ../DirectoryNavigator/FileSystem/FileSystem.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 04 Feb 2019
 * - first release
 *
 */

#include <string> 
namespace SrcPublisher {

	class Converter
	{
	public:
		Converter(std::string targetFullPath, std::string targetExt);
		void doConversion(const std::string& originFileSpec);
		std::string getTargetFullPath();
		std::string getExt();
		static std::string convertALine(std::string line);

	private:
		std::string targetFullPath_;
		std::string targetExt_;
		
	};
}



