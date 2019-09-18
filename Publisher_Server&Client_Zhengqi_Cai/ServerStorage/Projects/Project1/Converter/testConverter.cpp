///////////////////////////////////////////////////////////////
// testConverter.cpp - test of functions in Converter        //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
#include "testConverter.h"
#include "Converter.h"
#include "../Exectutive/Exectutive.h"
#include "../DirectoryNavigator/FileSystem/FileSystem.h"

#include <iostream>

using namespace SrcPublisher;
using namespace FileSystem;

#ifdef TEST_CONVERTER
int main() {
	testConverter tc;
	tc.testDoConversion();

}
#endif // TEST_CONVERTER

//----< test doConversion function >---------------------------

void testConverter::testDoConversion()
{
	Title("Init Converter...");
	std::string rootPath = "../ConvertedPages";
	if (!Directory::exists(rootPath)) {
		Directory::create(rootPath);
	}
	std::string targetExt = ".html";

	/*std::string leafDir = Exectutive::getCurrentTime();

	std::string targetPath = rootPath + "/" + leafDir;
	Directory::create(targetPath);*/

	SrcPublisher::Converter *pcvt = new SrcPublisher::Converter(Path::getFullFileSpec(rootPath), targetExt);
	std::cout << pcvt->getTargetFullPath() << " " << pcvt->getExt() << std::endl;
	pcvt->doConversion("C:/Users/zcai21/Desktop/Proj1Helper1/Proj1Helper/OodProject1Helper/Proj1Helper.h");
	delete pcvt;
}

//----< test testConvertALine function >---------------------------

void testConverter::testConvertALine()
{
	std::string s = SrcPublisher::Converter::convertALine("<html>");
	std::cout << s << std::endl;
}
