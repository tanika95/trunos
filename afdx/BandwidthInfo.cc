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
