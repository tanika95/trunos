#include "Sla.hh"

Sla::Sla()
{}

Sla::Sla(double bag, double lmax, double jitter)
	: bag(bag), lmax(8 * lmax / 1000), jitter(jitter)
{}

double Sla::rate() const
{
	return lmax / bag;
}

double Sla::burstSize() const
{
	return lmax * (1 + (jitter / bag));
}
