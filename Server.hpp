/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:26 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/02 23:12:20 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
#include <netdb.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>

extern bool	server_shutdown;

class Server
{
	private:
		std::string	_port;
		std::string	_pw;
		std::string _datetime;
		
		struct addrinfo	_hints;
		struct addrinfo	*_servinfo;
		int				_server_socket_fd;
		
	public:
		Server();
		~Server();
		Server(std::string port, std::string pw, struct tm *timeinfo);
		void setDatetime(struct tm *timeinfo);
		int fillServinfo(char *port);
	
};

#endif