/////////////////////////////////////////////////////////////////////
// ParseMgr.c - Manager of Parser toolset(Project 2)               //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "ParseMgr.h"
#include "../Parser/Parser.h"
#include "../customLogger/customLogger.h"
using namespace customLogging;
using namespace CodeAnalysis;
using namespace Lexer;
using namespace oldUtilities;

std::mutex ParseMgr::parMgrmtx_;
//----< constructor >---------------------------

ParseMgr::ParseMgr()
{
	
	if (logOpen_) {
		StringHelper::Title(logOpen_, "ParseMgrInit.\n");
	}
}

//----< destructor >---------------------------

CodeAnalysis::ParseMgr::~ParseMgr()
{
	StaticLogger::write(logOpen_, "ParseMgr deleted.\n");
	delete pConfigure;
}

//----< only function to parse a source file >---------------------------

int ParseMgr::doParse(std::string fFileSpec)
{
	std::string targetFileName = FileSystem::Path::getName(fFileSpec);
	std::ostringstream out;
	out << "Parsing " << targetFileName << ": \n";
	pConfigure = new ConfigParseForCodeAnal();
	Parser* pParser = pConfigure->Build();
	try
	{
		if (pParser)
		{
			if (!pConfigure->Attach(fFileSpec))
			{
				out << "\n  could not open file " + fFileSpec + "\n";
				return NULL;
			}
		}
		else
		{
			out << "\n\n  Parser not built\n\n";
			return NULL;
		}

		// save current package name

		Repository* pRepo = Repository::getInstance();
		pRepo->package() = targetFileName;

		// parse the package
		while (pParser->next())
		{
			pParser->parse();
		}
		//Demo::stop();
		StaticLogger::write(logOpen_, out.str());
		return 0;
	}
	catch (std::exception& ex) {
		out << "\n\n    " << ex.what() << "\n\n";
		out << "\n  exception caught at line " << __LINE__ << " ";
		out << "\n  in package \"" << fFileSpec << "\"";
		StaticLogger::write(logOpen_, out.str());
		return 1;
	}
}


//----< extract dependencies(relative path) >---------------------------

std::set<std::string> CodeAnalysis::ParseMgr::extractDepsR()
{
	std::set<std::string> DepsR;
	Repository* pRepo = Repository::getInstance();
	StaticLogger::write(logOpen_, "Extracting relative dependencies of "+ pRepo->package() + " \n");
	ASTNode* pGlobalScope = pRepo->getGlobalScope();
	std::vector<Lexer::ITokenCollection*> gobalStmt = pGlobalScope->statements_;
	for (auto pos = gobalStmt.begin(); pos != gobalStmt.end(); pos++) {
		DepsR.insert((*pos)->show());
	}
	return DepsR;
}

//----< collect function and class scope sequence in pq) >---------------------------

int CodeAnalysis::ParseMgr::function_classScopeSequence()
{
	StaticLogger::write(logOpen_, "Linearing scope sequence with pq.\n");
	Repository* pRepo = Repository::getInstance();
	ASTNode* pGlobalScope = pRepo->getGlobalScope();
	treeWalkForLinearScope(pGlobalScope);
	return 0;
}

//----< is there any scope entity in pq) >---------------------------

int CodeAnalysis::ParseMgr::sequenceSize() {
	return linearLineMark.size();
}

//----< peek top  >---------------------------

std::pair<int, std::string> CodeAnalysis::ParseMgr::peekNextScopeEntity()
{
	return linearLineMark.top();
}

//----< return the next scope entity in pq) >---------------------------

void CodeAnalysis::ParseMgr::popNextScopeEntity()
{
	linearLineMark.pop();
}

// -----< help function to linearize lineCount for writing  >-----------------------------------------------------

void ParseMgr::treeWalkForLinearScope(ASTNode * pRoot)
{
	std::string currentType = pRoot->type_;
	if (pRoot->type_ == "function") {
		linearLineMark.push(std::make_pair(pRoot->endLineCount_, "End"));
		linearLineMark.push(std::make_pair(pRoot->startLineCount_, currentType + "Begin"));
	}
	else if (pRoot->type_ == "class") {
		linearLineMark.push(std::make_pair(pRoot->endLineCount_ - 1, "End"));
		linearLineMark.push(std::make_pair(pRoot->startLineCount_, currentType + "Begin"));
	}
	auto iter = pRoot->children_.begin();
	while (iter != pRoot->children_.end())
	{
		treeWalkForLinearScope(*iter);
		++iter;
	}
}

//----< test stub >---------------------------
#ifdef TEST_PARSEMGR
#include "../FileSystem/FileSystem.h"
using namespace FileSystem;
int main() {
	ParseMgr pm(&std::cout);
	pm.doParse(Path::getFullFileSpec("../Parser/Parser.h"));
	pm.function_classScopeSequence();
	while (pm.sequenceSize()) {
		auto temp = pm.peekNextScopeEntity();
		std::cout << temp.first << "@@" << temp.second  <<std::endl;
		pm.popNextScopeEntity();
	}
	return 0;
}
#endif // TEST_ParseMgr

