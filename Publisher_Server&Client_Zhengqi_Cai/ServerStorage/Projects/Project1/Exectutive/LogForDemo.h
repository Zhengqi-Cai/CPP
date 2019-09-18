#pragma once
///////////////////////////////////////////////////////////////
// LogForDemo.h - Specific message for demo(Proj 1)          //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one specific static logger class: LogForDemo.
 * Its purpose is to demonstrate meeting nine requirement of Project 1.
 * It is implemented using static Logger class with specific message.
 *
 *
 *
 * Required Files:
 * ---------------
 * LogForDemo.h
 * ../Logger/Logger.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Feb 2019
 * - first release
 *
 */

#include <iostream>
#include "../Logger/Logger.h"

using namespace Utilities;
namespace SrcPublisher {
	class LogForDemo
	{
	public:
		static void loggerStart();
		static void DemoReq1();
		static void DemoReq2();
		static void DemoReq3();
		static void DemoReq4();
		static void DemoReq5(bool nonzero);
		static void DemoReq6();
		static void DemoReq7();
		static void DemoReq8n9();

	};
}

