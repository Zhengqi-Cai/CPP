/////////////////////////////////////////////////////////////////////
// Loader.cpp - Loading files for operation(Project 2)             //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
#include "Loader.h"
#include "../customLogger/customLogger.h"
using namespace customLogging;
using namespace CodePublisher;
//----< constructor >---------------------------
CodePublisher::Loader::Loader(ProcessCmdLine * ppcl) : BaseLoader(formatToBackSlash(Path::getFullFileSpec(ppcl->path()))), de(formatToBackSlash(ppcl->path()))
{
	preface(logOpen_,"Init Loader And Work...");
	preface(logOpen_,"Dir to search: "+ formatToBackSlash(ppcl->path()));

	preface(logOpen_, "Patterns: ");
	showSplits(logOpen_, ppcl->patterns());
	for (auto patt : ppcl->patterns())
	{
		de.addPattern(patt);
	}

	preface(logOpen_, "Regexes: ");
	showSplits(logOpen_, ppcl->regexes());
	for (auto regex : ppcl->regexes())
	{
		de.addRegex(regex);
	}

	if (ppcl->hasOption('s'))
	{
		preface(logOpen_, "Recurse: Yes\n");
		de.recurse();
	}

}

//CodePublisher::Loader::Loader(std::string fRootPath, bool subdir, std::vector<std::string> patterns, std::vector<std::string> regexes):BaseLoader(fRootPath), de(fRootPath,pout)
//{
//	preface("Init Loader And Work...", true, pout_);
//	preface("Dir to search: " + fRootPath_, true, pout_);
//	preface("Patterns: ", true, pout_);
//	showSplits(patterns, pout_);
//	for (auto patt : patterns)
//	{
//		de.addPattern(patt);
//	}
//
//	preface("Regexes: ", true, pout_);
//	showSplits(regexes, pout_);
//	for (auto regex : regexes)
//	{
//		de.addRegex(regex);
//	}
//
//	if (subdir)
//	{
//		preface("Recurse: Yes\n", true, pout_);
//		de.recurse();
//	}
//
//}

//----< main interface to load files >---------------------------
int CodePublisher::Loader::loadFiles()
{
	std::ostringstream os;
	os << "\n\n"<<"Loading files in " << getRootPath() << std::endl;
	StaticLogger::write(logOpen_,os.str());
	regexMatchMap_.clear();
	de.search();
	de.showStats();
	if (!de.fileCount()) {
		return 1;
	}
	else {
		de.processedFiles();
		regexMatchMap_ = de.matchedMap(); // all path with backslash
	}
	filesLoaded = true;
	return 0;
}

//----< test stub >---------------------------
#ifdef TEST_LOADER
int main(int argc, char** argv) {
	
	ProcessCmdLine *ppcl = new ProcessCmdLine(argc, argv);

	Utilities::Title("Verifying command...");
	preface("Command Line: ", true);

	ppcl->showCmdLine();
	ppcl->showRegexes();
	putline(1);

	Loader ld(ppcl);
	ld.loadFiles();

}
#endif // TEST_LOADER



