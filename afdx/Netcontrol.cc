#include "Netcontrol.hh"

#include <unistd.h>
#include "Common.hh"
#include "Controller.hh"

#include "Algorithm.hh"


REGISTER_APPLICATION(Netcontrol, {"controller", "switch-manager", "link-discovery", ""})

using namespace runos;
using namespace std;

Netcontrol::Netcontrol()
        : vlconf(VlConfig("/home/tanyaerm/cs/disser/vlsdn/netc.xml")),
                topo(vlconf.info()), bw(vlconf.bandwidth())
{
        vls = vlconf.dataflows();
}

void Netcontrol::init(Loader *loader, const Config &config)
{
    	Controller* ctrl = Controller::get(loader);
    	LOG(INFO) << "Netcontrol init";
    	auto table = ctrl->getTable("netcontrol");
        topo = topo.withHost(1).withHost(2).withHost(3).withHost(4);

    	auto swmanager = SwitchManager::get(loader);
    	connect(
            	swmanager, &SwitchManager::switchDiscovered,
            	this, &Netcontrol::switchDiscovered
    	);
    	connect(
            	swmanager, &SwitchManager::switchDown,
            	this, &Netcontrol::switchBroken
    	);

        auto lmanager = ILinkDiscovery::get(loader);
        connect(
                lmanager, SIGNAL(linkDiscovered(switch_and_port, switch_and_port)),
                this, SLOT(linkDiscovered(switch_and_port, switch_and_port))
        );
}

void Netcontrol::switchDiscovered(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " up";
        topo = topo.withSwitch(sw->id());
        // TODO: это фейк
        topo = topo
                .withLink({sw->id(), 0, sw->id() | HOST_MASK, 0, 20})
                .withHostLink(sw->id(), sw->id());
        if (topo.isFull()) {
                start();
        }
}

void Netcontrol::switchBroken(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " down";
        topo = topo.withoutSwitch(sw->id());
}

void Netcontrol::linkDiscovered(switch_and_port from, switch_and_port to)
{
        LOG(INFO) << "Link discovered";
        auto bdw = bw.getBandwidth(from.dpid, to.dpid);
        topo = topo
                .withLink({from.dpid, from.port, to.dpid, to.port, bdw})
                .withLink({to.dpid, to.port, from.dpid, from.port, bdw});
        if (topo.isFull()) {
                start();
        }
}

void Netcontrol::start()
{
        topo.log();
        vls = Algorithm(vls, topo, bw).initial();
}
