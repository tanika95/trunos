#include "Netcontrol.hh"

#include <unistd.h>
#include "Common.hh"
#include "Controller.hh"

#include "Algorithm.hh"
#include "NetStats.hh"


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
	net = Network(table);
        for (int i = 0; i < vlconf.info().hosts; i++) {
                topo = topo.withHost(i + 1);
        }

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

        connect(
                lmanager, SIGNAL(linkBroken(switch_and_port, switch_and_port)),
                this, SLOT(linkBroken(switch_and_port, switch_and_port))
        );
}

void Netcontrol::switchDiscovered(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " up";
        topo = topo.withSwitch(sw->id());
	net.withConnection(sw->id(), sw->connection());
	// TODO: это фейк
        if (sw->id() <= vlconf.info().hosts) {
                topo = topo
                        .withLink({sw->id(), 1, sw->id() | HOST_MASK, 1})
                        .withHostLink(sw->id(), sw->id());
                int also = sw->id() - 1;
                if (also == 0) {
                        also = 4;
                }
                topo = topo
                        .withLink({sw->id(), 2, also | HOST_MASK, 2})
                        .withHostLink(also, sw->id());
        }
        if (topo.isFull()) {
                start();
        }
}

void Netcontrol::switchBroken(Switch *sw)
{
        LOG(INFO) << "Switch " << sw->id() << " down";
        topo = topo.withoutSwitch(sw->id());
	net.withoutConnection(sw->id());
	reload();
}

void Netcontrol::linkDiscovered(switch_and_port from, switch_and_port to)
{
        LOG(INFO) << "Link discovered";
        auto bdw = bw.getBandwidth(from.dpid, to.dpid);
        topo = topo
                .withLink({from.dpid, from.port, to.dpid, to.port})
                .withLink({to.dpid, to.port, from.dpid, from.port});
        if (topo.isFull()) {
                start();
        }
}

void Netcontrol::linkBroken(switch_and_port from, switch_and_port to)
{
        LOG(INFO) << "Link broken";
        topo = topo
                .withoutLink({from.dpid, from.port, to.dpid, to.port})
                .withoutLink({to.dpid, to.port, from.dpid, from.port});
	reload();
}

void Netcontrol::start()
{
        //topo.log();
        try {
                vls = Algorithm(vls, topo, bw).initial();
        } catch(const std::exception &e) {
        	LOG(INFO) << "Initial configuration failed: " << e.what();
        	exit(-1);
        }
	net.apply(vls);
        NetStats(vls).logSwtches().logLinks();
	bw = bw.withVlSet(vls);
}

void Netcontrol::reload()
{
        //topo.log();
        try {
                vls = Algorithm(vls, topo, bw).run();
        } catch(const std::exception &e) {
        	LOG(INFO) << "Additional step failed: " << e.what();
        	exit(-1);
        }
	net.apply(vls);
        NetStats(vls).logSwtches().logLinks();
	bw = vlconf.bandwidth().withVlSet(vls);
}
