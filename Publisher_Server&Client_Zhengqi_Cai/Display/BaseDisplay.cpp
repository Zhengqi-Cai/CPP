/////////////////////////////////////////////////////////////////////
// BaseDisplay.cpp - Abstract base class of Display                //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "BaseDisplay.h"

//----< constructor for init of derived class>-------

CodePublisher::BaseDisplay::BaseDisplay(std::string fDirIn, std::string fDirOut) :fDirIn_(fDirIn), fDirOut_(fDirOut)
{
}

//----< set input directory >-------

void CodePublisher::BaseDisplay::setFDirIn(std::string fDirIn)
{
	fDirIn_ = fDirIn;
}

//----< set output directory >-------

void CodePublisher::BaseDisplay::setFDirOut(std::string fDirOut)
{
	fDirOut_ = fDirOut;
}

//----< abstract class- no test stub >-------

