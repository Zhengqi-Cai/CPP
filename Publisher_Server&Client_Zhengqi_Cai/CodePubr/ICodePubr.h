#pragma once
/////////////////////////////////////////////////////////////////////
// ICodePubr.h - Interface of CodePublisher(Project 3)             //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Interface class: ICodePubr.
 * Its purpose is to provide separated interface of codepubr for clients.
 * It is implemented using set as core data structure to store fileSpecs.
 *
 *
 * Required Files:
 * ---------------
 * ICodePubr.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include<string>
#include<set>

namespace CodePublisher {
	class ICodePubr
	{
	public:
		virtual bool IsWorking()=0;
		virtual int setFDirOut(std::string fDirOut) = 0;
		virtual std::string getFDirOut() = 0;
		virtual std::set<std::string> ProduceProtoPages()=0;
		virtual std::set<std::string> ProduceProtoWithDep() = 0;
		virtual std::set<std::string> ProduceProtoWithVis() = 0;
		virtual std::set<std::string> ProtoFullyProduce() = 0;
		virtual ~ICodePubr() {}
	};
	
}
