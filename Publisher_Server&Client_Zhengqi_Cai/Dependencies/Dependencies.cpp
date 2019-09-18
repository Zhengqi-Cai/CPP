/////////////////////////////////////////////////////////////////////
// Dependencies.cpp - constructs for adding Dependencies(Project 2)//
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "Dependencies.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include"../Utilities/StringUtilities/StringUtilities.h"
#include "../stringUtMore/stringUtMore.h"
#include "../FileSystem/FileSystem.h"
#include "../ParseMgr/ParseMgr.h"
#include "../customLogger/customLogger.h"
using namespace CodePublisher;
using namespace Utilities;
using namespace FileSystem;
using namespace CodeAnalysis;
using namespace customLogging;
//----< constructor >---------------------------

Dependencies::Dependencies(std::string fDirIn, std::string fDirOut, std::string searchRootPath) :BaseDependencies(fDirIn, fDirOut), searchRootPath_(searchRootPath)
{
	preface(logOpen_, "Init Dependencies with searchRootPath " + searchRootPath_+"\n");
}



//----< main interface to add dependencies from Loader >---------------------------

std::set<std::string> CodePublisher::Dependencies::handleDependcies(std::set<std::string>& fOriginFileSpecs)
{
	fOriginFileSpecs_.clear();
	fOriginFileSpecs_ = fOriginFileSpecs;
	std::set<std::string> succeededFProductSpecs;
	std::set<std::string> failedFOriginSpecs;
	std::ostringstream os;
	os << "\n\nAdding Dep to a set of files, from " << fDirIn_ <<" to " << fDirOut_ << ": \n";
	StaticLogger::write(logOpen_, os.str());
	for (auto pos = fOriginFileSpecs_.begin(); pos != fOriginFileSpecs_.end(); ++pos) {
		
		std::string fFileSpec = *pos;
		auto processedfFile = handleOneFileDep(fFileSpec);
		if (processedfFile != "") { // no error
			succeededFProductSpecs.insert(processedfFile);
		}
		else {
			failedFOriginSpecs.insert(fFileSpec);
		}
	}
	for (auto fFileSpec : failedFOriginSpecs) {
		fOriginFileSpecs.erase(fFileSpec);
	}

	return succeededFProductSpecs;
}

//----< destructor >---------------------------

CodePublisher::Dependencies::~Dependencies()
{
	StaticLogger::write(logOpen_,"Dependencies deleted.\n");
}

//----< private help function for add one file dependencies >---------------------------

std::string CodePublisher::Dependencies::handleOneFileDep(std::string fFileSpec)
{
	std::string targetFileName = Path::getName(fFileSpec);
	std::ostringstream os;
	os << "\nHandling dep of " << targetFileName << ": ";

	std::string currentPath = Path::getPath(fFileSpec);
	notInTrees_.clear();
	notBeChosens_.clear();
	valids_.clear();
	std::lock_guard<std::mutex> lg(CodeAnalysis::ParseMgr::parMgrmtx_);
	ParseMgr pm;
	if(pm.doParse(fFileSpec)) return "";
	//extractOneFileDep(fFileSpec);
	std::set<std::string> DepsR = pm.extractDepsR();
	for (auto dep : DepsR) {  //relative path
		std::vector<std::string> splited = split(dep, '\"');
		std::string fileDepR;
		std::string fileDepA;
		if (splited.size() >= 2) {
			fileDepR = formatToBackSlash(splited[1]);
			fileDepA = Path::getFullFileSpec(formatToBackSlash(currentPath) + "\\" + formatToBackSlash(fileDepR));
			if (fileDepA.find(formatToBackSlash(searchRootPath_)) < fileDepA.size()) {
				if (std::find(fOriginFileSpecs_.begin(), fOriginFileSpecs_.end(),fileDepA)!= fOriginFileSpecs_.end()) {
					valids_.push_back(Path::getName(fileDepA));
				}
				else {
					notBeChosens_.push_back(Path::getName(fileDepA));
				}
			}
			else {
				notInTrees_.push_back(Path::getName(fileDepA));
			}
		}
	}
	auto productFSpec = writeOneFileDep(targetFileName + ".html");
	os << "Succeed!\n";
	StaticLogger::write(logOpen_, os.str());
	return productFSpec;
}


//----< private help function for write one file dependencies >---------------------------

std::string CodePublisher::Dependencies::writeOneFileDep(std::string targetFileName)
{
	std::string originFFileSpec = Path::getFullFileSpec(fDirIn_ + "\\" + targetFileName);
	std::string outFFileSpec = Path::getFullFileSpec(fDirOut_ + "\\temp_" + targetFileName);
	File origin(originFFileSpec);
	origin.open(File::in, File::text);

	File out(outFFileSpec);
	out.open(File::out, File::text);
	while (origin.isGood() && out.isGood())
	{
		std::string temp = origin.getLine();
		out.putLine(temp);
		if (temp.find("<div id=\"dependencyDiv\">")!=std::string::npos) {
			out.putLine("<div id=\"dependencyLinks\">");
			out.putLine("<label>Dependency Files: </label>");
			for (auto valid : valids_) {
				std::string link = "<a href=\"" + valid + ".html" + "\">"+valid+"</a>";
				out.putLine(link);
			}
			for (auto noBC : notBeChosens_) {
				std::string link = "<a href=\"..\\notFound\\NotBeChoosen.txt\">" + noBC + "</a>";
				out.putLine(link);
			}
			for (auto noIT : notInTrees_) {
				std::string link = "<a href=\"..\\notFound\\NotInTree.txt\">" + noIT + "</a>";
				out.putLine(link);
			}
			out.putLine("</div>");
		}
	}
	origin.close();
	out.close();
	std::string removeTempName = Path::getFullFileSpec(fDirOut_ + "\\" + targetFileName);
	if (File::exists(removeTempName)) File::remove(removeTempName);
	rename(outFFileSpec.c_str(), removeTempName.c_str());
	return removeTempName;
}


//----< test stub >---------------------------

#ifdef TEST_DEPENDENCIES
#include "../Converter/Converter.h"
//#include"../FileSystem/FileSystem.h"
//using namespace FileSystem;
using namespace CodePublisher;
int main(int argc, char ** argv) {
	std::string dirOut_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithDep"); //always use backslash in path and format new path at first time

	std::set<std::string> fileSpecs;
	fileSpecs.insert(Path::getFullFileSpec("..\\Parser\\Parser.h"));
	fileSpecs.insert(Path::getFullFileSpec("..\\Parser\\ConfigureParser.h"));
	fileSpecs.insert(Path::getFullFileSpec("..\\Parser\\ActionsAndRules.h"));

	//CodePublisher::Converter cvt(Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages"), ".html");
	//cvt.doConversionS(fileSpecs);
	Dependencies dp(Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages"), dirOut_, Path::getFullFileSpec("..\\Parser") );
	dp.handleDependcies(fileSpecs);

}
#endif // TEST_DEPENDENCIES



