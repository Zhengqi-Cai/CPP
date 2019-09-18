///////////////////////////////////////////////////////////////
// testExectutive.cpp - test of functions in Exectutive      //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
#include "testExectutive.h"
#include "Exectutive.h"

#include <iostream>

using namespace Utilities;

#ifdef TEST_EXECTUTIVE

int main() {
	testExectutive te;
	te.testInitConverter();
}

#endif // TEST_EXECTUTIVE

//----< test read a line from cmdLine and put to  char** >----------------

void testExectutive::testCin()
{
	std::string cmd;
	int i = 0;
	std::cout << "Please enter the correct command:" << std::endl;
	getline(std::cin, cmd);
	std::vector<std::string> result = split(cmd, ' ');
	char* argv[50];
	for (std::vector<std::string>::size_type i = 0; i < result.size(); i++) {
		argv[i + 1] = const_cast<char*>(result[i].c_str());
		std::cout << argv[i + 1] << std::endl;

	}
}

//----< test getCorrectProcessCmdLine function >---------------------------

void testExectutive::testGetCorrectProcessCmdLine()
{
	int argc = 5;
	char** argv = new char*[5];
	argv[0] = const_cast<char*>("");
	argv[1] = const_cast<char*>("../A");
	argv[2] = const_cast<char*>("/s");
	argv[3] = const_cast<char*>("*.h");
	argv[4] = const_cast<char*>("*.cpp");

	ProcessCmdLine* ppcl = Exectutive::getCorrectCmd(argc,argv);
	std::cout << "Path is: " << ppcl->path() << std::endl;

	std::cout << "Patterns are: " << std::endl;
	ProcessCmdLine::Patterns ps = ppcl->patterns();
	for (auto p : ps) {
		std::cout << p << std::endl;
	}

	std::cout << "Regexes are: " << std::endl;
	ProcessCmdLine::Regexes rs = ppcl->regexes();
	for (auto r : rs) {
		std::cout << r << std::endl;
	}

	std::cout << "Options are: " << std::endl;
	ProcessCmdLine::Options os = ppcl->options();
	for (auto o : os) {
		std::cout << o << std::endl;
	}
	delete[] argv;
	delete ppcl;
}

//----< test initConverter function >---------------------------

void testExectutive::testInitConverter()
{
	SrcPublisher::Converter* pcvt = Exectutive::initConverter();
	std::cout << pcvt->getTargetFullPath() << " " << pcvt->getExt() << std::endl;
	delete pcvt;
}

//----< test initDirExplorerAndWork function >---------------------

void testExectutive::testInitDirExplorerAndWork()
{
	int argc = 5;
	char* argv[50];
	argv[0] = const_cast<char*>("");
	argv[1] = const_cast<char*>("..");
	argv[2] = const_cast<char*>("/s");
	argv[3] = const_cast<char*>("*.*");
	argv[4] = const_cast<char*>(".*.cpp$");
	ProcessCmdLine* ppcl = Exectutive::getCorrectCmd(argc, argv);
	SrcPublisher::Converter* pcvt = Exectutive::initConverter();

	Exectutive::initDirExplorerAndWork(ppcl,pcvt);
	
	delete ppcl;

}

//----< test initDisplayAndWork function >---------------------------

void testExectutive::testInitDisplayAndWork()
{
	SrcPublisher::Converter* pcvt = Exectutive::initConverter();
	Exectutive::initDisplayAndWork("C:/Users/zcai21/Desktop/Project1/Projec1_v2_Zhengqi_Cai/Projec1_v2_Zhengqi_Cai/ConvertedPages");
	delete pcvt;

}
