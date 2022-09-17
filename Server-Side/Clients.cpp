//headers
#include "Clients.h"
/// <summary>
/// 
/// </summary>
Clients::Clients() {

}
/// <summary>
/// 
/// </summary>
/// <param name="clientChannel"></param>
/// <param name="clientIp"></param>
/// <param name="clientMacId"></param>
/// <param name="clientPort"></param>
Clients::Clients(std::string clientChannel, std::string clientIp, std::string clientMacId, int clientPort) {
	this->clientChannel = clientChannel;
	this->clientIp = clientIp;
	this->clientMacId = clientMacId;
	this->clientPort = clientPort;
}
/// <summary>
/// 
/// </summary>
/// <param name="clientChannel"></param>
void Clients::setClientChannel(std::string clientChannel) {
	this->clientChannel = clientChannel;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Clients::getClientChannel() {
	return this->clientChannel;
}
/// <summary>
/// 
/// </summary>
/// <param name="clientIp"></param>
void Clients::setClientIp(std::string clientIp) {
	this->clientIp = clientIp;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Clients::getClientIp() {
	return this->clientIp;
}
/// <summary>
/// 
/// </summary>
/// <param name="clientMacId"></param>
void Clients::setClientMacId(std::string clientMacId) {
	this->clientMacId = clientMacId;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Clients::getClientMacId() {
	return this->clientMacId;
}
/// <summary>
/// 
/// </summary>
/// <param name="clientPort"></param>
void Clients::setClientPort(int clientPort) {
	this->clientPort = clientPort;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
int Clients::getClientPort() {
	return this->clientPort;
}
