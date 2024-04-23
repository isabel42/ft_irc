/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:06:01 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/22 14:45:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Irc.hpp"

class Client
{
	private:
		int		_client_fd;
		std::string _nickname;
		std::string _real_name;
		std::string _user_name;
		std::string	_readbuf;
		std::string	_sendbuf;
		bool _to_deconnect;
	
	public:
		Client();
		Client(int fd);
		~Client();
		void setReadBuffer(std::string const &buf);
		void setSendBuffer(std::string const &buf);
		std::string	& getReadBuffer();
		std::string	& getSendBuffer();
		bool&			getDeconnexionStatus();
		
		void setfd(int i);
};

#endif