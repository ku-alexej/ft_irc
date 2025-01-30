/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 19:42:07 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens = splitIrssiCommandinToken(cmd);

	std::cout << "[INFO]: " << YEL << "fd=" << RES << fd << GRN << " token=" << RES;
	printStringVector(tokens);
	std::cout << "[INFO]: try to handle \'" << YEL << tokens[0] << RES << "\'" << std::endl;

	std::map<std::string, void (Server::*)(std::vector<std::string>, int)>::iterator it;
	for (it = _cmdMap.begin(); it != _cmdMap.end(); it++) {
		// std::cout << "[INFO] it->first=[" << it->first << "]" << std::endl;
		if (it->first == tokens[0]) {
			// std::cout << "[INFO] [" << it->first << "]==[" << tokens[0] << "]" << std::endl;
			(this->*(it->second))(tokens, fd);
			return ;
		}
	}

	// here should be a reply
	std::cout << "[ERROR]: tell the client: it was unknown command \"" << tokens[0] << "\"" << std::endl;
}
