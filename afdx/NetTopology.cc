#include "NetTopology.hh"

using namespace std;

NetTopology::NetTopology()
{}

NetTopology::NetTopology(
	const map<uint32_t, NetHost> &hosts,
	const map<uint32_t, NetSwitch> &switches
) : hosts(hosts), switches(switches)
{}

NetTopology NetTopology::withSwitch(uint32_t id) const
{
	return NetTopology(id, addSwitch(switches, id));
}

NetTopology NetTopology::withoutSwitch(uint32_t id) const
{
	return NetTopology(id, removeSwitch(switches, id));
}

NetTopology NetTopology::withHost(uint32_t id) const
{

}

NetTopology NetTopology::withoutHost(uint32_t id) const
{

}

NetTopology NetTopology::withLink(const NetLink &link) const
{

}

NetTopology NetTopology::withoutLink(const NetLink &link) const
{

}


map<uint32_t, NetSwitch> NetTopology::addSwitch(const map<uint32_t, NetSwitch> &prev,
	uint32_t id) const
{
	prev[id] = NetSwitch(id);
	return prev;
}

map<uint32_t, NetLink> NetTopology::removeSwitch(const map<uint32_t, NetSwitch> &prev,
	uint32_t id) const
{
	prev.erase(id);
	return prev;
}
