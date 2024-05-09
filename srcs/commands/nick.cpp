/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:56 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 16:43:48 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

bool isUsed (int client_fd, std::string nick_tent, std::map<const int, Client> clients_s)
{
	std::map<const int, Client>::iterator	client_it		= clients_s.begin();
	while (client_it != clients_s.end())
	{
		if (client_fd != client_it->second.getfd() && nick_tent == client_it->second.getNickname())
			return true;
		client_it++;
	}
	return false;
}

void Server::nick(int const client_fd, cmd_struct cmd_infos)
{
	Client *client = this->getClient(client_fd);

	if (cmd_infos.message.empty())
		client->setSendBuffer(ERR_NONICKNAMEGIVEN(client->getNickname()));
	else if (cmd_infos.message_split.size() > 1 
			|| cmd_infos.message.find (',') != std::string::npos 
			|| cmd_infos.message.find ('*') != std::string::npos
			|| cmd_infos.message.find ('?') != std::string::npos 
			|| cmd_infos.message.find ('!') != std::string::npos
			|| cmd_infos.message.find ('@') != std::string::npos
			|| cmd_infos.message.find ('.') != std::string::npos
			|| cmd_infos.message[0] == '$'
			|| cmd_infos.message[0] == ':')
		client->setSendBuffer(ERR_ERRONEUSNICKNAME(client->getNickname(), cmd_infos.message_split[0]));
	else if ( isUsed(client_fd, cmd_infos.message_split[0], _clients) == true)
		client->setSendBuffer(ERR_NICKNAMEINUSE(client->getNickname(), cmd_infos.message_split[0]));
	else
	{
		if (client->isRegistrationDone() == true)
		{
			client->setOldNickname(client->getNickname());
			std::cout << "[Server] Nickname change registered. Old nickname is now : " << client->getOldNickname() << std::endl;
		}
		else
		{
			client->setOldNickname(cmd_infos.message_split[0]);
			client->setNbInfo(+1);
		}
		client->setNickname(cmd_infos.message_split[0]);
	}
	client->setSendBuffer(RPL_NICK(client->getOldNickname(), client->getUsername(), client->getNickname()));
}


