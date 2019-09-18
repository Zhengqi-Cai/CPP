/////////////////////////////////////////////////////////////////////
// CodePubr.cpp - Assembly of CodePublisher toolset(Project 2)     //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "CodePubr.h"
#include "../Loader/LoaderFactory.h"
#include "../Converter/ConverterFactory.h"
#include "../Dependencies/DependenciesFactory.h"
#include "../Display/DisplayFactory.h"

#include"../Utilities/StringUtilities/StringUtilities.h"
#include "../stringUtMore/stringUtMore.h"
#include "../customLogger/customLogger.h"
using namespace CodePublisher;
using namespace Utilities;
using namespace customLogging;
// -----< constrcutor >------------------------

CodePubr::CodePubr(Utilities::ProcessCmdLine* ppcl, std::string fDirOut) :fDirOut_(fDirOut),isWorking(false)
{
	Title(logOpen_,"\nCodePubr Init.\n");

	LoaderFactory lf;
	pld_ = lf.CreateCustom(ppcl);
	ConverterFactory cf;
	pcvt_ = cf.CreateCustom(fDirOut_,".html");
	DependenciesFactory df;
	pdpd_ = df.CreateCustom(fDirOut_, fDirOut_, pld_->getRootPath());
	DisplayFactory dpf;
	pdp_ = dpf.CreateCustom(fDirOut_, fDirOut_);

}


// -----< help destrcutor >------------------------

int CodePublisher::CodePubr::clearAll()
{
	delete pld_;
	delete pcvt_;
	delete pdpd_;
	delete pdp_;
	StaticLogger::write(logOpen_,"CodePubr deleted.\n");
	return 0;
}

// -----< set output directory >------------------------

int CodePublisher::CodePubr::setFDirOut(std::string fDirOut)
{
	fDirOut_ = fDirOut;
	pcvt_->setFDirOut(fDirOut_);
	pdpd_->setFDirIn(fDirOut_);
	pdpd_->setFDirOut(fDirOut_);
	pdp_->setFDirIn(fDirOut_);
	pdp_->setFDirOut(fDirOut_);
	return 0;
}

// -----< get output directory >------------------------

std::string CodePublisher::CodePubr::getFDirOut()
{
	return fDirOut_;
}

// -----< conevrt to html with a set of fileSpecs >------------------------

std::set<std::string> CodePublisher::CodePubr::ProduceProtoPages()
{
	StaticLogger::write(logOpen_, "\n\n<TASK>Producing proto pages into " + fDirOut_ + "...\n");
	std::set<std::string> fOriginFileSpecs;
	if (!pld_->isFilesLoaded()) { pld_->loadFiles(); }
	fOriginFileSpecs = MapToSet(pld_->matchedMap());
	return pcvt_->doConversionS(fOriginFileSpecs);
}

// -----< conevrt to html with dependencies analysis with a set of fileSpecs >------------------------

std::set<std::string> CodePublisher::CodePubr::ProduceProtoWithDep()
{
	StaticLogger::write(logOpen_, "\n\n<TASK>Producing proto pages with dependencies into " + fDirOut_ + "...\n");
	std::set<std::string> fOriginFileSpecs;
	if (!pld_->isFilesLoaded()) { pld_->loadFiles(); }
	fOriginFileSpecs = MapToSet(pld_->matchedMap());
	pcvt_->doConversionS(fOriginFileSpecs);
	return pdpd_->handleDependcies(fOriginFileSpecs);
}

// -----< conevrt to html with display buttons with a set of fileSpecs >------------------------

std::set<std::string> CodePublisher::CodePubr::ProduceProtoWithVis()
{
	StaticLogger::write(logOpen_, "\n\n<TASK>Producing proto pages with display buttons into " + fDirOut_ + "..\n");
	std::set<std::string> fOriginFileSpecs;
	if (!pld_->isFilesLoaded()) { pld_->loadFiles(); }
	fOriginFileSpecs = MapToSet(pld_->matchedMap());
	pcvt_->doConversionS(fOriginFileSpecs);
	return pdp_->handleDisplays(fOriginFileSpecs);
}

// -----< conevrt to html with dependencies analysis and display buttons with a set of fileSpecs >------------------------

std::set<std::string> CodePublisher::CodePubr::ProtoFullyProduce()
{
	StaticLogger::write(logOpen_, "\n\n<TASK>Producing fully proto pages into " + fDirOut_ + "...\n");
	isWorking = true;
	std::set<std::string> fOriginFileSpecs;
	if (!pld_->isFilesLoaded()) { pld_->loadFiles(); }
	fOriginFileSpecs = MapToSet(pld_->matchedMap());
	pcvt_->doConversionS(fOriginFileSpecs);
	pdpd_->handleDependcies(fOriginFileSpecs);
	
	auto productFPaths = pdp_->handleDisplays(fOriginFileSpecs);
	isWorking = false;
	StaticLogger::write(logOpen_, "\n\n<\\TASK>Producing " + std::to_string(productFPaths.size()) + "files in total.\n");
	return productFPaths;
}

// -----< destrcutor >------------------------

CodePubr::~CodePubr()
{
	clearAll();
}

// -----< load files and show them >------------------------

std::multimap<std::string, std::string> CodePubr::loadAndShow()
{
	pld_->loadFiles();
	return pld_->matchedMap();
}


// -----< test stub >------------------------
#ifdef TEST_CODEPUBR

#include"../FileSystem/FileSystem.h"
using namespace FileSystem;

int main(int argc, char** argv) {
	ProcessCmdLine *ppcl = new ProcessCmdLine(argc, argv);

	Utilities::Title("Verifying command...");
	preface("Command Line: ", true);

	ppcl->showCmdLine();
	ppcl->showRegexes();
	putline(1);

	std::string ProtoPagesFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages");
	std::string ProtoWithDepFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithDep");
	std::string ProtoWithVisFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithVis");
	std::string ProtoFullyProduceFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtofullyProduce");
	CodePubr* pcpr_ = new CodePubr(ppcl, ProtoPagesFullPath_,&std::cout);

	pcpr_->ProduceProtoPages();
	pcpr_->setFDirOut(ProtoWithDepFullPath_);
	pcpr_->ProduceProtoWithDep();

	pcpr_->setFDirOut(ProtoWithVisFullPath_);
	pcpr_->ProduceProtoWithVis();

	pcpr_->setFDirOut(ProtoFullyProduceFullPath_);
	pcpr_->ProtoFullyProduce();
	delete pcpr_;
	delete ppcl;

}
#endif // TEST_CODEPUBR
