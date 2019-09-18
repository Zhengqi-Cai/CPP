#pragma once
/////////////////////////////////////////////////////////////////////
// Display.h - construct for hide/show scopes in html(Project 2)   //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Display.
 * It is mainly designed as components of CodePublisher(Project 2).
 * Its duty is to receive file(s) and add appropriate html tags to 
 * allow clients hide/show classes, functions and comments scopes.
 * It is implemented mainly using ParseMgr Class for extraction
 * of scope information and linearizing the lineCount with a priority
 * queue and writing tags in with standard IO.
 *
 *
 *
 * Required Files:
 * ---------------
 * Display.h
 * BaseDisplay.h
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include <queue>
#include <utility>
#include <set>
#include "BaseDisplay.h"


namespace CodePublisher {
	
	class Display : public BaseDisplay
	{
	public:
		Display(std::string fDirIn, std::string fDirOut) ;
		std::set<std::string> handleDisplays(std::set<std::string>& fOriginFileSpecs) override;
		std::string handleOneFileDisp(std::string fFileSpec) override;
		~Display();
		int handleOneFileComments(std::string targetFileName);
		int handleOneFileFunctionAndClass(std::string targetFileName, std::string fFileSpec);

	private:
		std::string handleCommentsInOneLine(std::string instr, bool& isMultiLineComments);
		bool logOpen_ = false;
	};
}



