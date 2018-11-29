#include "NetTopology.hh"
#include "Common.hh"

using namespace std;

NetTopology::NetTopology()
{}

NetTopology::NetTopology(
	const map<uint32_t, NetHost> &hosts,
	const map<uint32_t, NetSwitch> &switches
) : hosts(hosts), switches(switches)
{}

void NetTopology::log() const
{
	LOG(INFO) << "Network";
	for (const auto &swtch : switches) {
		swtch.second.log();
	}
}

shared_ptr<NetTopology> NetTopology::withSwitch(uint32_t id) const
{
	return make_shared<NetTopology>(hosts, addSwitch(switches, id));
}

shared_ptr<NetTopology> NetTopology::withoutSwitch(uint32_t id) const
{
	return make_shared<NetTopology>(hosts, removeSwitch(switches, id));
}

shared_ptr<NetTopology> NetTopology::withHost(uint32_t id) const
{

}

shared_ptr<NetTopology> NetTopology::withoutHost(uint32_t id) const
{

}

shared_ptr<NetTopology> NetTopology::withLink(const NetLink &link) const
{

}

shared_ptr<NetTopology> NetTopology::withoutLink(const NetLink &link) const
{

}


map<uint32_t, NetSwitch> NetTopology::addSwitch(map<uint32_t, NetSwitch> prev, uint32_t id) const
{
	prev.insert({id, NetSwitch(id)});
	return prev;
}

map<uint32_t, NetSwitch> NetTopology::removeSwitch(map<uint32_t, NetSwitch> prev, uint32_t id) const
{
	prev.erase(id);
	return prev;
}
