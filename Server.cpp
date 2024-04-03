/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:02 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/02 23:11:56 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	
}

Server::~Server()
{
	
}

Server::Server(std::string port, std::string pw, struct tm *timeinfo)
:  _port(port), _pw(pw), _servinfo(NULL), _server_socket_fd(0)
{
	// std::cout << YELLOW << "Server running..." << RESET << std::endl;
	// std::cout << YELLOW << "Server listening" << RESET << std::endl;
	memset(&_hints, 0, sizeof(_hints));
	this->setDatetime(timeinfo);
}

void Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	_datetime = str;
}

int Server::fillServinfo(char *port)
{
	if (getaddrinfo(NULL, port, &_hints, &_servinfo) < 0)
	{
		// std::cerr << RED << "[Server] Flop du addrinfo" << RESET << std::endl;
		return (0);
	}
	return (1);
}