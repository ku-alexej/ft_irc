/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdWHO.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:16 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/03 12:38:02 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdWho(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);

	if (tokens.size() >= 2  || !tokens[1].empty()) {
		c->setReplyBuffer(RPL_ENDOFWHO(c->getNickname(), tokens[1]));
		return ;
	}
	
	c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
}
