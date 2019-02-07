#include "VlConfig.hh"

#include <vector>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include "Common.h"
#include "Sla.hh"

using namespace std;
using namespace boost::property_tree;


VlConfig::VlConfig(const string &file)
{
	LOG(INFO) << "Open VlConfig ";
	read_xml(file, tree);
}

VlSet VlConfig::dataflows() const
{
	VlSet vls;
	for (const auto &vl : tree.get_child("vls")) {
        	auto id = vl.second.get<uint32_t>("id");
		auto sender = vl.second.get<uint32_t>("sender");
		auto reciever = vl.second.get<uint32_t>("reciever");
		auto bag = vl.second.get<uint32_t>("bag");
	 	auto lmax = vl.second.get<uint32_t>("lmax");
		auto jitt = vl.second.get<double>("jitter");
		vls.push_back(Vl(id, sender, reciever, Sla(bag, lmax, jitt)));
	}
	return vls;
}

BandwidthInfo VlConfig::banwidth() const
{
	map<LinkInfo, double> bdw;
	for (const auto &l : tree.get_child("links")) {
		auto sender = l.second.get<uint32_t>("sender");
		auto reciever = l.second.get<uint32_t>("reciever");
		auto bw = l.second.get<double>("bw");
		bdw.insert({{sender, receiver}, NetHost(id)});
	}
	return bdw;
}
