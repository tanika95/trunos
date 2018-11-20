#include "NetSwitch.hh"

using namespace std;

NetSwitch::NetSwitch(uint32_t id)
	:  id(id)
{}

NetSwitch::NetSwitch(uint32_t id, const map<uint32_t, NetLink> &links, const NetLink &added)
	:  id(id), links(links)
{
	links[added.port(id)] = added;
}

NetSwitch NetSwitch::withLink(const NetLink &link)
{
	return NetSwitch(id, links, link);
}

NetSwitch NetSwitch::withoutLink(const NetLink &link)
{
	// TODO: как бы это сделать немьютабельно
}
