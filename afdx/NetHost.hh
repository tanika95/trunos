#pragma once

#include <vector>
#include "NetLink.hh"

// TODO: Зависит от размеров сети.
// При неверной оценке неавдекватно вляет на время работы алгоритмов
// можно заменить на + NetTopology::switches.size()
// Но для тестовой среды и так сойдёт
#define HOST_MASK 0x10

class NetHost {
public:
	NetHost(uint32_t id);
	NetHost();

	NetHost &withLink(uint32_t toid);
	NetHost &withoutLink(uint32_t toid);

	uint32_t getId() const;
	void log() const;
	uint32_t linksAmount() const;
	std::vector<uint32_t> getLinks() const;

private:
	uint32_t id;
	std::vector<uint32_t> switches;
};
