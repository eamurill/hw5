#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generate(string& current, const string& floating, const set<string>& dict, set<string>& results,int pos) {
	if(pos == current.size()) {
		// Base case: all positions filled
		int floating_count = 0;
		for(char c : floating) {
			if(count(current.begin(), current.end(), c) < count(floating.begin(), floating.end(), c)) {
				return;  // Not enough floating letters used
			}
		}
		if(dict.find(current) != dict.end()) {
			results.insert(current);
		}
		return;
	}

	if(current[pos] != '-') {
		generate(current, floating, dict, results, pos + 1);
	}
	else {
			// Try all letters a-z
		for(char c = 'a'; c <= 'z'; ++c) {
			current[pos] = c;
			generate(current, floating, dict, results, pos + 1);
		}
		current[pos] = '-';  // Backtrack
	}
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string> results;
    string current = in;
    generate(current, floating, dict, results, 0);
    return results;

}

// Define any helper functions here
