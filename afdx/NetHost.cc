#include "NetHost.hh"

#include <algorithm>
#include "Common.hh"

using namespace std;

NetHost::NetHost(uint32_t id)
	:  id(id)
{}

void NetHost::log() const
{
}

NetHost &NetHost::withLink(uint32_t toid)
{
	switches.push_back(toid);
	return *this;
}

NetHost &NetHost::withoutLink(uint32_t toid)
{
	switches.erase(find(switches.begin(), switches.end(), toid));
	return *this;
}
