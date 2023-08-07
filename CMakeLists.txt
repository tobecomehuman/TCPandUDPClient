# CMakeList.txt: TCPandUDP 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("TCPandUDP")

# 将源代码添加到此项目的可执行文件。
add_executable (TCPandUDP "TCPandUDP.cpp" "TCPandUDP.h" "CTcpClient.h" "CTcpClient.cpp" "CUdpClient.h" "CUdpClient.cpp" "SocketClient.h" "SocketClient.cpp" "CTcpServer.h" "CTcpServer.cpp")

# TODO: 如有需要，请添加测试并安装目标。
