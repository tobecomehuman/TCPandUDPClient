#pragma once
#include<iostream>
#include<vector>
#include"CTcpClient.h"
#include"CUdpClient.h"
using namespace std;
class SocketClient
{
public:
    SocketClient();
    SocketClient(string ip, int port, bool _isUdp = false);
    ~SocketClient();

    bool Connect();

    void DisConnect();

    void Send(const string Msg);

    void Send(const byte* data);

    string RecvMsg();
    vector<byte> RecvByte();
private:

    string _ip;
    int _port;
    bool _isUDP;
    bool init();
    bool _isInit = false;
    CUdpClient _udpClient;
    CTcpClient  _tcpClient;

};
