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
	if (link.to() & HOST_MASK) {
		hosts[link.to() ^ HOST_MASK] = hosts[link.to() ^ HOST_MASK].withLink(link.from());
	} else {
		switches[link.to()] = switches[link.to()].withLink(link);
	}
	return *this;
}

NetTopology &NetTopology::withoutLink(const NetLink &link)
{
	switches[link.from()] = switches[link.from()].withoutLink(link);
	if (link.to() & HOST_MASK) {
		hosts[link.to() ^ HOST_MASK] = hosts[link.to() ^ HOST_MASK].withoutLink(link.from());
	} else {
		switches[link.to()] = switches[link.to()].withoutLink(link);
	}
	return *this;
}

Graph NetTopology::graphForVL(const Vl &vl, const BandwidthInfo &bws) const
{
	vector<Edge> edgs;
	vector<double> bdws;
	for (const auto &swtch : switches) {
		const auto links = swtch.second.getLinks();
		for (const auto &link : links) {
			auto bw_left = bws.getBanwidth(link.second.from(), link.second.to());
			if (vl.bw() <= bw_left) {
				edgs.push_back(Edge(link.second.from(), link.second.to()));
				bdws.push_back(bw_left);
			}
		}
	}
	for (const auto &host : hosts) {
		const auto links = host.second.getLinks();
		const auto id = host.second.getId();
		for (const auto &link : links) {
			auto bw_left = bws.getBanwidth(id, link);
			if (vl.bw() <= bw_left) {
				edgs.push_back(Edge(id, link));
				bdws.push_back(bw_left);
			}
		}
	}

	return Graph(
		&edgs[0], &edgs[edgs.size() - 1],
		bdws.data(),
		switches.size() + hosts.size()
	);
}
