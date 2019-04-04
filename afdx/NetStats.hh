#pragma once
#include <stdint.h>
#include "Vl.hh"

class NetStats {
public:
	NetStats(const VlSet &vls);

	NetStats &logVlinks();
	NetStats &logSwtches();
	NetStats &logLinks();
private:
	const VlSet vls;
};
