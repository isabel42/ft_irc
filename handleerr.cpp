/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleerr.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:01:20 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/16 18:03:56 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


int	Server::handlePollerEvent(std::list<pollfd>& poll_fds, std::list<pollfd>::iterator &it)
{
	if (it->fd == _server_socket_fd)
	{
		std::cerr << "[Server] Listen socket error" << std::endl;
		return (-1);
	}
	else
	{
		delClient(poll_fds, it, it->fd);
		return (2);
	}
}