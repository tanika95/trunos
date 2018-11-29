#include "NetSwitch.hh"
#include "Common.hh"

using namespace std;

NetSwitch::NetSwitch(uint32_t id)
	:  id(id)
{}

NetSwitch::NetSwitch(uint32_t id, const map<uint32_t, NetLink> &links)
	:  id(id), links(links)
{
}

void NetSwitch::log() const
{
	LOG(INFO) << "------Switch----"<< id << "-----------" ;
	for (const auto &link : links) {
		link.second.log();
	}
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

map<uint32_t, NetLink> NetSwitch::addLink(map<uint32_t, NetLink> prev, const NetLink &link) const
{
	prev.insert({link.port(id), link});
	return prev;
}

map<uint32_t, NetLink> NetSwitch::removeLink(map<uint32_t, NetLink> prev, uint32_t port) const
{
	prev.erase(port);
	return prev;
}
