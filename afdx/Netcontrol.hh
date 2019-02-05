#pragma once
#include "Application.hh"

#include <memory>
#include "Loader.hh"
#include "Switch.hh"

#include "NetTopology.hh"


class Netcontrol : public Application
{
	SIMPLE_APPLICATION(Netcontrol, "netcontrol")

public:
	void init(Loader* loader, const Config& config) override;

private:
	void switchDiscovered(Switch *sw);
	void switchBroken(Switch *sw);

	NetTopology topo;

};
