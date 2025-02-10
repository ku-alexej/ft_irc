/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdINVITE.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:03 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:30:23 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
/*

INVITE message
     Command: INVITE
  Parameters: <nickname> <channel>
The INVITE command is used to invite a user to a channel. The parameter <nickname> is the nickname of the person to be invited to the target channel <channel>.

The target channel SHOULD exist (at least one user is on it). Otherwise, the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

Only members of the channel are allowed to invite other users. Otherwise, the server MUST reject the command with the ERR_NOTONCHANNEL numeric.

Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric. In particular, they SHOULD reject it when the channel has invite-only mode set, and the user is not a channel operator.

If the user is already on the target channel, the server MUST reject the command with the ERR_USERONCHANNEL numeric.

When the invite is successful, the server MUST send a RPL_INVITING numeric to the command issuer, and an INVITE message, with the issuer as <source>, to the target user. Other channel members SHOULD NOT be notified.

Numeric Replies:

RPL_INVITING (341)
ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERONCHANNEL (443)
Command Examples:

  INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
Message Examples:

  :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
                                        to the channel #test
See also:

IRCv3 invite-notify Extension
Invite list
Servers MAY allow the INVITE with no parameter, and reply with a list of channels the sender is invited to as RPL_INVITELIST (336) numerics, ending with a RPL_ENDOFINVITELIST (337) numeric.
*/

void Server::cmdInvite(std::vector<std::string> tokens, int fd)
{

  std::string channelName;
  std::string userName;
  Channel *channel;
  userName = tokens[1];
  channelName = tokens[2];
  Client *c = getClientByFd(fd);
  Client *invitedUser = getClientByNick(userName);
  channel = getChannel(channelName);

  if (tokens.size() < 2)
  {
    c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
    return;
  }
  if (channel == NULL)
  {
    c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelName));
    return;
  }
  if (!invitedUser)
  {
    c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), userName));
    return;
  }
  if (invitedUser->getRegistred() == false) {
		invitedUser->setReplyBuffer(ERR_NOTREGISTERED(invitedUser->getNickname()));
		return ;
	}
  if (channel->getClientByFd(c->getFd()) == NULL)
  {
    c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelName));
    return;
  }
  if (channel->getClientByFd(invitedUser->getFd()))
  {
    c->setReplyBuffer(ERR_USERONCHANNEL(c->getNickname(), invitedUser->getNickname(), channelName));
    return;
  }
  if (channel->getI() == true && channel->getOperatorByFd(c->getFd()) == NULL)
  {
    c->setReplyBuffer(ERR_CHANOPRIVSNEEDED(c->getNickname(), channelName));
    return;
  }
  if (invitedUser->isInvitedToChannel(channelName))
    return;

  invitedUser->addInvite(channelName);
  c->setReplyBuffer(RPL_INVITING(c->getNickname(), userName, channelName));

  std::stringstream ss;
  ss << c->getNickname() << " INVITE " << userName << " " << channelName;
  invitedUser->setReplyBuffer(ss.str());
}
