/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateClientCon.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:04:56 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/16 15:47:33 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void Server::addClient(int client_socket, std::list<pollfd> &poll_fds)
{
	pollfd client_pollfd;
	Client new_client(client_socket);

	// client_pollfd.fd = client_socket;
	client_pollfd.events = POLLIN | POLLOUT; 
	poll_fds.push_back(client_pollfd);
	_nb_clients++;

	_clients.insert(std::pair<int, Client>(client_socket, new_client)); // insert a new nod in client map with the fd as key
	std::cout << "[Server] Added client #" << client_socket << " successfully" << std::endl;
}

static int acceptSocket(int listenSocket)
{
	sockaddr_in client;
	socklen_t addr_size = sizeof(sockaddr_in);
	return (accept(listenSocket, (sockaddr *)&client, &addr_size));
}

static void	tooManyClients(int client_socket)
{
	const char * error = "[Server] You cannot join, the server is already full";
	std::cout << error << std::endl;
	send(client_socket, &error, strlen(error) + 1, 0);
	close(client_socket);
}

int	Server::createClientConnexion(std::list<pollfd>& poll_fds, std::list<pollfd>& new_pollfds)
{
	int client_sock = acceptSocket(_server_socket_fd); // Accepts the socket and returns a dedicated fd for this new Client-Server connexion
	if (client_sock == -1)
	{
		std::cerr << "[Server] Accept() failed" << std::endl;
		return (3);
	}
	if (poll_fds.size() - 1 < 10)
		addClient(client_sock, new_pollfds); // Beware, here we push the new client_socket in NEW_pollfds
	else
		tooManyClients(client_sock);
	return (1);
}