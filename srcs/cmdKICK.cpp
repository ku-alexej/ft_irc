/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:08 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:30:42 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void Server::cmdKick(std::vector<std::string> tokens, int fd)
{
	std::string channelName = tokens[1];
	std::string comment =  "Very boring and speaks about frogs all the time.";
	Client *c = getClientByFd(fd);

	if (tokens.size() < 3)
	{
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
		return;
	}
	if (tokens.size() > 3)
	{
		comment.clear();
		for (size_t i = 3; i < tokens.size(); ++i)
		{
			if (i != 2)
			{
				comment += " ";
			}
			comment += tokens[i];
		}
	}
	std::cout << "COMMENT" << comment << std::endl;
	Channel *channel = getChannel(channelName);
	if (!channel)
	{
		c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelName));
		return;
	}

	if (!channel->getClientByFd(c->getFd()))
	{
		c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelName));
		return;
	}

	if (channel->getOperatorByFd(c->getFd()) == NULL)
	{
		c->setReplyBuffer(ERR_CHANOPRIVSNEEDED(c->getNickname(), channelName));
		return;
	}

	std::vector<std::string> usersToKick = split(tokens[2], ',');

	for (size_t i = 0; i < usersToKick.size(); ++i)
	{
		std::string userName = usersToKick[i];
		Client *userToKick = getClientByNick(userName);

		if (!userToKick)
		{
			c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), userName));
			continue;
		}

		if (!channel->getClientByFd(userToKick->getFd()))
		{
			c->setReplyBuffer(ERR_USERNOTINCHANNEL(c->getNickname(), userName, channelName));
			continue;
		}

		std::stringstream ss;
		ss << c->getUserID() << " KICK " << channelName << " " << userName << " :" << comment;
		channel->deleteClient(userToKick);
		channel -> deleteOperator(userToKick);
		userToKick -> deleteChannel(channelName);
		channel->setReplyBufferForAllChannelClients(ss.str());
		userToKick->setReplyBuffer(ss.str());
		deleteEmptyChannel(channel);
	}
}
