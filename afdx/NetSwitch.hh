#pragma once

#include <map>
#include "NetLink.hh"

class NetSwitch {
public:
	NetSwitch(uint32_t id);

	NetSwitch withLink(const NetLink &link) const;
	NetSwitch withoutLink(const NetLink &link) const;
	NetSwitch withoutPort(uint32_t port) const;

	void log() const;
private:
	NetSwitch(uint32_t id, const std::map<uint32_t, NetLink> &links);
	std::map<uint32_t, NetLink>
		addLink(std::map<uint32_t, NetLink> prev, const NetLink &link) const;
	std::map<uint32_t, NetLink>
		removeLink(std::map<uint32_t, NetLink> prev, uint32_t port) const;

	uint32_t id;
	const std::map<uint32_t, NetLink> links;
};
