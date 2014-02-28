#include "timer.h"

Timer::Timer() {
	start();
	end_time = start_time;
}

void Timer::start() {
	gettimeofday(&start_time, NULL);
}

void Timer::stop() {
	gettimeofday(&end_time, NULL);
}



double Timer::get_duration_s() {
	return (double)(end_time.tv_sec - start_time.tv_sec) + (double)((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
}

double Timer::get_duration_ms() {
	return get_duration_s() * 1000.0;
}