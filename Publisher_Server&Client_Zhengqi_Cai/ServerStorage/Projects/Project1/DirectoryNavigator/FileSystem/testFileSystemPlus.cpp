///////////////////////////////////////////////////////////////
// testFileSystemPlus.cpp - addition test of FileSystem class//
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////

#include "FileSystem.h"
#include <iostream>

#ifdef TEST_FILESYSTEM_PLUS

using namespace FileSystem;

int main() {

	////test Directory::static bool exists(const std::string& path);
	//std::string unexist = "./debug/unexist";
	//std::cout << Directory::exists(unexist) << std::endl;

	////test Directory::static bool create(const std::string& path);
	//
	//std::cout << Directory::create(unexist) << "check it out in" + unexist << std::endl;
	//std::cout << Directory::exists(unexist) << std::endl;

	std::string existFile = "C:/Program Files/internet explorer/iexplore.exe";
	std::cout << File::exists(existFile)<<std::endl;

}
#endif // TEST_FILESYSTEM_PLUS
