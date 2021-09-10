/** @file Timer.cc
 *  @brief Implmentation of Timer class.
 *
 *  @author Michael S. Emanuel
 *  @date 2019-02-04
 */

// *********************************************************************************************************************
#include "Timer.hh"

// *********************************************************************************************************************
// Constants used in converting units
constexpr long aBillion {static_cast<long>(1.0e9)};
constexpr long aMillion {static_cast<long>(1.0e6)};
	
// *********************************************************************************************************************
// Constructor
Timer::Timer() :
	tp0 {highResTimePoint()},
	tp1 {highResTimePoint()}
{
	tick();
}

// *********************************************************************************************************************
// Start the timer.
void Timer::tick() 
	{tp0 = high_resolution_clock::now();}

// *********************************************************************************************************************
double Timer::tock() 
{
	// Time point when tock() is called
	highResTimePoint tp1 = high_resolution_clock::now();

	// The elapsed time in nanoseconds
	time_unit_t t = duration_cast<nanoseconds>(tp1 - tp0).count();

	// Compute the elapsed time in seconds.
	double tSeconds = static_cast<double>(t) / aBillion;

	// Return the elapsed time in seconds
	return tSeconds;
}

// *********************************************************************************************************************
double Timer::split()
{
	// Get the elapsed time
	double tSeconds {tock()};
	// Start the timer for the next split
	tick();
	// Return elapsed time of the split in seconds
	return tSeconds;
}

// *********************************************************************************************************************
double Timer::tock_msg(const string blurb) 
{
	// Time point when tock() is called
	highResTimePoint tp1 = high_resolution_clock::now();

	// The elapsed time in nanoseconds
	time_unit_t t = duration_cast<nanoseconds>(tp1 - tp0).count();

	// Create a formatted output with an appropriate amount of resolution for legibility.
	// This message is:
	// <blurb>: nnnnn.ddd <TimeUnits>.
	// TimeUnits is one of seconds, milliseoncds, microseconds, or nanoseconds.
	// If <blurb> omitted, message defaults to
	// Elapsed Time: nnnnn.ddd <TimeUnits>.

	// The template message
	// constexpr char msg[] = "{:s}{:s}{:9.3f} {:s}.\n";
	// A clang bug causes this to be rejected as an argument to print
	// Workaround: define msg as a macro instead
	#define MSG "{:s}{:s}{:9.3f} {:s}.\n"
	// The prefix of the message is either blurb or defaults to "Elapsed Time"
	const string prefix = blurb.length() > 0 ? blurb: "Elapsed Time";
	const string sep = (blurb.back() == '\n') ? "" : ": ";

	// Compute the elapsed time in seconds.
	double tSeconds = static_cast<double>(t) / aBillion;

	// Print a message stating the elapsed time.
	if (t > aBillion) 
	{
		print(MSG, prefix, sep, tSeconds, "seconds");
	}
	else if (t > aMillion) 
	{
		double tMilliSeconds = tSeconds * 1000;
		print(MSG, prefix, sep, tMilliSeconds, "milliseconds");
	}
	else if (t > 1000) 
	{
		double tMicroSeconds = tSeconds * aMillion;
		print(MSG, prefix, sep, tMicroSeconds, "microseconds");
	}
	else 
	{
		double tNanoSeconds = static_cast<double>(t);
		print("{:s}{:s}{:9.3f} {:s}.\n", prefix, sep, tNanoSeconds, "nanoseconds");
	}

	// Return the elapsed time in seconds
	return tSeconds;
}

// *********************************************************************************************************************
void TimerTest() 
{
	Timer t;

	t.tick();
	t.tock_msg("doing nothing");
}
