#include "Sla.hh"

SLA::SLA()
{}

SLA::SLA(double bag, double lmax, double jitter)
	: bag(bag), lmax(8 * lmax / 1000), jitter(jitter)
{}

double SLA::rate() const
{
	return lmax / bag;
}
double SLA::burstSize() const
{
	return lmax * (1 + (jitter / bag));
}
