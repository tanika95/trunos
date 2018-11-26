#pragma once

#include <map>
#include "NetLink.hh"

class NetHost {
public:
	NetHost(uint32_t id);

	NetHost withLink(uint32_t toid) const;
	NetHost withoutLink(uint32_t toid) const;
private:
	NetHost(uint32_t id, const std::vector<uint32_t> &switches);
	std::vector<uint32_t> addLink(const std::vector<uint32_t> &prev, uint32_t toid) const;
	std::vector<uint32_t> removeLink(const std::vector<uint32_t> &prev, uint32_t toid) const;

	const std::vector<uint32_t> switches;
};
