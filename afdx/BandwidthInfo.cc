#include "BandwidthInfo.hh"

#include <utility>
#include "Common.hh"

using namespace std;

BandwidthInfo::BandwidthInfo(const map<LinkInfo, double> &bandwidth, double def)
	: bandwidth(bandwidth), default_bw(def)
{}

void BandwidthInfo::log() const
{
	LOG(INFO) << "Bandwidth map";
	for (const auto &link : bandwidth) {
		LOG(INFO) << link.first.first << ' ' << link.first.second << ' ' << link.second;
	}
}

double BandwidthInfo::getBandwidth(uint32_t sender, uint32_t receiver) const
{
	try {
		return bandwidth.at(make_pair(sender, receiver));
	} catch (const out_of_range &ex) {
		return default_bw;
	}
}

BandwidthInfo& BandwidthInfo::withVl(const Vl &vl)
{
	const auto route = vl.switches();
	for (uint32_t i = 0; i < route.size() - 1; i++) {
		bandwidth[{route[i], route[i + 1]}] -= vl.bw();
	}
	return *this;
}

BandwidthInfo& BandwidthInfo::withVlPart(const Vl &vl, uint32_t edge)
{
	const auto route = vl.switches();
	bool broken = false;
	for (uint32_t i = 0; i < route.size() - 1; i++) {
		if (route[i] == edge) {
			broken = true;
		}
		if (broken) {
			bandwidth[{route[i], route[i + 1]}] -= vl.bw();
		}
	}
	return *this;
}

BandwidthInfo& BandwidthInfo::withoutVl(const Vl &vl)
{
	const auto route = vl.switches();
	for (uint32_t i = 0; i < route.size() - 1; i++) {
		bandwidth[{route[i], route[i + 1]}] += vl.bw();
	}
	return *this;
}

BandwidthInfo& BandwidthInfo::withoutVlPart(const Vl &vl, uint32_t edge)
{
	const auto route = vl.switches();
	bool broken = false;
	for (uint32_t i = 0; i < route.size() - 1; i++) {
		if (route[i] == edge) {
			broken = true;
		}
		if (broken) {
			bandwidth[{route[i], route[i + 1]}] += vl.bw();
		}
	}
	return *this;
}

BandwidthInfo& BandwidthInfo::withVlSet(const vector<Vl> &vls)
{
	for (const auto &vl : vls) {
		withVl(vl);
	}
	return *this;
}
