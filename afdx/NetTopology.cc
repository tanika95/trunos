#include "NetTopology.hh"
#include "Common.hh"

using namespace std;

NetTopology::NetTopology(const NetInfo &info)
	: info(info)
{
}

bool NetTopology::isFull() const
{
	return switches.size() == info.switches
		&& hosts.size() == info.hosts
		&& linksAmount() == 2 * info.links;
}

uint32_t NetTopology::linksAmount() const
{
	uint32_t links = 0;
	for (const auto &swtch : switches) {
		links += swtch.second.linksAmount();
	}
	for (const auto &host : hosts) {
		links += host.second.linksAmount();
	}
	return links;
}

void NetTopology::log() const
{
	LOG(INFO) << "Network";
	for (const auto &swtch : switches) {
		swtch.second.log();
	}
	for (const auto &host : hosts) {
		host.second.log();
	}
}

NetTopology &NetTopology::withSwitch(uint32_t id)
{
	switches.insert({id, NetSwitch(id)});
	return *this;
}

NetTopology &NetTopology::withoutSwitch(uint32_t id)
{
	switches.erase(id);
	return *this;
}

NetTopology &NetTopology::withHost(uint32_t id)
{
	hosts.insert({id, NetHost(id)});
	return *this;
}

NetTopology &NetTopology::withoutHost(uint32_t id)
{
	hosts.erase(id);
	return *this;
}

NetTopology &NetTopology::withLink(const NetLink &link)
{
	switches[link.from()] = switches[link.from()].withLink(link);
	return *this;
}

NetTopology &NetTopology::withoutLink(const NetLink &link)
{
	switches[link.from()] = switches[link.from()].withoutLink(link);
	return *this;
}

NetTopology &NetTopology::withHostLink(uint32_t hid, uint32_t sid)
{
	hosts[hid] = hosts[hid].withLink(sid);
	return *this;
}

NetTopology &NetTopology::withoutHostLink(uint32_t hid, uint32_t sid)
{
	hosts[hid] = hosts[hid].withoutLink(sid);
	return *this;
}

Graph NetTopology::graphForVl(const Vl &vl, const BandwidthInfo &bws) const
{
	vector<Edge> edgs;
	vector<double> bdws;
	for (const auto &swtch : switches) {
		const auto links = swtch.second.getLinks();
		for (const auto &link : links) {
			auto bw_left = bws.getBandwidth(link.second.from(), link.second.to());
			if (vl.bw() <= bw_left) {
				edgs.push_back(Edge(link.second.from(), link.second.to()));
				bdws.push_back(bw_left);
			}
		}
	}
	vector<uint32_t> ends = {vl.from() ^ HOST_MASK, vl.to() ^ HOST_MASK};
	for (const auto &i : ends) {
		auto host = hosts.at(i);
		const auto links = host.getLinks();
		for (const auto &link : links) {
			edgs.push_back(Edge(host.getId(), link));
			bdws.push_back(0.0);
		}
	}

	return Graph(
		&edgs[0], &edgs[edgs.size() - 1],
		bdws.data(),
		switches.size() + hosts.size()
	);
}

vector<VlSwitch> NetTopology::routeForVl(const vector<uint32_t> &route) const
{
	vector<VlSwitch> result;
	auto end = route.size() - 1;
	if (!(route[end] & HOST_MASK)) {
		result.push_back(switches.at(end).routeSwitch(route[end - 1], route[end - 1]));
	}
	for (uint32_t i = route.size() - 2; i > 0; i--) {
		result.push_back(
			switches.at(route[i]).routeSwitch(route[i + 1], route[i - 1])
		);
	}
	return result;
}

vector<VlState> NetTopology::brokenVls(const VlSet &vls) const
{
	vector<VlState> states;
	for (const auto &vl: vls) {
		states.push_back(vl.state(switches));
	}
	return states;
}
