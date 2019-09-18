#pragma once
/////////////////////////////////////////////////////////////////////
// DirExplorerN.h - Naive directory explorer(Modified for Proj 1)  //
// ver 1.5                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////


/* Package Operations:
 * -------------------
 * DirExplorerN provides a class, of the same name, that executes a
 * depth first search of a directory tree rooted at a specified path.
 * Each time it enters a directory, it invokes its member function
 * doDir, and for every file in that directory, it invokes doFile.
 *
 * We call this a "Naive Directory Explorer" because, while it carries
 * out its assigned responsibilities well, there is no way to change
 * what its doDir and doFile functions do, without changing the class
 * itself.  It would be much better to provide a mechanism to allow
 * a using application to supply this processing without changing
 * the Directory Navigator. 
 *
 * Other projects in the DirectoryNavigator folder in Repository/Cpp 
   do just that, in different ways.  

 * - DirExplorer-Naive (this project):
 *     Implements basic processing well, but applications have to
 *     change its code to affect how files and directories are
 *     handled.
 * - DirExplorer-Template:
 *     Applications provide template class parameters to define file
 *     and directory processing.
 * - DirExplorer-Inheritance:
 *     Applications subclass DirExplorerI, overriding virtual functions
 *     doFile, doDir, and doQuit to define how files and directories
 *     are handled, and whether processing should terminate before
 *     visiting all directories.
 * - DirExplorer-Events:
 *     Applications use Event Interfaces, published by DirExplorerE,
 *     by subscribing event-handler functions, and control terminate
 *      processing using a plug-in interface.
 * - DirExplorer-Provider:
 *     Applications implement a file system provider that implements
 *     a Provider interface published by DirExplorerP.
 *     
 * We'll be using the Repository/Cpp solution to illustrate techniques 
 * for building flexible software.
 *
 * Required Files:
 * ---------------
 * DirExplorerN.h, DirExplorerN.cpp
 * ../FileSystem/FileSystem.h									 // Directory and Path classes
 * ../Utilities/StringUtilities/StringUtilities.h                // Title function
 * ../Utilities/CodeUtilities/CodeUtilities.h                    // ProcessCmdLine class
 * ../../Converter/Converter.h
 *
 * Maintenance History:
 * --------------------
 * ver 1.5 : 04 Feb 2019
 * - Add pointer of a Converter and the demonstration choices
 *	 modify the constructor and destructor.
 *	 add vector of regexes and relevant tools for file filtering
 *	 modify showStat() function with a potential ERROR reminder.
 *
 * Original Author's Record:
 * ver 1.4 : 24 Jan 2019
 * - Removed all projects except those needed for DirExplorerN.
 * ver 1.3 : 19 Aug 2018
 * - Removed some options to make this version simple.  Those are
 *   implemented in the more advanced navigators, presented here.
 * ver 1.2 : 17 Aug 2018
 * - Moved method definitions to inlines, below the class declaration.
 * ver 1.1 : 16 Aug 2018
 * - Made no recursion default, added option /s for recursion.
 * ver 1.0 : 11 Aug 2018
 * - first release
 *
 * Reference:
 * --------------------
 * Proto-codes comes from DirExplorer-Naive package ver 1.4 by Dr. Jim Fawcett
 *
 */

#include <vector>
#include <iostream>
#include <regex>
#include <map>

#include "../FileSystem/FileSystem.h"
#include "../../Converter/Converter.h"
#include "../../ConsoleUITools/ConsoleUITools.h"

using namespace Utilities;

namespace FileSystem
{
  class DirExplorerN
  {
  public:
    using patterns = std::vector<std::string>;
	using regexes = std::vector<std::string>;

    static std::string version() { return "ver 1.5"; }

	DirExplorerN(const std::string& path, SrcPublisher::Converter* pcvt, bool loggerDirOn = false, bool loggerFileOn = false);
	~DirExplorerN();

    // set options for analysis

    void addPattern(const std::string& patt);
	void addRegex(const std::string& regex);
    void recurse(bool doRecurse = true);

    // conduct depth first search

    void search();
    void find(const std::string& path);

	 std::string matchedRegex(std::string filename);
	 void processedFiles();

    // define what happens when a file or dir is encountered

    void doFile(const std::string& filespec);
    void doDir(const std::string& dirname);

    // extract traversal statistics 

    size_t fileCount();
    size_t dirCount();
    void showStats();

  private:
    std::string path_;
    patterns patterns_;
	regexes regexes_;
    size_t dirCount_ = 0;
    size_t fileCount_ = 0;
    bool recurse_ = false;

	bool loggerDirOn_=false;
	bool loggerFileOn_=false;
	SrcPublisher::Converter* pcvt_;
	std::multimap<std::string, std::string> regexMatchStat;
  };

  //----< construct DirExplorerN instance with default pattern >-----

  inline DirExplorerN::DirExplorerN(const std::string& path, SrcPublisher::Converter* pcvt, bool loggerDirOn, bool loggerFileOn) : path_(path)
  {
	pcvt_ = pcvt;
    patterns_.push_back("*.*");
	regexes_.push_back(".*");
	loggerDirOn_ = loggerDirOn;
	loggerFileOn_ = loggerFileOn;
  }

  //----< destruct DirExplorerN instance >-----
  inline DirExplorerN::~DirExplorerN() {
	  delete pcvt_;
  }

  //----< add specified patterns for selecting file names >----------

  inline void DirExplorerN::addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }

  //----< add specified regexes for selecting file names >----------

  inline void DirExplorerN::addRegex(const std::string& regex) {
	  if (regexes_.size() == 1 && regexes_[0] == ".*") {
		  regexes_.pop_back();
	  }
	  regexes_.push_back(regex);
  }
  //----< set option to recusively walk dir tree >-------------------

  inline void DirExplorerN::recurse(bool doRecurse)
  {
    recurse_ = doRecurse;
  }
  //----< start Depth First Search at path held in path_ >-----------

  inline void DirExplorerN::search()
  {
    find(path_);
  }
  //----< search for directories and their files >-------------------
  /*
    Recursively finds all the dirs and files on the specified path,
    executing doDir when entering a directory and doFile when finding a file
  */
  inline void DirExplorerN::find(const std::string& path)
  {
    // show current directory

    std::string fpath = FileSystem::Path::getFullFileSpec(path);
    doDir(fpath);

    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
      for (auto f : files)
      {
		  //filter using regex
		  std::string matchedR = matchedRegex(f);
		  if (matchedR !="") {
			  regexMatchStat.insert(make_pair(matchedR, f));
			  std::string fileSpec = Path::fileSpec(fpath, f);
			  doFile(fileSpec);
		  }
      }
    }

    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
    for (auto d : dirs)
    {
      if (d == "." || d == "..")
        continue;
      std::string dpath = fpath + "\\" + d;
      if (recurse_)
      {
        find(dpath);   // recurse into subdirectories
      }
      else
      {
        doDir(dpath);  // show subdirectories
      }
    }
  }

  //----< return the matched regex of a filename >-------
  inline std::string DirExplorerN::matchedRegex(std::string filename) {
	  for (auto regex : regexes_)
	  {
		  std::regex rg(regex);
		  if (std::regex_match(filename, rg)) {
			  return regex;
		  }
	  }
	  return "";
  }

  //----< an application changes to enable specific file ops >-------

  inline void DirExplorerN::doFile(const std::string& filespec)
  {
    ++fileCount_;
	if (loggerFileOn_) {
		std::string filename = Path::getName(filespec, true);
		std::cout << "\n  --   " << filename;
	}
	pcvt_->doConversion(filespec);
  }
  //----< an application changes to enable specific dir ops >--------

  inline void DirExplorerN::doDir(const std::string& dirname)
  {
    ++dirCount_;
	if (loggerDirOn_) {
		std::cout << "\n  ++ " << dirname;
	}
  }
  //----< return number of files processed >-------------------------

  inline size_t DirExplorerN::fileCount()
  {
    return fileCount_;
  }
  //----< return number of directories processed >-------------------

  inline size_t DirExplorerN::dirCount()
  {
    return dirCount_;
  }
  //----< show final counts for files and dirs >---------------------

  inline void DirExplorerN::showStats()
  {
	std::string result = "processed " + std::to_string(fileCount_) + " files in " + std::to_string(dirCount_) +  " directories";
	
	try {
		if (!fileCount_) {
			result = "\nERROR: " + result + "\n";
			throw result.c_str();
		}else {
			std::cout << "\n" << result << std::endl;
		}
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
  }

  inline void DirExplorerN::processedFiles() {
	  if (fileCount_) {
		  preface("\n\nFiles found in each regex: ");
		  ConsoleUITools::showMultiMap(regexMatchStat);
	  }
  }
}

