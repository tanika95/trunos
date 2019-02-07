#pragma once
#include <map>
#include <tuple>
#include <stdint.h>
#include "VlConfig.hh"

typedef std::pair<uint32_t, uint32_t> Link;

class BandwidthInfo {
public:
	BandwidthInfo(const std::map<Link, double> &banwidth);

	double getBanwidth(uint32_t sender, uint32_t receiver) const;
private:
	std::map<Link, double> banwidth;
};
