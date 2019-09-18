/////////////////////////////////////////////////////////////////////
// BaseLoader.cpp - Abstract base class of Loader(Project 2)       //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "BaseLoader.h"

//----< constructor for init of derived class>-------

CodePublisher::BaseLoader::BaseLoader(std::string fRootPath) :fRootPath_(fRootPath),filesLoaded(false)
{
}

//----< set input directory >-------

std::multimap<std::string, std::string>& CodePublisher::BaseLoader::matchedMap()
{
	return regexMatchMap_;
}

//----< set output directory >-------

std::string CodePublisher::BaseLoader::getRootPath()
{
	return fRootPath_;
}

bool CodePublisher::BaseLoader::isFilesLoaded()
{
	return filesLoaded;
}

//----< abstract class- no test stub >-------


