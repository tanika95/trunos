#include "NetSwitch.hh"
#include "Common.hh"

using namespace std;

NetSwitch::NetSwitch(uint32_t id)
	:  id(id)
{}

NetSwitch::NetSwitch()
	:  NetSwitch(0)
{}

void NetSwitch::log() const
{
	LOG(INFO) << "------Switch----"<< id << "-----------" ;
	for (const auto &link : links) {
		link.second.log();
	}
}

uint32_t NetSwitch::linksAmount() const
{
	return links.size();
}

map<uint32_t, NetLink> NetSwitch::getLinks() const
{
	return links;
}

VlSwitch NetSwitch::routeSwitch(uint32_t from, uint32_t to) const
{
	return VlSwitch(id, links.at(from).port(id), links.at(to).port(id));
}

bool NetSwitch::portOn(uint32_t port) const
{
	if (active_ports.find(port) != active_ports.end()) {
		return true;
	} else {
		return false;
	}
}

bool NetSwitch::linkOn(uint32_t to) const
{
	if (links.at(to) != links.end()) {
		return true;
	} else {
		return false;
	}
}

NetSwitch &NetSwitch::withLink(const NetLink &link)
{
	links.insert({link.to(), link});
	active_ports.insert({link.port(id), link.to()});
	return *this;
}

NetSwitch &NetSwitch::withoutLink(const NetLink &link)
{
	links.erase(link.to());
	active_ports.erase(link.port(id));
	return *this;
}

NetSwitch &NetSwitch::withoutPort(uint32_t port)
{
	links.erase(active_ports.at(port));
	active_ports.erase(port);
	return *this;
}
