#pragma once
#include<string>
#include<vector>
#include<winsock2.h>
using namespace std;
#pragma comment(lib,"ws2_32")//Standard socket API.
class CTcpClient
{
public:
    CTcpClient();
    CTcpClient(string strServerIp, unsigned uServerPort);
    virtual ~CTcpClient();

    bool InitConnection();

    bool SendMsg(const string& strMsg);

    bool SendByte(const byte* datas);

    string RecvMsg();
    vector<byte> RecvByte();

    bool m_isConnected = false;
private:
    SOCKET m_socket = INVALID_SOCKET;
    string m_strServerIp;//Server IP listener
    unsigned int m_uServerPort = -1;//Server port listener
    struct addrinfo* m_servAddrInfo = NULL;//Server address structure list
};