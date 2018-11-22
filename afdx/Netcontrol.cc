#include "Netcontrol.hh"
#include "Common.hh"
#include "Controller.hh"

REGISTER_APPLICATION(Netcontrol, {"controller", ""})

using namespace runos;

void Netcontrol::init(Loader *loader, const Config &config)
{
    	Controller* ctrl = Controller::get(loader);
    	LOG(INFO) << "Netcontrol init";
    	auto table = ctrl->getTable("netcontrol");

    	swmanager = SwitchManager::get(loader);
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
        LOG(INFO) << "Switch " << sw->dpid() << " up";
        // TODO topo = topo.withSwitch();

}

void Netcontrol::switchBroken(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->dpid() << " down";
}
