/*
 * Copyright 2015 Applied Research Center for Computer Networks
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
