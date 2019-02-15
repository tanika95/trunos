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
	cout << "------Host----"<< id << "-----------" << endl;
	ostringstream ss;
	for (const auto &swtch : switches) {
		ss << swtch << ' ';
	}
	cout << "Connected to: " << ss.str()  << endl;

}

uint32_t NetHost::linksAmount() const
{
	return switches.size();
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
