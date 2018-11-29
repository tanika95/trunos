#pragma once

#include <vector>
#include "NetLink.hh"

class NetHost {
public:
	NetHost(uint32_t id);

	NetHost withLink(uint32_t toid) const;
	NetHost withoutLink(uint32_t toid) const;

	void log() const;
private:
	NetHost(uint32_t id, const std::vector<uint32_t> &switches);
	std::vector<uint32_t> addLink(std::vector<uint32_t> prev, uint32_t toid) const;
	std::vector<uint32_t> removeLink(std::vector<uint32_t> prev, uint32_t toid) const;

	uint32_t id;
	const std::vector<uint32_t> switches;
};
