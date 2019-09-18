/////////////////////////////////////////////////////////////////////
// BaseConverter.cpp - Abstract base class of Converter(Project 2) //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "BaseConverter.h"

//----< constructor for init of derived class>-------

CodePublisher::BaseConverter::BaseConverter(std::string fDirOut, std::string targetExt) :fDirOut_(fDirOut), targetExt_(targetExt)
{
}

//----< set output directory >-------

void CodePublisher::BaseConverter::setFDirOut(std::string fDirOut) 
{ 
	fDirOut_ = fDirOut; 
}

//----< abstract class- no test stub >-------
