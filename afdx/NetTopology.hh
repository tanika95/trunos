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
	NetTopology(
		const std::map<uint32_t, NetHost> &hosts,
		const std::map<uint32_t, NetSwitch> &switches
	);

	std::shared_ptr<NetTopology> withSwitch(uint32_t id) const;
	std::shared_ptr<NetTopology> withoutSwitch(uint32_t id) const;
	std::shared_ptr<NetTopology> withHost(uint32_t id) const;
	std::shared_ptr<NetTopology> withoutHost(uint32_t id) const;
	std::shared_ptr<NetTopology> withLink(const NetLink &link) const;
	std::shared_ptr<NetTopology> withoutLink(const NetLink &link) const;

	void log() const;

private:
	std::map<uint32_t, NetSwitch> addSwitch(std::map<uint32_t, NetSwitch> prev,
		uint32_t id) const;
	std::map<uint32_t, NetSwitch> removeSwitch(std::map<uint32_t, NetSwitch> prev,
		uint32_t id) const;

	const std::map<uint32_t, NetHost> hosts;
	const std::map<uint32_t, NetSwitch> switches;
};
