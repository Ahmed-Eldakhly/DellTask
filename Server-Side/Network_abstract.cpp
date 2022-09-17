// headers
#include "Network_abstract.h"
/// <summary>
/// 
/// </summary>
Network_abstract::Network_abstract() {

}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Network_abstract::getPayload() {
    return this->payload;
}

/// <summary>
/// 
/// </summary>
/// <param name="payload"></param>
void Network_abstract::setPayload(std::string payload) {
    this->payload = payload;
}
