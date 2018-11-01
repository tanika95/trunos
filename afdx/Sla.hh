#pragma once
#include <stdint.h>

class Sla {
public:
	Sla(double bag, double lmax, double jitt);
	Sla();

	double rate() const;
	double burstSize() const;
private:
	double bag;
	double lmax;
	double jitter;
};
