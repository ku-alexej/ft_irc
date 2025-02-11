/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQUIT.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:14 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/11 17:20:07 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdQuit(std::vector<std::string> tokens, int fd) {

	std::string	msg = "Quit:";

	if (tokens.size() > 1) {
		if (tokens[1][0] == ':') {
			tokens[1].erase(tokens[1].begin());
			for (size_t i = 1; i < tokens.size(); i++) {
				msg += " " + tokens[i];
			}
		} else {
			msg += " " + tokens[1];
		}
	}

	disconnectClient(fd, msg);
}
