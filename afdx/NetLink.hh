#pragma once
#include <stdint.h>

class NetLink {
public:
	NetLink(uint32_t sender, uint32_t sport, uint32_t receiver, uint32_t rport, double bw);

	uint32_t port(uint32_t sw) const;
	uint32_t from() const;
	uint32_t to() const;

	void log() const;
private:
	uint32_t sender;
	uint32_t sport;
	uint32_t receiver;
	uint32_t rport;
	double bandwidth [[maybe_unused]];
};
