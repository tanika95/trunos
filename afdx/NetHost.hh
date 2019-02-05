#pragma once

#include <vector>
#include "NetLink.hh"

class NetHost {
public:
	NetHost(uint32_t id);

	NetHost &withLink(uint32_t toid);
	NetHost &withoutLink(uint32_t toid);

	void log() const;

private:
	uint32_t id;
	std::vector<uint32_t> switches;
};
