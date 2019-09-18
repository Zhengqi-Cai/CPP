///////////////////////////////////////////////////////////////
// Converter.cpp - converter from txt to html(Proj 2)        //
// ver 1.2                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
#include "Converter.h"
#include <regex>
#include "../FileSystem/FileSystem.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include "../customLogger/customLogger.h"
using namespace customLogging;
using namespace CodePublisher;
using namespace FileSystem;
using namespace Utilities;
//----< constructor >-------

CodePublisher::Converter::Converter(std::string fDirOut, std::string targetExt) :BaseConverter(fDirOut, targetExt)
{
	preface(logOpen_, "Init Converter and work...\n");
}

//----< convert a txt file with predefined template >-------

std::string CodePublisher::Converter::doConversion(const std::string& fOriginFileSpec) {

	std::string oldFileName = Path::getName(fOriginFileSpec);
	std::string newFileName = oldFileName + targetExt_;
	std::string newFileSpec = Path::fileSpec(fDirOut_, newFileName);
	std::ostringstream os;
	os << "Converting " + oldFileName << ": ";

	try {
		File origin(fOriginFileSpec);
		origin.open(File::in, File::text);
		std::string current =Path::getPath(__FILE__);
		File templat(Path::getFullFileSpec(current + "..\\ServerStorage\\ClientsTemp\\template\\template.txt"));
		templat.open(File::in, File::text);

		File out(newFileSpec);
		out.open(File::out, File::text);
		int lineCount = 0;
		while (templat.isGood() && out.isGood())
		{
			std::string temp = templat.getLine();
			out.putLine(temp);
			if (temp == "<pre>") {
				while (origin.isGood() && out.isGood())
				{
					std::string tempContent = origin.getLine();
					lineCount++;
					std::string revise = Converter::convertALine(tempContent);
					revise = "<span class=\"lineCount\">" + std::to_string(lineCount) + "</span>" + revise;
					out.putLine(revise);
				}
			}
		}
		templat.close();
		origin.close();
		out.close();
		os << " Succeed!\n";
		StaticLogger::write(logOpen_, os.str());
	}
	catch(std::exception& ex){
		os << " Failed!\n";
		os << "\n    " << ex.what() << "\n";
		os << "\n  exception caught at line " << __LINE__ << " ";
		StaticLogger::write(logOpen_, os.str());
		File::remove(newFileSpec);
		return "";
	}
	return newFileSpec;
}

//----< convert a banch of files from a set >-------

std::set<std::string> CodePublisher::Converter::doConversionS(std::set<std::string>& FOriginFileSpecs)
{
	std::ostringstream os;
	os << "\n\nConverting a set of files to " << fDirOut_ << std::endl;
	StaticLogger::write(logOpen_, os.str());
	std::set<std::string> succeededFProductSpecs;
	std::set<std::string> failedFOriginSpecs;
	for (auto pos = (FOriginFileSpecs).begin(); pos != (FOriginFileSpecs).end(); ++pos) {
		std::string fFileSpec = *pos;
		auto processedfFile = doConversion(fFileSpec);
		if (processedfFile!="") { // no error
			succeededFProductSpecs.insert(processedfFile);
		}
		else {
			failedFOriginSpecs.insert(fFileSpec);
		}
	}
	for (auto fFileSpec : failedFOriginSpecs) {
		FOriginFileSpecs.erase(fFileSpec);
	}

	return succeededFProductSpecs;
}
//----< destructor >---------------------------

CodePublisher::Converter::~Converter()
{
	StaticLogger::write(logOpen_,"Converter deleted.\n");
}

//----< replace the escape char '<' '>' in a line of txt>-------

std::string CodePublisher::Converter::convertALine(std::string line)
{
	std::regex lt("<");
	std::regex gt(">");
	std::string revised= std::regex_replace(std::regex_replace(line, lt, "&lt;"), gt, "&gt;");
	return revised;
}

//----< test stub >---------------------------

#ifdef TEST_CONVERTER
using namespace CodePublisher;
int main(int argc, char ** argv) {

	std::set<std::string> fileSpecs;
	fileSpecs.insert(Path::getFullFileSpec("..\\Parser\\Parser.h"));
	CodePublisher::Converter cvt(Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages"), ".html");
	cvt.doConversionS(fileSpecs);
}
#endif // TEST_CONVERTER
