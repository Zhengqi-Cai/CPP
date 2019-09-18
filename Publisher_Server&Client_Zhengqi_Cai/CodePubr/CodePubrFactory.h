#pragma once
/////////////////////////////////////////////////////////////////////
// CodePubrFactory.h - Factory of CodePublisher(Project 3)         //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one factory class: CodePubrFactory.
 * Its purpose is to avoid directly including of specific codepubr class.
 *
 *
 * Required Files:
 * ---------------
 * CodePubrFactory.h
 * ICodePubr.h
 * "../Utilities/CodeUtilities/CodeUtilities.h"
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include"ICodePubr.h"
#include"../Utilities/CodeUtilities/CodeUtilities.h"
namespace CodePublisher {
	class CodePubrFactory
	{
	public:
		CodePubrFactory();
		~CodePubrFactory();
		ICodePubr* CreateCustom(Utilities::ProcessCmdLine* ppcl, std::string fDirOut);
	private:
		bool logOpen_ = true;
	};
}
