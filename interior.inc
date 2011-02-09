//
// Created: 08.02.11
// Aurthor: Degrey
//

#if defined _interior_included
#endinput
#endif

#define _interior_included
#pragma library interior

enum PickInfo
{
	Float:X,
	Float:Y,
	Float:Z,
	Float:FacingAngle
}

enum EnterInfo
{
	Float:X,
	Float:Y,
	Float:Z,
	Float:FacingAngle,
	interiorid
}
#define SIZE 81

new EnterPositions[SIZE][EnterInfo] = {
{296.920013,-111.071998,1001.515625,359.903076,6},
{365.674346,-10.712305,1001.851562,359.903076,9},
{772.111999,-3.898649,1000.728820,0.000000,5},
{207.738006,-109.019996,1005.132812,0.000000,15},
{501.980987,-69.150199,998.757812,180.000015,11},
{2807.620117,-1171.900024,1025.570312,0.000000,8},
{2216.340087,-1150.510009,1025.796875,270.000000,15},
{203.777999,-48.492401,1001.804687,0.000000,1},
{372.351989,-131.651000,1001.492187,359.903076,5},
{246.783996,63.900199,1003.640625,0.000000,6},
{1548.140014,-1366.420043,326.210937,89.999992,0},
{833.818969,7.418000,1004.179687,89.999992,3},
{286.148986,-40.644401,1001.515625,359.903076,1},
{363.415008,-74.579391,1001.507812,314.700012,10},
{365.672454,-10.711545,1001.851562,359.903076,9},
{363.412994,-74.578697,1001.507812,314.700012,10},
{207.054992,-138.804992,1003.507812,0.000000,3},
{296.920013,-111.071998,1001.515625,359.903076,6},
{365.673004,-10.713199,1001.851562,359.903076,9},
{285.800994,-84.547599,1001.515625,359.903076,4},
{372.351989,-131.651000,1001.492187,359.903076,5},
{246.783996,63.900199,1003.640625,0.000000,6},
{833.818969,7.418000,1004.179687,89.999992,3},
{372.351989,-131.651000,1001.492187,359.903076,5},
{372.351989,-131.651000,1001.492187,359.903076,5},
{285.800994,-84.547599,1001.515625,359.903076,4},
{2015.449951,1017.090026,996.875000,89.999992,10},
{285.800994,-84.547599,1001.515625,359.903076,4},
{388.872009,173.804992,1008.382812,89.999992,3},
{1212.020019,-28.663099,1000.953125,180.000015,3},
{365.673004,-10.713199,1001.851562,359.903076,9},
{372.351989,-131.651000,1001.492187,359.903076,5},
{2233.909912,1710.729980,1011.298706,180.000015,1},
{-26.691600,-55.714900,1003.546875,0.000000,6},
{365.673004,-10.713199,1001.851562,359.903076,9},
{363.412994,-74.578697,1001.507812,314.700012,10},
{501.980987,-69.150199,998.757812,180.000015,11},
{-26.691600,-55.714900,1003.546875,0.000000,6},
{363.412994,-74.578697,1001.507812,314.700012,10},
{-30.946699,-89.609596,1003.546875,0.000000,18},
{285.800994,-84.547599,1001.515625,359.903076,4},
{-30.946699,-89.609596,1003.546875,0.000000,18},
{365.673004,-10.713199,1001.851562,359.903076,9},
{207.053771,-138.804290,1003.507812,0.000000,3},
{226.294006,-7.431529,1002.210937,89.999992,5},
{203.777999,-48.492401,1001.804687,0.000000,1},
{1204.812866,-12.584808,1000.921875,0.000000,2},
{-100.325996,-22.816499,1000.718750,0.000000,3},
{372.351989,-131.651000,1001.492187,359.903076,5},
{-26.691600,-55.714900,1003.546875,0.000000,6},
{238.662002,141.052001,1003.023437,0.000000,3},
{288.746002,169.350997,1007.171875,0.000000,3},
{363.412994,-74.578697,1001.507812,314.700012,10},
{1133.069946,-9.573060,1000.679687,0.000000,12},
{-26.691600,-55.714900,1003.546875,0.000000,6},
{773.580017,-77.096702,1000.655029,0.000000,7},
{207.739395,-109.022705,1005.132812,0.000000,15},
{365.673004,-10.713199,1001.851562,359.903076,9},
{161.391006,-95.285598,1001.804687,0.000000,18},
{-26.691600,-55.714900,1003.546875,0.000000,6},
{372.351989,-131.651000,1001.492187,359.903076,5},
{363.412994,-74.578697,1001.507812,314.700012,10},
{363.412994,-74.578697,1001.507812,314.700012,10},
{365.673004,-10.713199,1001.851562,359.903076,9},
{365.673004,-10.713199,1001.851562,359.903076,9},
{-959.874023,1952.000000,9.000000,217.000015,17},
{420.484985,2535.590087,10.000000,35.019992,10},
{316.524993,-168.707000,999.593750,359.903076,6},
{-2637.449951,1404.630004,906.460937,0.000000,3},
{372.351989,-131.651000,1001.492187,359.903076,5},
{363.412994,-74.578697,1001.507812,314.700012,10},
{207.738006,-109.019996,1005.132812,0.000000,15},
{363.414398,-74.579460,1001.507812,314.700012,10},
{161.391006,-95.285598,1001.804687,0.000000,18},
{372.351989,-131.651000,1001.492187,359.903076,5},
{774.213989,-48.924301,1000.585937,0.000000,6},
{-2238.686279,130.904876,1035.414062,325.000000,6},
{286.148986,-40.644401,1001.515625,359.903076,1},
{365.673004,-10.713199,1001.851562,359.903076,9},
{203.777999,-48.492401,1001.804687,0.000000,1},
{363.412994,-74.578697,1001.507812,314.700012,10}
};

new ExitPositions[SIZE][PickInfo] = {
{2400.502685,-1978.478393,13.546875,0.000000},
{2397.830078,-1895.650024,13.382812,0.000000},
{2227.713623,-1723.650268,13.551807,136.999954},
{2244.479980,-1664.060058,15.476562,357.000030},
{2308.120117,-1643.630004,14.827047,93.000000},
{2808.000000,-1177.189941,25.376916,180.000015},
{2229.020019,-1159.800048,25.798063,89.999992},
{2112.870117,-1214.790039,23.967750,180.000015},
{2103.459960,-1806.589965,13.554687,91.999992},
{1552.449951,-1674.989990,16.195312,89.999992},
{1577.239990,-1330.670043,16.484375,314.000000},
{1631.859985,-1168.569946,24.078125,7.605606},
{1365.349975,-1279.060058,13.546875,89.999992},
{1199.130004,-920.570983,43.029186,180.000015},
{924.525024,-1352.770019,13.376605,89.999992},
{812.980651,-1616.138305,13.546875,270.420043},
{501.779418,-1358.499511,16.125158,315.000000},
{-2092.708984,-2463.809326,30.625000,319.000000},
{-2154.030029,-2461.280029,30.851562,229.000000},
{240.039001,-178.296997,1.578125,90.096984},
{203.705001,-205.350006,1.578125,180.000015},
{631.013000,-571.607971,16.335937,274.097503},
{1291.900634,269.456451,19.554687,7.605606},
{1362.640014,249.569000,19.566932,69.097511},
{2335.800048,75.230102,26.482131,270.000000},
{2336.800048,61.698699,26.480667,270.000000},
{2022.489990,1007.010009,10.820312,7.605606},
{2156.510009,943.229003,10.820312,7.605606},
{2415.600097,1123.709960,10.820312,270.000000},
{2543.149902,1022.059997,10.820312,7.605606},
{2635.580078,1671.079956,11.023437,89.999992},
{2635.580078,1849.869995,11.023437,89.999992},
{2193.919921,1676.420043,12.367187,7.605606},
{2190.975341,1991.020019,11.479047,89.999992},
{2393.179931,2045.760009,10.820312,0.000000},
{2363.639404,2071.021484,10.820312,89.999992},
{2441.147705,2062.039062,10.820312,180.000015},
{2452.469970,2062.040039,10.820312,180.000015},
{2470.830078,2033.880004,11.062500,89.999992},
{2546.709960,1967.180053,10.820312,180.000015},
{2535.939941,2083.560058,10.820312,89.999992},
{2890.929931,2447.179931,10.820312,224.000015},
{2844.530029,2401.159912,10.820312,224.000015},
{2818.636474,2401.541015,10.820312,124.999992},
{2795.239990,2424.699951,10.820312,124.999992},
{2772.020019,2447.639892,10.820312,124.999992},
{2506.739990,2130.489990,10.820312,0.000000},
{2089.520019,2074.479980,10.820312,270.000000},
{2351.889892,2529.090087,10.820312,180.000015},
{2247.659912,2401.360107,11.250000,0.000000},
{2286.959960,2429.110107,10.820312,180.000015},
{2337.100097,2455.949951,14.968750,180.000015},
{2172.959228,2795.793457,10.820312,270.000000},
{1659.420043,2252.790039,11.070102,0.000000},
{1934.150024,2307.169921,10.820312,89.999992},
{1968.699951,2294.199951,16.455863,180.000015},
{2105.790039,2257.489990,11.023437,270.000000},
{2105.790039,2228.760009,11.023437,270.000000},
{2090.580078,2221.100097,10.820312,180.000015},
{2097.760009,2221.100097,10.820312,180.000015},
{2083.489990,2221.100097,10.820312,180.000015},
{1875.339599,2072.070556,11.062500,270.000000},
{1161.529785,2072.020751,11.062500,270.000000},
{173.761001,1174.069946,14.757812,190.223999},
{-1211.810058,1832.459960,41.929687,312.000000},
{-594.263977,2020.300048,60.382812,14.000013},
{430.407012,2535.520019,16.353015,243.216979},
{-1508.890014,2608.750000,55.835937,180.000015},
{-2625.330078,1411.010009,7.093750,180.000015},
{-1725.890014,1359.339965,7.187500,96.000000},
{-2356.479980,1005.140014,50.898437,180.000015},
{-2377.320068,909.293029,45.445312,352.394378},
{-1910.260620,830.598937,35.171875,334.000000},
{-1886.199951,862.473022,35.171875,128.999984},
{-1805.790039,943.221008,24.890625,352.394378},
{-2269.459960,-155.957000,35.320312,270.000000},
{-2243.310058,128.520996,35.320312,89.999992},
{-2625.850097,209.143005,4.616612,352.394378},
{-2671.530029,259.140991,4.632812,352.394378},
{-2494.479980,-29.106500,25.765625,89.999992},
{-2335.950439,-166.645248,35.554687,270.000000}
};

stock interior_OnGameModeInit()
{
	DisableInteriorEnterExits();
	for(new i=0;i<SIZE;i++)
	{
		CreatePickup(1318,1,ExitPositions[i][X],ExitPositions[i][Y],ExitPositions[i][Z],-1);
		CreatePickup(1559,1,EnterPositions[i][X],EnterPositions[i][Y],EnterPositions[i][Z],-1);
		//CreateStreamMapIcon(2,ExitPositions[i][X],ExitPositions[i][Y],ExitPositions[i][Z]);
	}
	return 1;
}

stock interior_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	#pragma unused oldkeys,newkeys
	for(new id=0,idd;id<SIZE;id++)
	{
		if(IsPlayerInRangeOfPoint(playerid,1.5,EnterPositions[id][X],EnterPositions[id][Y],EnterPositions[id][Z]+0.5))
		{
			idd = GetPVarInt(playerid,"InteriorIndex");
			SetPlayerInterior(playerid,0);
			SetPlayerPos(playerid,ExitPositions[idd][X],ExitPositions[idd][Y],ExitPositions[idd][Z]);
			SetPlayerFacingAngle(playerid,ExitPositions[idd][FacingAngle]);
			return 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid,1.5,ExitPositions[id][X],ExitPositions[id][Y],ExitPositions[id][Z]))
		{
			SetPVarInt(playerid,"InteriorIndex",id);
			SetPlayerPos(playerid,EnterPositions[id][X],EnterPositions[id][Y],EnterPositions[id][Z]);
			SetPlayerFacingAngle(playerid,EnterPositions[id][FacingAngle]);
			SetPlayerInterior(playerid,EnterPositions[id][interiorid]);
			return 1;
		}
	}

	return 1;
}

stock IsPlayerAtEnterExit(playerid)
{
	for(new id=0;id<SIZE;id++)
	{
		if(
		IsPlayerInRangeOfPoint(playerid,1.5,EnterPositions[id][X],EnterPositions[id][Y],EnterPositions[id][Z]+0.5)
		|| 
		IsPlayerInRangeOfPoint(playerid,1.5,ExitPositions[id][X],ExitPositions[id][Y],ExitPositions[id][Z])
		) return 1;
	}
	return 0;
}