/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:26 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 17:58:45 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	toLower(std::string str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = std::tolower(str[i]);
		else if (str[i] == '[')
			str[i] = '{';
		else if (str[i] == ']')
			str[i] = '}';
		else if (str[i] == '~')
			str[i] = '^';
	}
	return (str);
}

void	Server::cmdNick(std::vector<std::string> tokens, int fd) {
	
	// std::cout << "cmdNick - 0" << std::endl;
	//check the name/nick is set
	Client *c = getClientByFd(fd);
	
	if (tokens.size() < 2 || tokens[1].empty()) {
		// std::cout << "cmdNick - 1" << std::endl;
		c->setReplyBuffer(ERR_NONICKNAMEGIVEN(c->getNickname()));
		// std::cout << "[NICK] is not defined" << std::endl;
		return ;
	}
	
	if (tokens[1].find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~[]{}^") != std::string::npos) {
		// std::cout << "cmdNick - 2" << std::endl;
		c->setReplyBuffer(ERR_ERRONEUSNICKNAME(c->getNickname(), tokens[1]));
		return ;
	}

	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (toLower(tokens[1]) == toLower(it->getNickname())) {
			// std::cout << "cmdNick - 3" << std::endl;
			c->setReplyBuffer(ERR_NICKNAMEINUSE(c->getNickname(), tokens[1]));
			return ;
		}
	}
		
	c->setNickname(tokens[1]);
	if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "", !c->getCapOn()) {
		// std::cout << "cmdNick - 4" << std::endl;
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getIp()));
	}
	std::cout << "cmdNick - X nick=[" << c->getNickname() << "]" << std::endl;
}