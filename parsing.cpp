/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:50:24 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/26 17:15:47 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static void splitMessage(std::vector<std::string> &cmds, std::string msg, std::string delimeter)
{
	int pos = 0;
	std::string substr;
	
	if ((pos = msg.find(delimeter)) == static_cast<int>(std::string::npos))
		cmds.push_back(msg);

	while ((pos = msg.find(delimeter)) != static_cast<int>(std::string::npos))
	{
		substr = msg.substr(0, pos);
		cmds.push_back(substr);
		msg.erase(0, pos + delimeter.length());
	}
}

// void Server::fillClients(std::map<const int, Client> &client_list, int client_fd, std::string cmd)
// {
// 	std::map<const int, Client>::iterator it = client_list.find(client_fd);
// 	cmd_struct cmd_infos;
// 	if (parseCommand(cmd, cmd_infos) == -1)
// 		return ;

// 	if (cmd.find("NICK") != std::string::npos)
// 		nick(this, client_fd, cmd_infos);
// 	else if (cmd.find("USER") != std::string::npos)
// 		user(this, client_fd, cmd_infos);
// 	else if (cmd.find("PASS") != std::string::npos)
// 	{
// 		if (pass(this, client_fd, cmd_infos) == SUCCESS)
// 			it->second.setConnexionPassword(true);
// 		else
// 			it->second.setConnexionPassword(false);
// 	}
// }

// void Server::execCommand(int const client_fd, std::string cmd_line)
// {
// 	std::string	validCmds[VALID_LEN] = {
// 		"INVITE",
// 		"JOIN",
// 		"KICK",
// 		"KILL",
// 		"LIST",
// 		"MODE",
// 		"MOTD",
// 		"NAMES",
// 		"NICK",
// 		"NOTICE",
// 		"OPER",
// 		"PART",
// 		"PING",
// 		"PRIVMSG",
// 		"QUIT",
// 		"TOPIC",
// 		"USER",
// 		};

// 	Client *client = getClient(this, client_fd);
// 	cmd_struct cmd_infos;
// 	int index = 0;

	// if (parseCommand(cmd_line, cmd_infos) == -1)
	// 	return ;

// 	std::cout << "******" << cmd_infos.message << std::endl;

	// while (index < VALID_LEN)
	// {
	// 	if (cmd_infos.name == validCmds[index])
	// 		break;
	// 	index++;
	// }

	// switch (index + 1)
	// {
	// 	case 1: invite(this, client_fd, cmd_infos); break;
	// 	case 2: join(this, client_fd, cmd_infos); break;
	// 	case 3: kick(this, client_fd, cmd_infos); break;
	// 	case 4: kill(this, client_fd, cmd_infos); break;
	// 	case 5: list(this, client_fd, cmd_infos); break;
	// 	case 6: modeFunction(this, client_fd, cmd_infos); break;
	// 	case 7: motd(this, client_fd, cmd_infos); break;
	// 	case 8: names(this, client_fd, cmd_infos); break;
	// 	case 9: nick(this, client_fd, cmd_infos); break;
    // 	case 10: notice(this, client_fd, cmd_infos); break;
	// 	case 11: oper(this, client_fd, cmd_infos); break;
	// 	case 12: part(this, client_fd, cmd_infos); break;
	// 	case 13: ping(this, client_fd, cmd_infos); break;
	// 	case 14: privmsg(this, client_fd, cmd_infos); break;
	// 	case 15: quit(this, client_fd, cmd_infos); break;
	// 	case 16: topic(this, client_fd, cmd_infos); break;
	// 	case 17: user(this, client_fd, cmd_infos); break;
	// 	default:
	// 		addToClientBuffer(this, client_fd, ERR_UNKNOWNCOMMAND(client->getNickname(), cmd_infos.name));
// 	}
// }

void Server::parseMessage(std::string message)
{
	std::vector<std::string>				cmds;
	// std::map<const int, Client>::iterator	it = _clients.find(client_fd);
	// Client *client = getClient(client_fd);

	splitMessage(cmds, message, "\n");
	// std::cout << std::endl << "**" << cmds[1] << "**" << std::endl;

	// for (size_t i = 0; i != cmds.size(); i++)
	// {
		// if (client->isRegistrationDone() == false)
		// {
		// 	if (client->hasAllInfo() == false)
		// 	{
		// 		fillClients(_clients, client_fd, cmds[i]);
		// 		if (client->getNbInfo() == 3)
		// 			client->hasAllInfo() = true;
		// 	}
		// 	if (client->hasAllInfo() == true && client->isWelcomeSent() == false)
		// 	{
		// 		if (client->is_valid() == SUCCESS)
		// 		{
		// 			sendClientRegistration(this, client_fd, it);
		// 			client->isWelcomeSent() = true;
		// 			client->isRegistrationDone() = true;
		// 		}		
		// 		else
		// 			throw Server::InvalidClientException();
		// 	}
		// }
		// else
			// execCommand(client_fd, cmds[i]);
	// }
	
	cmd_struct cmd_infos;
	for (size_t i = 0; i != cmds.size(); i++)
		parseCommand(cmds[i], cmd_infos);
}

/**
 * @brief 
 * 
 * 	exple de ligne : @id=234AB :dan!d@localhost PRIVMSG #chan :Hey what's up!
 *  autre exple : /ping localhost devient : PRIVMSG localhost :PING 1671195504 289728
 * 
 */
int	parseCommand(std::string cmd_line, cmd_struct &cmd_infos)
{
	if (cmd_line.empty() == true)
		return (-1);
	
	std::vector<std::string> parts;
	cmd_line.push_back(' ');
	splitMessage(parts, cmd_line, " ");
	cmd_line.pop_back();
	std::vector<std::string>::iterator	it = parts.begin();
	
	// COMMAND
	if ((*it).front() == ':')	// Cas du préfixe (supprimer cette partie d'une copy) pour retomber sur un cas "CMD arg <arg2>" ou "CMD"
	{
		(*it).erase(0, 1);
		cmd_infos.prefix.assign(*it);
		it++;
		
	}
	if (it != parts.end())
	{
		cmd_infos.name.assign(*it);
		it++;
	}
	if (it != parts.end())
	{
		std::size_t length = 0;
		if (cmd_infos.prefix.size() > 0)
			length += 2;
		if (cmd_infos.name.size() > 0)
			length++;
		length = length +  cmd_infos.prefix.size() + cmd_infos.name.size();
		cmd_infos.message.assign(cmd_line.substr(length));
	}
		
	std::cout << "PREFIX: " << "$" << cmd_infos.prefix << "$" << std::endl;
	std::cout << "COMMAND: " << "$" << cmd_infos.name << "$" << std::endl;
	std::cout << "MESSAGE: " << "$" << cmd_infos.message << "$" << std::endl;
	return (1);
}
