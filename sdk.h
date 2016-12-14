
#pragma once
#pragma warning(disable : 4800)
#pragma warning(disable : 4244)
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;
#include "definitions.h"
#include "indexes.h"

#include "libraries\vmt.h"

#include "structs\vector.h"
#include "structs\vmatrix.h"
#include "structs\usercmd.h"
#include "structs\playerinfo.h"
#include "structs\engine.h"
#include "structs\globals.h"
#include "structs\input.h"
#include "structs\panel.h"
#include "structs\surface.h"
#include "structs\client.h"
#include "structs\crc32.h"
#include "structs\quaternion.h"
#include "structs\modelinfo.h"
#include "structs\checksum_md5.h"
#include "libraries\interfaces.h"
#include "Utils.h"
#include "structs\baseentity.h"
#include "structs\cliententlist.h"
#include "structs\trace.h"

#include "libraries\math.h"

void StartCheat();
BOOL WINAPI DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();

		HWND hwnd = GetConsoleWindow();

		HMENU hMenu = GetSystemMenu(hwnd, FALSE);
		if (hMenu) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

		SetConsoleTitle("[Enigma]: Console");
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		printf("RUN\n");
		Interfaces.GetInterfaces();
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartCheat, NULL, NULL, NULL);
	}
	return true;
}
