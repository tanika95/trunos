#pragma once
#include "Application.hh"
#include "Loader.hh"

class Dropall : public Application
{
	SIMPLE_APPLICATION(Dropall, "dropall")
public:
	void init(Loader* loader, const Config& config) override;
};
