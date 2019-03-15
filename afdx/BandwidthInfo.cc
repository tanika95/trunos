#include "BandwidthInfo.hh"

#include <utility>

using namespace std;

BandwidthInfo::BandwidthInfo(const map<LinkInfo, double> &bandwidth, double def)
	: bandwidth(bandwidth), default_bw(def)
{}

double BandwidthInfo::getBandwidth(uint32_t sender, uint32_t receiver) const
{
	try {
		return bandwidth.at(make_pair(sender, receiver));
	} catch (const out_of_range &ex) {
		return default_bw;
	}
}

void BandwidthInfo::decrease(const LinkInfo &link, double bw)
{
    	if (bandwidth.find(link) != bandwidth.end()) {
		bandwidth[link] -= bw;
	}
}

void BandwidthInfo::increase(const Vl &vl)
{
	const auto route = vl.switches();
	for (uint32_t i = 0; i < route.size(); i++) {
		bandwidth[{route[i], route[i + 1]}] += vl.bw();
	}
}
