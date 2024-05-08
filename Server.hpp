/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:26 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 16:38:57 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# include "Irc.hpp"
# include "Commands.hpp"


class Server
{
	private:
		std::string	_port;
		std::string	_pw;
		std::string _datetime;
		bool		_onoff;
			
		struct addrinfo	_hints;
		struct sockaddr_in	_param;
		int				_server_socket_fd;
		std::map <const int, Client> _clients;
		int		_nb_clients;
		
	public:
		Server();
		~Server();
		Server(std::string port, std::string pw, struct tm *timeinfo);
		void setDatetime(struct tm *timeinfo);
		void setParam();
		void setHints();
		void launchServer();
		void ServerLoop();

		int createClientConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>& new_pollfds);
		void addClient(int client_socket, std::vector<pollfd> &poll_fds);
		
		int handleExistingConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it);
		Client*	getClient(int const client_fd);
		void delClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator &it, int current_fd);

		int	handlePolloutEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd);

		int	handlePollerEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it);

		void fillClients(std::map<const int, Client> &client_list, int client_fd, std::string cmd);
		void execCommand(int const client_fd, std::string cmd_line);
		void parseMessage(int client_fd, std::string message);

		//--- commands --

		void user(int const client_fd, cmd_struct cmd_infos);
		void nick(int const client_fd, cmd_struct cmd_infos);
		
};

#endif