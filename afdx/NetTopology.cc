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
		&& linksAmount() == info.links;
}

uint32_t NetTopology::linksAmount() const
{
	uint32_t links = 0;
	for (const auto &swtch : switches) {
		links += swtch.linksAmount();
	}
	for (const auto &host : hosts) {
		links += host.linksAmount();
	}
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
	switches[link.sender()] = switches[link.sender()].withLink(link);
	return *this;
}

NetTopology &NetTopology::withoutLink(const NetLink &link)
{
	switches[link.sender()] = switches[link.sender()].withoutLink(link);
	return *this;
}
