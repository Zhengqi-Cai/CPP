#pragma once
/////////////////////////////////////////////////////////////////////
// LoaderFactory.h - Factory of Loader(Project 3)                  //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one factory class: LoaderFactory.
 * Its purpose is to avoid directly including of specific Loader class.
 *
 *
 * Required Files:
 * ---------------
 * LoaderFactory.h
 * BaseLoader.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 9 Apr 2019
 * - first release
 *
 */

#include "BaseLoader.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"

using namespace Utilities;
namespace CodePublisher {
	class LoaderFactory
	{
	public:
		LoaderFactory();
		~LoaderFactory();
		BaseLoader* CreateCustom(ProcessCmdLine * ppcl);
	};
}

