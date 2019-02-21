#pragma once
#include "Application.hh"

#include <memory>
#include "LinkDiscovery.hh"
#include "Loader.hh"
#include "Switch.hh"

#include "BandwidthInfo.hh"
#include "NetTopology.hh"
#include "Vl.hh"
#include "VlConfig.hh"


class Netcontrol : public Application
{
	Q_OBJECT
	SIMPLE_APPLICATION(Netcontrol, "netcontrol")

public:
	Netcontrol();
	void init(Loader* loader, const Config& config) override;

private:
	void start();

	void switchDiscovered(Switch *sw);
	void switchBroken(Switch *sw);

protected slots:
	void linkDiscovered(switch_and_port from, switch_and_port to);

private:

	VlSet vls;
	VlConfig vlconf;
	NetTopology topo;
	BandwidthInfo bw;

};
