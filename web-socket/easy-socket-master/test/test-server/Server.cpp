#include <iostream>
#include <masesk/EasySocket.hpp>
using namespace std;
using namespace masesk;

void handleData(const std::string &data , const std::string& y) {
	cout << "Client sent: " + data << endl;
}

int main() {
	EasySocket socketManager;
	string x;
	socketManager.socketListen("test", 8080, &handleData , x);
	return 0;
}