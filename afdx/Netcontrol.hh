#pragma once
#include "Application.hh"
#include "Loader.hh"
#include "Switch.hh"


class Netcontrol : public Application
{
	SIMPLE_APPLICATION(Netcontrol, "netcontrol")

public:
	void init(Loader* loader, const Config& config) override;

private:
	switchDiscovered(Switch *sw);
	switchBroken(Switch *sw);

};
