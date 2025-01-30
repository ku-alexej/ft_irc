/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:18 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 16:12:27 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool	isInputValid(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (false);
	}
	
	std::string port = av[1];
	if (port.find_first_not_of("0123456789") != std::string::npos) {
		std::cerr << RED << "Error: <port> must contain only numbers \"0123456789\"" << RES << std::endl;
		return (false);
	}
	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535) {
		std::cerr << RED << "Error: <port> must be in range [1024 .. 65535]" << RES << std::endl;
		return (false);
	}
	
	std::string password = av[2];
	if (password.empty()) {
		std::cout << YEL << "[WARN]: password not set" << YEL << std::endl;
	}
	
	return (true);
}

int	main(int ac, char **av) {
	if (!isInputValid(ac, av))
		return (EXIT_FAILURE);

	Server server(atoi(av[1]), av[2], SERVER_NAME);
	try {
		std::cout << GRN << "[INFO]: turning on the server" << RES << std::endl;
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		server.turnOn();
	} catch(const std::exception &e) {
		server.turnOff();
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	
	std::cout << GRN << "[INFO]: the server was closed" << RES << std::endl;
	
	return (EXIT_SUCCESS);    
}
