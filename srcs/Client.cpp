/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:09:11 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 14:55:26 by itovar-n         ###   ########.fr       */
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

int Client::getfd()
{
	return (_client_fd);
}


bool&			Client::isRegistrationDone() 	{ return (_registrationDone); }
bool&			Client::isWelcomeSent()			{ return (_welcomeSent); }
bool&			Client::hasAllInfo() 			{ return (_hasAllInfo); }
bool&			Client::getDeconnexionStatus()	{ return (_to_deconnect); }
int				Client::getNbInfo() const 		{ return (_nbInfo); }

void			Client::setNbInfo(int n) 		
{
	_nbInfo += n;
	if (_nbInfo <= 0)
		_nbInfo = 0;
}

void	Client::setNickname(std::string const &nickname)
{
	// If the nickname has more than 9 characters, it must be truncated
	_nickname = (_nickname.size() > 9) ? nickname.substr(0, 9) : nickname;
}

void	Client::setOldNickname(std::string const &nickname)
{
	_old_nickname = nickname;
}

void	Client::setUsername(std::string const &username)
{
	_username = username;
}

void	Client::setRealname(std::string const &realname)
{
	_realname = realname;
}

std::string Client::getNickname() const			{return (_nickname); }
std::string Client::getOldNickname() const		{return (_old_nickname); }
std::string Client::getUsername() const			{return (_username); }