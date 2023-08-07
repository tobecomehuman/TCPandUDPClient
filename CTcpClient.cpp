#include "CTcpClient.h"
#include<sstream>
#include<iostream>
#include<Ws2tcpip.h>
#include<mstcpip.h>
#include<vector>
CTcpClient::CTcpClient() {};
CTcpClient::CTcpClient(string strServerIp, unsigned uServerPort) :m_strServerIp(strServerIp), m_uServerPort(uServerPort)
{
}

CTcpClient::~CTcpClient()
{
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
    }
    WSACleanup();
    freeaddrinfo(m_servAddrInfo);
    m_isConnected = false;
}

bool CTcpClient::InitConnection()
{
    WSADATA wsaData;
    //initiate environment
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "TCP:Initate windows socket failed!" << endl;
        return false;
    }

    addrinfo hints = { 0, };
    hints.ai_flags = AI_NUMERICHOST;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    stringstream ssPort;
    ssPort << m_uServerPort;

    if (getaddrinfo(m_strServerIp.c_str(), ssPort.str().c_str(), &hints, &m_servAddrInfo) != 0)
    {
        cout << "TCP:Get sever addrInfo failed!" << endl;
        return false;
    }

    if (m_socket != INVALID_SOCKET)
    {
        cout << "TCP: The Socket is not empty!Recreating!\n";
        closesocket(m_socket);
    }
    m_socket = INVALID_SOCKET;

    if ((m_socket = socket(m_servAddrInfo->ai_family, m_servAddrInfo->ai_socktype, m_servAddrInfo->ai_protocol)) == SOCKET_ERROR)
    {
        cout << "TCP: soocket creating failed!" << endl;
        return false;
    }

    int iResult = connect(m_socket, m_servAddrInfo->ai_addr, (int)m_servAddrInfo->ai_addrlen);

    if (iResult == SOCKET_ERROR)
    {
        iResult = WSAGetLastError();

        if (iResult != WSAEWOULDBLOCK)
        {
            cout << "TCP:Connect server failed" << endl;
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            return false;
        }
    }

    cout << "TCP: initiating connection succeed!";
    m_isConnected = true;
    return true;
}

bool CTcpClient::SendMsg(const string& strMsg)
{
    if (!m_socket)
    {
        return false;
    }
    if (send(m_socket, strMsg.c_str(), strMsg.length(), 0) != INVALID_SOCKET)
    {
        cout << "Send succeed!\n";
        return true;
    }
    else
    {
        cout << "Send failed!\n";
        return false;
    }
}

bool CTcpClient::SendByte(const byte* datas)
{

    if (!m_socket)
    {
        return false;
    }
    const char* charDatas = reinterpret_cast<const char*>(datas);

    ////如果charDatas是一个以null结尾的字符串，可以使用strlen函数来测量其长度，如果charDatas不是以null结尾的字符数组，则可以使用sizeof运算符来测量其长度，如下所示：
    //c++
    //    const char* charDatas;
    //size_t len = strlen(charDatas); // 如果charDatas是以null结尾的字符串，则使用strlen函数测量其长度
    //size_t arrLen = sizeof(charDatas) / sizeof(char); // 如果charDatas是字符数组，则使用sizeof运算符测量其长度
    //需要注意的是，sizeof运算符返回的是数组的总字节数，因此需要除以单个元素的字节数才能得到数组的长度。
    if (send(m_socket, charDatas, strlen(charDatas), 0) != INVALID_SOCKET)
    {
        cout << "Send succeed!\n";
        return true;
    }
    else
    {
        cout << "Send failed!\n";
        return false;
    }
}



string CTcpClient::RecvMsg()
{
    if (!m_socket)
    {
        return false;
    }
    const int iBufSize = 4096;
    char recvBuf[iBufSize] = { 0, };
    auto iRecvSize = recv(m_socket, recvBuf, iBufSize, 0);
    string  msgReceived(recvBuf);
    if (iRecvSize > 0)
    {
        cout << "TCP: Receive succeeded!\n";
        return msgReceived;
    }
    else
    {
        cout << "TCP: Receive failed!\n";
        return NULL;
    }
}

vector<byte> CTcpClient::RecvByte()
{

    vector<byte> recvByte;

    if (!m_socket)
    {
        recvByte.clear();
        cout << "TCP: The Socket is NULL\n";
        return recvByte;
    }
    const int iBufSize = 2048;
    char recvBuf[iBufSize] = { 0, };
    auto iRecvSize = recv(m_socket, recvBuf, iBufSize, 0);
    for (int i = 0; i < 2048; i++)
    {
        recvByte.push_back(recvBuf[i]);
    }

    if (iRecvSize > 0)
    {
        cout << "TCP: Receive succeeded!\n";
        return recvByte;
    }
    else
    {
        recvByte.clear();
        cout << "TCP: Receive failed!\n";
        return recvByte;
    }
}
