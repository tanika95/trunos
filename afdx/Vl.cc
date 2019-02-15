#include "Vl.hh"

using namespace std;

Vl::Vl(uint32_t vid, uint32_t sid, uint32_t rid, Sla params)
	: id(vid), sender(sid), receiver(rid), params(params)
{
}

Vl::Vl()
{
}

double Vl::bw() const
{
	return params.rate();
}

uint32_t Vl::from() const
{
	// TODO : host mask
	return sender;
}

uint32_t Vl::to() const
{
	// TODO : host mask
	return receiver;
}
