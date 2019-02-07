#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "BandwidthInfo.hh"
#include "Vl.hh"

class VlConfig {
public:
	VlConfig(const std::string &file);
	VlSet dataflows() const;
	BandwidthInfo banwidth() const;

private:
	boost::property_tree::ptree tree;
};
