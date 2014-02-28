#ifndef CS184_TIMER_H
#define CS184_TIMER_H
#include "include.h"

#include <sys/time.h>

class Timer {
public:
	Timer();

	void start();
	void stop();
	
	double get_duration_s();
	double get_duration_ms();

private:
	timeval start_time;
	timeval end_time;
};

#endif