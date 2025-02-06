/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:26 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/06 12:16:39 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	toLower(std::string str) {						// after connection sent reply according Protocol: "CASEMAPPING Parameter"
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
	Client *c = getClientByFd(fd);

	if (tokens.size() < 2 || tokens[1].empty()) {
		c->setReplyBuffer(ERR_NONICKNAMEGIVEN(c->getNickname()));
		return ;
	}

	if (tokens[1].find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~[]{}^_") != std::string::npos) {
		c->setReplyBuffer(ERR_ERRONEUSNICKNAME(c->getNickname(), tokens[1]));
		return ;
	}

	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (toLower(tokens[1]) == toLower(it->getNickname())) {
			c->setReplyBuffer(ERR_NICKNAMEINUSE(c->getNickname(), tokens[1]));
			return ;
		}
	}

	std::string oldName = c->getNickname();
	c->setNickname(tokens[1]);

	// examples of possible replyes when change nickname:
	// :dan-!d@localhost NICK Mamoped
	// :WiZ NICK Kilroy					<- the code use this one

	if (!oldName.empty() && !c->getCapOn()) {
		c->setReplyBuffer(":" + oldName + " NICK " + tokens[1]);
	} else if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "" && !c->getCapOn()) {
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getHostname()));
	}
}
