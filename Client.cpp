/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:09:11 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/25 15:03:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
}

Client::Client(int client_fd)
: _client_fd(client_fd), _to_deconnect(false), _connexion_password(false),\
 _registrationDone(false), _welcomeSent(false), _hasAllInfo(false), _nbInfo(0)
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


bool&			Client::isRegistrationDone() 	{ return (_registrationDone); }
bool&			Client::isWelcomeSent()			{ return (_welcomeSent); }
bool&			Client::hasAllInfo() 			{ return (_hasAllInfo); }
bool&			Client::getDeconnexionStatus()	{ return (_to_deconnect); }
int				Client::getNbInfo() const 		{ return (_nbInfo); }