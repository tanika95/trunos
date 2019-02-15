#pragma once

#include <vector>
#include "NetLink.hh"

#define HOST_MASK 0xf00000

class NetHost {
public:
	NetHost(uint32_t id);
	NetHost();

	NetHost &withLink(uint32_t toid);
	NetHost &withoutLink(uint32_t toid);

	void log() const;
	uint32_t linksAmount() const;

private:
	uint32_t id;
	std::vector<uint32_t> switches;
};
