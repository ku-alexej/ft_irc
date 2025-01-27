/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replyes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:11 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/27 19:25:21 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLYES_HPP
# define REPLYES_HPP

# define CRLF "\r\n"

// client = nickname of user

// --- errors ---
// "401" // WHOIS PRIVMSG
# define ERR_NOSUCHNICK(client, nickOrChannel)						"401: " + client + " " + nickOrChannel ":No such nick/channel"

// "402" // WHOIS PRIVMSG
# define ERR_NOSUCHSERVER(client, serverName)						"402: " + client + " " + serverName + " :No such server"

// "403:" // JOIN PART MODE TOPIC INVITE KICK
# define ERR_NOSUCHCHANNEL(client, channelName)						"403: " + client + " " + channelName + " :No such channel"

// "404" // PRIVMSG
# define ERR_CANNOTSENDTOCHAN(client, channelName)					"404: " + client + " " + channelName + " :Cannot send to channel"

// "405" // JOIN
# define ERR_TOOMANYCHANNELS(client, channelName)					"405: " + client + " " + channelName + " :You have joined too many channels"

// "407" // PRIVMSG
# define ERR_TOOMANYTARGETS											"407"

// "409" // PING
# define ERR_NOORIGIN(client)										"409: " + client + " :No origin specified"

// "410" // CAP
# define ERR_INVALIDCAPCMD											"410"

// "411" // PRIVMSG
# define ERR_NORECIPIENT(client, command)							"411: " + client + " :No recipient given (" + command + ")"

// "412" // PRIVMSG
# define ERR_NOTEXTTOSEND(client)									"412: " + client + " :No text to send"

// "413" // PRIVMSG
# define ERR_NOTOPLEVEL												"413"

// "414" // PRIVMSG
# define ERR_WILDTOPLEVEL											"414"

// "431" // NICK WHOIS
# define ERR_NONICKNAMEGIVEN(client)								"431: " + client + " :No nickname given"

// "432" // NICK
# define ERR_ERRONEUSNICKNAME(client, nickName)						"432: " + client + " " + nickName + " :Erroneus nickname"

// "433" // NICK
# define ERR_NICKNAMEINUSE(client, nickName)						"433: " + client + " " + nickName + " :Nickname is already in use"

// "436" // NICK
# define ERR_NICKCOLLISION(client, nickName, userName, hostName)	"436: " + client + " " + nickName + " :Nickname collision KILL from " + userName + "@" + hostName + ""

// "441" // KICK
# define ERR_USERNOTINCHANNEL(client, nickName, channelName)		"441: " + client + " " + nickName + " " + channelName + " :They aren't on that channel"

// "442" // PART TOPIC INVITE KICK
# define ERR_NOTONCHANNEL(client, channelName)						"442: " + client + " " + channelName + " :You're not on that channel"

// "443" // INVITE
# define ERR_USERONCHANNEL(client, nickName, channelName)			"443: " + client + " " + nickName + " " + channelName + " :is already on channel"

// "461" // PASS USER PING JOIN PART TOPIC INVITE KICK
# define ERR_NEEDMOREPARAMS(client, command)						"461: " + client + " " + command + " :Not enough parameters"

// "462" // PASS USER
# define ERR_ALREADYREGISTERED(client)								"462: " + client + " :You may not reregister"

// "464" // PASS
# define ERR_PASSWDMISMATCH(client)									"464: " + client + " :Password incorrect"

// "471" // JOIN
# define ERR_CHANNELISFULL(client, channelName)						"471: " + client + " " + channelName + " :Cannot join channel (+l)"

// "473" // JOIN
# define ERR_INVITEONLYCHAN(client, channelName)					"473: " + client + " " + channelName + " :Cannot join channel (+i)"

// "474" // JOIN
# define ERR_BANNEDFROMCHAN(client, channelName)					"474: " + client + " " + channelName + " :Cannot join channel (+b)"

// "475" // JOIN
# define ERR_BADCHANNELKEY(client, channelName)						"475: " + client + " " + channelName + " :Cannot join channel (+k)"

// "476" // JOIN
# define ERR_BADCHANMASK(channelName)								"476: " + channelName + " :Bad Channel Mask"

// "482" // MODE TOPIC INVITE KICK
# define ERR_CHANOPRIVSNEEDED(client, channelName)					"482: " + client + " " + channelName + " :You're not channel operator"


// --- replyes ---
# define RPL_WHOISCERTFP		"276" // WHOIS
# define RPL_AWAY				"301" // WHOIS PRIVMSG
# define RPL_WHOISREGNICK		"307" // WHOIS
# define RPL_WHOISUSER			"311" // WHOIS
# define RPL_WHOISSERVER		"312" // WHOIS
# define RPL_WHOISOPERATOR		"313" // WHOIS
# define RPL_WHOISIDLE			"317" // WHOIS
# define RPL_WHOISCHANNELS		"319" // WHOIS
# define RPL_WHOISSPECIAL		"320" // WHOIS
# define RPL_CHANNELMODEIS		"324" // MODE
# define RPL_CREATIONTIME		"329" // MODE
# define RPL_WHOISACCOUNT		"330" // WHOIS
# define RPL_NOTOPIC			"331" // TOPIC
# define RPL_TOPIC				"332" // JOIN TOPIC
# define RPL_TOPICWHOTIME		"333" // JOIN TOPIC
# define RPL_WHOISACTUALLY		"338" // WHOIS
# define RPL_INVITING			"341" // INVITE
# define RPL_NAMREPLY			"353" // JOIN
# define RPL_ENDOFNAMES			"366" // JOIN
# define RPL_WHOISHOST			"378" // WHOIS
# define RPL_WHOISMODES			"379" // WHOIS
# define RPL_WHOISSECURE		"671" // WHOIS

// --- QUIT
// nothing

// --- NOTICE
// newer sent reply / error back

#endif