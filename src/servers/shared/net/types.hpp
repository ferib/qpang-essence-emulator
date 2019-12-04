#ifndef _TYPES_H
#define _TYPES_H

#include <boost/asio.hpp>

using TcpSocket = boost::asio::ip::tcp::socket;
using IoService = boost::asio::io_service;
using ErrorCode = boost::system::error_code;

#endif //_TYPES_H