// headers
#include "Network_abstract.h"

Network_abstract::Network_abstract() {
}

std::string Network_abstract::getPayload() {
    return this->payload;
}

void Network_abstract::setPayload(std::string payload) {
    this->payload = payload;
}
