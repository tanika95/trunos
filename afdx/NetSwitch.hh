#pragma once

#include <map.h>
#include "NetLink.hh"

class NetSwitch {
public:
	NetSwitch(uint32_t id);

	NetSwitch withLink(const NetLink &link) const;
	NetSwitch withoutLink(const NetLink &link) const;
	NetSwitch withoutPort(uint32_t port) const
private:
	NetSwitch(uint32_t id, const std::map<uint32_t, NetLink> &links);
	std::map<uint32_t, NetLink>
		addLink(const std::map<uint32_t, NetLink> &prev, const NetLink &link) const;
	std::map<uint32_t, NetLink>
		removeLink(const std::map<uint32_t, NetLink> &prev, uint32_t port) const;

	const std::map<uint32_t, NetLink> links;
};
