#include "Vl.hh"

using namespace std;

Vl::Vl(uint32_t vid, uint32_t sid, uint32_t rid, SLA params)
	: id(v_id), sender(sid), receiver(rid), params(params)
{
}

Vl::Vl()
{
}
