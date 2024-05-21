/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:37:25 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/21 17:58:58 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"
#include "Server.hpp"


static std::string	getReason(std::vector<std::string> msg_to_parse);
static void			broadcastToChannel(Channel &channel, Client &client, std::string kicked, std::string reason);

/**
 * @brief The KICK command can be used to request the forced removal of a user 
 *  from a channel. It causes the <user> to be removed from the <channel> by force. 
 *  If no comment is given, the server SHOULD use a default message instead.
 * 
 *  Parameters: <channel> <user> *( "," <user> ) [<comment>]
 * 
 * Numeric Replies:
 * 
 * ERR_NEEDMOREPARAMS (461)
 * ERR_NOSUCHCHANNEL (403)
 * ERR_CHANOPRIVSNEEDED (482)
 * ERR_USERNOTINCHANNEL (441)
 * ERR_NOTONCHANNEL (442)
 * 
 * Example:
 * Client's request : KICK #Finnish John :Speaking English
 * 
 * Server's Response: " Command to kick John from #Finnish using "Speaking English" 
 * 						as the reason (comment)."
 *
 * @param server
 * @param cmd_infos Structure w/ prefix, command name and message
 */
void	Server::kick(int const client_fd, cmd_struct cmd_infos)
{
	Client *client = this->getClient(client_fd);
	if (cmd_infos.message_split.empty() || cmd_infos.message_split.size() < 2)
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), cmd_infos.name));
		return ;
	}
	
	std::string	requester_name	= client->getNickname();
	std::string	channel_name	= cmd_infos.message_split[0];
	std::string	kicked_name		= cmd_infos.message_split[1];
	std::string	reason			= getReason(cmd_infos.message_split);

	std::map<std::string, Channel>::iterator it_chan	= _channels.find(channel_name);

	reason = (reason.empty()) ? ":Kicked by the channel's operator" : reason;

	if (it_chan == _channels.end())
		client->setSendBuffer(ERR_NOSUCHCHANNEL(requester_name, channel_name));
	else if (it_chan->second.doesClientExist(requester_name) == false)
		client->setSendBuffer(ERR_NOTONCHANNEL(requester_name, channel_name));
	else if (it_chan->second.doesClientExist(kicked_name) == false)
		client->setSendBuffer(ERR_USERNOTINCHANNEL(requester_name, kicked_name, channel_name));
	else if (it_chan->second.isOperator(requester_name) == false) // you're not a channel operator
		client->setSendBuffer(ERR_CHANOPRIVSNEEDED(requester_name, channel_name));
	else
	{
		broadcastToChannel(it_chan->second, *client, kicked_name, reason);
		it_chan->second.getClientList().erase(kicked_name);
		it_chan->second.addToKicked(kicked_name);
	}
}


static void			broadcastToChannel(Channel &channel, Client &client, std::string kicked, std::string reason)
{
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();
	
	while (member != channel.getClientList().end())
	{
		member->second.setSendBuffer(RPL_KICK(user_id(client.getNickname(), client.getUsername()), channel.getName(), kicked, reason));
		member++;
	}
}

static std::string	getReason(std::vector<std::string> msg_to_parse)
{
	std::string reason;
	reason.clear();
	for (size_t i = 2; i < msg_to_parse.size(); i++)
	{
		if (i > 2)
			reason = reason.append(" ");
		reason = reason.append(msg_to_parse[i]);
	}
	return (reason);
}