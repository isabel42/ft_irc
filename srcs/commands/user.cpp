/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:52:17 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/10 12:16:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

/**
 * @brief The USER command is used at the beginning of a connection to specify 
 * 		  the username and realname of a new user.
 * 		
 * 	The minimum length of <username> is 1, ie. it MUST NOT be empty. 
 * 	If it is empty, the server SHOULD reject the command with ERR_NEEDMOREPARAMS.
 * 
 *  If a client tries to send the USER command after they have already completed
 *  registration with the server, the ERR_ALREADYREGISTERED reply should be sent
 *  and the attempt should fail.
 * 	
 *  SYNTAX : USER <username> 0 * <realname>
 * 
 * 	Numeric Replies:
 * 		ERR_NEEDMOREPARAMS (461)
 * 		ERR_ALREADYREGISTERED (462)
 * 
 *  Examples:
 * 	[Client] USER marine 0 * :Marine Sanjuan
 * 	=> Username is marine, Realname is Marine Sanjuan
 * 
 * 	[Client] USER msanjuan msanjuan localhost :Marine SANJUAN
 *  => Username is msanjuan, Realname is Marine Sanjuan
 */

void Server::user(int const client_fd, cmd_struct cmd_infos)
{
	std::vector<std::string> names;
	Client *client = this->getClient(client_fd);
	
	std::string mess_cp = cmd_infos.message + ' ';
	splitMessage(names, mess_cp, " ");
	
	if (cmd_infos.message_split.size() < 4)
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), cmd_infos.name));
	else if (client->isRegistrationDone() == true)
		client->setSendBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
	else
	{
		client->setUsername(cmd_infos.message_split[0]);
		if (cmd_infos.message_split[3][0] == ':')
			cmd_infos.message_split[3].erase(0, 1);
		for (size_t i = 4; i < cmd_infos.message_split.size(); i++)
		{
			cmd_infos.message_split[3] = cmd_infos.message_split[3].append(" ");
			cmd_infos.message_split[3] = cmd_infos.message_split[3].append(cmd_infos.message_split[i]);
		}
		client->setRealname(cmd_infos.message_split[3]);
		client->setNbInfo(+1);
	}
}