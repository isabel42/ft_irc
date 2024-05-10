/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:08:04 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/10 12:22:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"


/**
 * @brief The PING command is sent to check the other side of the connection is still
 * 		connected, and/or to check for connection latency.
 * 
 * 		When receiving a PING message, clients or servers must reply to it with a
 * 		PONG message with the same <token> value. 
 * 
 * 		Numeric replies:
 * 		461 - ERR_NEEDMOREPARAMS -  "<client> <command> :Not enough parameters" > DEALT BY IRSSI
 * 		409 - ERR_NOORIGIN - "<client> :No origin specified" (when <token> is empty) > DEALT BY IRSSI
 * 
 * 		IRSSI :
 * 		With this reference client, sending a PING to a server sends a CTCP request
 * 		to a nickname or a channel. Using the char '*' pings every user in a channel.
 * 		Syntax : PING [<nick> | <channel> | *]
 * 
 * @return SUCCESS (0) or FAILURE (1) 
 */

 int Server::ping(int client_fd, cmd_struct cmd_infos)
 {
	 Client *client = this->getClient(client_fd);
	 cmd.message.insert(0, ":");
	 client->RPL_PONG(user_id(nickname, username), cmd.message));
 }