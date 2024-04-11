/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:26 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/09 12:13:03 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include <stdio.h>
#include <string.h>
#include <netdb.h>

# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <cstdlib>
# include <vector>
# include <map>
# include <list>
# include <unistd.h>
# include <sstream>
# include <string>
# include <cerrno>
# include <ctime>

# include "Client.hpp"


extern bool	server_shutdown;

class Server
{
	private:
		std::string	_port;
		std::string	_pw;
		std::string _datetime;
			
		struct addrinfo	_hints;
		struct addrinfo	*_param;
		int				_server_socket_fd;
		std::map <const int, Client> _clients;
		
	public:
		Server();
		~Server();
		Server(std::string port, std::string pw, struct tm *timeinfo);
		void setDatetime(struct tm *timeinfo);
		void setParam(char *port);
		void setHints();
		void launchServer();
		void ServerLoop();

		int createClientConnexion(std::list<pollfd>& poll_fds, std::list<pollfd>& new_pollfds);
		void addClient(int client_socket, std::list<pollfd> &poll_fds);
	
};

#endif