#include "Algorithm.hh"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "Common.hh"

using namespace std;
using namespace boost;

bool vlbwsort (VL vl1, VL vl2) { return vl1.bw() > vl2.bw(); }
bool vlidsort (VL vl1, VL vl2) { return vl1.id() < vl2.id(); }

Algorithm::Algorithm(const VlSet &vls, const NetTopology &topo)
	: links(vls), map(topo)
{}

VlSet Algorithm::run()
{
	LOG(INFO) << "Algorithm started";
	try {
		const auto vls = baseStep(links);
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
	sort(links.begin(), links.end(), vlbwsort);
	for (auto link : links) {
		link = searchPath(link, link.from(), link.to());
	}
	return links;
}

VlSet Algorithm::baseStep(VlSet links)
{
	LOG(INFO) << "Base step started";
	return links;
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
