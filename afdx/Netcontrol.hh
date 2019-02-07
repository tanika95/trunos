#pragma once
#include "Application.hh"

#include <memory>
#include "LinkDiscovery.hh"
#include "Loader.hh"
#include "Switch.hh"

#include "NetTopology.hh"


class Netcontrol : public Application
{
	Q_OBJECT
	SIMPLE_APPLICATION(Netcontrol, "netcontrol")

public:
	void init(Loader* loader, const Config& config) override;

private:
	void switchDiscovered(Switch *sw);
	void switchBroken(Switch *sw);

protected slots:
	void linkDiscovered(switch_and_port from, switch_and_port to);

private:
	std::shared_ptr<NetTopology> topo;

};
