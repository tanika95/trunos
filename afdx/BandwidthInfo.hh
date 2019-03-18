#pragma once
#include <map>
#include <tuple>
#include <stdint.h>
#include "Vl.hh"

typedef std::pair<uint32_t, uint32_t> LinkInfo;

class BandwidthInfo {
public:
	BandwidthInfo(const std::map<LinkInfo, double> &bandwidth, double def);

	double getBandwidth(uint32_t sender, uint32_t receiver) const;
	BandwidthInfo& withVl(const Vl &vl);
	BandwidthInfo& withoutVl(const Vl &vl);
	BandwidthInfo& withoutVlPart(const Vl &vl, uint32_t edge);
	BandwidthInfo& withVlSet(const std::vector<Vl> &vl);

private:
	std::map<LinkInfo, double> bandwidth;
	double default_bw;
};
