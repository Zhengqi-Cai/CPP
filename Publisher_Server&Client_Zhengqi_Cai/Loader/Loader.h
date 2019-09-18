#pragma once
/////////////////////////////////////////////////////////////////////
// Loader.h - Loading files for operation(Project 2)               //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one file-loading class: Loader.
 * It is mainly designed as components of CodePublisher(Project 2).
 * Its main duty is receiving handled command line from processCmdLine 
 * class, search files, record adn return fullFileSpec as a multimap. 
 * It is implemented mainly using DirExplorerN class as well as some 
 * tools in FileSystem nameSpace.
 *
 *
 *
 * Required Files:
 * ---------------
 * Loader.h
 * BaseLoader.h
 * "../DirExplorer-Naive/DirExplorerN.h"
 * "../stringUtMore/stringUtMore.h"
 * 
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 01 Mar 2019
 * - first release
 *
 */
#include "../DirExplorer-Naive/DirExplorerN.h"
#include "../stringUtMore/stringUtMore.h"
#include <string>
#include "BaseLoader.h"


using namespace Utilities;
namespace CodePublisher {
	
	class Loader : public BaseLoader
	{
	public:
		Loader(ProcessCmdLine* ppcl);
		//Loader(std::string fRootPath, bool subdir, std::vector<std::string>patterns, std::vector<std::string>regexes);
		int loadFiles() override;
	private:
		DirExplorerN de;
		bool logOpen_=true;
	};
	//normaly we should use template or inheritence to extend dirExploreN with more functionality
	//However, as the duty of my dirExploreN is only provide a map of searched file, which is independant
	//I just use it directly
}
