// gaurd to prevent including file many time.
#pragma once

// headers
#include <string>

// class prototype
class Clients
{
	public:
		Clients();
		Clients(std::string clientChannel , std::string clientIp , std::string clientMacId, int clientPort);
		void setClientChannel(std::string clientChannel);
		std::string getClientChannel();
		void setClientIp(std::string clientChannel);
		std::string getClientIp();
		void setClientMacId(std::string clientChannel);
		std::string getClientMacId();
		void setClientPort(int clientPort);
		int getClientPort();

	protected:

	private:
		std::string clientChannel;
		int clientPort;
		std::string clientIp;
		std::string clientMacId;

};

