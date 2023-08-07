#include"SocketClient.h"
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    string _localHost = "127.0.0.1";
    int _porName = 6005;
    SocketClient _client(_localHost, 6005);
    if (_client.Connect()) { getchar(); }
 /*   string strAskMsg = "ask";*/
  /*   vector<byte>strAskMsg;
     strAskMsg.push_back('a'); strAskMsg.push_back('s'); strAskMsg.push_back('k');*/
    byte strAskMsg[] = {'a','s','k'};
    for (int i = 0; i <3; i++)
    {
        _client.Send(strAskMsg);
        
        _client.RecvMsg();
        
    }
    getchar();
    return 0;
}