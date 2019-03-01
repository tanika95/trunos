#include "Algorithm.hh"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "Common.hh"
#include "Timer.hh"

using namespace std;
using namespace boost;

Algorithm::Algorithm(const VlSet &vls, const NetTopology &topo, const BandwidthInfo &bw)
	: links(vls), map(topo), bw(bw)
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
	{
		Timer timer("Initial search");
		for (auto &link : links) {
			auto path = searchPath(link, link.from(), link.to());
			link = link.withRoute(map.routeForVl(path));
		}
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

vector<uint32_t> Algorithm::searchPath(const Vl &vl, uint32_t from, uint32_t to)
{
	Graph network = map.graphForVl(vl, bw);
	vector<Vertex> path(num_vertices(network), graph_traits<Graph>::null_vertex());
	Vertex start = vertex(from, network);
	vector<double> distances(num_vertices(network), 0.0);

	dijkstra_shortest_paths(network, start,
		predecessor_map(&path[0]).distance_map(&distances[0]));

	unsigned long v = path[to];
	if (v == path[v]) {
		throw runtime_error("Путь не найден");
	}
	vector<uint32_t> route = {to};
	bw.decrease({to, v}, vl.bw());
	while (path[v] != v) {
		route.push_back(v);
		auto next = v;
		v = path[v];
		bw.decrease({v, next}, vl.bw());
	}
	route.push_back(from);
	return route;
}
