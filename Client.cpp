/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:09:11 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/24 14:14:59 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
}

Client::Client(int client_fd): _client_fd(client_fd), _to_deconnect(false)
{
	// std::cout << YELLOW << "Client constructor for Client #" << client_fd << RESET << std::endl;
}

Client::~Client()
{
}

void	Client::setReadBuffer(std::string const &buf)
{
	_readbuf += buf;
}
void	Client::setSendBuffer(std::string const &buf)
{
	_sendbuf += buf;
}

std::string	& Client::getReadBuffer()
{
	return (_readbuf);
}

std::string	& Client::getSendBuffer()
{
	return (_sendbuf);
}

void Client::setfd(int i)
{
	this->_client_fd = i;
}

bool&			Client::getDeconnexionStatus()	{ return (_to_deconnect); }