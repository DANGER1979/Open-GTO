/*
	
	About: player
	Author: ziggi
	
*/

#if defined _kplayer_included
	#endinput
#endif

#define _kplayer_included
#pragma library kplayer


enum info_Player {
	Float:Armour,
	Float:Health,
	IP[MAX_IP],
	Money,
	BankMoney,
}
new gPlayer[MAX_PLAYERS][info_Player];