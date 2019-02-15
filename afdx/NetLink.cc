#include "NetLink.hh"
#include <stdexcept>
#include "Common.hh"

using namespace std;

NetLink::NetLink(uint32_t sender, uint32_t sport, uint32_t receiver, uint32_t rport, double bw)
	: sender(sender), sport(sport), receiver(receiver), rport(rport), bandwidth(bw)
{
}

void NetLink::log() const
{
	cout << "link from " << sender << " to " << receiver << endl;
}

uint32_t NetLink::port(uint32_t sw) const
{
	if (sw == sender) {
		return sport;
	}
	if (sw == receiver) {
		return rport;
	}
	throw logic_error("Неверный id узла для канала");
}

uint32_t NetLink::from() const
{
	return sender;
}

uint32_t NetLink::to() const
{
	return receiver;
}
