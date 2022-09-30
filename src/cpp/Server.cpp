#include "../headers/Server.h"

Server::Server(const std::string &ip, int port)
{
    // Create a socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cout << "Can`t create a socket!" << endl;
        throw("Can`t create a socket!");
    }
    // bind a socket to ip and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        cout << "Can`t bind socket!";
        throw("Can`t bind socket!");
    }
}

void Server::start()
{
    while (true)
    {
        // mark the socket for listening in
        if (listen(listening, SOMAXCONN) == -1)
        {
            cout << "Can`t listned!";
            throw("Can`t listned!");
        }
        cout << " Listening " << endl;
        // accept a call
        sockaddr_in client;
        socklen_t clientSize;
        char host[NI_MAXHOST];
        char svc[NI_MAXSERV];

        int clientSocket = accept(listening,
                                  (sockaddr *)&client,
                                  &clientSize);

        if (clientSocket == -1)
        {
            cout << "Problem with client connection!";
            throw("Problem with client connection!");
        }

        cout << " Connected: " << clientSocket << endl;

        memset(host, 0, NI_MAXHOST);
        memset(svc, 0, NI_MAXSERV);

        int result = getnameinfo((sockaddr *)&client,
                                 sizeof(client),
                                 host,
                                 NI_MAXHOST,
                                 svc,
                                 NI_MAXSERV,
                                 0);

        if (result)
            cout << host << " connected on " << svc << endl;

        else
        {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on " << ntohs(client.sin_port) << endl;
        }

        thread t(handleUser,clientSocket);
        t.join();
    }

    // close the listening socket
    close(listening);
}

void Server::handleUser(int clientSocket)
{
    // while receiving display message, echo message
    char buf[4096];
    while (true)
    {
        memset(buf, 0, 4096);
        int byteRecv = recv(clientSocket, buf, 4096, 0);
        if (byteRecv == -1)
        {
            cerr << "There was a connection issue" << endl;
            break;
        }
        if (byteRecv == 0)
        {
            cout << "Client disconnected" << endl;
            break;
        }
        // display message
        cout << "Received: " << string(buf, 0, byteRecv) << "\t\tClient ID : " << clientSocket << endl;
        // resend message
        send(clientSocket, buf, byteRecv + 1, 0);
    }
    // close socket
    close(clientSocket);
}