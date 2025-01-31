/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replyes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:11 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/31 15:20:01 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLYES_HPP
# define REPLYES_HPP

# define CRLF			"\r\n"
# define CMD_LEN		512
# define SERVER_NAME	"DarkForest"

// client = nickname of user

// --- errors ---
// "401" // WHOIS PRIVMSG
# define ERR_NOSUCHNICK(client, nickOrChannel)						"401 " + (client.empty() ? "empty" : client) + " " + nickOrChannel + " :No such nick/channel"
// "402" // WHOIS PRIVMSG
# define ERR_NOSUCHSERVER(client, serverName)						"402 " + (client.empty() ? "empty" : client) + " " + serverName + " :No such server"
// "403:" // JOIN PART MODE TOPIC INVITE KICK
# define ERR_NOSUCHCHANNEL(client, channelName)						"403 " + (client.empty() ? "empty" : client) + " " + channelName + " :No such channel"
// "404" // PRIVMSG
# define ERR_CANNOTSENDTOCHAN(client, channelName)					"404 " + (client.empty() ? "empty" : client) + " " + channelName + " :Cannot send to channel"
// "405" // JOIN
# define ERR_TOOMANYCHANNELS(client, channelName)					"405 " + (client.empty() ? "empty" : client) + " " + channelName + " :You have joined too many channels"
// "407" // PRIVMSG
# define ERR_TOOMANYTARGETS											"407"
// "409" // PING
# define ERR_NOORIGIN(client)										"409 " + (client.empty() ? "empty" : client) + " :No origin specified"
// "410" // CAP
# define ERR_INVALIDCAPCMD											"410"
// "411" // PRIVMSG
# define ERR_NORECIPIENT(client, command)							"411 " + (client.empty() ? "empty" : client) + " :No recipient given (" + command + ")"
// "412" // PRIVMSG
# define ERR_NOTEXTTOSEND(client)									"412 " + (client.empty() ? "empty" : client) + " :No text to send"
// "413" // PRIVMSG
# define ERR_NOTOPLEVEL												"413"
// "414" // PRIVMSG
# define ERR_WILDTOPLEVEL											"414"
// "421"
# define ERR_UNKNOWNCOMMAND(client, command)						"421 " + (client.empty() ? "empty" : client) + " " + command + " :Unknown command"
// "431" // NICK WHOIS
# define ERR_NONICKNAMEGIVEN(client)								"431 " + (client.empty() ? "empty" : client) + " :No nickname given"
// "432" // NICK
# define ERR_ERRONEUSNICKNAME(client, nickName)						"432 " + (client.empty() ? "empty" : client) + " " + nickName + " :Erroneus nickname"
// "433" // NICK
# define ERR_NICKNAMEINUSE(client, nickName)						"433 " + (client.empty() ? "empty" : client) + " " + nickName + " :Nickname is already in use"
// "436" // NICK
// # define ERR_NICKCOLLISION(client, nickName, userName, hostName)	"436 " + (client.empty() ? "empty" : client) + " " + nickName + " :Nickname collision KILL from ~" + userName + "@" + hostName + ""
// "441" // KICK
# define ERR_USERNOTINCHANNEL(client, nickName, channelName)		"441 " + (client.empty() ? "empty" : client) + " " + nickName + " " + channelName + " :They aren't on that channel"
// "442" // PART TOPIC INVITE KICK
# define ERR_NOTONCHANNEL(client, channelName)						"442 " + (client.empty() ? "empty" : client) + " " + channelName + " :You're not on that channel"
// "443" // INVITE
# define ERR_USERONCHANNEL(client, nickName, channelName)			"443 " + (client.empty() ? "empty" : client) + " " + nickName + " " + channelName + " :is already on channel"
// "461" // PASS USER PING JOIN PART TOPIC INVITE KICK
# define ERR_NEEDMOREPARAMS(client, command)						"461 " + (client.empty() ? "empty" : client) + " " + command + " :Not enough parameters"
// "462" // PASS USER
# define ERR_ALREADYREGISTERED(client)								"462 " + (client.empty() ? "empty" : client) + " :You may not reregister"
// "464" // PASS
# define ERR_PASSWDMISMATCH(client)									"464 " + (client.empty() ? "empty" : client) + " :Password incorrect"
// "471" // JOIN
# define ERR_CHANNELISFULL(client, channelName)						"471 " + (client.empty() ? "empty" : client) + " " + channelName + " :Cannot join channel (+l)"
// "473" // JOIN
# define ERR_INVITEONLYCHAN(client, channelName)					"473 " + (client.empty() ? "empty" : client) + " " + channelName + " :Cannot join channel (+i)"
// "474" // JOIN
# define ERR_BANNEDFROMCHAN(client, channelName)					"474 " + (client.empty() ? "empty" : client) + " " + channelName + " :Cannot join channel (+b)"
// "475" // JOIN
# define ERR_BADCHANNELKEY(client, channelName)						"475 " + (client.empty() ? "empty" : client) + " " + channelName + " :Cannot join channel (+k)"
// "476" // JOIN
# define ERR_BADCHANMASK(channelName)								"476 " + channelName + " :Bad Channel Mask"
// "482" // MODE TOPIC INVITE KICK
# define ERR_CHANOPRIVSNEEDED(client, channelName)					"482 " + (client.empty() ? "empty" : client) + " " + channelName + " :You're not channel operator"
// "502"
# define ERR_USERSDONTMATCH(client)									"502 " + (client.empty() ? "empty" : client) + " :Cant change mode for other users"
// "501"
# define ERR_UMODEUNKNOWNFLAG(client)								"501 " + (client.empty() ? "empty" : client) + " :Unknown MODE flag"


// --- replyes ---
// "001" // after correct pass + nick + blallala
# define RPL_WELCOME(client, nickName, userName, hostName)				"001 " + (client.empty() ? "empty" : client) + " :Welcome to the IRC Network, " + nickName + "!~" + userName + "@" + hostName

# define RPL_UMODEIS(client, userModes)									"221 " + (client.empty() ? "empty" : client) + " " + userModes + ""
// "276" // WHOIS
# define RPL_WHOISCERTFP(client, nickName, fingerprint)					"276 " + (client.empty() ? "empty" : client) + " " + nickName + " :has client certificate fingerprint " + fingerprint + ""
// "301" // WHOIS PRIVMSG
# define RPL_AWAY(client, nickName, msg)								"301 " + (client.empty() ? "empty" : client) + " " + nickName + " :" + msg + ""
// "307" // WHOIS
# define RPL_WHOISREGNICK(client, nickName)								"307 " + (client.empty() ? "empty" : client) + " " + nickName + " :has identified for this nick"
// "311" // WHOIS
# define RPL_WHOISUSER(client, nickName, userName, hostname, realName)	"311 " + (client.empty() ? "empty" : client) + " " + nickName + " ~" + userName + " " + hostname + " * :" + realName + ""
// "312" // WHOIS
# define RPL_WHOISSERVER(client, nickName, serverName, serverInfo)		"312 " + (client.empty() ? "empty" : client) + " " + nickName + " " + serverName + " :" + serverInfo + ""
// "313" // WHOIS
# define RPL_WHOISOPERATOR(client, nickName)							"313 " + (client.empty() ? "empty" : client) + " " + nickName + " :is an IRC operator"
// "317" // WHOIS
# define RPL_WHOISIDLE(client, nickName, secs, signon)					"317 " + (client.empty() ? "empty" : client) + " " + nickName + " " + secs + " " + signon + " :seconds idle, signon time"
// "318" // WHOIS
# define RPL_ENDOFWHOIS(client, nickName)								"318 " + (client.empty() ? "empty" : client) + " " + nickName + " :End of /WHOIS list"
// "319" // WHOIS
# define RPL_WHOISCHANNELS(client, nickName, channelName)				"319 " + (client.empty() ? "empty" : client) + " " + nickName + " :[prefix]" + channelName + "{ [prefix]" + channelName + "}"
// "320" // WHOIS
# define RPL_WHOISSPECIAL(client, nickName)								"320 " + (client.empty() ? "empty" : client) + " " + nickName + " :blah blah blah"
// "324" // MODE
# define RPL_CHANNELMODEIS(client, channelName, modeString, modeArgs)	"324 " + (client.empty() ? "empty" : client) + " " + channelName + " " + modeString + " " + modeArgs + "..."
// "329" // MODE
# define RPL_CREATIONTIME(client, channelName, creationTime)			"329 " + (client.empty() ? "empty" : client) + " " + channelName + " " + creationTime + ""
// "330" // WHOIS
# define RPL_WHOISACCOUNT(client, nickName, account)					"330 " + (client.empty() ? "empty" : client) + " " + nickName + " " + account + " :is logged in as"
// "331" // TOPIC
# define RPL_NOTOPIC(client, channelName)								"331 " + (client.empty() ? "empty" : client) + " " + channelName + " :No topic is set"
// "332" // JOIN TOPIC(client, nickName)
# define RPL_TOPIC(client, channelName, topic)							"332 " + (client.empty() ? "empty" : client) + " " + channelName + " :" + topic + ""
// "333" // JOIN TOPIC
# define RPL_TOPICWHOTIME(client, channelName, nickName, setat)			"333 " + (client.empty() ? "empty" : client) + " " + channelName + " " + nickName + " " + setat + ""
// "338" // WHOIS
# define RPL_WHOISACTUALLY(client, nickName)							"338 " + (client.empty() ? "empty" : client) + " " + nickName + " :is actually ..."
																	// "" + (client.empty() ? "empty" : client) + " " + nickName + " <host|ip> :Is actually using host"
																	// "" + (client.empty() ? "empty" : client) + " " + nickName + " ~" + userName + "@<hostname> <ip> :Is actually using host"
// "341" // INVITE
# define RPL_INVITING(client, nickName, channelName)					"341 " + (client.empty() ? "empty" : client) + " " + nickName + " " + channelName + ""
// "353" // JOIN
# define RPL_NAMREPLY(client, symbol, channelName, nickName)			"353 " + (client.empty() ? "empty" : client) + " " + symbol + " " + channelName + " :[prefix]" + nickName + "{ [prefix]" + nickName + "}"
// "366" // JOIN
# define RPL_ENDOFNAMES(client, channelName)							"366 " + (client.empty() ? "empty" : client) + " " + channelName + " :End of /NAMES list"
// "378" // WHOIS
# define RPL_WHOISHOST(client, nickName)								"378 " + (client.empty() ? "empty" : client) + " " + nickName + " :is connecting from *@localhost 127.0.0.1"
// "379" // WHOIS
# define RPL_WHOISMODES(client, nickName)								"379 " + (client.empty() ? "empty" : client) + " " + nickName + " :is using modes +ailosw"
// "671" // WHOIS
# define RPL_WHOISSECURE(client, nickName)								"671 " + (client.empty() ? "empty" : client) + " " + nickName + " :is using a secure connection"

// --- QUIT
// nothing

// --- NOTICE
// newer sent reply / error back

#endif