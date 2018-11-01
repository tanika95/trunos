#include "Netcontrol.hh"
#include "Controller.hh"

REGISTER_APPLICATION(Netcontrol, {"controller", ""})

using namespace runos;

void Netcontrol::init(Loader *loader, const Config &config)
{
    Controller* ctrl = Controller::get(loader);
    LOG(INFO) << "Netcontrol init";
}
