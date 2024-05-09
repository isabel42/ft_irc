/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:06:01 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 14:54:48 by itovar-n         ###   ########.fr       */
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
		std::string _old_nickname;
		std::string _realname;
		std::string _username;
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
		
		void 			setfd(int i);
		int				getfd();
		bool&			isRegistrationDone();
		void			setRegistrationDone(bool boolean);
		bool&			isWelcomeSent();
		void			setWelcomeSent(bool boolean);
		bool&			hasAllInfo();
		void			sethasAllInfo(bool boolean);
		int				getNbInfo() const;
		void			setNbInfo(int n);
		void			setNickname(std::string const &nickname);
		void			setOldNickname(std::string const &nickname);
		void			setUsername(std::string const &username);
		void			setRealname(std::string const &realname);
		std::string		getNickname() const;
		std::string		getOldNickname() const;
		std::string		getUsername() const;
};
#endif