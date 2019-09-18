///////////////////////////////////////////////////////////////
// Converter.cpp - converter mainly from txt to html(Proj 1) //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
#include "Converter.h"
#include "../DirectoryNavigator/FileSystem/FileSystem.h"

#include <iostream>
#include <regex>

using namespace SrcPublisher;
using namespace FileSystem;

//----< constructor >-------

Converter::Converter(std::string targetFullPath, std::string targetExt) :targetFullPath_(targetFullPath) 
{
	targetExt_ = targetExt;
}

//----< acquire target fullpath of converted files >-------

std::string Converter::getTargetFullPath()
{
	return targetFullPath_;
}

//----< acquire target extension of converted files >-------

std::string SrcPublisher::Converter::getExt()
{
	return targetExt_;
}

//----< mainly convert a txt file to a visible html file >-------
//	input: a valid FullFileSpec of a txt file
//	output: the converted File 
void Converter::doConversion(const std::string& originFileSpec) {
	std::string oldFileName = Path::getName(originFileSpec);
	std::string newFileName = oldFileName + targetExt_;
	std::string newFileSpec = Path::fileSpec(targetFullPath_, newFileName);

	File origin(originFileSpec);
	origin.open(File::in, File::text);
	File templat("../template/web/html.txt");
	templat.open(File::in, File::text);

	File out(newFileSpec);
	out.open(File::out, File::text);

	while (templat.isGood() && out.isGood())
	{
		std::string temp = templat.getLine();
		out.putLine(temp);
		if (temp == "<pre>") {
			while (origin.isGood() && out.isGood())
			{
				std::string tempContent = origin.getLine();
				//std::cout << "\n  " << temp.c_str();
				std::string revise = Converter::convertALine(tempContent);
				out.putLine(revise);
			}
		}
	}
	templat.close();
	origin.close();
	out.close();
	std::cout << "\n\n";

}//----< replace the escape char '<' '>' in a line of txt>-------

std::string Converter::convertALine(std::string line)
{
	std::regex lt("<");
	std::regex gt(">");
	std::string revised= std::regex_replace(std::regex_replace(line, lt, "&lt;"), gt, "&gt;");
	return revised;
}

