/*

	��������: ������� ����������
	�����: ziggi

*/


#if defined _vehshop_included
	#endinput
#endif

#define _vehshop_included
#pragma library vehshop

enum vshop_Info {
	Float:vshop_X,
	Float:vshop_Y,
	Float:vshop_Z,
	Float:vshop_A,
	vshop_ID,
	Text3D:vshop_Text3D,
}
new vshop_Vehicles[][vshop_Info] = {
	// wang cars
	{-1948.7234,269.2943,35.2865,124.3050},
	{-1950.4930,259.6267,35.3084,53.4259},
	{-1952.4955,265.6270,40.7236,292.5036},
	{-1952.7627,258.7505,40.9033,258.7441},
	{-1956.2396,297.6752,35.1036,67.0766},
	{-1957.6256,276.9989,35.2012,132.1882},
	{-1960.8898,258.5982,35.1779,330.8205},
	// ottos autos
	{-1663.4675,1211.4713,6.9668,276.9533},
	{-1656.4816,1215.6754,13.3731,259.0980},
	{-1650.9432,1208.6349,13.4013,247.0109},
	{-1660.5276,1215.1526,20.8028,315.8404},
	{-1656.2656,1208.2466,20.8036,268.7285}
};

new vshop_VehiclesModels[] = {411, 451, 558, 560, 561, 562, 565, 566, 567, 603};


stock vshop_OnGameModeInit()
{
	vshop_ChangeVehicles();
	return 1;
}

stock vshop_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused newstate, oldstate
	if (vshop_IsShopVehicle( GetPlayerVehicleID(playerid) )) {
		vshop_ShowBuyDialog(playerid);
	}
	return 1;
}

stock vshop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem, inputtext
	if (dialogid == vshop_DialogID) {
		RemovePlayerFromVehicle(playerid);
		if (!response) {
			return 0;
		}
		if (GetPlayerVehicleCount(playerid) >= GetPlayerVehicleMaximumCount(playerid)) {
			show_Msg_Dialog(playerid, "������� �����������", "� ��� ������������ ���������� ����������", "��");
			return 0;
		}
		
		new vehicleid = GetPlayerVehicleID(playerid);
		new cost = GetVehicleCost( GetVehicleModel(vehicleid) );
		
		if (oGetPlayerMoney(playerid) < cost) {
			show_Msg_Dialog(playerid, "������� �����������", "� ��� ������������ �����", "��");
			return 0;
		}
		
		oGivePlayerMoney(playerid, -cost, 1);
		buyVehicle(playerid, vehicleid);
		
		show_Msg_Dialog(playerid, "������� �����������", "\
			�� ������� ������ ���� ����������.\n\
			����� ������� ��������� ����������, ������� � ���� ������������ � �������� ���.",
			"��"
		);
		return 1;
	}
	return 1;
}

stock vshop_OnVehicleSpawn(vehicleid)
{
	if (vshop_IsShopVehicle(vehicleid)) {
		SetVehicleFuel(vehicleid, 0);
	}
	return 1;
}

stock vshop_OneMinuteTimer()
{
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		new Float:dist = GetVehicleDistanceFromPoint(vshop_Vehicles[i][vshop_ID], vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z]);
		if (dist >= 4.0) {
			SetVehicleToRespawn(vshop_Vehicles[i][vshop_ID]);
		}
	}
}

stock vshop_ChangeVehicles()
{
	new string[MAX_STRING], model;
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		if (vshop_Vehicles[i][vshop_ID] != 0) {
			// ���� ���-�� ���� � ����������
			foreach (new playerid : Player) {
				if (vshop_Vehicles[i][vshop_ID] == GetPlayerVehicleID(playerid)) {
					HideDialog(playerid);
					RemovePlayerFromVehicle(playerid);
				}
			}
			// ������� ���������
			DestroyVehicle(vshop_Vehicles[i][vshop_ID]);
			Delete3DTextLabel(vshop_Vehicles[i][vshop_Text3D]);
		}
		
		model = vshop_VehiclesModels[ random( sizeof(vshop_VehiclesModels) ) ];
		vshop_Vehicles[i][vshop_ID] = CreateVehicle(model,
			vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z], vshop_Vehicles[i][vshop_A],
			colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], 0
		);
		SetVehicleFuel(vshop_Vehicles[i][vshop_ID], 0);
		
		format(string, sizeof(string), "{CCCCCC}%s\n{00AA00}����: {CCCCCC}$%d\n{999999}������ ��� �������", GetVehicleName(model), GetVehicleCost(model));
		vshop_Vehicles[i][vshop_Text3D] = Create3DTextLabel(string, COLOUR_WHITE, vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z], 20.0, 0, 1);
		Attach3DTextLabelToVehicle(vshop_Vehicles[i][vshop_Text3D], vshop_Vehicles[i][vshop_ID], 0.0, 0.0, 0.2);
	}
}

stock vshop_OneHourTimer()
{
	static hours;
	hours++;
	
	if (hours >= VEHSHOP_CAR_CHANGE_TIME) {
		hours = 0;
		vshop_ChangeVehicles();
	}
}

stock buyVehicle(playerid, vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	AddPlayerVehicle(playerid, 0, model, colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], float(GetMaxVehicleFuel(model)));
	return 1;
}

stock vshop_ShowBuyDialog(playerid)
{
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
	new string[MAX_STRING];
	format(string, sizeof(string),
		"�� ������ ������ ���������� '%s' �� $%d?",
		GetVehicleName(model), GetVehicleCost(model)
	);
	return ShowPlayerDialog(playerid, vshop_DialogID, DIALOG_STYLE_MSGBOX,
		"������� �����������",
		string,
		"������", "�����"
	);
}

stock vshop_IsShopVehicle(vehicleid)
{
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		if (vshop_Vehicles[i][vshop_ID] == vehicleid) {
			return 1;
		}
	}
	return 0;
}
