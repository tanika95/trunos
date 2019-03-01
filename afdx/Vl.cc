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

Vl &Vl::withRoute(const vector<VlSwitch> &r)
{
	route = r;
	return *this;
}
