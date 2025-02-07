/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPART.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:30:54 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::cmdPart(std::vector<std::string> tokens, int fd)
{
	std::vector<std::string> channelsNames;
	std::vector<std::string> channelsKeys;
	Channel *channel;
	std::stringstream msg;
	std::string reason;

	Client *c = getClientByFd(fd);

	if (tokens.size() < 2)
	{
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
		return;
	}
	channelsNames = split(tokens[1], ',');
	if (tokens.size() > 2)
	{
		for (size_t i = 2; i < tokens.size(); ++i)
		{
			if (i != 2)
				reason += " ";
			reason += tokens[i];
		}
	}
	reason.erase(0, 1);
	for (size_t i = 0; i < channelsNames.size(); i++)
	{
		channel = getChannel(channelsNames[i]);
		if (!channel)
		{
			c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelsNames[i]));
			return;
		}
		if (!(channel->isMember(c->getNickname())))
		{
			c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelsNames[i]));
			return;
		}
		if (reason.empty())
			msg << c->getUserID() << " PART " << channel->getName();
		else
			msg << c->getUserID() << " PART " << channel->getName() << " :" << reason;
		c->setReplyBuffer(msg.str());
		c->deleteChannel(channelsNames[i]);
		if (channel->isOperator(c->getNickname()))
			channel->deleteOperator(c);
		channel->deleteClient(c);
		channel->setReplyBufferForAllChannelClients(msg.str());
	}
	if (channel->isEmpty())
	{
		std::vector<Client *> clients = channel->getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			(*it)->deleteInvite(channel->getName());
		}
		removeChannel(channel->getName());
	}
}
