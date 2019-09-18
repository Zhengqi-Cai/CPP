/////////////////////////////////////////////////////////////////////
// LoaderFactory.cpp - Factory of Loader(Project 3)                //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "LoaderFactory.h"
#include"Loader.h"
using namespace CodePublisher;

LoaderFactory::LoaderFactory()
{
}


LoaderFactory::~LoaderFactory()
{
}

BaseLoader* CodePublisher::LoaderFactory::CreateCustom(ProcessCmdLine * ppcl)
{
	return (new Loader(ppcl));
}

