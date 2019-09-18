#include "BaseDependencies.h"
/////////////////////////////////////////////////////////////////////
// BaseDependencies.cpp - Abstract base class of Dependencies      //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

//----< constructor for init of derived class>-------

CodePublisher::BaseDependencies::BaseDependencies(std::string fDirIn, std::string fDirOut) : fDirIn_(fDirIn), fDirOut_(fDirOut)
{

}

//----< set input directory >-------

void CodePublisher::BaseDependencies::setFDirIn(std::string fDirIn)
{
	fDirIn_ = fDirIn;
}

//----< set output directory >-------

void CodePublisher::BaseDependencies::setFDirOut(std::string fDirOut)
{
	fDirOut_ = fDirOut;
}


//----< abstract class- no test stub >-------
