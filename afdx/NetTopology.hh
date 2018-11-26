#pragma once

#include <map>
#include "NetHost.hh"
#include "NetLink.hh"
#include "NetSwitch.hh"


class NetTopology
{
public:
	NetTopology();
	NetTopology withSwitch(uint32_t id) const;
	NetTopology withoutSwitch(uint32_t id) const;
	NetTopology withHost(uint32_t id) const;
	NetTopology withoutHost(uint32_t id) const;
	NetTopology withLink(const NetLink &link) const;
	NetTopology withoutLink(const NetLink &link) const;

private:
	NetTopology(
		const std::map<uint32_t, Host> &hosts,
		const std::map<uint32_t, NetSwitch> &switches
	);

	std::map<uint32_t, NetSwitch> addSwitch(const std::map<uint32_t, NetSwitch> &prev,
		uint32_t id) const;
	std::map<uint32_t, NetLink> removeSwitch(const map<uint32_t, NetSwitch> &prev,
		uint32_t id) const;

	const std::map<uint32_t, NetSwitch> switches;
	const std::map<uint32_t, Host> hosts;
};
