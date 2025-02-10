/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replyes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:11 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/10 15:43:00 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLYES_HPP
# define REPLYES_HPP

# define CRLF			"\r\n"
# define CMD_LEN		512
# define SERVER_NAME	"DarkForest"

// client = nickname of user

# define MODE_SET(client, userName, hostName, channelName, mode, variable)	std::string(":") + (client.empty() ? "*" : client) + "!" + userName + "@" + hostName + " MODE " + channelName + " " + mode + " " + variable + ""
# define JOIN_OK(client, userName, hostName, channelName)					std::string(":") + (client.empty() ? "*" : client) + "!" + userName + "@" + hostName + " JOIN " + channelName + ""
# define QUIT_CHANNEL(client, userName, hostName, msg)						std::string(":") + (client.empty() ? "*" : client) + "!" + userName + "@" + hostName + " QUIT :" + msg + ""
# define QUIT_SERVER(msg)													"ERROR :" + msg + ""

// --- errors ---
# define ERR_NOSUCHNICK(client, nickOrChannel)							"401 " + (client.empty() ? "*" : client) + " " + nickOrChannel + " :No such nick/channel"
# define ERR_NOSUCHSERVER(client, serverName)							"402 " + (client.empty() ? "*" : client) + " " + serverName + " :No such server"
# define ERR_NOSUCHCHANNEL(client, channelName)							": 403 " + (client.empty() ? "*" : client) + " " + channelName + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(client, channelName)						"404 " + (client.empty() ? "*" : client) + " " + channelName + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(client, channelName)						"405 " + (client.empty() ? "*" : client) + " " + channelName + " :You have joined too many channels"
# define ERR_TOOMANYTARGETS												"407"
# define ERR_NOORIGIN(client)											"409 " + (client.empty() ? "*" : client) + " :No origin specified"
# define ERR_INVALIDCAPCMD												"410"
# define ERR_NORECIPIENT(client, command)								"411 " + (client.empty() ? "*" : client) + " :No recipient given (" + command + ")"
# define ERR_NOTEXTTOSEND(client)										"412 " + (client.empty() ? "*" : client) + " :No text to send"
# define ERR_NOTOPLEVEL													"413"
# define ERR_WILDTOPLEVEL												"414"
# define ERR_UNKNOWNCOMMAND(client, command)							"421 " + (client.empty() ? "*" : client) + " " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(client)									"431 " + (client.empty() ? "*" : client) + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(client, nickName)							"432 " + (client.empty() ? "*" : client) + " " + nickName + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(client, nickName)							"433 " + (client.empty() ? "*" : client) + " " + nickName + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(client, nickName, channelName)			"441 " + (client.empty() ? "*" : client) + " " + nickName + " " + channelName + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(client, channelName)							"442 " + (client.empty() ? "*" : client) + " " + channelName + " :You're not on that channel"
# define ERR_USERONCHANNEL(client, nickName, channelName)				"443 " + (client.empty() ? "*" : client) + " " + nickName + " " + channelName + " :is already on channel"
# define ERR_NOTREGISTERED(client)										"451 " + (client.empty() ? "*" : client) + ":You have not registered"
# define ERR_NEEDMOREPARAMS(client, command)							"461 " + (client.empty() ? "*" : client) + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(client)									"462 " + (client.empty() ? "*" : client) + " :You may not reregister"
# define ERR_PASSWDMISMATCH(client)										"464 " + (client.empty() ? "*" : client) + " :Password incorrect"
# define ERR_CHANNELISFULL(client, channelName)							"471 " + (client.empty() ? "*" : client) + " " + channelName + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(client, modechar)								"472 " + (client.empty() ? "*" : client) + " " + modechar + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(client, channelName)						"473 " + (client.empty() ? "*" : client) + " " + channelName + " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN(client, channelName)						"474 " + (client.empty() ? "*" : client) + " " + channelName + " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY(client, channelName)							"475 " + (client.empty() ? "*" : client) + " " + channelName + " :Cannot join channel (+k)"
# define ERR_BADCHANMASK(channelName)									"476 " + channelName + " :Bad Channel Mask"
# define ERR_CHANOPRIVSNEEDED(client, channelName)						"482 " + (client.empty() ? "*" : client) + " " + channelName + " :You're not channel operator"
# define ERR_USERSDONTMATCH(client)										"502 " + (client.empty() ? "*" : client) + " :Cant change mode for other users"
# define ERR_UMODEUNKNOWNFLAG(client, flag)								"501 " + (client.empty() ? "*" : client) + " :Unknown user MODE flag " + flag + ""
# define ERR_INVALIDMODEPARAM(client, target, mode, param, msg)			"696 " + (client.empty() ? "*" : client) + " " + target + " " + mode + " " + param + " :" + msg + ""

// --- replyes ---
# define RPL_WELCOME(client, nickName, userName, hostName)				"001 " + (client.empty() ? "*" : client) + " :Welcome to the IRC Network, " + nickName + "!~" + userName + "@" + hostName
# define RPL_ISSUPPORT(client)											"005 " + (client.empty() ? "*" : client) + \
																		" CHANMODES=,o,lk,ti" + \
																		" CASEMAPPING=ascii" + \
																		" CHANTYPES=#" + \
																		" PREFIX=(o)@" + \
																		" :are supported by this server"
# define RPL_UMODEIS(client, userModes)									"221 " + (client.empty() ? "*" : client) + " " + userModes + ""
# define RPL_WHOISCERTFP(client, nickName, fingerprint)					"276 " + (client.empty() ? "*" : client) + " " + nickName + " :has client certificate fingerprint " + fingerprint + ""
# define RPL_AWAY(client, nickName, msg)								"301 " + (client.empty() ? "*" : client) + " " + nickName + " :" + msg + ""
# define RPL_WHOISREGNICK(client, nickName)								"307 " + (client.empty() ? "*" : client) + " " + nickName + " :has identified for this nick"
# define RPL_WHOISUSER(client, nickName, userName, hostname, realName)	"311 " + (client.empty() ? "*" : client) + " " + nickName + " ~" + userName + " " + hostname + " * :" + realName + ""
# define RPL_WHOISSERVER(client, nickName, serverName, serverInfo)		"312 " + (client.empty() ? "*" : client) + " " + nickName + " " + serverName + " :" + serverInfo + ""
# define RPL_WHOISOPERATOR(client, nickName)							"313 " + (client.empty() ? "*" : client) + " " + nickName + " :is an IRC operator"
# define RPL_ENDOFWHO(client, mask)										"315 " + (client.empty() ? "*" : client) + " " + mask + " :End of WHO list"
# define RPL_WHOISIDLE(client, nickName, secs, signon)					"317 " + (client.empty() ? "*" : client) + " " + nickName + " " + secs + " " + signon + " :seconds idle, signon time"
# define RPL_ENDOFWHOIS(client, nickName)								"318 " + (client.empty() ? "*" : client) + " " + nickName + " :End of /WHOIS list"
# define RPL_WHOISCHANNELS(client, nickName, channelName)				"319 " + (client.empty() ? "*" : client) + " " + nickName + " :[prefix]" + channelName + "{ [prefix]" + channelName + "}"
# define RPL_WHOISSPECIAL(client, nickName)								"320 " + (client.empty() ? "*" : client) + " " + nickName + " :blah blah blah"
# define RPL_CHANNELMODEIS(client, channelName, modeString, modeArgs)	"324 " + (client.empty() ? "*" : client) + " " + channelName + " " + modeString + " " + modeArgs + ""
# define RPL_CREATIONTIME(client, channelName, creationTime)			"329 " + (client.empty() ? "*" : client) + " " + channelName + " " + creationTime + ""
# define RPL_WHOISACCOUNT(client, nickName, account)					"330 " + (client.empty() ? "*" : client) + " " + nickName + " " + account + " :is logged in as"
# define RPL_NOTOPIC(client, channelName)								"331 " + (client.empty() ? "*" : client) + " " + channelName + " :No topic is set"
# define RPL_TOPIC(client, channelName, topic)							"332 " + (client.empty() ? "*" : client) + " " + channelName + " :" + topic + ""
# define RPL_TOPICWHOTIME(client, channelName, nickName, setat)			"333 " + (client.empty() ? "*" : client) + " " + channelName + " " + nickName + " " + setat + ""
# define RPL_WHOISACTUALLY(client, nickName)							"338 " + (client.empty() ? "*" : client) + " " + nickName + " :is actually ..."
# define RPL_INVITING(client, nickName, channelName)					"341 " + (client.empty() ? "*" : client) + " " + nickName + " " + channelName + ""
# define RPL_NAMREPLY(client, symbol, channelName, nickList)			"353 " + (client.empty() ? "*" : client) + " " + symbol + " " + channelName + " :" + nickList + ""
# define RPL_ENDOFNAMES(client, channelName)							"366 " + (client.empty() ? "*" : client) + " " + channelName + " :End of /NAMES list"
# define RPL_ENDOFBANLIST(client, channelName)							"368 " + (client.empty() ? "*" : client) + " " + channelName + " :End of channel ban list"
# define RPL_WHOISHOST(client, nickName)								"378 " + (client.empty() ? "*" : client) + " " + nickName + " :is connecting from *@localhost 127.0.0.1"
# define RPL_WHOISMODES(client, nickName)								"379 " + (client.empty() ? "*" : client) + " " + nickName + " :is using modes +ailosw"
# define RPL_WHOISSECURE(client, nickName)								"671 " + (client.empty() ? "*" : client) + " " + nickName + " :is using a secure connection"

#endif