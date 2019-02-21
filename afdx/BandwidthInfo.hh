#pragma once
#include <map>
#include <tuple>
#include <stdint.h>

typedef std::pair<uint32_t, uint32_t> LinkInfo;

class BandwidthInfo {
public:
	BandwidthInfo(const std::map<LinkInfo, double> &bandwidth, double def);

	double getBandwidth(uint32_t sender, uint32_t receiver) const;
	void decrease(const LinkInfo &link, double bw);

private:
	std::map<LinkInfo, double> bandwidth;
	double default_bw;
};
