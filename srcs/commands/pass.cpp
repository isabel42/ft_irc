/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:56:04 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/10 12:15:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"


/**
 * @brief The PASS command is used to set a ‘connection password’.
 * The password supplied must match the one defined in the server configuration.
 * 	
 * Syntax: PASS <password>
 * 
 * Numeric replies:
 * 	ERR_NEEDMOREPARAMS (461)
 * 	ERR_ALREADYREGISTERED (462)
 * 	ERR_PASSWDMISMATCH (464)
 * 
 * Example :
 *  [CLIENT] /PASS secretpassword
 */

bool Server::pass(int const client_fd, cmd_struct cmd_infos)
{
	Client *client = this->getClient(client_fd);

	if (cmd_infos.message.empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), cmd_infos.name));
		return false;
	}
	if (_pw == cmd_infos.message)
	{
		client->setNbInfo(+1);
		return true;
	}
	client->setSendBuffer(ERR_PASSWDMISMATCH(client->getNickname()));
	if (client->isRegistrationDone() == false)
		client->setNbInfo(-1);
	return false;
	
}