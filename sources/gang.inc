//
// Created:		14.09.06
// Aurthor:		Iain Gilbert
// Last modify 06.02.2011 by ZiGGi
//

#if defined _gang_included
  #endinput
#endif

#define _gang_included
#pragma library gang


#include "base"

new Gang_Create_Cost = GANG_CREATE_COST,
	Gang_Colour_Cost = GANG_COLOUR_COST; 

enum MemberInfo {
	member_name[MAX_PLAYER_NAME+1],
	member_playerid
}

new GangMemberInfo[MAX_GANGS][MAX_GANG_SIZE][MemberInfo];

enum GangInfo {
	bool:gang_active, //bool
	gang_name[MAX_NAME],
	gang_motd[MAX_STRING],
	gang_colour,
	gang_kills,
	gang_score,
	gang_xp,
	gang_level,
	gang_money,
	gang_house,
}
new Gangs[MAX_GANGS][GangInfo];

stock GangLoadConfig()
{
	if (!ini_Exist(ConfigDB)) return 0;
	new file_gang = ini_Open(ConfigDB);
	ini_Get(file_gang, "Gang_DB", GangDB);
	ini_GetInt(file_gang, "Gang_Create_Cost", Gang_Create_Cost);
	ini_GetInt(file_gang, "Gang_Colour_Cost", Gang_Colour_Cost);
	ini_Close(file_gang);
	return 1;
}

stock GangSaveConfig()
{
	new file_gang = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_gang, "Gang_DB", GangDB);
	ini_SetInt(file_gang, "Gang_Create_Cost", Gang_Create_Cost);
	ini_SetInt(file_gang, "Gang_Colour_Cost", Gang_Colour_Cost);
	ini_Close(file_gang);
	return 1;
}

stock gang_OnGameModeInit()
{
	GangLoadConfig();
	GameMSG("SERVER: Gang module init");
	return 1;
}

stock FindGangFreeSlot()
{
	for (new id = 1; id < MAX_GANGS; id++)
	{
		if (Gangs[id][gang_active] != true)
		{
			return id;
		}
	}
	return 0;
}

stock GangLoad(gangname[])
{
	for (new id = 1; id < MAX_GANGS; id++)
	{
		if (Gangs[id][gang_active] == true && !strcmp(gangname, Gangs[id][gang_name], false))
		{
			return id; 
		}
	}

	new gangid = FindGangFreeSlot();
	if (gangid == 0)
	{
		return GameMSG("ERROR: ��������� ���� ��� ����� �� ������");
	}
	Gangs[gangid][gang_active] = true;
	gang_load_db_ini(gangid, gangname);
	return gangid;
}

stock gang_load_db_ini(gangid, gangname[])
{
	new filename_gang[MAX_STRING];
	format(filename_gang, sizeof(filename_gang), "%s%s"GTO_FILES_FORMAT, GangDB, gangname);
	if (!ini_Exist(filename_gang)) return;
	new file_gang = ini_Open(filename_gang);
	ini_Get(file_gang, "Name", Gangs[gangid][gang_name], MAX_NAME);
	ini_Get(file_gang, "Motd", Gangs[gangid][gang_motd], MAX_STRING);
	ini_GetInt(file_gang, "Colour", Gangs[gangid][gang_colour]);
	ini_GetInt(file_gang, "Kills", Gangs[gangid][gang_kills]);
	ini_GetInt(file_gang, "Score", Gangs[gangid][gang_score]);
	ini_GetInt(file_gang, "XP", Gangs[gangid][gang_xp]);
	ini_GetInt(file_gang, "Level", Gangs[gangid][gang_level]);
	ini_GetInt(file_gang, "Money", Gangs[gangid][gang_money]);
	ini_GetInt(file_gang, "House", Gangs[gangid][gang_house]);
	for (new gangmember = 0, string[MAX_STRING]; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
		
		format(string, sizeof(string), "Member%d", gangmember);
		ini_Get(file_gang, string, GangMemberInfo[gangid][gangmember][member_name], MAX_PLAYER_NAME+1);
	}
	ini_Close(file_gang);
	return;
}

stock gang_OnPlayerCommandText(playerid, text[]) // process player commands
{
	new cmd[20], idx;
	cmd = strcharsplit(text, idx,' ');
	if (strlen(cmd) == 0) return 0;

	if (GetPlayerMuteTime(playerid) != 0)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[1][14]);
	}

	if (!strcmp(cmd, "/g", true))
 	{
		if (GetPlayerGangID(playerid) == 0 || strlen(text[idx+1]) == 0)
		{
			return 1;
		}
		new gangmessage[MAX_STRING];
	 	format(gangmessage, sizeof(gangmessage), "%s"CHAT_SHOW_ID" �����: {FFFFFF}%s", oGetPlayerName(playerid), playerid, text[idx+1]);
		SendGangMessage(GetPlayerGangID(playerid), gangmessage, COLOUR_GANG_CHAT);
		GameMSG("player: %s(%d): %s", oGetPlayerName(playerid), playerid, text[idx+1]);
		return 1;
	}
	if (!strcmp(cmd, "/gang", true))
	{
  		cmd = strcharsplit(text, idx,' ');
  		if (strlen(cmd) == 0) return 0;
  		if (!strcmp(cmd, "help", true))
  		{
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][4]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][5]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][6]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][7]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][8]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][9]);
			return 1;
  		}
  		if (!strcmp(cmd, "commands", true))
  		{
			new string[MAX_STRING];
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][10]);
			format(string, sizeof(string), lang_texts[6][11], Gang_Create_Cost);
			SendClientMessage(playerid, COLOUR_MISC, string);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][12]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][13]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][14]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][15]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][16]);
  			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][17]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][18]);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][19]);
			format(string, sizeof(string), lang_texts[6][20], Gang_Colour_Cost);
			SendClientMessage(playerid, COLOUR_MISC, string);
			SendClientMessage(playerid, COLOUR_MISC, lang_texts[6][21]);
			return 1;
  		}
  		if (!strcmp(cmd, "colours", true))
  		{
			SendClientMessage(playerid, COLOUR_GREEN, lang_texts[6][22]);
			for (new i = 0; i < sizeof(colors_Array); i++)
			{
				SendClientMessage(playerid, colors_Array[i][color_code], colors_Array[i][color_name]);
			}
			return 1;
  		}
  		if (!strcmp(cmd, "stats", true) || !strcmp(cmd, "stat", true) || !strcmp(cmd, "status", true))
  		{
	  		if (GetPlayerGangID(playerid) == 0)
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][24]);
			}

	  		new gangid = GetPlayerGangID(playerid), string[MAX_STRING];
	  		format(string, sizeof(string), lang_texts[6][25], Gangs[gangid][gang_name]);
			SendClientMessage(playerid, Gangs[gangid][gang_colour], string);
			if (strlen(Gangs[gangid][gang_motd]) > 0)
			{
				format(string, sizeof(string), lang_texts[6][80], Gangs[gangid][gang_motd]);
				SendClientMessage(playerid, Gangs[gangid][gang_colour], string);
			}
	  		format(string, sizeof(string), lang_texts[6][26], Gangs[gangid][gang_kills]);
			SendClientMessage(playerid, COLOUR_MISC, string);
	  		format(string, sizeof(string), lang_texts[6][40], Gangs[gangid][gang_money]);
			SendClientMessage(playerid, COLOUR_MISC, string);
			format(string, sizeof(string), lang_texts[6][27], Gangs[gangid][gang_score]);
			SendClientMessage(playerid, COLOUR_MISC, string);
			format(string, sizeof(string), lang_texts[6][82], Gangs[gangid][gang_xp]);
			SendClientMessage(playerid, COLOUR_MISC, string);
			format(string, sizeof(string), lang_texts[6][83], Gangs[gangid][gang_level]);
			SendClientMessage(playerid, COLOUR_MISC, string);
			format(string, sizeof(string), lang_texts[6][28], GangOnlineCount(gangid));
			SendClientMessage(playerid, COLOUR_MISC, string);
			return 1;
  		}
  		if (!strcmp(cmd, "members", true))
  		{
	  		if (GetPlayerGangID(playerid) == 0)
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][29]);
			}

	  		new gangid = GetPlayerGangID(playerid), status[10], string[MAX_STRING];
	  		format(string, sizeof(string), lang_texts[6][30], Gangs[gangid][gang_name]);
			SendClientMessage(playerid, Gangs[gangid][gang_colour], string);
	  		for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
			{
				if (strlen(GangMemberInfo[gangid][gangmember][member_name]) <= 0)
				{
					continue;
				}
		   		if (gang_IsPlayerConnect(gangid, gangmember))
		   		{
	  				set(status, "� ����");
		 			format(string, sizeof(string), lang_texts[6][31], gangmember, GangMemberInfo[gangid][gangmember][member_name], GangMemberInfo[gangid][gangmember][member_playerid], status, GetPlayerLevel(GangMemberInfo[gangid][gangmember][member_playerid]));
	 			}
	 			else
	 			{
	  				set(status, "�� � ����");
	  				format(string, sizeof(string), lang_texts[6][32], gangmember, GangMemberInfo[gangid][gangmember][member_name], status);
	 			}
	 			SendClientMessage(playerid, COLOUR_MISC, string);
			}
			return 1;
  		}
  		if (!strcmp(cmd, "create", true))
  		{
			new string[MAX_STRING];
	  		if (GetPlayerGangID(playerid) != 0)
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][33]);
			}

	  		if (oGetPlayerMoney(playerid) < Gang_Create_Cost)
	  		{
		  		format(string, sizeof(string), lang_texts[6][34], Gang_Create_Cost);
				SendClientMessage(playerid, COLOUR_RED, string);
				return 1;
	  		}
	  		
			new colourname[MAX_NAME], gangcolour = 255;
			colourname = strcharsplit(text, idx, ' ');
			if (!strlen(colourname))
			{
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][35]);
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][36]);
				return 1;
		 	}
		 	for (new colourid = 0; colourid < sizeof(colors_Array); colourid++)
		 	{
			 	if (strcmp(colourname, colors_Array[colourid][color_name], true))
			 	{
					continue;
				}
				gangcolour = colors_Array[colourid][color_code];
		 	}
		 	if (gangcolour == 255)
		 	{
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][37]);
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][38]);
				return 1;
			}
			
			new gangname[MAX_STRING];
			if (text[idx] != '\0')
			{
				set(gangname, text[idx+1]);
			}
	  		
		 	if (strlen(gangname) > MAX_GANG_NAME_LEN || strlen(gangname) < MIN_GANG_NAME_LEN)
		 	{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][39]);
			}
			if (!StringCharCheck(gangname) || !strcmp(gangname, "Unknown", true))
			{
				format(string, sizeof(string), lang_texts[6][41], ALLOWED_STRING_SYMBOLS_STR);
				return SendClientMessage(playerid, COLOUR_RED, string);
			}
			if (GangCreate(playerid, gangname, gangcolour) != 0)
			{
				oGivePlayerMoney(playerid,-Gang_Create_Cost, 1);
				SendClientMessage(playerid, COLOUR_GREEN, lang_texts[6][42]);
				GameMSG("player: %s(%d): created gang '%s' ", oGetPlayerName(playerid), playerid, gangname);
			}
			else
			{
				SendClientMessage(playerid, COLOUR_GREEN, lang_texts[6][43]);
			}
  			return 1;
  		}
  		if (!strcmp(cmd, "accept", true) || !strcmp(cmd, "join", true))
  		{
	  		if (GetPlayerGangID(playerid) != 0)
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][44]);
			}

	  		if (GetPVarInt(playerid, "GangInvite") == 0)
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][45]);
			}

			new gangid = GetPVarInt(playerid, "GangInvite"), string[MAX_STRING];
			if (GangOnlineCount(gangid) >= MAX_GANG_SIZE)
			{
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][46]);
				SetPVarInt(playerid, "GangInvite", 0);
				return 1;
			}
	  		if (GangJoinMember(gangid, playerid) == 1)
	  		{
		  		format(string, sizeof(string), lang_texts[6][47], Gangs[gangid][gang_name]);
				SendClientMessage(playerid, COLOUR_GANG, string);
				format(string, sizeof(string), lang_texts[6][48], oGetPlayerName(playerid));
				SendGangMessage(gangid, string, COLOUR_GANG);
				GameMSG("player: %d:  %s: have joined '%s' gang.", playerid, oGetPlayerName(playerid), Gangs[gangid][gang_name]);
				return 1;
			}
			else
			{
		  		format(string, sizeof(string), lang_texts[6][49], Gangs[gangid][gang_name]);
				SendClientMessage(playerid, COLOUR_RED, string);
				return 1;
			}
  		}
  		
  		new gangid = GetPlayerGangID(playerid);
		if (gangid == 0)
		{
			return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][50]);
		}

  		if (!strcmp(cmd, "quit", true) || !strcmp(cmd, "leave", true))
  		{
	  		GangRemoveMember(gangid, oGetPlayerName(playerid));
	  		return 1;
  		}
  		if (!strcmp(cmd, "invite", true))
  		{
	  		if (!gang_IsLeader(playerid))
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][52]);
			}

	  		new inviteid = strval(strcharsplit(text, idx,' ')),
				string[MAX_STRING];

	  		if (!IsPlayerLogin(inviteid))
	  		{
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][55]);
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][56]);
				return 1;
			}
			if (GetPlayerGangID(inviteid) != 0)
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][57]);
			}

		 	format(string, sizeof(string), lang_texts[6][58], oGetPlayerName(playerid), Gangs[gangid][gang_name]);
			SendClientMessage(inviteid, COLOUR_GANG, string);
			format(string, sizeof(string), lang_texts[6][59], oGetPlayerName(inviteid), Gangs[gangid][gang_name]);
			SendClientMessage(playerid, COLOUR_GANG, string);
			SetPVarInt(inviteid, "GangInvite", gangid);
			GameMSG("player: %d:  %s: has invited %s to join gang '%s'.", playerid, oGetPlayerName(playerid), oGetPlayerName(inviteid), Gangs[gangid][gang_name]);
			return 1;
  		}
  		if (!strcmp(cmd, "kick", true))
  		{
	  		if (!gang_IsLeader(playerid))
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][60]);
			}

			new kickplayername[MAX_NAME], string[MAX_STRING];
			set(kickplayername, text[idx+1]);
			
			if (!strlen(kickplayername))
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][61]);
			}
			if (IsNumeric(kickplayername))
			{
				set(kickplayername, GangMemberInfo[gangid][strval(kickplayername)][member_name]);
			}
			if (GangRemoveMember(gangid, kickplayername))
			{
				format(string, sizeof(string), lang_texts[6][62], kickplayername);
				SendClientMessage(playerid, COLOUR_GREEN, string);
			}
			else
			{
				format(string, sizeof(string), lang_texts[6][63], kickplayername);
				SendClientMessage(playerid, COLOUR_RED, string);
			}
			return 1;
  		}
  		if (!strcmp(cmd, "colour", true))
  		{
	  		if (!gang_IsLeader(playerid))
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][64]);
			}

			new string[MAX_STRING];
			if (oGetPlayerMoney(playerid) < Gang_Colour_Cost)
	  		{
				format(string, sizeof(string), lang_texts[6][65], Gang_Colour_Cost);
				SendClientMessage(playerid, COLOUR_RED, string);
				return 1;
			}
			new colourname[MAX_NAME], gangcolour;
			colourname = strcharsplit(text, idx, ' ');
			if (!strlen(colourname))
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][66]);
			}
			for (new colourid = 0; colourid < sizeof(colors_Array); colourid++)
		 	{
				if (strcmp(colourname, colors_Array[colourid][color_name], true))
				{
					continue;
				}
				gangcolour = colors_Array[colourid][color_code];
		 	}
		 	if (gangcolour == 0)
		 	{
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][67]);
				SendClientMessage(playerid, COLOUR_RED, lang_texts[6][68]);
				return 1;
			}
			format(string, sizeof(string), lang_texts[6][69], Gang_Colour_Cost);
			SendClientMessage(playerid, gangcolour, string);
			SetGangColour(gangid, gangcolour);
			oGivePlayerMoney(playerid,-Gang_Colour_Cost, 1);
			return 1;
  		}
  		if (!strcmp(cmd, "motd", true))
  		{
	  		if (!gang_IsLeader(playerid))
	  		{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][52]);
			}
			
			new len = strlen(text[idx+1]);
			if (len == 0)
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][91]);
			}
			if (len > MAX_GANG_MOTD_LEN)
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[6][85]);
			}
			
			if (!strcmp(text[idx+1], "delete", false))
			{
				Gangs[gangid][gang_motd][0] = '\0';
				SendGangMessage(gangid, lang_texts[6][87], COLOUR_GANG);
			}
			else
			{
				set(Gangs[gangid][gang_motd], text[idx+1]);
				new string[MAX_STRING];
				format(string, sizeof(string), lang_texts[6][81], oGetPlayerName(playerid), playerid, Gangs[gangid][gang_motd]);
				SendGangMessage(gangid, string, COLOUR_GANG);
			}
			return 1;
  		}
	}
 	return 0;
}

stock gang_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused reason, playerid
	new gangid = GetPlayerGangID(killerid);
	GiveGangXP(gangid, (1+Gangs[gangid][gang_level]) * 20);
	return 1;
}

stock PlayerGangColour(playerid)
{
	new gangid = GetPlayerGangID(playerid);
	if (gangid != 0 && Gangs[gangid][gang_colour] != 0)
	{
		return Gangs[gangid][gang_colour];
	}
	return COLOUR_PLAYER;
}

stock GangJoinMember(gangid, playerid)
{
	if (gangid == 0)
	{
		GameMSG("script_warning: invalid gang id.");
		return 0;
	}
	if (GetPlayerGangID(playerid) != 0)
	{
		GameMSG("script_warning: player already in a gang!");
		return 0;
	}
	if (GangOnlineCount(gangid) >= MAX_GANG_SIZE)
	{
		GameMSG("script_warning: Gang is already full.");
		return 0;
	}
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (strlen(GangMemberInfo[gangid][gangmember][member_name]) != 0)
		{
			continue;
		}

		set(GangMemberInfo[gangid][gangmember][member_name], oGetPlayerName(playerid));
		GangMemberInfo[gangid][gangmember][member_playerid] = playerid;
		SetPlayerGangID(playerid, gangid);
		SetPlayerGangName(playerid, Gangs[gangid][gang_name]);
		GangMemberLogin(playerid, gangid);
		SetPlayerColor(playerid, PlayerGangColour(playerid));
		new houseid = gang_GetHouse(gangid);
		if (houseid != -1)
		{
			SetPlayerSpawnHouseID(playerid, houseid);
		}
		return 1;
	}
	return 0;
}

stock GangRemoveMember(gangid, kickplayername[])
{
	new playerid = INVALID_PLAYER_ID, string[MAX_STRING];
	// ���� ����� �����, �� ������� �����
	if (!strcmp(GangMemberInfo[gangid][0][member_name], kickplayername, true))
	{
		format(string, sizeof(string), "�� ������� ����� '%s'!", Gangs[gangid][gang_name]);
		SendClientMessage(GangMemberInfo[gangid][0][member_playerid], COLOUR_RED, string);
		format(string, sizeof(string), "����� ����� %s(%d) ������ ����� '%s'.", kickplayername, GangMemberInfo[gangid][0][member_playerid], Gangs[gangid][gang_name]);
		for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
		{
			if (!IsPlayerConnected(GangMemberInfo[gangid][gangmember][member_playerid]))
			{
				continue;
			}
			playerid = GangMemberInfo[gangid][gangmember][member_playerid];
			SetPlayerGangID(playerid, 0);
			SetPlayerGangName(playerid, nullstr);
			if (GetPlayerSpawnHouseID(playerid) == SPAWN_HOUSE_GANG)
			{
				SetPlayerSpawnHouseID(playerid, SPAWN_HOUSE_NONE);
			}
			set(GangMemberInfo[gangid][gangmember][member_name], nullstr);
			SendClientMessage(playerid, COLOUR_RED, string);
			SetPlayerColor(playerid, PlayerGangColour(playerid));
			GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
		}
		format(string, sizeof(string), "%s%s"GTO_FILES_FORMAT, GangDB, Gangs[gangid][gang_name]);
		ini_Remov(string);
		Gangs[gangid][gang_active] = false;
		return 1;
	}
	playerid = INVALID_PLAYER_ID;
	for (new gangmember = 1; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (strcmp(GangMemberInfo[gangid][gangmember][member_name], kickplayername, true))
		{
			continue;
		}

		playerid = GangMemberInfo[gangid][gangmember][member_playerid];
		GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
		set(GangMemberInfo[gangid][gangmember][member_name], nullstr);
		if (GetPlayerSpawnHouseID(playerid) == SPAWN_HOUSE_GANG)
		{
			SetPlayerSpawnHouseID(playerid, SPAWN_HOUSE_NONE);
		}
		format(string, sizeof(string), lang_texts[6][70], kickplayername);
		SendGangMessage(gangid, string, COLOUR_GANG);
		GameMSG("%s has been removed from gang '%s'", kickplayername, Gangs[gangid][gang_name]);
		if (playerid != INVALID_PLAYER_ID)
		{
			format(string, sizeof(string), lang_texts[6][71], Gangs[gangid][gang_name]);
			SendClientMessage(playerid, COLOUR_GANG, string);
			SetPlayerGangID(playerid, 0);
			SetPlayerGangName(playerid, nullstr);
		}
		SetPlayerColor(playerid, PlayerGangColour(playerid));
		if (GangOnlineCount(gangid) == 0)
		{
			GangUnload(gangid);
		}
		return 1;
	}
	return 0;
}

stock GangCreate(leaderid, gangname[], gangcolour)
{
	if (!IsPlayerLogin(leaderid)) return 0;
	new filename_gang[MAX_STRING];
	format(filename_gang, sizeof(filename_gang), "%s%s"GTO_FILES_FORMAT, GangDB, gangname);
	if (ini_Exist(filename_gang))
	{
		SendClientMessage(leaderid, COLOUR_RED, lang_texts[6][73]);
		return 0;
	}
	new gangid = FindGangFreeSlot();
	if (gangid == 0)
	{
		return GameMSG("[ERROR] ��������� ���� ��� ����� �� ������");
	}
	Gangs[gangid][gang_active] = true;
	set(Gangs[gangid][gang_name], gangname);
	Gangs[gangid][gang_colour] = gangcolour;
	Gangs[gangid][gang_kills] = 0;
	Gangs[gangid][gang_score] = 0;
	Gangs[gangid][gang_level] = 0;
	Gangs[gangid][gang_xp] = 0;
	Gangs[gangid][gang_house] = GetPlayerSpawnHouseID(leaderid);
	for (new gangmember =0 ; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
		set(GangMemberInfo[gangid][gangmember][member_name], nullstr);
	}
	set(GangMemberInfo[gangid][0][member_name], oGetPlayerName(leaderid));
	GangMemberInfo[gangid][0][member_playerid] = leaderid;
	SetPlayerGangName(leaderid, gangname);
	SetPlayerGangID(leaderid, gangid);
	SetPlayerColor(leaderid, PlayerGangColour(leaderid));
	GangSave(gangid);
	return gangid;
}

stock GangSaveAll()
{
	for (new i = 1; i < MAX_GANGS; i++)
	{
		if (Gangs[i][gang_active])
		{
			GangSave(i);
			if (GangOnlineCount(i) == 0)
			{
				GangUnload(i);
			}
		}
	}
}

stock GangMemberLogout(playerid, gangid)
{
	SetPVarInt(playerid, "GangInvite", 0);
	if (gangid == 0)
	{
		return;
	}
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (GangMemberInfo[gangid][gangmember][member_playerid] == playerid)
		{
			GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
			break;
		}
	}
	if (GangOnlineCount(gangid) == 0)
	{
		GangUnload(gangid);
	}
	else
	{
		new string[MAX_STRING];
		format(string, sizeof(string), lang_texts[6][74], oGetPlayerName(playerid));
		SendGangMessage(gangid, string, COLOUR_GANG);
	}
	return;
}

stock GangSave(gangid)
{
	if (gangid == 0 || !Gangs[gangid][gang_active] || !strlen(Gangs[gangid][gang_name]))
	{
		return 0;
	}
	gang_save_db_ini(gangid);
	return 1;
}

stock gang_save_db_ini(gangid)
{
	new filename_gang[MAX_STRING];
	format(filename_gang, sizeof(filename_gang), "%s%s"GTO_FILES_FORMAT, GangDB, Gangs[gangid][gang_name]);
	new file_gang = (!ini_Exist(filename_gang)) ? ini_Create(filename_gang) : ini_Open(filename_gang);
	ini_Set(file_gang, "Name", Gangs[gangid][gang_name]);
	ini_Set(file_gang, "Motd", Gangs[gangid][gang_motd]);
	ini_SetInt(file_gang, "Colour", Gangs[gangid][gang_colour]);
	ini_SetInt(file_gang, "Kills", Gangs[gangid][gang_kills]);
	ini_SetInt(file_gang, "Score", Gangs[gangid][gang_score]);
	ini_SetInt(file_gang, "XP", Gangs[gangid][gang_xp]);
	ini_SetInt(file_gang, "Level", Gangs[gangid][gang_level]);
	ini_SetInt(file_gang, "Money", Gangs[gangid][gang_money]);
	ini_SetInt(file_gang, "House", Gangs[gangid][gang_house]);
	for (new gangmember = 0, string[MAX_STRING]; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		format(string, sizeof(string), "Member%d", gangmember);
		ini_Set(file_gang, string, GangMemberInfo[gangid][gangmember][member_name]);
	}
	ini_Close(file_gang);
}

stock GangUnload(gangid)
{
	GangSave(gangid);
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		GangMemberInfo[gangid][gangmember][member_playerid] = INVALID_PLAYER_ID;
	}
	Gangs[gangid][gang_active] = false;
}

stock GangKill(gangid, killerid, victimid, reason)
{
	#pragma unused reason
	if (victimid != INVALID_PLAYER_ID)
	{
		Gangs[gangid][gang_kills]++;
	}
	if (GetPlayerGangID(killerid) == GetPlayerGangID(victimid))
	{
		new string[MAX_STRING];
		format(string, sizeof(string), lang_texts[6][76], oGetPlayerName(killerid));
		SendGangMessage(GetPlayerGangID(killerid), string, COLOUR_GANG);
		return 1;
	}
	return 0;
}

stock GangMemberLogin(playerid, gangid)
{
	if (gangid == 0) return 0;
	new pl_name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, pl_name, sizeof(pl_name));
	for (new gangmember = 0, string[MAX_STRING]; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (strcmp(GangMemberInfo[gangid][gangmember][member_name], pl_name, false))
		{
			continue;
		}
		
		format(string, sizeof(string), lang_texts[6][77], pl_name);
		SendGangMessage(gangid, string, COLOUR_GANG);
		GangMemberInfo[gangid][gangmember][member_playerid] = playerid;
		SetPlayerGangID(playerid, gangid);
		SetPlayerGangName(playerid, Gangs[gangid][gang_name]);
		format(string, sizeof(string), lang_texts[6][78], Gangs[gangid][gang_name], GangOnlineCount(gangid)-1);
		SendClientMessage(playerid, COLOUR_GANG, string);
		if (strlen(Gangs[gangid][gang_motd]) > 0)
		{
			format(string, sizeof(string), lang_texts[6][80], Gangs[gangid][gang_motd]);
			SendClientMessage(playerid, COLOUR_GANG, string);
		}
		SetPVarInt(playerid, "GangInvite", 0);
		SetPlayerColor(playerid, Gangs[gangid][gang_colour]);
		return 1;
	}
	return 0;
}

stock SendGangMessage(gangid, message[], colour)
{
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (gang_IsPlayerConnect(gangid, gangmember))
		{
			SendClientMessage(GangMemberInfo[gangid][gangmember][member_playerid], colour, message);
		}
	}
}

stock GangOnlineCount(gangid)
{
	new memberscount = 0;
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (gang_IsPlayerConnect(gangid, gangmember))
		{
			memberscount++;
		}
	}
	return memberscount;
}

stock GangGiveXP(gangid, xpamount, giverid)
{
	Gangs[gangid][gang_score] += xpamount;
	new giveamount = xpamount / GangOnlineCount(gangid),
		string[MAX_STRING];
	
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (!gang_IsPlayerConnect(gangid, gangmember) || giverid == GangMemberInfo[gangid][gangmember][member_playerid])
		{
			continue;
		}
		if (GetPlayerXP(GangMemberInfo[gangid][gangmember][member_playerid]) < MAX_XP) 
		{
			GivePlayerXP(GangMemberInfo[gangid][gangmember][member_playerid], giveamount, 0);
			format(string, sizeof(string), lang_texts[6][79], giveamount, oGetPlayerName(giverid));
			SendClientMessage(GangMemberInfo[gangid][gangmember][member_playerid], COLOUR_XP_GOOD, string);
			CheckPlayerLevel(GangMemberInfo[gangid][gangmember][member_playerid]);
		} 
		else 
		{
			format(string, sizeof(string), lang_texts[9][17]);
			SendClientMessage(GangMemberInfo[gangid][gangmember][member_playerid], COLOUR_RED, string);
		}
	}
}

stock SetGangColour(gangid, colour)
{
	Gangs[gangid][gang_colour] = colour;
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (gang_IsPlayerConnect(gangid, gangmember))
		{
			SetPlayerColor(GangMemberInfo[gangid][gangmember][member_playerid], colour);
		}
	}
}

stock GangGivePlayerXP(playerid, xpamount)
{
	if (GetPlayerGangID(playerid) == 0 || xpamount <= 100) return;
	GangGiveXP(GetPlayerGangID(playerid), xpamount / 4, playerid);
	return;
}

stock gang_RenameMember(gangid, old_name[MAX_PLAYER_NAME+1], new_name[MAX_PLAYER_NAME+1])
{
	for (new gangmember = 0; gangmember < MAX_GANG_SIZE; gangmember++)
	{
		if (!strcmp(GangMemberInfo[gangid][gangmember][member_name], old_name, true))
		{
			set(GangMemberInfo[gangid][gangmember][member_name], new_name);
			return 1;
		}
	}
	return 0;
}


stock gang_IsLeader(playerid)
{
	new gangid = GetPlayerGangID(playerid);
	if (gangid != 0 && playerid == GangMemberInfo[gangid][0][member_playerid])
	{
		return 1;
	}
	return 0;
}

stock gang_SetHouse(gangid, houseid)
{
	Gangs[gangid][gang_house] = houseid;
}

stock gang_GetHouse(gangid)
{
	return Gangs[gangid][gang_house];
}

stock gang_IsPlayerConnect(gangid, gangmember)
{
	return GangMemberInfo[gangid][gangmember][member_playerid] == INVALID_PLAYER_ID ? 0 : 1;
}

stock GiveGangMoney(gangid, amount)
{
	Gangs[gangid][gang_money] += amount;
}

stock GetGangMoney(gangid)
{
	return Gangs[gangid][gang_money];
}

// Gang Level
new GangLevelList[] = {
	0, // 0
	500, // 1
	1000, // 2
	2000, // 3
	5000, // 4
	7500, // 5
	11000, // 6
	16000, // 7
	21000, // 8
	31000, // 9
	46000 // 10
};
#define MAX_GANG_LEVEL	(sizeof(GangLevelList)-1)
#define MAX_GANG_XP		GangLevelList[MAX_GANG_LEVEL]

stock GetGangLevel(gangid)
{
	return Gangs[gangid][gang_level];
}

stock SetGangLevel(gangid, level)
{
	return Gangs[gangid][gang_level] = level;
}

stock GetGangXP(gangid)
{
	return Gangs[gangid][gang_xp];
}

stock GetGangColour(gangid)
{
	return Gangs[gangid][gang_colour];
}

stock GiveGangXP(gangid, xpamount)
{
	Gangs[gangid][gang_xp] += xpamount;
	CheckGangLevel(gangid);
}
stock SetGangXP(gangid, xpamount)
{
	Gangs[gangid][gang_xp] = xpamount;
	CheckGangLevel(gangid);
}

stock GetGangXPToLevel(gangid, level)
{
	return GangLevelList[level] - Gangs[gangid][gang_xp];
}

stock CalculateGangLevel(gangid)
{
	for (new i = 0; i <= MAX_GANG_LEVEL; i++)
	{
		if (GetGangXP(gangid) < GangLevelList[i]) continue;
		return i;
	}
	return -1;
}

stock CheckGangLevel(gangid)
{
	return Gangs[gangid][gang_level] = CalculateGangLevel(gangid);
}


