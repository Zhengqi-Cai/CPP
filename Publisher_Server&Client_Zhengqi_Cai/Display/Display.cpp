/////////////////////////////////////////////////////////////////////
// Display.cpp - construct for hide/show scopes in html(Project 2) //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "Display.h"
#include "../ParseMgr/ParseMgr.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include"../Utilities/CodeUtilities/CodeUtilities.h"
#include "../stringUtMore/stringUtMore.h"
#include "../FileSystem/FileSystem.h"
using namespace CodeAnalysis;
using namespace CodePublisher;
using namespace Utilities;
using namespace FileSystem;

// -----< constructor >-----------------------------------------------------

Display::Display(std::string fDirIn, std::string fDirOut):BaseDisplay(fDirIn,fDirOut)
{
	std::ostringstream os;
	preface(logOpen_,"Init Display And Work...\n");
}

// -----< main interface to handle a banch of files >-----------------------------------------------------

std::set<std::string> Display::handleDisplays(std::set<std::string>& fOriginFileSpecs)
{
	StaticLogger::write(logOpen_, "\n\nAdding Visibility to a set of files, from " + fDirIn_ + " to " + fDirOut_ + ": \n");
	std::set<std::string> succeededFProductSpecs;
	std::set<std::string> failedFOriginSpecs;

	for (auto pos = fOriginFileSpecs.begin(); pos != fOriginFileSpecs.end(); ++pos) {

		std::string fFileSpec = *pos;
		auto processedfFile = handleOneFileDisp(fFileSpec);
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

// -----< help function to handle a file >-----------------------------------------------------

std::string Display::handleOneFileDisp(std::string fFileSpec)
{
	std::string targetFileName = Path::getName(fFileSpec) + ".html";
	std::ostringstream out;
	out << "\nHandling display of " + targetFileName +": ";
	handleOneFileComments(targetFileName);
	std::string fDirIn = fDirIn_;
	fDirIn_ = fDirOut_;
	handleOneFileFunctionAndClass(Path::getName(fFileSpec) + ".html", fFileSpec);
	out << "Succeed!" << std::endl;
	StaticLogger::write(logOpen_, out.str());
	fDirIn_ = fDirIn;
	return Path::fileSpec(fDirOut_,targetFileName);
}
//----< destructor >---------------------------

CodePublisher::Display::~Display()
{
	StaticLogger::write(logOpen_,"Display deleted.\n");
}

// -----< help function to add tags for comments in one file  >-----------------------------------------------------

int Display::handleOneFileComments(std::string targetFileName)
{
	std::string originFFileSpec = Path::getFullFileSpec(fDirIn_ + "/" + targetFileName);
	std::string outFFileSpec = Path::getFullFileSpec(fDirOut_ + "/temp_" + targetFileName);

	File origin(originFFileSpec);
	origin.open(File::in, File::text);

	File out(outFFileSpec);
	out.open(File::out, File::text);

	bool isInPre=false;
	bool isMultiLineComments = false;
	while (origin.isGood() && out.isGood())
	{
		std::string temp = origin.getLine();
		std::string converted(temp);
		if (temp.find("<div id=\"showAndHide\">") != std::string::npos) {
			converted += "\n<button class=\"Comments\" value = \"show\" onClick = toggleDIsplay(this)>Comments</button>";
		}
		if (temp == "</pre>") {
			isInPre = false;
		}
		if (isInPre) {
			converted = handleCommentsInOneLine(temp, isMultiLineComments);
		}
		
		out.putLine(converted);
		if (temp == "<pre>") {
			isInPre = true;
		}
	}
	origin.close();
	out.close();
	std::string removeTempName = Path::getFullFileSpec(fDirOut_ + "\\" + targetFileName);
	if (File::exists(removeTempName)) File::remove(removeTempName);
	rename(outFFileSpec.c_str(), removeTempName.c_str());
	return 0;
}

// -----< private help function to handle tags for comments in one line  >-----------------------------------------------------

std::string Display::handleCommentsInOneLine(std::string instr, bool& isMultiLineComments)
{
	std::string outstr(instr);
	std::string pretagForComments = "<span class =\"commentsHidden\">comments hidden</span><span class=\"comments\">";
	std::string posttagForComments = "</span>";
	int cursor = 0;
	while (true) {
		if (isMultiLineComments) {
			if (outstr.find("*/",cursor) == std::string::npos) {
				break;
			}
			else {
				isMultiLineComments = false;
				cursor = outstr.find("*/", cursor);
				outstr.insert(cursor, posttagForComments);
				cursor = cursor + 2 + posttagForComments.size();
			}
		}
		if (outstr.find("//", cursor) != std::string::npos) {
			cursor = outstr.find("//", cursor);
			outstr.insert(cursor+2, pretagForComments);
			outstr.insert(outstr.size(), posttagForComments);
			cursor = outstr.size();
			break;
		}
		else {
			if (outstr.find("/*", cursor) == std::string::npos) {
				break;
			}
			else {
				isMultiLineComments = true;
				cursor = outstr.find("/*", cursor);
				outstr.insert(cursor +2, pretagForComments);
				cursor = cursor + pretagForComments.size() + 2;
			}
		}
	}
	return outstr;
}


// -----< help function to handle tags for function&class in one line  >-----------------------------------------------------

int Display::handleOneFileFunctionAndClass(std::string targetFileName, std::string fFileSpec){
	std::lock_guard<std::mutex> lg(CodeAnalysis::ParseMgr::parMgrmtx_);
	ParseMgr pm;
	if (pm.doParse(fFileSpec)) return 1;
	pm.function_classScopeSequence();
	std::string originFFileSpec = Path::getFullFileSpec(fDirIn_ + "/" + targetFileName);
	std::string outFFileSpec = Path::getFullFileSpec(fDirOut_ + "/temp_" + targetFileName);
	File origin(originFFileSpec);
	origin.open(File::in, File::text);

	File out(outFFileSpec);
	out.open(File::out, File::text);

	int lineCount = 0;
	bool isInPre = false;
	std::string pretagForFunction = "<span class =\"functionHidden\">function hidden</span><span class = \"function\">";
	std::string posttag = "</span>";
	std::string pretagForClass = "<span class =\"classHidden\">class hidden</span><span class = \"class\">";
	while (origin.isGood() && out.isGood())
	{
		std::string temp = origin.getLine();
		std::string converted(temp);
		if (temp.find("<div id=\"showAndHide\">") != std::string::npos) {
			converted += "\n<button class=\"Class\" value = \"show\" onClick = toggleDIsplay(this) >Class</button>";
			converted += "\n<button class = \"Function\" value = \"show\" onClick = toggleDIsplay(this)>Function</button>";
		}
		if (temp == "</pre>") isInPre = false;
		if (isInPre) {
			lineCount++;
			if (pm.sequenceSize()) {
				if (pm.peekNextScopeEntity() == std::make_pair(lineCount, std::string("classBegin"))) {
					int openBracket = converted.find("{");
					converted.insert(openBracket + 1, pretagForClass);
					pm.popNextScopeEntity();
				}
				else if (pm.peekNextScopeEntity() == std::make_pair(lineCount, std::string("functionBegin"))) {
					int openBracket = converted.find("{");
					converted.insert(openBracket + 1, pretagForFunction);
					pm.popNextScopeEntity();
				}
				if(pm.peekNextScopeEntity() == std::make_pair(lineCount, std::string("End"))){ //it must be an end scope;
					int closeBracket = converted.find("}");
					if (closeBracket == std::string::npos) closeBracket = 0;
					converted.insert(closeBracket, posttag);
					pm.popNextScopeEntity();
				}	
			}
		}
		out.putLine(converted);
		if (temp == "<pre>") isInPre = true;
	}
	origin.close();
	out.close();
	std::string removeTempName = Path::getFullFileSpec(fDirOut_ + "\\" + targetFileName);
	if (File::exists(removeTempName)) File::remove(removeTempName);
	rename(outFFileSpec.c_str(), removeTempName.c_str());
	return 0;
}
//actually this function has just 50 lines when removing all blacklines. But it may be hard to read.




// -----< test stub >-----------------------------------------------------
#ifdef TEST_DISPLAY
#include "../Converter/Converter.h"

int main(int argc, char ** argv) {
	std::set<std::string> fileSpecs;
	fileSpecs.insert(Path::getFullFileSpec("..\\Parser\\Parser.h"));
	Display dp(Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages"), Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithVis"));
	dp.handleDisplays(fileSpecs);
	return 0;
}
#endif // TEST_DISPLAY

