#pragma once
#include <stdint.h>

class NetLink
{
public:
	NetLink(uint32_t sender, uint32_t sport, uint32_t receiver, uint32_t rport);

	uint32_t port(uint32_t sw) const;

	void log() const;
private:
	uint32_t sender;
	uint32_t sport;
	uint32_t receiver;
	uint32_t rport;
};
