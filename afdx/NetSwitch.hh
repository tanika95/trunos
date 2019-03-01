#pragma once

#include <map>
#include "NetLink.hh"
#include "VlSwitch.hh"

class NetSwitch {
public:
	NetSwitch(uint32_t id);
	NetSwitch();

	NetSwitch &withLink(const NetLink &link);
	NetSwitch &withoutLink(const NetLink &link);
	NetSwitch &withoutPort(uint32_t port);

	void log() const;
	uint32_t linksAmount() const;
	std::map<uint32_t, NetLink> getLinks() const;
	VlSwitch routeSwitch(uint32_t from, uint32_t to) const;
	VlSwitch borderSwitch(uint32_t from, uint32_t to) const;

private:
	uint32_t id;
	std::map<uint32_t, NetLink> links;
};
