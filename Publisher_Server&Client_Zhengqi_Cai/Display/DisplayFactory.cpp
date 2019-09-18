/////////////////////////////////////////////////////////////////////
// DisplayFactory.cpp - Factory of Display(Project 3)              //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "DisplayFactory.h"
#include"Display.h"
using namespace CodePublisher;

DisplayFactory::DisplayFactory()
{
}


DisplayFactory::~DisplayFactory()
{
}

BaseDisplay * CodePublisher::DisplayFactory::CreateCustom(std::string fDirIn, std::string fDirOut)
{
	return new Display(fDirIn,fDirOut);
}
