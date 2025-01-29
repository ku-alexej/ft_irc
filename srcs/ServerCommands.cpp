/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 18:00:17 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void    Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens;
	tokens = splitIrssiCommandinToken(cmd);
	
	std::cout << "[INFO]: " << GRN << "token=" << RES;
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
}
