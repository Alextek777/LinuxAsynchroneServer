#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <exception>
#include <thread>
using namespace std;

class Server{
    std::string ip;
    int port;

    int listening;
    static void handleUser(int clientSocket);
public:
    Server(const std::string& ip, int port);

    void start();
};
