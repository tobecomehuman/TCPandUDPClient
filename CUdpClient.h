#pragma once
#include<vector>
#include<winsock2.h>
#include<string>
using namespace std;

class CUdpClient
{
public:
    CUdpClient();
    CUdpClient(string strSeverIp, unsigned uServerPort);
    virtual ~CUdpClient();

    bool Init();

    bool SendByte(const byte* data);

    bool SendMsg(const string& strMsg);

    string RecvMsg();
    vector<byte> RecvByte();
private:
    SOCKET m_socket = INVALID_SOCKET;
    string m_strServerIp;//Server IP listener
    unsigned int m_uServerPort = -1;//Server port listener
    struct addrinfo* m_servAddrInfo = NULL;//Server address structure list

};
