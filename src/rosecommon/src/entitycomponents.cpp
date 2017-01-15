#include "entityComponents.h"

uint16_t getId(Entity entity) {
    return entity.component<BasicInfo>()->id_;
}

std::string &getName(Entity entity) {
    return entity.component<BasicInfo>()->name_;
}

std::shared_ptr<CMapClient> getClient(Entity entity) {
    if (!entity.component<SocketConnector>())
        return nullptr;
    return entity.component<SocketConnector>()->client_.lock();
}

