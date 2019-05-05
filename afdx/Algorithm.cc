#include "Algorithm.hh"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "Common.hh"
#include "Timer.hh"

using namespace std;
using namespace boost;

Algorithm::Algorithm(const VlSet &vls, const NetTopology &topo, const BandwidthInfo &bw)
	: links(vls), map(topo), bw(bw), brokenmap(map.brokenVls(links))
{}

VlSet Algorithm::run()
{
	LOG(INFO) << "Algorithm started";
	try {
		const auto vls = baseStep(links);
		return vls;
	} catch(const std::exception &e) {
		LOG(INFO) << "Base step failed: " << e.what();
		const auto vls = additionalStep(links);
		return vls;
	}
}

VlSet Algorithm::initial()
{
	LOG(INFO) << "Initial algorithm started";
	Timer timer("Initial search");
	for (auto &link : links) {
		auto network = map.graphForVl(link, bw);
		auto path = searchPath(network, link.from(), link.to());
		link = link.withRoute(map.routeForVl(path));
		bw = bw.withVl(link);
	}
	return links;
}

VlSet Algorithm::baseStep(VlSet vls)
{
	LOG(INFO) << "Base step started";
	Timer timer("Base step");
	auto bandwidth = takeOffBroken(bw);
	int i = 0;
	for (auto &link : vls) {
		if (link.getId() != brokenmap[i].id) {
			throw logic_error("Несоответствие индексов вк с картой вк");
		}
		if (brokenmap[i].broken) {
			auto network = map.graphForVl(link, bandwidth);
			auto path = searchPath(network, brokenmap[i].sedge, link.to());
			link = link.withChangedRoute(map.routeForVl(path), brokenmap[i].sedge);

			bandwidth = bandwidth.withVlPart(link, brokenmap[i].sedge);
		} else {
			link = link.stable();
		}
		i++;
	}
	return vls;
}

VlSet Algorithm::additionalStep(VlSet vls)
{
	LOG(INFO) << "Additional step started";
	Timer timer("Additional step");
	auto bandwidth = takeOffHeavy(bw);
	int i = 0;
	for (auto &link : vls) {
		if (link.getId() != brokenmap[i].id) {
			throw logic_error("Несоответствие индексов вк с картой вк");
		}
		link = link.stable();
		if (brokenmap[i].broken) {
			auto network = map.graphForVl(link, bandwidth);
			auto path = searchPath(network, link.from(), link.to());
			link = link.withRoute(map.routeForVl(path));
			bw = bw.withVl(link);
		}
		i++;
	}
	i = 0;
	for (auto &link : vls) {
		if (link.getId() != brokenmap[i].id) {
			throw logic_error("Несоответствие индексов вк с картой вк");
		}
		if (brokenmap[i].brokenHeavier && !brokenmap[i].broken) {
			auto network = map.graphForVl(link, bandwidth);
			auto path = searchPath(network, link.from(), link.to());
			link = link.withRoute(map.routeForVl(path));
			bw = bw.withVl(link);
		}
		i++;
	}
	return vls;
}

vector<uint32_t> Algorithm::searchPath(Graph network, uint32_t from, uint32_t to) const
{
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
	while (path[v] != v) {
		route.push_back(v);
		v = path[v];
	}
	route.push_back(from);
	return route;
}

BandwidthInfo Algorithm::takeOffBroken(BandwidthInfo bdw)
{
	int i = 0;
	for (auto &link : links) {
		if (link.getId() != brokenmap[i].id) {
			throw logic_error("Несоответствие индексов вк с картой вк");
		}
		if (brokenmap[i].broken) {
			bdw = bdw.withoutVlPart(link, brokenmap[i].sedge);
		}
		i++;
	}
	return bdw;
}

BandwidthInfo Algorithm::takeOffHeavy(BandwidthInfo bdw)
{
	int i = 0;
	for (auto &link : links) {
		if (link.getId() != brokenmap[i].id) {
			throw logic_error("Несоответствие индексов вк с картой вк");
		}
		if (brokenmap[i].brokenHeavier) {
			bdw = bdw.withoutVl(link);
		}
		i++;
	}
	return bdw;
}
