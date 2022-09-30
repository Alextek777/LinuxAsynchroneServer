#include "../headers/Server.h"

using namespace std;

int main(int argc, char** argv)
{
    try{
        Server server("192.168.1.5",54000);
        server.start();
    }
    catch(const std::string& str){
        cout << "FITAL ERROR : " << str << endl;
        return -1;
    }
    catch(...){
        cout << "FITAL ERROR" << endl;
        return -1;
    }

    return 0;
}