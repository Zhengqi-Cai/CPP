#pragma once
/////////////////////////////////////////////////////////////////////
// ParseMgr.h - Manager of Parser toolset(Project 2)               //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Manager class: ParseMgr.
 * Its purpose is to provide interface of parse related actitivities for 
 * good encapsulation of low level parse tools and avoid cyclic dependencies.
 * It is implemented mainly using a set of parser toolset, and some data structure
 * like priority_queue to collect specific results.
 *
 *
 * Required Files:
 * ---------------
 * ParseMgr.h
 * "../Parser/ConfigureParser.h"
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include "../Parser/ConfigureParser.h"
#include <set>
namespace CodeAnalysis {
	// predicate of priority_queue below
	class cmpLine {
	public:
		bool operator()(std::pair<int, std::string> p1, std::pair<int, std::string> p2)
		{
			if (p1.first == p2.first) return p1.second.size() < p2.second.size();
			return p1.first > p2.first;
		}
	};

	class ParseMgr
	{
	public:
		ParseMgr();
		~ParseMgr();
		int doParse(std::string fFileSpec);
		std::set<std::string> extractDepsR();
		int function_classScopeSequence();
		int sequenceSize();
		std::pair<int, std::string> peekNextScopeEntity();
		void popNextScopeEntity();
		static std::mutex parMgrmtx_;

	private:
		void treeWalkForLinearScope(ASTNode* pRoot);
		ConfigParseForCodeAnal* pConfigure;
		std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, cmpLine> linearLineMark;
		bool logOpen_ = false;
	};

	
}
// I just want to become familiar with pq. Using map may be a better choice cuz it would sort by key auto.

