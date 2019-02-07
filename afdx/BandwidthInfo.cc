#include "BandwidthInfo.hh"

#include <utility>

using namespace std;

BandwidthInfo::BandwidthInfo(const map<LinkInfo, double> &banwidth)
{}

double BandwidthInfo::getBanwidth(uint32_t sender, uint32_t receiver) const
{
	return banwidth[make_pair(sender, receiver)];
}
