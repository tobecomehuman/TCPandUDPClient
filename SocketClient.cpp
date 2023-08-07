#include"SocketClient.h"
SocketClient::SocketClient()
{
}

SocketClient::SocketClient(string ip, int port, bool useUDP ) :_port(port), _ip(ip), _isUDP(useUDP)
{
    init();
}

SocketClient::~SocketClient()
{
    _udpClient.~CUdpClient();
    _tcpClient.~CTcpClient();
}

bool SocketClient::init()
{
    if (_isUDP)
    {
        _udpClient = CUdpClient(_ip, _port);
        _isInit = true;
    }
    else
    {
        _tcpClient = CTcpClient(_ip, _port);
        _isInit = true;
    }
    return _isInit;
}

bool SocketClient::Connect()
{
    if (!_tcpClient.m_isConnected || !_isInit)
    {
        init();
        _tcpClient.InitConnection();

    }
    return _tcpClient.m_isConnected;
}

void SocketClient::DisConnect()
{
    _tcpClient.~CTcpClient();
}

void SocketClient::Send(const string Msg)
{
    if (!_isUDP)
    {
        if (!_tcpClient.m_isConnected || !_isInit)
        {
            init();
            _tcpClient.InitConnection();
        }
        _tcpClient.SendMsg(Msg);
    }
    else
    {
        _udpClient.SendMsg(Msg);
    }
}

void SocketClient::Send(const byte* data)
{
    if (!_isUDP)
    {
        if (!_tcpClient.m_isConnected || !_isInit)
        {
            init();
            _tcpClient.InitConnection();
        }
        _tcpClient.SendByte(data);
    }
    else
    {
        _udpClient.SendByte(data);
    }
}

string SocketClient::RecvMsg()
{
    if (!_isUDP)
    {
        return _tcpClient.RecvMsg();
    }
    else
    {
        return _udpClient.RecvMsg();
    }
}

vector<byte> SocketClient::RecvByte()
{
    if (!_isUDP)
    {
        return _tcpClient.RecvByte();
    }
    else
    {
        return _udpClient.RecvByte();
    }
}




