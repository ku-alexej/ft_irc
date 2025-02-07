/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQUIT.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:14 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/07 19:42:10 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdQuit(std::vector<std::string> tokens, int fd) {

	Client		*c = getClientByFd(fd);
	std::string	msg = "Quit:";
	(void) c;

	if (tokens[1][0] == ':') {
		tokens[1].erase(tokens[1].begin());
	}

	for (size_t i = 1; i < tokens.size(); i++) {
		msg += " " + tokens[i];
	}

	std::cout << "It is a reason for QUIT msg=[" << msg << "]" << std::endl;

	c->clearReplyBuffer();
	std::vector<std::string> channelsNames = c->getChannelNames();
	for (std::vector<std::string>::iterator it = channelsNames.begin(); it != channelsNames.end(); it++) {
		Channel *ch = getChannel(*it);
		ch->deleteOperator(c);
		ch->deleteClient(c);
		ch->setReplyBufferForAllChannelClients(QUIT_CHANNEL(c->getNickname(), c->getUsername(), c->getHostname(), msg));
	}

	c->setReplyBuffer(QUIT_SERVER(c->getNickname(), msg));
	sentReply(fd);

	close(fd);
	deleteClient(*c);
	for (size_t i = 0; i < _fds.size(); i++) {
		if (_fds[i].fd == fd) {
			deleteFromFds(i);
			return ;
		}
	}
}
