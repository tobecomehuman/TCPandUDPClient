#include "CUdpClient.h"
#include<iostream>
#include<sstream>
#include<Ws2tcpip.h>
#include<mstcpip.h>

CUdpClient::CUdpClient()
{
}

/// <summary>
/// UDP构造
/// </summary>
/// <param name="strSeverIp">Server IP</param>
/// <param name="uServerPort">Server Port</param>
CUdpClient::CUdpClient(string strSeverIp, unsigned uServerPort) :m_strServerIp(strSeverIp), m_uServerPort(uServerPort)
{
}

/// <summary>
/// UDP析构
/// </summary>
CUdpClient::~CUdpClient()
{
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
    }
    WSACleanup();
    freeaddrinfo(m_servAddrInfo);
}

/// <summary>
/// 初始化
/// </summary>
/// <returns></returns>
bool CUdpClient::Init()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "UDP: Initate windows socket failed!" << endl;
        return false;
    }

    addrinfo hints = { AI_NUMERICHOST,AF_INET,SOCK_DGRAM,IPPROTO_UDP, };

    stringstream ssPort;
    ssPort << m_uServerPort;

    if (getaddrinfo(m_strServerIp.c_str(), ssPort.str().c_str(), &hints, &m_servAddrInfo) != 0)
    {
        cout << "UDP: Get sever addrInfo failed!" << endl;
        return false;
    }


    if (m_socket != INVALID_SOCKET)
    {
        cout << "UDP: The Socket is not empty!Recreating!\n";
        closesocket(m_socket);
    }
    m_socket = INVALID_SOCKET;

    if (m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == SOCKET_ERROR)
    {
        cout << "UDP: soocket creating failed!" << endl;
        return false;
    }


    cout << "UDP: initiating connection succeed!";
    return true;
}

bool CUdpClient::SendByte(const byte* data)
{
    if (!m_socket)
    {
        return false;
    }
    const char* charDatas = reinterpret_cast<const char*>(data);

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

/// <summary>
/// 发送信息
/// </summary>
/// <param name="strMsg"></param>
/// <returns></returns>
bool CUdpClient::SendMsg(const string& strMsg)
{
    if (!m_socket)
    {
        cout << "UDP: Socket is not created" << endl;
        return false;
    }
    if (send(m_socket, strMsg.c_str(), strMsg.length(), 0) != INVALID_SOCKET)
    {
        cout << "UDP: Send succeed!\n";
        return true;
    }
    else
    {
        cout << "UDP: Send failed!\n";
        return false;
    }
    return false;
}

/// <summary>
/// 接收信息
/// </summary>
/// <returns></returns>
string CUdpClient::RecvMsg()
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
        cout << "UDP: Receive succeeded!\n";
        return msgReceived;
    }
    else
    {
        cout << "UDP: Receive failed!\n";
        return NULL;
    }
}

vector<byte> CUdpClient::RecvByte()
{
    vector<byte> recvByte;

    if (!m_socket)
    {
        recvByte.clear();
        cout << "UDP: The Socket is NULL\n";
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
        cout << "UDP: Receive succeeded!\n";
        return recvByte;
    }
    else
    {
        recvByte.clear();
        cout << "UDP: Receive failed!\n";
        return recvByte;
    }
}
