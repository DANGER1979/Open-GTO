//
// Created:     17.09.06
// Aurthor:    Iain Gilbert
//
// Modified by ZiGGi
//

#if defined _bank_included
	#endinput
#endif

#define _bank_included
#pragma library bank


#define GetPlayerBankMoney(%0) GetPVarInt(%0, "BankMoney")
#define GivePlayerBankMoney(%0,%1) SetPVarInt(%0, "BankMoney", GetPVarInt(%0, "BankMoney") + %1)

new ProfitCount = BANK_PROFIT, 
	MAX_BANK = MAX_BANK_MONEY;

new Banks[][CoordInfo] = {
	{-22.9578, -54.8951, 1003.5469}, // LV 24/7 bank
	{-27.0310, -89.5228, 1003.5469} // 24/7 bank
};

stock BankLoadConfig()
{
	if (!ini_Exist(ConfigDB)) return 0;
	new file_bank = ini_Open(ConfigDB);
    ini_GetInt(file_bank, "Bank_ProfitCount", ProfitCount);
    ini_GetInt(file_bank, "Bank_MAX_MONEY", MAX_BANK);
	ini_Close(file_bank);
	return 1;
}

stock BankSaveConfig()
{
	new file_bank = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_SetInt(file_bank, "Bank_ProfitCount", ProfitCount);
	ini_SetInt(file_bank, "Bank_MAX_MONEY", MAX_BANK);
	ini_Close(file_bank);
	return 1;
}

stock bank_OnGameModeInit()
{
	BankLoadConfig();
	for (new bankid = 0; bankid < sizeof(Banks); bankid++)
	{
	    CreatePickup(1274, 23, Banks[bankid][Coord_X], Banks[bankid][Coord_Y], Banks[bankid][Coord_Z]);
		CreatePickupText("����", Banks[bankid][Coord_X], Banks[bankid][Coord_Y], Banks[bankid][Coord_Z]);
	}
	GameMSG(lang_texts[2][0]);
	return 1;
}

stock bank_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys, newkeys
	bank_ShowDialog_Start(playerid);
	return 1;
}

stock bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case bank_Start_DialogID:
		{
			if (!response) return 0;
			bank_ShowDialog_List(playerid);
			return 1;
		}
		case bank_FirstList_DialogID:
		{
			if (!response) return 0;
			switch (listitem)
			{
				case 0: bank_ShowDialog_Withdraw(playerid);
				case 1: bank_ShowDialog_Deposit(playerid);
				case 2: show_GangWMoney_Menu(playerid);
				case 3: show_GangDMoney_Menu(playerid);
			}
			return 1;
		}
		case bank_Withdraw_DialogID: // ����� ������
		{
			if (!response) return bank_ShowDialog_List(playerid);
			
			new amount = strval(inputtext);
			if (amount <= 0 || strlen(inputtext) == 0 || !IsNumeric(inputtext))
			{
				show_Msg_Dialog(playerid, lang_texts[2][3], lang_texts[2][13], lang_texts[2][5]);
				return 0;
			}
			if (amount > GetPlayerBankMoney(playerid))
			{
				amount = GetPlayerBankMoney(playerid);
			}
			oGivePlayerMoney(playerid, amount, 0);
			GivePlayerBankMoney(playerid, -amount);
			new string[MAX_STRING];
			format(string, sizeof(string), lang_texts[2][7], amount, GetPlayerBankMoney(playerid));
			show_Msg_Dialog(playerid, lang_texts[2][3], string, lang_texts[2][5]);
			PlayerPlaySoundOnPlayer(playerid, 1084);
			return 1;
		}
		case bank_Deposit_DialogID: // �������� ������
		{
			if (!response) return bank_ShowDialog_List(playerid);
			
			new amount = strval(inputtext);
			if (amount <= 0 || strlen(inputtext) == 0 || !IsNumeric(inputtext))
			{
				show_Msg_Dialog(playerid, lang_texts[2][3], lang_texts[2][13], lang_texts[2][5]);
				return 0;
			}
			if (oGetPlayerMoney(playerid) < amount)
			{
				amount = oGetPlayerMoney(playerid);
			}
			if (GetPlayerBankMoney(playerid) + amount > MAX_BANK)
			{
				amount = MAX_BANK - GetPlayerBankMoney(playerid);
				SendClientMessage(playerid, COLOUR_RED, lang_texts[2][15]);
			}
			oGivePlayerMoney(playerid, -amount, 0);
			GivePlayerBankMoney(playerid, amount);
			new string[MAX_STRING];
			format(string, sizeof(string), lang_texts[2][14], amount, GetPlayerBankMoney(playerid));
			show_Msg_Dialog(playerid, lang_texts[2][3], string, lang_texts[2][5]);
			PlayerPlaySoundOnPlayer(playerid, 1084);
			return 1;
		}
		case gang_wmoney_menu_DialogID:
		{
			if (!response)
			{
				return bank_ShowDialog_List(playerid);
			}
			
			new amount = strval(inputtext);
   			if (amount <= 0 || strlen(inputtext) == 0 || !IsNumeric(inputtext))
   			{
				return show_Msg_Dialog(playerid, lang_texts[2][23], lang_texts[6][92], lang_texts[6][93]);
			}
			
			if (oGetPlayerMoney(playerid) < amount)
			{
				return show_Msg_Dialog(playerid, lang_texts[2][23], lang_texts[6][92], lang_texts[6][94]);
			}
			
			new gangid = GetPlayerGangID(playerid);
			
			oGivePlayerMoney(playerid, -amount);
			GiveGangMoney(gangid, amount);
			
			new string[MAX_STRING];
			format(string, sizeof(string), lang_texts[2][26], oGetPlayerName(playerid), playerid, amount);
			SendGangMessage(gangid, string, COLOUR_GANG);
			return 1;
		}
		case gang_dmoney_menu_DialogID:
		{
			if (!response)
			{
				return bank_ShowDialog_List(playerid);
			}
			
			new amount = strval(inputtext);
   			if (amount <= 0 || strlen(inputtext) == 0 || !IsNumeric(inputtext))
   			{
				return show_Msg_Dialog(playerid, lang_texts[2][23], lang_texts[6][92], lang_texts[6][93]);
			}
			
			new gangid = GetPlayerGangID(playerid);
			if (GetGangMoney(gangid) < amount)
			{
				return show_Msg_Dialog(playerid, lang_texts[2][23], lang_texts[6][92], lang_texts[6][94]);
			}
			
			oGivePlayerMoney(playerid, amount);
			GiveGangMoney(gangid, -amount);
			
			new string[MAX_STRING];
			format(string, sizeof(string), lang_texts[2][27], oGetPlayerName(playerid), playerid, amount);
			SendGangMessage(gangid, string, COLOUR_GANG);
			return 1;
		}
	}
	return 1;
}

stock bank_ShowDialog_Start(playerid)
{
	new string[MAX_STRING];
	format(string, sizeof(string), lang_texts[2][1], ProfitCount, GetPlayerBankMoney(playerid));
	return ShowPlayerDialog(playerid, bank_Start_DialogID, DIALOG_STYLE_MSGBOX,
		lang_texts[2][3],
		string,
		lang_texts[2][16], lang_texts[2][6]
	);
}

stock bank_ShowDialog_List(playerid)
{
	new string[MAX_STRING];
	set(string, lang_texts[2][4]);
  	
	if (GetPlayerGangID(playerid) != 0)
	{
		strcat(string, lang_texts[2][20], sizeof(string));
		
		if (gang_IsLeader(playerid))
		{
			strcat(string, lang_texts[2][21], sizeof(string));
		}
	}
	
	return ShowPlayerDialog(playerid, bank_FirstList_DialogID, DIALOG_STYLE_LIST,
		lang_texts[2][3],
		string,
		lang_texts[2][5], lang_texts[2][6]
	);
}

stock bank_ShowDialog_Withdraw(playerid)
{
	new string[MAX_STRING];
	format(string, sizeof(string), lang_texts[2][9], GetPlayerBankMoney(playerid));
	ShowPlayerDialog(playerid, bank_Withdraw_DialogID, DIALOG_STYLE_INPUT,
		lang_texts[2][3],
		string,
		lang_texts[2][10], lang_texts[2][12]
	);
}

stock bank_ShowDialog_Deposit(playerid)
{
	new string[MAX_STRING];
	format(string, sizeof(string), lang_texts[2][8], GetPlayerBankMoney(playerid));
	ShowPlayerDialog(playerid, bank_Deposit_DialogID, DIALOG_STYLE_INPUT,
		lang_texts[2][3],
		string,
		lang_texts[2][11], lang_texts[2][12]
	);
}

stock show_GangWMoney_Menu(playerid)
{
	return ShowPlayerDialog(playerid, gang_wmoney_menu_DialogID, DIALOG_STYLE_INPUT,
		lang_texts[2][23],
		lang_texts[2][28],
		lang_texts[2][5], lang_texts[2][6]
	);
}

stock show_GangDMoney_Menu(playerid)
{
	return ShowPlayerDialog(playerid, gang_dmoney_menu_DialogID, DIALOG_STYLE_INPUT,
		lang_texts[2][23],
		lang_texts[2][29],
		lang_texts[2][5], lang_texts[2][6]
	);
}

stock IsPlayerAtBank(playerid)
{
	for (new bankid = 0; bankid < sizeof(Banks); bankid++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2, Banks[bankid][Coord_X], Banks[bankid][Coord_Y], Banks[bankid][Coord_Z]))
		{
			return bankid;
		}
	}
	return -1;
}

stock Profit()
{
	foreach (Player, playerid)
	{
		if (IsPlayerLogin(playerid))
		{
			GivePlayerBankMoney(playerid, (GetPlayerBankMoney(playerid) / 100) * ProfitCount);
		}
	}
	return 1;
}
