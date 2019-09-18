#pragma once
///////////////////////////////////////////////////////////////
// Exectutive.h - Source Publisher Entrance(Proj 1)          //
// ver 1.1                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one Project-Entrance class: Exectutive.
 * Its purpose is to glue separate parts and get correct commands
 * from users for source code conversion and display.
 * It is implemented using standard IO to interact, and some tools
 * in Utilities and FileSystem like ProcessCmdLine to analyze inputs.
 *
 *
 *
 * Required Files:
 * ---------------
 * Exectutive.h
 * ../DirectoryNavigator/DirExplorer-Naive/DirExplorerN.h
 * ../DirectoryNavigator/FileSystem/FileSystem.h
 * ../DirectoryNavigator/Utilities/CodeUtilities/CodeUtilities.h
 * ../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h
 * ../Converter/Converter.h
 * ../Display/Display.h
 * ./LogForDemo.h
 *
 * Build Process:
 * --------------
 * devenv Projec1_Zhengqi_Cai.sln
 *
 * Maintenance History:
 * --------------------
 * ver 1.1 : 10 Feb 2019
 * - add LogForDemo and Logger
 * ver 1.0 : 04 Feb 2019
 * - first release
 *
 */



#include "../Converter/Converter.h"
#include "../Display/Display.h"
#include "../ConsoleUITools/ConsoleUITools.h"

using namespace SrcPublisher;
using namespace Utilities;

class Exectutive
{
public:
	static ProcessCmdLine* getCorrectCmd(int argc, char** argv);
	static std::string customUsage();
	static SrcPublisher::Converter* initConverter();
	static int initDirExplorerAndWork(ProcessCmdLine* ppcl, SrcPublisher::Converter* pcvt);
	static void initDisplayAndWork(std::string path);
};

