#pragma once

#include <map.h>
#include "NetLink.hh"

class NetSwitch {
public:
	NetSwitch(uint32_t id);

	NetSwitch withLink(const NetLink &link);
	NetSwitch withoutLink(const NetLink &link);
private:
	NetSwitch(uint32_t id, const std::map<uint32_t, NetLink> &links, const NetLink &link);

	std::map<uint32_t, NetLink> links;
};
