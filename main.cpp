/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:35:26 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/02 23:12:33 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static void	signal_handler(int signal)
{
	(void)signal;
	server_shutdown = true;
}

int main(int argc, char **argv)
{

	if (argc == 3)
	{
		time_t rawtime;
		struct tm * timeinfo;

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		signal(SIGINT, signal_handler);
		Server server(argv[1], argv[2], timeinfo);

		// char filename[39] = "srcs/config/ManageServOperators.config";
		// server.readFromConfigFile(filename);
		
		// // The three following functions calls are just set up
		// server.setHints();
		if (server.fillServinfo(argv[1]) == 0)
			return (0);
		// server.launchServer();
		// // Below, the main loop for server/client connection
		// try
		// {
		// 	server.manageServerLoop();
		// }
		// catch(const std::exception& e) 
		// {
		// 	std::cerr << RED << "Caught exception : " << RESET << e.what() << std::endl;
		// }

		return (1);
	}
	else
	{
		std::cout << "Correct usage is ./ircserv [port] [password] :)" << std::endl;
		return (0);
	}
	
}