/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:35:26 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/25 16:46:06 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool server_shutdown = false;

static void	signal_handler(int signal)
{
	(void)signal;
	server_shutdown = true;
}

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		std::cout << "Correct usage is ./ircserv [port] [password] :)" << std::endl;
		return (0);
	}
	else
	{
		time_t rawtime;
		struct tm * timeinfo;

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		signal(SIGINT, signal_handler);
		// char filename[39] = "srcs/config/ManageServOperators.config";
		// server.readFromConfigFile(filename);
		
		try
		{
		// // The three following functions calls are just set up
			Server server(argv[1], argv[2], timeinfo);
			server.setHints();
			server.setParam();
			server.launchServer();
		// // Below, the main loop for server/client connection
			server.ServerLoop();
		}
		catch(const std::exception& e) 
		{
			std::cerr << "Caught exception : " << e.what() << std::endl;
		}

		return (1);
	}
	
}