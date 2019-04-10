#include "Network.hh"
#include "Settings.hh"
#include "Timer.hh"

using namespace std;
using namespace of13;
using namespace runos;

Network::Network()
	: table(0)
{}

Network::Network(uint8_t table)
	: table(table)
{}

Network &Network::withConnection(uint32_t id, SwitchConnectionPtr connection)
{
	connections.insert({id, connection});
	return *this;
}

Network &Network::withoutConnection(uint32_t id)
{
	connections.erase(id);
	return *this;
}

void Network::apply(const VlSet &vls)
{
	LOG(INFO) << "Applying VlSet";
	Timer timer("Apply changes");
	for (const auto vl : vls) {
		const auto settings = vl.getSettings();

		const auto rmeter = MeterMod(0, OFPMC_DELETE,
			OFPMF_PKTPS || OFPMF_BURST, vl.getId());
		const auto rflow = deleteFlow(vl.getId());
		for (const auto sw : settings.remove) {
			if (connections.find(sw.id) != connections.end()) {
				connections[sw.id]->send(rflow);
				connections[sw.id]->send(BarrierRequest{});
				connections[sw.id]->send(rmeter);
			}
		}

		const auto metermod = addMeter(settings.params, vl.getId());
		for (const auto sw : settings.add) {
			auto flowmod = addFlow(sw, vl.getId());
			connections[sw.id]->send(metermod);
			connections[sw.id]->send(BarrierRequest{});
			connections[sw.id]->send(flowmod);

		}

	}
}

MeterMod Network::addMeter(const Sla &params, uint32_t id)
{
	MeterMod meter(0, OFPMC_ADD, OFPMF_KBPS | OFPMF_BURST, id);
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
	auto in_port = new InPort(sw.sport);
	fm.add_oxm_field(in_port);
        auto vlan = new VLANVid(id);
	fm.add_oxm_field(vlan);

	ApplyActions port_act;
	auto out = new OutputAction(sw.rport, 0);
	port_act.add_action(out);
        fm.add_instruction(port_act);

	Meter meter_act(id);
	fm.add_instruction(meter_act);

        return fm;
}

FlowMod Network::deleteFlow(uint32_t id)
{
	FlowMod fm;
        fm.command(OFPFC_DELETE);
	fm.table_id(table);
        auto vlan = new VLANVid(id);
	fm.add_oxm_field(vlan);
        return fm;
}
