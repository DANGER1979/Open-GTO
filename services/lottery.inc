/*

	��������: ������ �������
	�����: ZiGGi
	����: 08.05.2011

*/


#if defined _lottery_included
	#endinput
#endif

#define _lottery_included
#pragma library lottery


static
	LotteryEnabled = LOTTERY_ENABLED,
	LotteryTime = LOTTERY_TIME,
	LotteryWinMoney = LOTTERY_WIN_MONEY,
	LotteryTicketCost = LOTTERY_TICKET_COST,
	LotteryCount = -1,
	lottery_timer;

stock lottery_LoadConfig()
{
	if (!ini_Exist(ConfigDB)) return 0;
	new file_lwm = ini_Open(ConfigDB);
	ini_GetInt(file_lwm, "Lottery_Enabled", LotteryEnabled);
	ini_GetInt(file_lwm, "Lottery_Time", LotteryTime);
	ini_GetInt(file_lwm, "Lottery_Win_Money", LotteryWinMoney);
	ini_GetInt(file_lwm, "Lottery_Ticket_Cost", LotteryTicketCost);
	ini_Close(file_lwm);
	return 1;
}

stock lottery_SaveConfig()
{
	new file_lwm = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_SetInt(file_lwm, "Lottery_Enabled", LotteryEnabled);
	ini_SetInt(file_lwm, "Lottery_Time", LotteryTime);
	ini_SetInt(file_lwm, "Lottery_Win_Money", LotteryWinMoney);
	ini_SetInt(file_lwm, "Lottery_Ticket_Cost", LotteryTicketCost);
	ini_Close(file_lwm);
	return 1;
}

stock lottery_OnGameModeInit()
{
	lottery_LoadConfig();
	if (LotteryEnabled != 1) return 0;
	GameMSG("SERVER: Lottery system init");
	return 1;
}

stock lottery_OnPlayerCommandText(playerid, text[])
{
	if (LotteryEnabled != 1) return 0;
	if (LotteryCount < 0)
	{
		return SendClientMessage(playerid, COLOUR_PM, "������� ��� �� ��������!");
	}
	new cmd[20], idx;
	cmd = strcharsplit(text, idx,' ');
	
	if (!strcmp(cmd, "/lottery", true))
	{
		new tmp[MAX_STRING];
		tmp = strcharsplit(text, idx, ' ');
		new value = strval(tmp);
		
		if (strlen(tmp) == 0 || value < 1 || value > 100)
		{
			return SendClientMessage(playerid, COLOUR_PM, "����������: /lottery <����� 1..100>");
		}
		if (GetPVarInt(playerid, "lottery_Value") != 0)
		{
			return SendClientMessage(playerid, COLOUR_PM, "�������: �� ��� ������ �����!");
		}
		foreach (Player, id)
		{
			if (GetPVarInt(id, "lottery_Value") == value)
			{
				return SendClientMessage(playerid, COLOUR_PM, "�������: ���� ����� ��� ������!");
			}
		}
		
		oGivePlayerMoney(playerid, -LotteryTicketCost);
		SetPVarInt(playerid, "lottery_Value", value);
		
		new string[MAX_STRING];
		format(string, sizeof(string), "�����, � ��� ����� � ������� %d", value);
		SendClientMessageToAll(COLOUR_GREEN, string);
		return 1;
	}
	return 0;
}

forward lottery_Timer();
public lottery_Timer()
{
	if (LotteryEnabled != 1) return 0;
	LotteryCount++;
	if (LotteryCount < LotteryTime)
	{
		new string[MAX_STRING];
		format(string, sizeof(string), "�������: �� ��������� ��������� �������� %d �����!", LotteryTime-LotteryCount);
		SendClientMessageToAll(COLOUR_GREEN, string);
		return 0;
	}
	KillTimer(lottery_timer);
	LotteryCount = -1;
	new win_value = mathrandom(1, 100),
		winner = 0;
	
	foreach (Player, playerid)
	{
		if (GetPVarInt(playerid, "lottery_Value") == win_value)
		{
			winner = 1;
			oGivePlayerMoney(playerid, LotteryWinMoney, 1);
			
			new string[MAX_STRING];
			
			format(string, sizeof(string), "�� �������� � �������! ��� ���� $%d", LotteryWinMoney);
			SendClientMessage(playerid, COLOUR_GREEN, string);
			
			format(string, sizeof(string), "����������� � ������� ���� %s(%d), �� ������� $%d", oGetPlayerName(playerid), playerid, LotteryWinMoney);
			SendClientMessageToAll(COLOUR_GREEN, string);
		}
		else
		{
			DeletePVar(playerid, "lottery_Value");
		}
	}
	if (winner == 0)
	{
		new string[MAX_STRING];
		format(string, sizeof(string), "� ������� ����� �� �������, ���������� ����� - %d.", win_value);
		SendClientMessageToAll(COLOUR_GREEN, string);
	}
	return 1;
}

stock lottery_RunTimer()
{
	if (LotteryEnabled != 1) return 0;
	LotteryCount = 0;
	lottery_timer = SetTimer("lottery_Timer", 60000, 1);
	
	new string[MAX_STRING];
	format(string, sizeof(string), "�������: ������ ���������� ������, ���������� �������� $%d!", LotteryWinMoney);
	SendClientMessageToAll(COLOUR_GREEN, string);
	format(string, sizeof(string), "�������: ������� /lottery <����� 1..100>, ��� ������� ������. ���� ������ $%d", LotteryTicketCost);
	SendClientMessageToAll(COLOUR_GREEN, string);
	format(string, sizeof(string), "�������: �� ��������� ��������� �������� %d �����!", LotteryTime);
	SendClientMessageToAll(COLOUR_GREEN, string);
	return 1;
}