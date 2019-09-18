/////////////////////////////////////////////////////////////////////
// Exectutive.cpp - Source Publisher Entrance(Proj 1)              //
// ver 1.1                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////


#include "Exectutive.h"
#include "LogForDemo.h"
#include "../DirectoryNavigator/DirExplorer-Naive/DirExplorerN.h"
#include "../DirectoryNavigator/FileSystem/FileSystem.h"

#include<ctime>

using namespace SrcPublisher;
using namespace FileSystem;

//----< get valid command from cmdLine >---------------------------

ProcessCmdLine* Exectutive::getCorrectCmd(int argc, char** argv)
{
	
	ProcessCmdLine *ppcl = new ProcessCmdLine(argc, argv);
	if (ppcl->hasOption('l')) LogForDemo::loggerStart();
	LogForDemo::DemoReq1();
	LogForDemo::DemoReq2();
	LogForDemo::DemoReq3();
	LogForDemo::DemoReq4();
	Utilities::Title("Verifying command...");
	preface("Command Line: ");
	ppcl->showCmdLine();
	ppcl->showRegexes();
	putline();

	try {
		if (ppcl->parseError() || (!Directory::exists(ppcl->path())))
		{
			throw "Error: Deficient parameters or invalid path!\n";
			
		}
	}
	catch (const char* msg) {
		std::cerr << msg << customUsage() << std::endl;
		delete ppcl;
		return NULL;
	}
	//ppcl are cleaned after the creation of DirExplorerN
	return ppcl;
}

//----< customUsage of cmdLine for this project >---------------------------

std::string Exectutive::customUsage()
{
	std::string usage;
	usage += "\n  Command Line: path [/option]* [/pattern]*";
	usage += "\n    path is relative or absolute path where processing begins";
	usage += "\n    [/option]* are one or more options of the form:";
	usage += "\n      /s - walk directory recursively";
	//usage += "\n      /h - hide empty directories";
	//usage += "\n      /a - on stopping, show all files in current directory";
	usage += "\n    [pattern]* are one or more pattern strings of the form:";
	usage += "\n      *.h *.cpp *.cs *.txt or *.*";
	usage += "\n";
	return usage;
}

//----< initialize a Converter with certain output folder and extension >-------

SrcPublisher::Converter* Exectutive::initConverter()
{
	Title("Init Converter...");
	std::string rootPath = "../ConvertedPages";
	if (!Directory::exists(rootPath)) {
		Directory::create(rootPath);
	}
	else {
		//delete original files to avoid their influence
		std::vector<std::string> oldFiles = FileSystem::Directory::getFiles(rootPath, "*.*");
		for (std::vector<std::string>::iterator it = oldFiles.begin(); it != oldFiles.end(); ++it) {
			File::remove(Path::fileSpec(rootPath,*it));
		}
	}
	
	std::string targetExt = ".html";

	//pcvt are passed and cleaned by destrcutor of DirExplorerN
	SrcPublisher::Converter *pcvt = new SrcPublisher::Converter(Path::getFullFileSpec(rootPath), targetExt);
	ConsoleUITools::showItem("Target full path: ", pcvt->getTargetFullPath());
	ConsoleUITools::showItem("Target extension: ", pcvt->getExt());
	return pcvt;
}

//----< initialize a custom DirExplorer, doSearch and operations >---------------------------

int Exectutive::initDirExplorerAndWork(ProcessCmdLine* ppcl, SrcPublisher::Converter* pcvt)
{
	Title("Init DirExplorer And Work...");
	//de work within this block
	DirExplorerN de(ppcl->path(), pcvt);

	ConsoleUITools::showItem("Dir to search: ", ppcl->path());

	ConsoleUITools::showItems("Patterns: ", ppcl->patterns());
	for (auto patt : ppcl->patterns())
	{
		de.addPattern(patt);
	}

	ConsoleUITools::showItems("Regexes: ", ppcl->regexes());
	for (auto regex : ppcl->regexes())
	{
		de.addRegex(regex);
	}

	if (ppcl->hasOption('s'))
	{
		preface("Recurse: Yes");
		de.recurse();
	}
	delete ppcl;
	//search and operate
	de.search();
	LogForDemo::DemoReq5(de.fileCount());
	de.showStats();
	if (!de.fileCount()) {
		return 1;
	}
	else {
		LogForDemo::DemoReq6();
		de.processedFiles();
	}
	return 0;

}

//----< initialize a valid Display and display >---------------------------

void Exectutive::initDisplayAndWork(std::string path)
{
	Title("Init Display And Work...");
	title("(Note:You may change the appPath in './displayParam.txt' and need close the open browers before this display.)");

	std::string appSpec;
	File paramFile("../displayParam.txt");
	paramFile.open(File::in, File::text);
	if(paramFile.isGood()) {
		appSpec = paramFile.getLine();
		
	}
	paramFile.close();

	std::string targetPath = path;
	int maxDisplay = 10;

	ConsoleUITools::showItem("Default maxPlay is: ", maxDisplay);
	ConsoleUITools::showItem("Default AppSpec is: ", appSpec);

	//dp work within this block
	Display dp(targetPath, appSpec, maxDisplay);
	LogForDemo::DemoReq7();
	LogForDemo::DemoReq8n9();
	dp.doDisplay();
	std::cout << "\n\n";
}


/*	The project use MVC Pattern, Model is DirExplorer, View is Display, Control is Exectutive;

	Direct Input:path (option/c++ regex/windows pattern)*, if demonstrating dirs/files or not, (appSpec);
	Implicit Input: targetPath, targetExt, maxDisplay

	Potential problems and handles:
	deficient params(handled with parseError() in ProcessCmdLine Class and feedback in Exectutive);
	invalid path(handled and feedback in Exectutive);
	invalid pattern(no match for the pattern);
	invalid appSpec(handled and feedback in Exectutive);

	Output: (searched directories),(matched names and number of files), converted files and pop-up display;

*/

#ifdef EXECTUTIVE
	int main(int argc, char *argv[])
	{
		//process cmdLine
		ProcessCmdLine *ppcl = Exectutive::getCorrectCmd(argc, argv);
		if (ppcl == NULL) {
			return 1;
		}

		//init Converter
		SrcPublisher::Converter* pcvt = Exectutive::initConverter();
		std::string targetFullPath = pcvt->getTargetFullPath();

		//init DirExplorer
		if(Exectutive::initDirExplorerAndWork(ppcl, pcvt)) return 1;

		//init Display
		Exectutive::initDisplayAndWork(targetFullPath);
		return 0;
	}

#endif // EXECTUTIVE



	



	
