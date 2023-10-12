/**
 * \brief Item 14: Think carefully about copying behaviour in resource-managing classes.
 */

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <chrono>
#include <thread>

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace std;

class SocketConnectionManager
{
public:
    SocketConnectionManager()
    {
        cout << "SmartPtr: Default Constructor called. " << this << endl;
    }

    ~SocketConnectionManager()
    {
        cout << "SmartPtr: Destructor called. " << this << endl;
    }
};

int main()
{

    // All programs that use asio need to have at least one boost::asio::io_service object.
    boost::asio::io_service ioServiceObj;
    udp::socket udpSocket(ioServiceObj, udp::endpoint(udp::v4(), 1024));

    // wrap this in try catch
    // Wait for the client
    // while(true){
    if (udpSocket.is_open())
    {
        cout << "UDP Socket is open.\n";
    }
    else
    {
        cout << "UDP Socket is not open.\n";
    }
    cout << "Server: Started running...\t "
         << "\n";
    // std::vector<std::vector<char>> receivedStrBuffer(1024);
    // std::vector<std::vector<char>> receivedStrBuffer(100, vector<char>(100));
    std::vector<char> receivedStrBuffer(100);// e, vector<char>(100));
    cout << "0\n";
    udp::endpoint remoteEndpoint;
    cout << "1\n";
    boost::system::error_code errCode;
    // std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "2\n";

    size_t bytesRead = udpSocket.receive_from(boost::asio::buffer(receivedStrBuffer), remoteEndpoint, 0, errCode);
    cout << "3\n";

    if (errCode && errCode != boost::asio::error::message_size)
    {
        cout << "Server: Error occurred while receiving data from client.\n";
        // break;
    }
    cout << "4\n";
    receivedStrBuffer.resize(bytesRead);
    cout << "5\n";

    std::cout << "Received " << bytesRead << " bytes from " << remoteEndpoint << ": "; // << std::string(receivedStrBuffer.begin(), receivedStrBuffer.end());
    cout << "6\n";

    // Deserialize the vector of const char* into std::string objects
    // std::vector<std::string> stringVector;
    //  receivedStrBuffer.at(0).resize(23);

    // cout << "8\n";
    // // Access and print the deserialized std::string objects
    std::cout << "Deserialized String: ";
    for (char byte : receivedStrBuffer)
    {
        cout << byte;
    }
    cout << "\n";
    cout << bytesRead << " 2\n";
    // cout << "xxx " << fileopen << endl;
    cout << "3\n";

    std::string respStr = "Hello from Server!\n";
    boost::system::error_code ignoredErrCode;
    udpSocket.send_to(buffer(respStr), remoteEndpoint, 0, ignoredErrCode);
    cout << "Server: Stilll running...\n";

    return 0;
}