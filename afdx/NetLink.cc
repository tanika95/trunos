#include "NetLink.hh"
#include <stdexcept>

using namespace std;

NetLink::NetLink(uint32_t sender, uint32_t sport, uint32_t receiver, uint32_t rport)
	: sender(sender), sport(sport), receiver(receiver), rport(rport)
{
}

uint32_t NetLink::port(uint32_t sw)
{
	if (sw == sender) {
		return sport;
	}
	if (sw == receiver) {
		return rport;
	}
	throw logic_error("Неверный id узла для канала");
}
