/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:02 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/18 18:22:30 by itovar-n         ###   ########.fr       */
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
: _port(port), _pw(pw), _server_socket_fd(0), _nb_clients(0)
{
	
	// std::cout << YELLOW << "Server running..." << RESET << std::endl;
	// std::cout << YELLOW << "Server listening" << RESET << std::endl;
	this->setDatetime(timeinfo);
}

void Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	_datetime = str;
}

void Server::setHints()
{
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_INET;		  // Ipv4
	_hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	_hints.ai_flags = AI_PASSIVE;	  // Localhost by default
}

void Server::setParam()
{
	// if (getaddrinfo(NULL, _port, &_hints, &_param) < 0)
	// 	throw(std::out_of_range("Server] Flop du addrinfo"));
	memset(&_param, 0, sizeof(_param));
	_param.sin_family = AF_INET;
    _param.sin_addr.s_addr = INADDR_ANY;
    _param.sin_port = htons(atoi(_port.c_str()));
}


void Server::launchServer()
{
	_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_socket_fd < 0)
	{
		close (_server_socket_fd);
		throw (std::out_of_range("[Server] Flop de la socket :("));
	}
	int optvalue = 1; // enables the re-use of a port if the IP address is different
	if (setsockopt(_server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue)) < 0 )
	{
		close (_server_socket_fd);
		throw (std::out_of_range("[Server] Impossible to reuse"));
	}

	// if (fcntl(_server_socket_fd, F_SETFL, O_NONBLOCK))
    //     throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
		
	if (bind(_server_socket_fd,(sockaddr *) &_param, sizeof(_param)) < 0)
	{
		close (_server_socket_fd);
		throw (std::out_of_range("[Server] Bind failed"));
	}
	if (listen(_server_socket_fd, 10) < 0)
	{
		close (_server_socket_fd);
		throw (std::out_of_range("[Server] Listen failed"));
	}
	this->_onoff = 1;
}

void Server::ServerLoop()
{
	std::vector<pollfd> poll_fds;
	pollfd server_poll_fd;

	server_poll_fd.fd = _server_socket_fd;
	server_poll_fd.events = POLLIN;

	poll_fds.push_back(server_poll_fd);
	
	while (server_shutdown == false)
	{
		std::vector<pollfd> new_pollfds; // tmp struct hosting potential newly-created fds

		if (poll((pollfd *)&poll_fds[0], (unsigned int)poll_fds.size(), -1) <= 0) // -1 == no timeout
		{
			if (errno == EINTR)
				break ;
			throw (std::out_of_range("[Server] Socket error"));
		}

		std::vector<pollfd>::iterator it = poll_fds.begin();
		
		while (it != poll_fds.end())
		{
			if (it->revents & POLLIN) // => If the event that occured is a POLLIN (aka "data is ready to recv() on this socket")
			{
				if (it->fd == _server_socket_fd)
				{
					if (this->createClientConnexion(poll_fds, new_pollfds) == 3)
					{
						continue;
					}
				}
				else // => If the dedicated fd for the Client/Server connection already exists
				{
					if (this->handleExistingConnexion(poll_fds, it) == 2)
						break ;
				}
			}
			else if (it->revents & POLLOUT) // = "Alert me when I can send() data to this socket without blocking."
			{
				if (handlePolloutEvent(poll_fds, it, it->fd) == 2)
					break;
			}
			else if (it->revents & POLLERR)
			{
				if (handlePollerEvent(poll_fds, it) == 2)
					break ;
				else
					throw (std::out_of_range("[Server] Poll error"));
			}
			it++;
		}
		poll_fds.insert(poll_fds.end(), new_pollfds.begin(), new_pollfds.end()); // Add the range of NEW_pollfds in poll_fds (helps recalculating poll_fds.end() in the for loop)
	}
}