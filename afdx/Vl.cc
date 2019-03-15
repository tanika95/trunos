#include "Vl.hh"

#include <sstream>
#include "Common.hh"
#include "NetHost.hh"

using namespace std;

Vl::Vl(uint32_t vid, uint32_t sid, uint32_t rid, Sla params)
	: id(vid), sender(sid), receiver(rid), params(params)
{
}

Vl::Vl()
{
}

void Vl::log() const
{
	LOG(INFO) << "vl " << id << " bw " << bw();
	ostringstream ss;
	ss <<'h' << sender << ' ';
	for (const auto &sw : route) {
		ss << sw.id << ' ';
	}
	ss << 'h' << receiver;
	LOG(INFO) << "Route: " << ss.str();
}

uint32_t Vl::getId() const
{
	return id;
}

double Vl::bw() const
{
	return params.rate();
}

uint32_t Vl::from() const
{
	return sender | HOST_MASK;
}

uint32_t Vl::to() const
{
	return receiver | HOST_MASK;
}

VlState Vl::state(const map<uint32_t, NetSwitch> &switches) const
{
	if (switches.find(route[0].id) == switches.end()
			|| !switches.at(route[0].id).linkOn(from())) {
		return VlState(id, true, from());
	}
	for (uint32_t i = 0; i < route.size() - 1; i++) {
		if (switches.find(route[i].id) != switches.end()) {
			const auto sw = switches.at(route[i].id);
			if (!sw.portOn(route[i].rport)) {
				return VlState(id, true, route[i].id);
			}
		} else {
			return VlState(id, true, route[i - 1].id);
		}
	}
	return VlState(id, false);
}

vector<uint32_t> Vl::switches() const
{
	vector<uint32_t> sw;
	for (const auto &r : route) {
		sw.push_back(r.id);
	}
	return sw;
}

Vl &Vl::withRoute(const vector<VlSwitch> &r)
{
	route = r;
	return *this;
}

Vl &Vl::withChangedRoute(const vector<VlSwitch> &new_route, uint32_t edge)
{
	int i = 0;
	for (const auto &r: route) {
		if (r.id == edge) {
			break;
		}
		i++;
	}
	route.erase(route.begin() + i + 1, route.end());
	route.insert(route.end(), new_route.begin() + 1, new_route.end());
	return *this;
}
