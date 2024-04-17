/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hadlein.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:34 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/16 17:47:26 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::delClient(std::list<pollfd> &poll_fds, std::list<pollfd>::iterator &it, int current_fd)
{
	std::cout << "[Server] Deconnection of client #" << current_fd << std::endl;

	int key = current_fd;

	close(current_fd);
	_clients.erase(key);
	poll_fds.erase(it);
	_nb_clients--;

	std::cout << "[Server] " << "Client deleted. Total Client is now: " << _nb_clients << std::endl;
}

Client*	Server::getClient(int const client_fd)
{
	// std::map<const int, Client>&		client_list = server->getClients();
	std::map<const int, Client>::iterator it_client = _clients.find(client_fd);
	
	if (it_client == _clients.end())
		return (NULL);
	return (&it_client->second);
}

int	Server::handleExistingConnexion(std::list<pollfd>& poll_fds, std::list<pollfd>::iterator &it)
{
	Client *client;
	client = getClient(it->fd);
	char message[BUF_SIZE_MSG];
	int read_count;
	
	memset(message, 0, sizeof(message));
	read_count = recv(it->fd, message, BUF_SIZE_MSG, 0); // Retrieves the Client's message

	if (read_count == -1) // when recv returns an error
	{
		std::cerr << "[Server] Recv() failed [456]" << std::endl;
		delClient(poll_fds, it, it->fd);
		return (2);
	}
	else if (read_count == 0) // when a client disconnects
	{
		std::cout << "[Server] A client just disconnected\n";
		delClient(poll_fds, it, it->fd);
		return (2);
	}
	else
	{
		// if (message)
			std::cout << std::endl <<  "[Client] Message received from client "<< it->fd << " << "<< message << std::endl;
		// print("[Client] Message received from client ", it->fd, message); // si affichage incoherent regarder ici
		client->setReadBuffer(message);

		if (client->getReadBuffer().find("\r\n") != std::string::npos)
		{
			std::cout << client->getReadBuffer();
			// try 
			// {
			// 	parseMessage(it->fd, client->getReadBuffer());
			// 	if (client->getReadBuffer().find("\r\n"))
			// 		client->getReadBuffer().clear();
			// }
			// catch(const std::exception& e) 
			// { 
			// 	std::cout << "[SERVER] Caught exception : ";
			// 	std::cerr << e.what() << std::endl;
			// 	if (client->isRegistrationDone() == true)
			// 		client->setDeconnexionStatus(true);
			// 	return (BREAK);
			// }
		}
	}
	return (0);
}