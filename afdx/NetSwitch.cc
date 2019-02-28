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
	auto link = links.at(to);
	return VlSwitch(id, links.at(to).port(from), links.at(to).port(id));
}

VlSwitch NetSwitch::borderSwitch(uint32_t to) const
{
	auto link = links.at(to);
	return VlSwitch(id, 0, links.at(to).port(id));
}

NetSwitch &NetSwitch::withLink(const NetLink &link)
{
	links.insert({link.to(), link});
	return *this;
}

NetSwitch &NetSwitch::withoutLink(const NetLink &link)
{
	const auto port = link.port(id);
	links.erase(port);
	return *this;
}

NetSwitch &NetSwitch::withoutPort(uint32_t port)
{
	links.erase(port);
	return *this;
}
