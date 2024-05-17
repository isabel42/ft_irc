/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:22:11 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/17 18:23:23 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"
#include "Server.hpp"


// bool			containsAtLeastOneAlphaChar(std::string str);
// std::string		retrieveKey(std::string msg_to_parse);
// void			addChannel(Server *server, std::string const &channelName);
// void			addClientToChannel(Server *server, std::string &channelName, Client &client);
// void			sendChanInfos(Server *server, Channel &channel, std::string channel_name, Client &client);
/**
 * @brief The JOIN command indicates that the client wants to join the given channel(s), 
 * 	each channel using the given key for it. The server receiving the command checks 
 * 	whether or not the client can join the given channel, and processes the request. 
 * 
 * 	While a client is joined to a channel, they receive all relevant information about 
 * 	that channel including the JOIN, PART, KICK, and MODE messages affecting the channel. 
 * 	They receive all PRIVMSG and NOTICE messages sent to the channel, and they also 
 * 	receive QUIT messages from other clients joined to the same channel (to let them 
 * 	know those users have left the channel and the network). 
 * 
 *  Numeric Replies:
 *  
 *  ERR_NEEDMOREPARAMS (461)
 *  ERR_NOSUCHCHANNEL (403)
 *  ERR_TOOMANYCHANNELS (405)
 *  ERR_BADCHANNELKEY (475)
 *  ERR_BANNEDFROMCHAN (474)
 *  ERR_CHANNELISFULL (471)
 *  ERR_INVITEONLYCHAN (473)
 *  ERR_BADCHANMASK (476)
 *  RPL_TOPIC (332)
 *  RPL_TOPICWHOTIME (333)
 *  RPL_NAMREPLY (353)
 *  RPL_ENDOFNAMES (366)
 *  
 *  Examples:
 * 	[CLIENT]  JOIN #foobar
 *  [SERVER] ; join channel #foobar.
 * 
 * 	[CLIENT]  JOIN #foo,#bar fubar,foobar
 * 	[SERVER]; join channel #foo using key "fubar" and channel #bar using key "foobar".
 */

 
void	addChannel(Server *server, std::string const &channelName)
{
	// check if channel already exists.
	std::map<std::string, Channel>::iterator it = server->getChannels().find(channelName);
	if (it != server->getChannels().end())
	{
		std::cout << "Channel already exists, choose an other name\n";
		return ;
	}
	Channel	channel(channelName);
	server->getChannels().insert(std::pair<std::string, Channel>(channelName, channel));
}

bool		getChannelName(std::string &str)
{
	if (str.size() > 1 && str[0] != '#' && str[0] != '&')
		return (false);
	str.erase(0,1);
	str = str.substr(200);
	return (true);
	
}

std::string	getListOfMembers(std::string client, Channel &channel)
{
	std::map<std::string, Client>&			client_list	= channel.getClientList();
	std::map<std::string, Client>::iterator	it;
	std::string								nick;
	std::string								members_list;

	for (it = client_list.begin(); it != client_list.end(); it++)
	{
		nick.clear();
		nick = it->second.getNickname();
		if (it->second.getMode().find('i') != std::string::npos\
			&& channel.doesClientExist(client) == false)
				continue;
			
		if (channel.isOperator(nick) == true)
			members_list += "@";
		members_list += nick;
		members_list += " ";
	}
	if (members_list.size() >= 1 && members_list[members_list.size() - 1] == ' ')
		members_list.erase(members_list.end()-1);
	return (members_list);
}


std::string	getSymbol(Channel &channel)
{
	std::string symbol;

	if (channel.getMode().find('s') != std::string::npos) {
		symbol += "@";
	} else if (channel.getMode().find('p') != std::string::npos) {
		symbol += "*";
	} else {
		symbol += "=";
	}
	return (symbol); 
}

void		sendChanInfos( Channel &channel, std::string channel_name, Client &client)
{
	std::string	nick		= client.getNickname();
	std::string username	= client.getUsername();
 	
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();

	while (member != channel.getClientList().end())
	{
		member->second.setSendBuffer(RPL_JOIN(user_id(nick, username), channel_name));
		if (channel.getTopic().empty() == false)
			member->second.setSendBuffer(RPL_TOPIC(nick, channel_name, channel.getTopic()));
		
		std::string	list_of_members = getListOfMembers(nick, channel);
		std::string symbol			= getSymbol(channel);

		member->second.setSendBuffer(RPL_NAMREPLY(username, symbol, channel_name, list_of_members));
		member->second.setSendBuffer(RPL_ENDOFNAMES(username, channel_name));
		member++;
	}
}


void	addClientToChannel(Channel &it, Client &client)
{
	std::string client_nickname = client.getNickname();
	if (it.doesClientExist(client_nickname) == false)
	{
		it.getClientList().insert(std::pair<std::string, Client>(client.getNickname(), client));
	}
	else 
		std::cout << client.getNickname() << "already here\n" ;
}

void	Server::join(int const client_fd, cmd_struct cmd_infos)
{
	Client *client = this->getClient(client_fd);
	std::string client_nickname = client->getNickname();
	std::vector<std::string>	channel_name;
	std::vector<std::string>	keys;
	
	if (cmd_infos.message.empty() == true || cmd_infos.message_split.size() > 2 ) 
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client_nickname, cmd_infos.name));
	
	splitMessage(channel_name, cmd_infos.message_split[0], ",");
	
	splitMessage(keys, cmd_infos.message_split[1], ",");
	std::vector<std::string>::iterator it_keys = keys.begin();
	
	for (std::vector<std::string>::iterator it_channel = channel_name.begin(); it_channel != channel_name.end(); ++it_channel)
	{
		getChannelName(*it_channel);
		std::map<std::string, Channel>::iterator it			= _channels.find(*it_channel);
		if (it == _channels.end()) // si on ne le trouve pas, créer le channel
		{
			addChannel(this, *it_channel);	
		}
		else if (it->second.getMode().find('k') != std::string::npos) // Si channel en mode +k
		{
			if (it_keys == keys.end() || keys.empty())
				{
					client->setSendBuffer(ERR_NEEDMOREPARAMS(client_nickname, cmd_infos.name));
					break;
				}
			if (*it_keys != it->second.getChannelPassword())
			{
				client->setSendBuffer(ERR_BADCHANNELKEY(client_nickname, *it_channel));
				++it_keys;
				continue; // on passe la suite, au prochain channel à ajouter síl y en a un
			}
			++it_keys;
		}

		std::map<std::string, Channel>::iterator it_chan = _channels.find(*it_channel);
		// vérifier si le channel est full
		if (it_chan->second.getCapacityLimit() != -1 && (int)it_chan->second.getClientList().size() == it_chan->second.getCapacityLimit())
		{
			client->setSendBuffer(ERR_CHANNELISFULL(client_nickname, *it_channel));
			continue ; // on passe la suite, au prochain channel à ajouter síl y en a un
		}
		// vérifier si le client est banned avant de le join au channel
		if (it_chan->second.getMode().find("b") != std::string::npos && it_chan->second.isBanned(client_nickname) == true)
		{
			client->setSendBuffer(ERR_BANNEDFROMCHAN(client_nickname, *it_channel));
		} 
		else 
		{
			addClientToChannel(it_chan->second, *client);
			if (it_chan->second.getOperators().empty())
				it_chan->second.addFirstOperator(client->getNickname());
			sendChanInfos(it_chan->second, *it_channel, *client);
		}
	}
	
}

/**
 * @brief If a client’s JOIN command to the server is successful, the server MUST send, in this order:
 * 
 * 	1) A JOIN message
 * 	2) The channel's TOPIC if there is one (RPL_TOPIC)
 * 	3) The NAMES of the users in this channel
 *  
 * [:msanjuan_!msanjuan@localhost 353 msanjuan_ = #hello :@msanjuan_ ]
 */
