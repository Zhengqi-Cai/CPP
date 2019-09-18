/////////////////////////////////////////////////////////////////////
// Display.cpp - process starter for file display(Proj 1)          //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include "Display.h"
#include "../Process/Process/Process.h"

#include <algorithm>
#include <regex>


using namespace FileSystem;
using namespace SrcPublisher;

//----< constructor >-------
//	input: a valid fullSpec of targetDirectory
Display::Display(const std::string fullPath, const std::string appPath, int max)
{
	std::regex bs("\\\\");
	appPath_ = std::regex_replace(appPath,bs,"/");
	fullPath_= std::regex_replace(fullPath, bs, "/");
	max_ = max;
}

//----< display specified files using specified app one by one >-------

void Display::doDisplay() {
	std::vector<std::string> files = FileSystem::Directory::getFiles(fullPath_, "*.*");

	Process p;
	p.application(appPath_);

	std::string cmdHeader = "file:///";

	std::cout << "\n  Press key to start";
	_getche();

	std::string appPathLower = appPath_;
	transform(appPathLower.begin(), appPathLower.end(), appPathLower.begin(), ::tolower);
	for (std::vector<std::string>::size_type i = 0; i < ((files.size() < max_) ? files.size() : max_); ++i)
	{
		std::string cmdLine = cmdHeader + Path::fileSpec(fullPath_, files[i]);

		if ((appPathLower.find("chrome") < appPathLower.size()) || (appPathLower.find("firefox") < appPathLower.size())) {
			cmdLine = "-new-instance " + cmdLine;
		}
		else {
			cmdLine = "/A " + cmdLine;
		}
		std::cout << "\n  starting process: \"" << appPath_ << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.commandLine(cmdLine);
		p.create();
		CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
		p.setCallBackProcessing(callback);
		p.registerCallback();

		WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
	}

	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);
}

//----< test stub >-------
#ifdef TEST_DISPLAY
int main() {
	Display dp("C:\Users\zcai21\Desktop\Projec1_v2_Zhengqi_Cai\ConvertedPages","C:\Program Files\internet explorer\iexplore.exe");
	dp.doDisplay();
}

#endif // DEBUG








