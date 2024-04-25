/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:06:01 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/25 15:03:24 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Irc.hpp"

class Client
{
	private:
		int		_client_fd;
		// std::string _nickname;
		// std::string _real_name;
		// std::string _user_name;
		bool _to_deconnect;
		bool _connexion_password;
		bool _registrationDone;
		bool _welcomeSent;
		bool _hasAllInfo;
		int _nbInfo;
		std::string	_readbuf;
		std::string	_sendbuf;
	
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
		bool&			isRegistrationDone();
		void			setRegistrationDone(bool boolean);
		bool&			isWelcomeSent();
		void			setWelcomeSent(bool boolean);
		bool&			hasAllInfo();
		void			sethasAllInfo(bool boolean);
		int				getNbInfo() const;
		void			setNbInfo(int n);
};

#endif