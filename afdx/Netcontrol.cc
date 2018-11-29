#include "Netcontrol.hh"
#include "Common.hh"
#include "Controller.hh"

REGISTER_APPLICATION(Netcontrol, {"controller", "switch-manager", "link-discovery", ""})

using namespace runos;

void Netcontrol::init(Loader *loader, const Config &config)
{
    	Controller* ctrl = Controller::get(loader);
    	LOG(INFO) << "Netcontrol init";
    	auto table = ctrl->getTable("netcontrol");

    	auto swmanager = SwitchManager::get(loader);
    	connect(
            	swmanager, &SwitchManager::switchDiscovered,
            	this, &Netcontrol::switchDiscovered
    	);
    	connect(
            	swmanager, &SwitchManager::switchDown,
            	this, &Netcontrol::switchBroken
    	);
}

void Netcontrol::switchDiscovered(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " up";
        // TODO topo = topo.withSwitch();

}

void Netcontrol::switchBroken(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " down";
}
