#pragma once
#include "Sla.hh"

class Vl {
public:
	Vl(uint32_t vid, uint32_t sid, uint32_t rid, Sla params);
	Vl();

private:
	uint32_t id;
	uint32_t sender;
	uint32_t receiver;
	Sla params;
};

typedef std::vector<Vl> VlSet;
