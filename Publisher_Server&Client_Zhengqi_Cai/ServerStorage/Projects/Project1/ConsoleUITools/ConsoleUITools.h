#pragma once
///////////////////////////////////////////////////////////////
// ConsolUITools.h - Tools for console interaction           //
// ver 1.0                                                   //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one tools-collection class: ConsoleUITools.
 * Its purpose is support basic console interaction with users for
 * reading datas and logging.
 * 
 *
 *
 *
 * Required Files:
 * ---------------
 * ConsoleUITools.h
 * ../DirectoryNavigator/Utilities/CodeUtilities/CodeUtilities.h
 *../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h
 *
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 05 Feb 2019
 * - first release for Proj 1
 *
 */
#include <iostream>
#include <vector>
#include <map>

#include "../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h"
#include "../DirectoryNavigator/Utilities/CodeUtilities/CodeUtilities.h"

namespace Utilities {
	class ConsoleUITools
	{

	public:
		template <typename T>
		static void showItems(const std::string& thepreface, const std::vector<T>& items);

		template <typename T>
		static void readItems(const std::string& thepreface, std::vector<T>& items);

		template <typename T>
		static void readItem(const std::string& thepreface, T& item);

		template <typename T>
		static void showItem(const std::string& thepreface, const T& item);

		static std::string getCurrentTime();

		static bool getTOrF(std::string question);

		template <typename typeK, typename typeV>
		static void showMultiMap(const std::multimap<typeK, typeV>& mm);

	};
	
	//show items in format: 
	//preface: item1 item2 item3...
	template<typename T>
	inline void ConsoleUITools::showItems(const std::string& thepreface, const std::vector<T>& items)
	{
		preface(thepreface);
		for (auto it : items)
		{
			std::cout << it << " ";
		}
		std::cout << std::endl;
	}

	//read items by cin partitioned by whitespace to provided empty vector, end by enter
	template<typename T>
	inline void ConsoleUITools::readItems(const std::string& thepreface, std::vector<T>& items)
	{
		preface(thepreface);
		T temp;
		while (std::cin.peek()!='\n') {
			std::cin >> temp;
			items.push_back(temp);
		}
		std::cout << std::endl;
	}

	//read the first item by cin partitioned by whitespace to provided T variable
	template<typename T>
	inline void ConsoleUITools::readItem(const std::string & thepreface, T & item)
	{
		preface(thepreface);
		std::cin >> item;
		std::cout << std::endl;

	}

	//show items in format: 
	//preface: item
	template<typename T>
	inline void ConsoleUITools::showItem(const std::string & thepreface, const T & item)
	{
		preface(thepreface);
		std::cout << item << std::endl;
	}

	//show key-values in a multimap
	template<typename typeK, typename typeV>
	inline void ConsoleUITools::showMultiMap(const std::multimap<typeK, typeV>& mm)
	{
		typeK formerK = mm.begin()->first;
		for (auto pos = mm.begin(); pos != mm.end(); ++pos) {
			if (pos == mm.begin() || !(pos->first == formerK)) {
				std::cout << "\n\n" + pos->first << std::endl;
			}
			std::cout << pos->second << std::endl;

		}
	}
}

