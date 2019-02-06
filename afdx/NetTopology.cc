#include "NetTopology.hh"
#include "Common.hh"

using namespace std;

NetTopology::NetTopology()
{}

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

}

NetTopology &NetTopology::withoutLink(const NetLink &link)
{

}
