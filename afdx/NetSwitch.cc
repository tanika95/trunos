#include "NetSwitch.hh"

using namespace std;

NetSwitch::NetSwitch(uint32_t id)
	:  id(id)
{}

NetSwitch::NetSwitch(uint32_t id, const map<uint32_t, NetLink> &links)
	:  id(id), links(links)
{
	links[added.port(id)] = added;
}

NetSwitch NetSwitch::withLink(const NetLink &link) const
{
	return NetSwitch(id, addLink(links, link));
}

NetSwitch NetSwitch::withoutLink(const NetLink &link) const
{
	const auto port = link.port(id);
	return NetSwitch(id, removeLink(links, port));
}

NetSwitch NetSwitch::withoutPort(uint32_t port) const
{
	return NetSwitch(id, removeLink(links, port));
}

map<uint32_t, NetLink> NetSwitch::addLink(const map<uint32_t, NetLink> &prev,
	const NetLink &link) const
{
	prev[link.port(id)] = link;
	return prev;
}

map<uint32_t, NetLink> NetSwitch::removeLink(const map<uint32_t, NetLink> &prev,
	uint32_t port) const
{
	prev.erase(port);
	return prev;
}
