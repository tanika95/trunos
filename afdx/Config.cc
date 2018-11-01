#include "Config.hh"

#include <vector>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include "Sla.hh"

using namespace std;
using namespace boost::property_tree;


Config::Config(const string &file)
{
	LOG(INFO) << "Open config ";
	read_xml(file, tree);
}

VlSet Config::dataflows()
{
	VlSet vls;
	for (const auto &vl : tree.get_child("links")) {
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
