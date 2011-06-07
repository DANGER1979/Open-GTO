/*


*/

#if defined _level_system_included
	#endinput
#endif

#define _level_system_included
#pragma library level_system


#define GetPlayerLevel(%1) GetPVarInt(%1,"Level")
#define SetPlayerLevel(%1,%2) SetPVarInt(%1,"Level",%2)
#define GetPlayerXP(%1) GetPVarInt(%1,"XP")
#define SetPlayerXP(%1,%2) SetPVarInt(%1,"XP",%2)

enum LevelInfo 
{
	level_xp,
    level_name[MAX_NAME]
}

#define MAX_LEVEL	60
#define MAX_XP		60000000
#define MAX_LVLXP	60000000

new LevelList[MAX_LEVEL+1][LevelInfo] = {
{  0,		"0 �������" },
{  500,		"1 �������" },
{  1000,	"2 �������" },
{  2000,	"3 �������" },
{  5000,	"4 �������" },
{  7500,	"5 �������" },
{  11000,	"6 �������" },
{  16000,	"7 �������" },
{  21000,	"8 �������" },
{  31000,	"9 �������" },
{  46000,	"10 �������" },
{  70000,	"11 �������" },
{  100000,	"12 �������" },
{  135000,	"13 �������" },
{  190000,	"14 �������" },
{  225000,	"15 �������" },
{  300000,	"16 �������" },
{  380000,	"17 �������" },
{  480000,	"18 �������" },
{  590000,	"19 �������" },
{  700000, 	"20 �������" },
{  820000,	"21 �������" },
{  950000,	"22 �������" },
{  1200000,	"23 �������" },
{  1350000,	"24 �������" },
{  1420000, "25 �������" },
{  1500000, "26 �������" },
{  1600000, "27 �������" },
{  1700000, "28 �������" },
{  1800000, "29 �������" },
{  2500000, "30 �������" },
{  3000000, "31 �������" },
{  3500000, "32 �������" },
{  4000000, "33 �������" },
{  5500000, "34 �������" },
{  6000000, "35 �������" },
{  6500000, "36 �������" },
{  7000000, "37 �������" },
{  7500000, "38 �������" },
{  8000000, "39 �������" },
{  10500000, "40 �������" },
{  12000000, "41 �������" },
{  13000000, "42 �������" },
{  14200000, "43 �������" },
{  15400000, "44 �������" },
{  16600000, "45 �������" },
{  17800000, "46 �������" },
{  19000000, "47 �������" },
{  21000000, "48 �������" },
{  23000000, "49 �������" },
{  26000000, "50 �������" },
{  29000000, "51 �������" },
{  32000000, "52 �������" },
{  35000000, "53 �������" },
{  38000000, "54 �������" },
{  41000000, "55 �������" },
{  43000000, "56 �������" },
{  46000000, "57 �������" },
{  50000000, "58 �������" },
{  55000000, "59 �������" },
{  60000000, "60 �������" }
};

stock LevelSystem_LoadConfig()
{
	if(ini_Exist(ConfigDB))
	{
		new file_ls = ini_Open(ConfigDB);
		ini_Get(file_ls,"Level_DB",LevelDB);
		ini_Close(file_ls);
	}
	if(ini_Exist(LevelDB))
	{
		new file_base_level = ini_Open(LevelDB);
		for(new i=0,temp[MAX_STRING];i<=MAX_LEVEL;i++)
		{
			format(temp,sizeof(temp),"Level%d_Experience",i);
			ini_GetInt(file_base_level,temp,LevelList[i][level_xp]);
			format(temp,sizeof(temp),"Level%d_Rankname",i);
			ini_Get(file_base_level,temp,LevelList[i][level_name],MAX_NAME);
		}
		ini_Close(file_base_level);
	}
	return 1;
}

stock LevelSystem_SaveConfig()
{
	new file_ls = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_ls,"Level_DB",LevelDB);
	ini_Close(file_ls);
	
	new file_base_level = (ini_Exist(LevelDB)) ? ini_Open(LevelDB) : ini_Create(LevelDB);
	for(new i=0,temp[MAX_STRING];i<=MAX_LEVEL;i++)
	{
	    format(temp,sizeof(temp),"Level%d_Rankname",i);
		ini_Set(file_base_level,temp,LevelList[i][level_name]);
		format(temp,sizeof(temp),"Level%d_Experience",i);
		ini_SetInt(file_base_level,temp,LevelList[i][level_xp]);
	}
	ini_Close(file_base_level);
	return 1;
}

stock LevelSystem_OnGameModeInit()
{
	LevelSystem_LoadConfig();
	GameMSG("SERVER: (system)Level System module init");
	return 1;
}

stock GetLevelName(level)
{
	new name[MAX_NAME];
	if(level < 0 || level > MAX_LEVEL+1) return name;
	set(name,LevelList[level][level_name]);
	return name;
}

stock GetXPToLevel(playerid,level)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if((level <= MAX_LEVEL) && (level > GetPlayerLevel(playerid)))
	{
		return (LevelList[level][level_xp] - GetPlayerXP(playerid));
	}
	else return 0;
}

stock CalculatePlayerLevel(playerid)
{
	if (!IsPlayerConnected(playerid)) return 0;
	new level;
	for(new i;i<=MAX_LEVEL;i++)
	{
		if(GetPlayerXP(playerid) >=LevelList[i][level_xp]) level = i;
	}
	return level;
}

stock GivePlayerXP(playerid, xpamount,showtext=0) // showtext = do we display "You gain %d XP"  to client
{
	if(!IsPlayerConnected(playerid) || xpamount == 0) return 0;
	GangGivePlayerXP(playerid,xpamount);

	new texttime = (xpamount > 5000) ? 2000 : 1000;
	
	if(GetPlayerXP(playerid) + xpamount < 0)
	{
		xpamount = -GetPlayerXP(playerid);
	}
	if(GetPlayerXP(playerid) + xpamount >= MAX_LVLXP)
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[9][17] );
		xpamount = MAX_LVLXP - GetPlayerXP(playerid);
	}
	new string[MAX_STRING];
	if(xpamount > 0)
	{
		format(string, sizeof(string),  lang_texts[9][18] , xpamount);
		GameTextForPlayer(playerid,string,texttime,3);
		if(showtext == 1)
		{
			format(string, sizeof(string),  lang_texts[9][20] , xpamount);
			SendClientMessage(playerid, COLOUR_XP_GOOD, string);
		}
	}
	else
	{
		format(string, sizeof(string),  lang_texts[9][19] , -xpamount);
		GameTextForPlayer(playerid,string,texttime,3);
		if(showtext == 1)
		{
			format(string, sizeof(string),  lang_texts[9][21] , -xpamount);
			SendClientMessage(playerid, COLOUR_XP_BAD, string);
		}
	}
	SetPlayerXP(playerid,GetPlayerXP(playerid) + xpamount);
	CheckPlayerLevel(playerid);
	return 1;
}

stock CheckPlayerLevel(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	new level = CalculatePlayerLevel(playerid);
	if(GetPlayerLevel(playerid) < level)
		PlayerLevelUp(playerid,level);
	else if(GetPlayerLevel(playerid) > level)
		PlayerLevelDown(playerid,level);
	return 1;
}

stock PlayerLevelDown(playerid,level)
{
	if(!IsPlayerConnected(playerid)) return 1;
	SetPVarInt(playerid,"Level",level);
	PlayerPlaySoundOnPlayer(playerid,1057);
	UpdatePlayerScore(playerid);
	new string[MAX_STRING];
	format(string, sizeof(string),  lang_texts[9][22] , GetPlayerLevel(playerid));
	SendClientMessage(playerid, COLOUR_XP_BAD, string);
	GameMSG("player: %d:  %s: decreased his level to %d",playerid,oGetPlayerName(playerid),GetPlayerLevel(playerid));
	return 1;
}

stock PlayerLevelUp(playerid,level)
{
	if(!IsPlayerConnected(playerid)) return 1;
	SetPVarInt(playerid,"Level",level);
	SetMaxPlayerHealth(playerid);
	PlayerPlaySoundOnPlayer(playerid,1057);
	UpdatePlayerScore(playerid);
	new string[MAX_STRING];
	format(string, sizeof(string),  lang_texts[9][23] , GetPlayerLevel(playerid));
	SendClientMessage(playerid, COLOUR_XP_GOOD, string);
	
	ShowWeaponsOnLevel(playerid,GetPlayerLevel(playerid));
	
	GameMSG("player: %d:  %s: increased his level to %d",playerid,oGetPlayerName(playerid),GetPlayerLevel(playerid));
	return 1;
}