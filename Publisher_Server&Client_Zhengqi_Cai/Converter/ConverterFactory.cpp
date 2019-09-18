/////////////////////////////////////////////////////////////////////
// ConverterFactory.cpp - Factory of Converter(Project 3)          //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "ConverterFactory.h"
#include"Converter.h"

using namespace CodePublisher;
ConverterFactory::ConverterFactory()
{
}


ConverterFactory::~ConverterFactory()
{
}

BaseConverter * CodePublisher::ConverterFactory::CreateCustom(std::string fDirOut, std::string targetExt)
{
	return new Converter(fDirOut,targetExt);
}
