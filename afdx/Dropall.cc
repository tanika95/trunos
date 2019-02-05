#include "Dropall.hh"

#include <memory>
#include <mutex>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/thread.hpp>

#include "api/Packet.hh"
#include "api/PacketMissHandler.hh"
#include "api/TraceablePacket.hh"
#include "types/ethaddr.hh"
#include "oxm/openflow_basic.hh"

#include "Topology.hh"
#include "SwitchConnection.hh"
#include "Flow.hh"
#include "STP.hh"
#include "Maple.hh"
#include "Decision.hh"
#include "Common.hh"


REGISTER_APPLICATION(Dropall, {"maple", ""})

using namespace runos;

void Dropall::init(Loader *loader, const Config &)
{
    auto maple = Maple::get(loader);

    maple->registerHandler("dropall",
        [=](Packet& pkt, FlowPtr, Decision decision) {
                return decision.drop();
    });
}
