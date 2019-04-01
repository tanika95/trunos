#include "Network.hh"
#include "Common.hh"
#include "Timer.hh"

using namespace std;
using namespace of13;

Network::Network()
{}

void Network::apply(const VlSet &vls)
{
	LOG(INFO) << "Applying VlSet";
	Timer timer("Apply changes");
	for (const auto vl : vls) {
		const auto settings = vl.getSettings();
		const auto rmeter = MeterMod(0, OFPMC_DELETE,
			OFPMF_PKTPS || OFPMF_BURST, vl.getId());
		for (const auto sw : settings.remove) {
			// TODO: connections - map switchей надо добавить если он уже офф
			connections[sw.id]->connection()->send(fm);
			connections[sw.id]->connection()->send(rmeter);
		}
		const auto metermod = addMeter(settings.params, vl.getId());
		for (const auto sw : settings.add) {
			auto flowmod = addFlow(sw, vl.getId());
			connections[sw.id]->connection()->send(metermod);
			connections[sw.id]->connection()->send(flowmod);
		}

	}
}

MeterMod Network::addMeter(const Sla &params, uint32_t id)
{
	MeterMod meter(0, OFPMC_ADD, OFPMF_PKTPS || OFPMF_BURST, id);
	MeterBandDrop *band = new MeterBandDrop(params.rate(), params.burstSize());
	meter.add_band(band);
	return meter;
}

FlowMod Network::addFlow(const VlSwitch &sw, uint32_t id)
{
	FlowMod fm;
        fm.command(OFPFC_ADD);
        fm.buffer_id(OFP_NO_BUFFER);
	fm.table_id(table);
	auto in_port = new InPort(sw.src);
	fm.add_oxm_field(in_port);
        auto vlan = new VLANVid(id);
	fm.add_oxm_field(vlan);

	ApplyActions port_act;
	auto out = new OutputAction(sw.rport, WTF? DENIS);
	act.add_action(out);
        fm.add_instruction(port_act);

	Meter meter_act(id);
	fm.add_instruction(meter_act);

        return fm;
}
