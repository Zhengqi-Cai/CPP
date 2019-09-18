///////////////////////////////////////////////////////////////
// LogForDemo.h - Specific message for demo(Proj 1)          //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////

#include "LogForDemo.h"


//----< start the logger to show >---------------------------
void SrcPublisher::LogForDemo::loggerStart()
{
	Logger::start();
}
//----< demonstration for requirement 1 >---------------------------
void SrcPublisher::LogForDemo::DemoReq1()
{
	std::string demo;
	demo += "All the packages in this project are created as C++ Windows Console Project ";
	demo += "and are editted in Visual Studio2017. You can open .sln to find some details.";
	Logger::title("Demonstrate Req #1, use Visual Studio 2017 and its C++ Windows Console Projects.");
	Logger::content(demo);
}
//----< demonstration for requirement 3 >---------------------------
void SrcPublisher::LogForDemo::DemoReq3()
{
	std::string demo;
	demo += "This project contain 10 packages:\n";
	demo += "Exectutive, Converter, Display, DirExplorer-Naive FileSystemDemo Process ";
	demo += "StringUtilities CodeUtilities ConsoleUITools Logger.\n";
	Logger::title("Demonstrate Req #3, provide Executive, Converter, and Display packages.");
	Logger::content(demo);
}
//----< demonstration for requirement 2 >---------------------------
void SrcPublisher::LogForDemo::DemoReq2()
{
	std::string demo;
	demo += "Only stardard IO are used in this project, including iofstream and iostream. ";
	demo += "I use std::cin and std::cout directly as well as functions from Utilities namespace for iostream(as you can see in Logger.cpp)";
	demo += " and use functions in FileSystemDemo for filestream(as you can see in Converter.cpp).\n";
	demo += "'new' operator is used to create and pass objects in separate function like:\n";
	demo += "\tProcessCmdLine *ppcl = new ProcessCmdLine(argc, argv);\n";
	demo += "All the new object are deleted in certain place.";

	Logger::title("Demonstrate Req #2, use the standard streams libraries for all I/O and operators new and delete for memory management.");
	Logger::content(demo);
}
//----< demonstration for requirement 4 >---------------------------
void SrcPublisher::LogForDemo::DemoReq4()
{
	Logger::title("Demonstrate Req#4, accept from the command line a path and a regular expression");
}
//----< demonstration for requirement 5 >---------------------------
void SrcPublisher::LogForDemo::DemoReq5(bool nonzero)
{
	Logger::title("Demonstrate Req#5, should no matches be found, shall write an error message to the console.");
	if (nonzero) {
		Logger::content("This command is for a nonzero search. You can find the zero search one with another console.");
	}
	else {
		Logger::content("This command is for a zero search with Error.");
	}

}
//----< demonstration for requirement 6 >---------------------------
void SrcPublisher::LogForDemo::DemoReq6()
{
	Logger::title("Demonstrate Req#6, convert each matching fileto a valid html file in 'convertedPages'.");
}
//----< demonstration for requirement 7 >---------------------------
void SrcPublisher::LogForDemo::DemoReq7()
{
	Logger::title("Demonstrate Req#7, display each converted file, waiting for the child to exit before displaying the next file.");
}
//----< demonstration for requirement 8 and 9 >---------------------------
void SrcPublisher::LogForDemo::DemoReq8n9()
{
	std::string demo;
	demo += "As you can see, the message above shows the necessary information. You can modify '/l' as an option for demonstration of requirement. ";
	Logger::title("Demonstrate Req#8&9, include an automated test that demonstrates you meet all the functional requirements above with Logger.");
	Logger::content(demo);
}


//----< test stub >---------------------------
#ifdef TEST_LOGFORDEMO
int main() {
	loggerStart();
	DemoReq1();
	DemoReq2();
	DemoReq3();
	DemoReq4();
	DemoReq5(1);
	DemoReq6();
	DemoReq7();
	DemoReq8n9();
}
#endif // TEST_LOGFORDEMO


