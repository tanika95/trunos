#include "NetHost.hh"

#include <algorithm>
#include <sstream>
#include "Common.hh"

using namespace std;

NetHost::NetHost(uint32_t id)
	:  id(id)
{}

void NetHost::log() const
{
	LOG(INFO) << "------Host----"<< id << "-----------" ;
	ostringstream ss;
	for (const auto &swtch : switches) {
		ss << swtch << ' ';
	}
	LOG(INFO) << "Connected to: " << ss.str();

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
