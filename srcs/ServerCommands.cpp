/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:14:44 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens;
	tokens = splitIrssiCommandinToken(cmd);

	std::cout << "[INFO]: " << YEL << "fd=" << RES << fd << GRN << " token=" << RES;
	printStringVector(tokens);

	std::cout << "[INFO]: try to handle \'" << YEL << tokens[0] << RES << "\'" << std::endl;
	if (tokens[0] == "CAP")
		cmdCap(tokens, fd);
	if (tokens[0] == "PASS")
		cmdPass(tokens, fd);
	if (tokens[0] == "NICK")
		cmdNick(tokens, fd);
	if (tokens[0] == "USER")
		cmdUser(tokens, fd);
	if (tokens[0] == "PING")
		cmdPing(tokens, fd);
	if (tokens[0] == "WHOIS")
		cmdWhois(tokens, fd);
	if (tokens[0] == "JOIN")	// join channel
		cmdJoin(tokens, fd);
	if (tokens[0] == "PART")	// leave channel
		cmdPart(tokens, fd);
	if (tokens[0] == "TOPIC")	// show/change channel topic
		cmdTopic(tokens, fd);
	if (tokens[0] == "INVITE")	// invite to channel
		cmdInvite(tokens, fd);
	if (tokens[0] == "KICK")	// kick from channel (reason is optional)
		cmdKick(tokens, fd);
	if (tokens[0] == "MODE")	// change channel modes i, t, k, o, l
		cmdMode(tokens, fd);
	if (tokens[0] == "QUIT")	// leave the server
		cmdQuit(tokens, fd);
}
