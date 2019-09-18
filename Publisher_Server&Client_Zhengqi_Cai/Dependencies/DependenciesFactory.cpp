/////////////////////////////////////////////////////////////////////
// DependenciesFactory.cpp - Factory of Dependencies(Project 3)    //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "DependenciesFactory.h"
#include "Dependencies.h"

using namespace CodePublisher;
DependenciesFactory::DependenciesFactory()
{
}


DependenciesFactory::~DependenciesFactory()
{
}

BaseDependencies * CodePublisher::DependenciesFactory::CreateCustom(std::string fDirIn, std::string fDirOut, std::string searchRootPath)
{
	return new Dependencies(fDirIn,fDirOut,searchRootPath);
}
