/////////////////////////////////////////////////////////////////////
// ICodePubr.cpp - Interface of CodePublisher(Project 3)           //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include"ICodePubr.h"
#include"CodePubrFactory.h"


#ifdef TEST_ICODEPUBR
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include"../FileSystem/FileSystem.h"
#include"../Logger/Logger.h"
using namespace FileSystem;
using namespace Utilities;
using namespace CodePublisher;
using namespace Logging;

int main(int argc, char** argv) {
	ProcessCmdLine *ppcl = new ProcessCmdLine(argc, argv);

	Utilities::Title(true, "Verifying command...");
	preface(true,"Command Line: ");

	ppcl->showCmdLine();
	ppcl->showRegexes();
	putline(1);

	std::string ProtoPagesFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoPages");
	std::string ProtoWithDepFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithDep");
	std::string ProtoWithVisFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtoWithVis");
	std::string ProtoFullyProduceFullPath_ = Path::getFullFileSpec("..\\ConvertedFiles\\ProtofullyProduce");
	CodePubrFactory cpf;
	ICodePubr* pcpr_ = cpf.CreateCustom(ppcl, ProtoPagesFullPath_);

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

#endif // TEST_ICODEPUBR


