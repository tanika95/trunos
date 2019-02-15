#include "BandwidthInfo.hh"

#include <utility>

using namespace std;

BandwidthInfo::BandwidthInfo(const map<LinkInfo, double> &banwidth, double def)
	: banwidth(banwidth), default_bw(def)
{}

double BandwidthInfo::getBanwidth(uint32_t sender, uint32_t receiver) const
{
	try {
		return banwidth.at(make_pair(sender, receiver));
	} catch (const out_of_range &ex) {
		try {
			return banwidth.at(make_pair(receiver, sender));
		} catch (const out_of_range &ex) {
			return default_bw;
		}
	}
}
