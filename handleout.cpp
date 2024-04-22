/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleout.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:48:43 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/18 11:40:06 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	sendServerRpl(int const client_fd, std::string client_buffer)
{
	std::istringstream	buf(client_buffer);
	std::string			reply;
	
	send(client_fd, client_buffer.c_str(), client_buffer.size(), 0);
	while (getline(buf, reply))
	{
		std::cout << "[Server] Message sent to client " \
				  << client_fd << "       >> " << reply << std::endl;
	}
}

int	Server::handlePolloutEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd)
{
	Client *client = this->getClient(current_fd);

	if (!client)
		std::cout << "[Server] Did not found connexion to client sorry" << std::endl;
	else
	{
	// send(client_fd, client_buffer.c_str(), client_buffer.size(), 0);
		sendServerRpl(current_fd, client->getSendBuffer());
		client->getSendBuffer().clear();
		if (client->getDeconnexionStatus() == true)
		{
			delClient(poll_fds, it, current_fd);
			return (2);
		}
	}
	return (0);
}