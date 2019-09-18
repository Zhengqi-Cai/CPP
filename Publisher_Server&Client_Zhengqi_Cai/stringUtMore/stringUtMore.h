#pragma once
/////////////////////////////////////////////////////////////////////
// stringUtMore.h - Supplement of StringUtilities tools            //
// ver 1.0                                                         //
// Zhengqi Cai, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains more string related tools as supplement.
 * Its purpose is to help handle strings.
 * It is implemented usually using template for generic use.
 *
 *
 *
 * Required Files:
 * ---------------
 * stringUtMore.h
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 10 Mar 2019
 * - first release
 *
 */
#include <set>
#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include "../customLogger/customLogger.h"
using namespace customLogging;
namespace Utilities {
	// -----< show elements of multimap >-----------------------------------------------------
	template<typename typeK, typename typeV>
	inline void showMultiMap(bool logOpen,const std::multimap<typeK, typeV>& mm)
	{
		std::ostringstream out;
		typeK formerK = mm.begin()->first;

		for (auto pos = mm.begin(); pos != mm.end(); ++pos) {
			if (pos == mm.begin() || !(pos->first == formerK)) {
				out << "\n" << pos->first << std::endl;
				formerK = pos->first;
			}
			out << pos->second << std::endl;

		}
		StaticLogger::write(logOpen, out.str());
	}

	// -----< format path string to slash >-----------------------------------------------------

	inline std::string formatToSlash(std::string path) {
		std::regex bs("\\\\");
		return std::regex_replace(path, bs, "/");
	}

	// -----< format path string to back slash >-----------------------------------------------------

	inline std::string formatToBackSlash(std::string path) {
		std::regex bs("/");
		return std::regex_replace(path, bs, "\\");
	}

	// -----< extract values in map to set >-----------------------------------------------------
	template<typename K, typename V>
	inline std::set<V> MapToSet(std::multimap<K, V> thmap) {
		std::set<V> theset;
		for (auto pos = thmap.begin(); pos != thmap.end(); ++pos) {
			theset.insert(pos->second);
		}
		return theset;
	}

	// -----< predicate class for find a value in a map >-----------------------------------------------------

	template<class K, class V> class findValue {
	public:
		findValue(V& targetValue);
		bool operator()(const std::pair<K,V> &pair) { return pair.second == targetValue_; };

	private:
		V& targetValue_;
	};

	template<class K, class V>
	inline findValue<K,V>::findValue(V & targetValue): targetValue_(targetValue)
	{
	}

}