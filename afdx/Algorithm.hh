#pragma once

#include <boost/property_map/property_map.hpp>
#include "NetTopology.hh"
#include "Vl.hh"

class Algorithm {
public:
	Algorithm(const VlSet &vls, const NetTopology &topo, BandwidthInfo &bw);
	VlSet run();
	VlSet initial();

private:
	VlSet links;
	NetTopology map;
	BandwidthInfo &bw;

	VlSet baseStep(VlSet vls);
	VlSet additionalStep();
	std::vector<uint32_t> searchPath(const Vl &vl, uint32_t from, uint32_t to);
};
