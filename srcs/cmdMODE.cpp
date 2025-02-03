/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:10 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/03 19:23:12 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdUserMode(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);
	Client *t = getClientByNick(tokens[1]);

	if (t == NULL) {
		c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), tokens[1]));
		return ;
	}

	if (c->getNickname() != tokens[1]) {
		c->setReplyBuffer(ERR_USERSDONTMATCH(c->getNickname()));
		return ;
	}

	if (tokens.size() == 2) {
		c->setReplyBuffer(RPL_UMODEIS(c->getNickname(), ""));
		return ;
	}

	c->setReplyBuffer(ERR_UMODEUNKNOWNFLAG(c->getNickname()));
}

bool	isUsableMode(std::string mode) {
	if (mode[1] == 't' || mode[1] == 'i' || mode[1] == 'l' || mode[1] == 'k' || mode[1] == 'o')
		return (true);
	return (false);
}

bool	isValueNeeded(const char c, const char sign) {
	if (sign == '+')
		if (c == 'l' || c == 'k' || c == 'o')
			return (true);
	if (sign == '-')
		if (c == 'k' || c == 'o')
			return (true);
	return (false);
}

void	Server::setModeT(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	(void) fd;
	(void) mode;
	(void) variable;
}

void	Server::setModeI(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	(void) fd;
	(void) mode;
	(void) variable;
}

void	Server::setModeL(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	(void) fd;
	(void) mode;
	(void) variable;
}

void	Server::setModeK(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	(void) fd;
	(void) mode;
	(void) variable;
}

void	Server::setModeO(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	(void) fd;
	(void) mode;
	(void) variable;
}


void	Server::setMode(std::vector<std::string> tokens, int fd, std::string mode, std::string variable) {
	(void) tokens;
	// Client *c = getClientByFd(fd);

	std::cout << "try to set [" + mode + "]=[" + variable + "]";

	if (isValueNeeded(mode[1], mode[0]) && variable.empty()) {					// ignore mode
		std::cout << " FAIL: no variable" << std::endl;
		return ;
	}

	switch (mode[1]) {															// set mode
		case 't':
			setModeT(tokens, fd, mode, variable);
			std::cout << " TRY" << std::endl;
			break;
		case 'i':
			setModeI(tokens, fd, mode, variable);
			std::cout << " TRY" << std::endl;
			break;
		case 'l':
			setModeL(tokens, fd, mode, variable);
			std::cout << " TRY" << std::endl;
			break;
		case 'k':
			setModeK(tokens, fd, mode, variable);
			std::cout << " TRY" << std::endl;
			break;
		case 'o':
			setModeO(tokens, fd, mode, variable);
			std::cout << " TRY" << std::endl;
			break;
	}

}

	// std::map<std::string, std::string> modesToUse = getModes(tokens),;
	// runModes(modesToUse);
void	Server::runModes(std::vector<std::string> tokens, int fd) {
	std::vector<std::pair<std::string, std::string> > modesToUse;
	std::string sign = "+";
	Client *c = getClientByFd(fd);

	std::string modestring = tokens[2];
	size_t variableIndex = 3;
	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == '+') {
			sign = "+";
			continue;
		} else if (modestring[i] == '-') {
			sign = "-";
			continue;
		}
		if (isValueNeeded(modestring[i], sign[0])) {
			std::string mode = sign + modestring[i];
			std::string variable = (variableIndex < tokens.size()) ? tokens[variableIndex] : "";
			modesToUse.push_back(std::make_pair(mode, variable));
			variableIndex++;
		} else {
			std::string mode = sign + modestring[i];
			modesToUse.push_back(std::make_pair(mode, ""));
		}
	}

	std::cout << "[MODE]=[variable]" << std::endl;
	for (std::vector<std::pair<std::string, std::string> >::iterator it = modesToUse.begin(); it != modesToUse.end(); it++) {
		std::cout << "[" + it->first + "]=[" + it->second + "]" << std::endl;
	}

	//here we try to set each mode
	for (std::vector<std::pair<std::string, std::string> >::iterator it = modesToUse.begin(); it != modesToUse.end(); it++) {
		if (isUsableMode(it->first))
			setMode(tokens, fd, it->first, it->second);
		else
			c->setReplyBuffer(ERR_UNKNOWNMODE(c->getNickname(), it->first));
	}
}


void	Server::cmdChannelMode(std::vector<std::string> tokens, int fd) {
	// ERR_NOSUCHCHANNEL (403)
	// RPL_CREATIONTIME (329)		-- optional, can skip it
	// RPL_CHANNELMODEIS (324)
	// ERR_CHANOPRIVSNEEDED (482)

	// When the server is done processing the modes,
	// a MODE command is sent to all members of the channel containing the mode changes.

	// -i [---]
	// +i [---]								>> ERR_INVITEONLYCHAN (473)

	// -t [---]
	// +t [---]								>> ERR_NEEDMOREPARAMS (461)
	//										>> ERR_NOSUCHCHANNEL (403)
	//										>> ERR_NOTONCHANNEL (442)
	//										>> ERR_CHANOPRIVSNEEDED (482)
	//										>> RPL_NOTOPIC (331)
	//										>> RPL_TOPIC (332) + RPL_TOPICWHOTIME (333)

	// -k [current password]
	// +k [password to set]					>> ERR_INVALIDMODEPARAM ()
	//										>> ERR_INVALIDKEY ()
	//										>> ERR_BADCHANNELKEY (475)

	// -o [nickneme to remove op rights]
	// +o [nickname to give op rights]		>> This mode is standard. The prefix and mode letter used for it, respectively, are "@" and "+o".
	//										>> Users with this mode may perform channel moderation tasks such as kicking users, applying channel modes,
	//										>> and set other users to operator (or lower) status.

	// -l [---]
	// +l [user limit]						>> ERR_CHANNELISFULL (471)

	Client	*c = getClientByFd(fd);
	Channel	*ch = getChannel(tokens[1]);

	// if (!isValidChannelName(tokens[1])) {
	// 	c->setReplyBuffer(ERR_BADCHANMASK(tokens[1]));
	// 	return;
	// }

	if (ch == NULL) {
		c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), tokens[1]));
		return ;
	}

	if (tokens.size() == 2) {
		c->setReplyBuffer(RPL_CHANNELMODEIS(c->getNickname(), ch->getName(), ch->getModes(), ch->getModesArgs(ch->getClientByFd(fd) != NULL)));
		return ;
	}

	if (tokens.size() == 3 && tokens[2] == "b") {
		c->setReplyBuffer(RPL_ENDOFBANLIST(c->getNickname(), ch->getName()));
		return ;
	}

	if (ch->getOperatorByFd(fd) == NULL) {
		c->setReplyBuffer(ERR_CHANOPRIVSNEEDED(c->getNickname(), tokens[1]));
		return ;
	}

	// use MODE
	runModes(tokens, fd);
	// runModes(modesToUse);
}

void	Server::cmdMode(std::vector<std::string> tokens, int fd) {

	Client *c = getClientByFd(fd);

	if(tokens.size() < 2 || tokens[1].empty()) {
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
		return ;
	}

	// MODE for client: we have +i in irssi afer registration

	if(tokens[1][0] != '#') {
		cmdUserMode(tokens, fd);
		return ;
	}

	if(tokens[1][0] != '#') {
		cmdUserMode(tokens, fd);
		return ;
	}

	// MODE for channel: as in subject
	if(tokens[1][0] == '#') {
		cmdChannelMode(tokens, fd);
		return ;
	}
}
