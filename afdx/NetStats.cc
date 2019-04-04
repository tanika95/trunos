#include "NetStats.hh"
#include <map>
#include <utility>
#include "Common.hh"
#include "BandwidthInfo.hh"

using namespace std;

NetStats::NetStats(const VlSet &vls)
	: vls(vls)
{}

NetStats &NetStats::logVlinks()
{
	for (const auto &vl : vls) {
                vl.log();
        }
	return *this;
}

NetStats &NetStats::logSwtches()
{
	LOG(INFO) << "Switch usage NetStats";
	map<uint32_t, uint32_t> usage;
	for (const auto &vl : vls) {
                const auto switches = vl.switches();
		for (const auto &sw : switches) {
			if (usage.find(sw) != usage.end()) {
				usage[sw] += 1;
			} else {
				usage[sw] = 1;
			}
		}
        }
	for (const auto &sw : usage) {
		LOG(INFO) << 's' << sw.first << ' ' << sw.second;
	}
	return *this;
}

NetStats &NetStats::logLinks()
{
	LOG(INFO) << "Links usage NetStats";
	map<LinkInfo, uint32_t> usage;
	for (const auto &vl : vls) {
                const auto sw = vl.switches();
		for (uint32_t i = 0; i < sw.size() - 1; i++) {
			auto from = sw[i] < sw[i + 1] ? sw[i] : sw[i + 1];
			auto to = sw[i] > sw[i + 1] ? sw[i] : sw[i + 1];
			auto pair = make_pair(from, to);
			if (usage.find(pair) != usage.end()) {
				usage[pair] += 1;
			} else {
				usage[pair] = 1;
			}
		}
        }
	for (const auto &l : usage) {
		LOG(INFO) << "link "
			<< l.first.first << '-' << l.first.second
			<< ' ' << l.second;
	}
	return *this;
}
