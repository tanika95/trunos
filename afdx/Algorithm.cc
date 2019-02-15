#include "Algorithm.hh"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;

bool vlbwsort (Vl vl1, Vl vl2) { return vl1.bw() > vl2.bw(); }

Algorithm::Algorithm(const VlSet &vls, const NetTopology &topo)
	: links(vls), map(topo)
{}

VlSet Algorithm::run()
{
	cout << "Algorithm started";
	try {
		const auto vls = baseStep(links);
		return vls;
	} catch(const std::exception &e) {
		cout << "Base step failed";
		const auto vls = additionalStep();
		return vls;
	}
}

VlSet Algorithm::initial()
{
	cout << "Initial algorithm started";
	sort(links.begin(), links.end(), vlbwsort);
	for (auto link : links) {
		link = searchPath(link, link.from(), link.to());
	}
	return links;
}

VlSet Algorithm::baseStep(VlSet links)
{
	cout << "Base step started";
	return links;
}

VlSet Algorithm::additionalStep()
{
	cout << "Additional step started";
	return {};
}

Vl Algorithm::searchPath(const Vl &vl, uint32_t from, uint32_t to)
{
	return {};
}
