/////////////////////////////////////////////////////////////////////
// CodePubrFactory.cpp - Factory of CodePublisher(Project 3)       //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "CodePubrFactory.h"
#include"CodePubr.h"
#include"../Utilities/StringUtilities/StringUtilities.h"
#include "../customLogger/customLogger.h"
using namespace Utilities;
using namespace CodePublisher;
using namespace customLogging;
CodePubrFactory::CodePubrFactory()
{
}


CodePubrFactory::~CodePubrFactory()
{
	
}

ICodePubr * CodePublisher::CodePubrFactory::CreateCustom(Utilities::ProcessCmdLine* ppcl, std::string fDirOut)
{
	Title(logOpen_,"CodePubrFactory creating custom...");

	return (new CodePubr(ppcl, fDirOut));
}
