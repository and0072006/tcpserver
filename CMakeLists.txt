cmake_minimum_required(VERSION 3.9)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(server
	tcpserver/main.cpp
	tcpserver/main.cpp
	tcpserver/main.cpp
	tcpclient/main.cpp
	tcpclient/main.cpp
	conf/ConfigReaderFromFile.cpp
	conf/ConfigReaderFromFile.h
	conf/CParameters.cpp
	conf/CParameters.h
	conf/IConfigReader.h
	log/FileLogger.cpp
	log/FileLogger.h
	log/ILoggerImpl.h
	log/Logger.cpp
	log/Logger.h)
