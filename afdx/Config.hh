#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "Vl.hh"

class Config
{
public:
	Config(const std::string &file);
	VlSet dataflows();

private:
	boost::property_tree::ptree tree;
};
