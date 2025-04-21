#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSchedule(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCounts,
    size_t day,
    size_t slot
) {
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    // Base case: all days scheduled
    if (day == numDays) {
        return true;
    }

    // If we've filled all slots for today, move to the next day
    if (slot == dailyNeed) {
        return fillSchedule(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1, 0);
    }

    // Try assigning each worker
    for (size_t worker = 0; worker < numWorkers; ++worker) {
        if (!avail[day][worker]) continue;
        if (shiftCounts[worker] >= maxShifts) continue;
        if (find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) continue;

        // Assign worker
        sched[day][slot] = worker;
        shiftCounts[worker]++;

        if (fillSchedule(avail, dailyNeed, maxShifts, sched, shiftCounts, day, slot + 1)) {
            return true;
        }

        // Backtrack
        sched[day][slot] = INVALID_ID;
        shiftCounts[worker]--;
    }

    // No valid assignment found
    return false;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
		return false;
	}
	sched.clear();
	// Add your code below
	
	size_t numDays = avail.size();
	size_t numWorkers = avail[0].size();

	sched.resize(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
	vector<size_t> shiftCounts(numWorkers, 0);

	return fillSchedule(avail, dailyNeed, maxShifts, sched, shiftCounts, 0, 0);


}

