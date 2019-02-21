#include "Algorithm.hh"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "Common.hh"
#include "Timer.hh"

using namespace std;
using namespace boost;

bool vlbwsort (Vl vl1, Vl vl2) { return vl1.bw() > vl2.bw(); }

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
	sort(links.begin(), links.end(), vlbwsort);
	{
		Timer timer("Initial search");
		for (auto link : links) {
			link = searchPath(link, link.from(), link.to());
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

Vl Algorithm::searchPath(const Vl &vl, uint32_t from, uint32_t to)
{
	Graph network = map.graphForVL(vl, bw);
	vector<Vertex> path(num_vertices(network), graph_traits<Graph>::null_vertex());
	Vertex start = vertex(from, network);
	vector<double> distances(num_vertices(network), 0.0);

	{
		Timer timer("dejkstra search");
		dijkstra_shortest_paths(network, start,
			predecessor_map(&path[0]).distance_map(&distances[0]));
	}

	unsigned long v = to;
	if (distances[to] < 0.001 || v == path[v]) {
		throw runtime_error("Путь не найден");
	}
	IndexMap index = get(vertex_index, network);
	std::vector<int> route;
	while (path[v] != v) {
		//int prev = v;
		v = path[v];
		if (path[v] == v) {
			break;
		}
		route.push_back(index[v]);
	}
	for (auto r : route) {
	 	LOG(INFO) << r;
	}
	return {};
}
