#pragma once
#include <vector>
#include <boost/property_map/property_map.hpp>
#include "NetTopology.hh"
#include "Vl.hh"
#include "VlState.hh"

class Algorithm {
public:
	Algorithm(const VlSet &vls, const NetTopology &topo, const BandwidthInfo &bw);
	VlSet run();
	VlSet initial();

private:
	VlSet links;
	NetTopology map;
	BandwidthInfo bw;
	const std::vector<VlState> brokenmap;

	VlSet baseStep(VlSet vls);
	VlSet additionalStep();

	BandwidthInfo takeOffBroken(BandwidthInfo bw);
	BandwidthInfo takeOffHeavy(BandwidthInfo bw);

	std::vector<uint32_t> searchPath(Graph network, uint32_t from, uint32_t to) const;
};
