#pragma once

#include <map>
#include <memory>
#include "NetHost.hh"
#include "NetLink.hh"
#include "NetSwitch.hh"


class NetTopology
{
public:
	NetTopology();

	NetTopology &withSwitch(uint32_t id);
	NetTopology &withoutSwitch(uint32_t id);
	NetTopology &withHost(uint32_t id);
	NetTopology &withoutHost(uint32_t id);
	NetTopology &withLink(const NetLink &link);
	NetTopology &withoutLink(const NetLink &link);

	void log() const;

private:
	std::map<uint32_t, NetHost> hosts;
	std::map<uint32_t, NetSwitch> switches;
};
