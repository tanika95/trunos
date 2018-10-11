#pragma once
#include <stdint.h>

class SLA {
public:
	SLA(double bag, double lmax, double jitt);
	SLA();

	double rate() const;
	double burstSize() const;
private:
	double bag;
	double lmax;
	double jitter;
};
