/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:31:50 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/08 16:36:28 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include <stdio.h>
#include <string.h>
#include <netdb.h>

# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <cstdlib>
# include <vector>
# include <map>
# include <list>
# include <unistd.h>
# include <sstream>
# include <string>
# include <cerrno>
# include <ctime>
# include <stdlib.h>

# include <fcntl.h>

#include "NumRpy.hpp"
#include "Utils.hpp"
#include "Client.hpp"


#define BUF_SIZE_MSG 4096

extern bool	server_shutdown;

// struct cmd_struct
// {
// 	std::string	prefix;
// 	std::string	name;
// 	std::string	message;
// 	std::vector<std::string>	message_split;
// };

#endif