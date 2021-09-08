/** @file Timer.hh
 *  @brief Timer class to replicate the behavior of Matlab functions tic() and toc()
 *  
 *  tick() sets a time point.
 *  tock() reports the elapsed time since the last time point set by tic().
 *  Timer provides a class with the same facilities.  Each instance of Timer has its own encapsulated data  
 *  so mulitple instances can run at once.
 *   
 *  @author Michael S. Emanuel
 *  @date 2019-02-04
 */

// *********************************************************************************************************************
#pragma once

// *********************************************************************************************************************
// Library dependencies
#include <chrono>
	using std::chrono::high_resolution_clock;
	using std::chrono::time_point;
	using std::chrono::duration_cast;
	using std::chrono::nanoseconds;

#include <string>
    using std::string;

#include <fmt/format.h>
	using fmt::print;
	using fmt::format;

// *********************************************************************************************************************
// Type aliases
// Define a type name for a high resolution time point
using highResTimePoint = time_point<high_resolution_clock>;

// Define a type name for the integer type with the number of time units
using time_unit_t = long long;

// *********************************************************************************************************************
/**
@class Timer
@brief Timer class to replicate the behavior of Matlab functions tic() and toc()
*/
class Timer 
{
public:
	/// Constructor
	Timer();

	/// Set time time point
	void tick();

	/// Return the elapsed time in seconds without any string
	double tock();

	/// Take a "split" by calculating elapsed time, then re-starting timer
	double split();

	/// Return the elapsed time in seconds
	double tock_msg(const string blurb = "");

private:
	/// Static time point that is updated each time tick() is called
	highResTimePoint tp0;
    /// Static time point that is updated each time tock() is called
    highResTimePoint tp1;
};
