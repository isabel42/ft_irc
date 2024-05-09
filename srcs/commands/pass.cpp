/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:56:04 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 16:22:05 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

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