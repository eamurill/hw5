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
void generate(string& current, string floating, const set<string>& dict, set<string>& results, int pos);
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
void generate(
    string& current,
    string floating,
    const set<string>& dict,
    set<string>& results,
    int pos
) {
    if (pos == int(current.size())) {
        if (!floating.empty()) return; // not all floating letters used
        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (current[pos] != '-') {
        generate(current, floating, dict, results, pos + 1);
    }
    else {
        // Optimization: if remaining '-' equals floating letters, we *must* use them
        if (count(current.begin() + pos, current.end(), '-') == int(floating.size())) {
            // Try placing each floating letter
            for (size_t i = 0; i < floating.size(); ++i) {
                char c = floating[i];
                current[pos] = c;
                string nextFloating = floating;
                nextFloating.erase(i, 1); // remove used floating letter
                generate(current, nextFloating, dict, results, pos + 1);
            }
        }
        else {
            // Try all 26 letters
            for (char c = 'a'; c <= 'z'; ++c) {
                current[pos] = c;
                string nextFloating = floating;
                // If this letter is one of the required floating letters, consume one copy
                auto it = find(nextFloating.begin(), nextFloating.end(), c);
                if (it != nextFloating.end()) {
                    nextFloating.erase(it);
                }
                generate(current, nextFloating, dict, results, pos + 1);
            }
        }
        current[pos] = '-'; // backtrack
    }
}