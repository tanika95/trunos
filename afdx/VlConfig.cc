#include "VlConfig.hh"

#include <vector>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include "Common.hh"
#include "Sla.hh"

using namespace std;
using namespace boost::property_tree;

bool vlbwsort (Vl vl1, Vl vl2) { return vl1.bw() > vl2.bw(); }

VlConfig::VlConfig(const string &file)
{
	LOG(INFO) << "Open VlConfig ";
	read_xml(file, tree);
}

VlSet VlConfig::dataflows() const
{
	VlSet vls;
	auto conf = tree.get_child("config");
	for (const auto &vl : conf.get_child("vls")) {
        	auto id = vl.second.get<uint32_t>("id");
		auto sender = vl.second.get<uint32_t>("sender");
		auto receiver = vl.second.get<uint32_t>("receiver");
		auto bag = vl.second.get<uint32_t>("bag");
	 	auto lmax = vl.second.get<uint32_t>("lmax");
		auto jitt = vl.second.get<double>("jitter");
		vls.push_back(Vl(id, sender, receiver, Sla(bag, lmax, jitt)));
	}
	sort(vls.begin(), vls.end(), vlbwsort);
	return vls;
}

NetInfo VlConfig::info() const
{
	NetInfo info;
	auto conf = tree.get_child("config");
        info.switches = conf.get_child("switches").get_value<uint32_t>();
	info.links = conf.get_child("links").get_value<uint32_t>();
	info.hosts = conf.get_child("hosts").get_value<uint32_t>();
	return info;
}

BandwidthInfo VlConfig::bandwidth() const
{
	map<LinkInfo, double> bdw;
	auto conf = tree.get_child("config");
	for (const auto &l : conf.get_child("linksinfo")) {
		auto sender = l.second.get<uint32_t>("sender");
		auto receiver = l.second.get<uint32_t>("receiver");
		auto bw = l.second.get<double>("bw");
		bdw.insert({{sender, receiver}, bw});
		bdw.insert({{receiver, sender}, bw});
	}
	auto def = conf.get_child("default_bw").get_value<double>();
	return BandwidthInfo(bdw, def);
}
