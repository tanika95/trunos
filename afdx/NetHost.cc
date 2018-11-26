#include "NetHost.hh"

#include <algorithm>

using namespace std;

NetHost::NetHost(uint32_t id)
	:  id(id)
{}

NetHost::NetHost(uint32_t id, const vector<uint32_t> &links)
	:  id(id), links(links)
{
	links[added.port(id)] = added;
}

NetHost NetHost::withLink(uint32_t toid) const
{
	return NetHost(id, addLink(switches, toid));
}

NetHost NetHost::withoutLink(uint32_t toid) const
{
	return NetHost(id, removeLink(switches, toid));
}

vector<uint32_t> NetHost::addLink(const vector<uint32_t> &prev, uint32_t toid) const
{
	prev.push_back(toid);
	return prev;
}

vector<uint32_t> NetHost::removeLink(const vector<uint32_t> &prev, uint32_t toid) const
{
	prev.erase(find(prev.begin(), prev.end(), toid));
	return prev;
}
