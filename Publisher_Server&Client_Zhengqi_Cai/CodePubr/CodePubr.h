#pragma once
/////////////////////////////////////////////////////////////////////
// CodePubr.h - Assembly of CodePublisher toolset(Project 2)       //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Assembly class: CodePubr.
 * Its purpose is to provide interface of parse related actitivities for
 * good encapsulation of low level parse tools and avoid cyclic dependencies.
 * It is implemented mainly using a set of parser toolset, and some data structure
 * like priority_queue to collect specific results.
 *
 *
 * Required Files:
 * ---------------
 * CodePubr.h
 * "../Utilities/CodeUtilities/CodeUtilities.h"
 * "../Loader/BaseLoader.h"
 * "../Converter/BaseConverter.h"
 * "../Dependencies/BaseDependencies.h"
 * "../Display/BaseDisplay.h"
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include "ICodePubr.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include "../Loader/BaseLoader.h"
#include "../Converter/BaseConverter.h"
#include "../Dependencies/BaseDependencies.h"
#include "../Display/BaseDisplay.h"
#include <map>
#include <set>

namespace CodePublisher {
	class CodePubr :public ICodePubr
	{
	public:
		CodePubr(Utilities::ProcessCmdLine* ppcl,std::string fDirOut);
		~CodePubr();
		int clearAll();

		// Inherited via ICodePubr
		virtual bool IsWorking()override { return isWorking; }
		virtual int setFDirOut(std::string fDirOut) override;
		virtual std::string getFDirOut() override;
		virtual std::set<std::string> ProduceProtoPages() override;
		virtual std::set<std::string> ProduceProtoWithDep() override;
		virtual std::set<std::string> ProduceProtoWithVis() override;
		virtual std::set<std::string> ProtoFullyProduce() override;


	private:
		std::multimap<std::string, std::string> loadAndShow();

		BaseLoader* pld_ = NULL;
		BaseConverter* pcvt_ = NULL;
		BaseDependencies* pdpd_ = NULL;
		BaseDisplay* pdp_ = NULL;
		bool isWorking;
		std::set<std::string> fProducedFileSpecs_;
		std::string fDirOut_;
		bool logOpen_ = true;

	};
}
