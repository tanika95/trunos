#pragma once

#include <map>
#include "Host.hh"
#include "NetSwitch.hh"


class NetTopology
{
public:
	NetTopology();
	NetTopology withSwitch(uint32_t id);
	NetTopology withHost(uint32_t host);
private:
	std::map<uint32_t, NetSwitch> switches;
	std::map<uint32_t, Host> hosts;
};
