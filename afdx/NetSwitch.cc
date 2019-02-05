#include "NetSwitch.hh"
#include "Common.hh"

using namespace std;

NetSwitch::NetSwitch(uint32_t id)
	:  id(id)
{}

void NetSwitch::log() const
{
	LOG(INFO) << "------Switch----"<< id << "-----------" ;
	for (const auto &link : links) {
		link.second.log();
	}
}

NetSwitch &NetSwitch::withLink(const NetLink &link)
{
	links.insert({link.port(id), link});
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
