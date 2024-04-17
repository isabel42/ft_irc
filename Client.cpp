/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:09:11 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/16 17:56:33 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
}

Client::Client(int fd): _client_fd(fd)
{
}

Client::~Client()
{
}

void	Client::setReadBuffer(std::string const &buf)
{
	_readbuf += buf;
}

std::string	Client::getReadBuffer()
{
	return (_readbuf);
}

std::string	Client::getSendBuffer()
{
	return (_sendbuf);
}

void Client::setfd(int i)
{
	this->_client_fd = i;
}

bool&			Client::getDeconnexionStatus()	{ return (_to_deconnect); }