#pragma once
#include "Application.hh"
#include "Loader.hh"


class Netcontrol : public Application
{
	SIMPLE_APPLICATION(Netcontrol, "netcontrol")

public:
    void init(Loader* loader, const Config& config) override;

private:

};
