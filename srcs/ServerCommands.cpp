/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/10 20:08:11 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens = splitIrssiCommandinToken(cmd);

	if (tokens.size() < 1) {
		return;
	}
	
	std::cout << "[INFO]: " << YEL << "fd=" << RES << fd << GRN << " token=" << RES;
	printStringVector(tokens);
	std::cout << "[INFO]: try to handle \'" << YEL << tokens[0] << RES << "\'" << std::endl;

	std::map<std::string, void (Server::*)(std::vector<std::string>, int)>::iterator it;
	for (it = _cmdMap.begin(); it != _cmdMap.end(); it++) {
		if (it->first == tokens[0]) {
			(this->*(it->second))(tokens, fd);
			return ;
		}
	}

	Client *c = getClientByFd(fd);
	c->setReplyBuffer(ERR_UNKNOWNCOMMAND(c->getUsername(), tokens[0]));
	std::cout << "[ERROR]: fd=" << fd << " unknown command \"" << tokens[0] << "\"" << std::endl;
}
