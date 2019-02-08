#include "Algorithm.hh"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "Common.hh"

using namespace std;
using namespace boost;


Algorithm::Algorithm(const VlSet &vls, const NetTopology &topo)
	: links(vls), map(topo)
{}

VlSet Algorithm::run()
{
	LOG(INFO) << "Algorithm started";
	try {
		const auto vls = baseStep();
		return vls;
	} catch(const std::exception &e) {
		LOG(INFO) << "Base step failed";
		const auto vls = additionalStep();
		return vls;
	}
}

VlSet Algorithm::initial()
{
	LOG(INFO) << "Initial algorithm started";
	return {};
}

VlSet Algorithm::baseStep()
{
	LOG(INFO) << "Base step started";
	return {};
}

VlSet Algorithm::additionalStep()
{
	LOG(INFO) << "Additional step started";
	return {};
}

Vl Algorithm::searchPath(const Vl &vl, uint32_t from, uint32_t to)
{
	return {};
}
