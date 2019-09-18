///////////////////////////////////////////////////////////////////////
// CodeUtilities.cpp - small, generally useful, helper classes       //
// ver 1.2                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

#include "CodeUtilities.h"
#include "../StringUtilities/StringUtilities.h"
#include <string>
#include <iostream>
#include <functional>
#include "../../customLogger/customLogger.h"

namespace Utilities {
	/////////////////////////////////////////////////////////////////////
	// preface function
	// - used to add a string preface to an output, e.g., "\n  "

	void preface(bool logOpen, const std::string& msg, bool doReturn, const std::string& prefix)
	{
		std::ostringstream os;
		if (doReturn) os << "\n" << prefix << msg;
		customLogging::StaticLogger::write(logOpen, os.str());
	}

	std::string defaultUsage()
	{
		std::string usage;
		usage += "\n  Command Line: path [/option]* [/pattern]* [integer]";
		usage += "\n    path is relative or absolute path where processing begins";
		usage += "\n    [/option]* are one or more options of the form /s, /r, etc.";
		usage += "\n    [pattern]* are one or more pattern strings used for matching";
		usage += "\n    [integer] is the maximum number of items to process";
		usage += "\n";
		return usage;
	}

	/*----< path operations >------------------------------------------*/

	void ProcessCmdLine::path(const Path& path)
	{
		path_ = path;
	}

	ProcessCmdLine::Path ProcessCmdLine::path()
	{
		return path_;
	}

	void ProcessCmdLine::showPath()
	{
		customLogging::StaticLogger::write(logOpen_, path_ + " ");
	}

	/*----< options operations >---------------------------------------*/

	void ProcessCmdLine::option(Option option)
	{
		options_.push_back(option);
	}

	ProcessCmdLine::Options ProcessCmdLine::options()
	{
		return options_;
	}

	bool ProcessCmdLine::hasOption(Option op)
	{
		for (auto item : options_)
		{
			if (item == op)
			{
				return true;
			}
		}
		return false;
	}

	void ProcessCmdLine::showOptions()
	{
		std::ostringstream os;
		for (auto opt : options_)
		{
			os << '/' << char(opt) << " ";
		}
		customLogging::StaticLogger::write(logOpen_, os.str());
	}

	/*----< patterns operations >--------------------------------------*/

	void ProcessCmdLine::pattern(const Pattern& pattern)
	{
		patterns_.push_back(pattern);
	}

	ProcessCmdLine::Patterns ProcessCmdLine::patterns()
	{
		return patterns_;
	}

	ProcessCmdLine::Regexes ProcessCmdLine::regexes()
	{
		return regexes_;
	}

	void ProcessCmdLine::showPatterns()
	{
		std::ostringstream os;
		for (auto patt : patterns_)
		{
			os << patt << " ";
		}
		customLogging::StaticLogger::write(logOpen_, os.str());
	}

	void ProcessCmdLine::showRegexes()
	{
		std::ostringstream os;
		for (auto regex : regexes_)
		{
			os << regex << " ";
		}
		customLogging::StaticLogger::write(logOpen_, os.str());
	}

	/*----< maxItems operations >--------------------------------------*/

	void ProcessCmdLine::maxItems(Number maxItems)
	{
		maxItems_ = maxItems;
	}

	ProcessCmdLine::Number ProcessCmdLine::maxItems()
	{
		return maxItems_;
	}

	void ProcessCmdLine::showMaxItems()
	{
		if (maxItems_ != 0)
			customLogging::StaticLogger::write(logOpen_, maxItems_ + " ");
	}

	bool ProcessCmdLine::isValidRegex(const std::string & regex)
	{
		bool res = true;
		try
		{
			std::regex tmp(regex);
		}
		catch (const std::regex_error& e)
		{
			(e);
			res = false;
		}
		return res;
	}

	/*----< parseError operation >-------------------------------------*/

	bool ProcessCmdLine::parseError()
	{
		return parseError_;
	}

	/*----< command line operations >----------------------------------*/

	ProcessCmdLine::ProcessCmdLine(int argc, char** argv)
	{
		//usage_ = defaultUsage();
		if (argc < 2)
		{
			customLogging::StaticLogger::write(logOpen_, "\n  command line parse error");
			//usage();
			parseError_ = true;
			return;
		}

		path_ = argv[1];

		for (int i = 2; i < argc; ++i)
		{
			if (argv[i][0] == '/')
			{
				if (strlen(argv[i]) > 2)
					continue;
				options_.push_back(argv[i][1]);
			}
			else
			{
				int number = atoi(argv[i]);
				if (number > 0)
				{
					maxItems_ = number;
				}
				else if (isValidRegex(argv[i]))
				{
					regexes_.push_back(argv[i]);
				}
				else
				{
					patterns_.push_back(argv[i]);
				}
			}
		}
	}

	/*inline void ProcessCmdLine::showCmdLine(int argc, char** argv)
	{
		if (argc > 2)
		{
			*pout_ << "  empty";
			return;
		}
		for (int i = 0; i < argc; ++i)
		{
			if (argv[i] == "0")
				continue;
			if (argv[i][0] == '/')
			{
				*pout_ << "/" + char(argv[i][1]) << " ";
			}
			else
			{
				*pout_ << argv[i] << " ";
			}
		}
	}*/

	void ProcessCmdLine::showCmdLine()
	{

		if (path_ == "" && options_.size() == 0 && patterns_.size() == 0)
		{
			customLogging::StaticLogger::write(logOpen_, "empty");
			return;
		}
		showPath();
		preface(logOpen_, "", false);
		showOptions();
		preface(logOpen_, "", false);
		showPatterns();
		preface(logOpen_, "", false);
		showMaxItems();
	}

	void ProcessCmdLine::usage(const Usage& usage)
	{
		usage_ = usage;
	}

	void ProcessCmdLine::usage()
	{
		customLogging::StaticLogger::write(logOpen_, usage_);
	}
}

#ifdef TEST_CODEUTILITIES

using namespace Utilities;
using namespace Logging;
int main(int argc, char* argv[])
{
	StaticLogger::attach(&std::cout);
	StaticLogger::start();

  Title("Testing CodeUtilities");
  putline();

  title("Testing ProcessCmdLine");
  ProcessCmdLine pcl(argc, argv);
  pcl.usage();

  preface("Command Line: "); pcl.showCmdLine();
  preface("path:     "); pcl.showPath();
  preface("Options:  "); pcl.showOptions();
  preface("Patterns: "); pcl.showPatterns();
  preface("MaxItems: "); pcl.showMaxItems();
  std::cout << "\n";

  preface("changing path: ");
  pcl.path("c:\\su");
  pcl.showPath();

  preface("adding option: ");
  pcl.option('/q');
  pcl.showOptions();

  preface("adding pattern: ");
  pcl.pattern("*.htm");
  pcl.showPatterns();

  preface("changing maxItems: ");
  pcl.maxItems(15);
  pcl.showMaxItems();
  putline();
  preface("new command line: ");
  pcl.showCmdLine();
  putline();

  title("Testing Box and PersistFactory");
  Box<double> boxedDouble = 3.1415927;
  StaticLogger::write(true,"\n  boxedDouble = " + boxedDouble);
  boxedDouble = 0.33333;
  StaticLogger::write(true, "\n  boxedDouble = " + boxedDouble);

  PersistFactory<std::string> name = std::string("Jim");
  name.append(" Fawcett");
  StaticLogger::write(true, "\n  " + name.toXml("name"));

  PersistFactory<Box<double>> value = Box<double>(9.87654);
  StaticLogger::write(true, "\n  " + value.toXml("value"));
  value += 3.14159;
  StaticLogger::write(true, "\n  " + value.toXml("value"));

  StaticLogger::write(true, "\n\n");


  title("test std::string Converter<T>::toString(T)");

  std::string conv1 = Converter<double>::toString(3.1415927);
  std::string conv2 = Converter<int>::toString(73);
  std::string conv3 = Converter<std::string>::toString("a_test_string plus more");

  StaticLogger::write(true, "\n  Converting from values to strings: ");

  StaticLogger::write(true, conv1 + ", " + conv2 + ", " + conv3);

  putline();

  title("test T Converter<T>::toValue(std::string)");
  StaticLogger::write(true, "\n  Converting from strings to values: ");

  StaticLogger::write(true, Converter<double>::toValue(conv1) + ", ");

  StaticLogger::write(true, "\n  " + value.toXml("value"));

  std::cout << Converter<int>::toValue(conv2) << ", ";
  StaticLogger::write(true, "\n  " + value.toXml("value"));

  std::cout << Converter<std::string>::toValue(conv3);

  putline(2);
  return 0;
}
#endif
