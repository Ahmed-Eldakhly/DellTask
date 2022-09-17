//headers
#include "Clients.h"

Clients::Clients() {

}

Clients::Clients(std::string clientChannel, std::string clientIp, std::string clientMacId, int clientPort) {
	this->clientChannel = clientChannel;
	this->clientIp = clientIp;
	this->clientMacId = clientMacId;
	this->clientPort = clientPort;
}

void Clients::setClientChannel(std::string clientChannel) {
	this->clientChannel = clientChannel;
}

std::string Clients::getClientChannel() {
	return this->clientChannel;
}

void Clients::setClientIp(std::string clientIp) {
	this->clientIp = clientIp;
}

std::string Clients::getClientIp() {
	return this->clientIp;
}

void Clients::setClientMacId(std::string clientMacId) {
	this->clientMacId = clientMacId;
}

std::string Clients::getClientMacId() {
	return this->clientMacId;
}

void Clients::setClientPort(int clientPort) {
	this->clientPort = clientPort;
}

int Clients::getClientPort() {
	return this->clientPort;
}
