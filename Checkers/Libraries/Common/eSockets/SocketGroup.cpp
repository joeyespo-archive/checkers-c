// Winsock.h - Net Eye
// Winsock Information Header File
// By Joe Esposito


#pragma once


// Header File:
#include "Main.h"



bool SocketGroupAdd (LPSOCKETGROUP lpsgSocketGroup, SOCKET skSocket)
{
	LPSOCKETLIST lpSocketList;

	if (lpsgSocketGroup == NULL) return false;


	lpSocketList = new SOCKETLIST;
	lpSocketList->skSocket = skSocket;
	lpSocketList->lpNext = NULL;
	lpSocketList->lpPrev = lpsgSocketGroup->lpLast;

	if (lpsgSocketGroup->lpFirst == NULL)
	{
		lpsgSocketGroup->lpFirst = lpSocketList;

		lpSocketList->lpNext = NULL;
		lpSocketList->lpPrev = NULL;
	}

	lpsgSocketGroup->lpLast = lpSocketList;

	if (lpSocketList->lpPrev != NULL) lpSocketList->lpPrev->lpNext = lpSocketList;
	
	return true;
}

bool SocketGroupRemove (LPSOCKETGROUP lpsgSocketGroup, SOCKET skSocket)
{
	LPSOCKETLIST lpSocketList, lpSocketListTemp;

	if (lpsgSocketGroup == NULL) return false;

	
	for (lpSocketList = lpsgSocketGroup->lpFirst; lpSocketList != NULL; lpSocketList = lpSocketListTemp)
	{
		lpSocketListTemp = lpSocketList->lpNext;
		
		if (lpSocketList->skSocket == skSocket)
		{
			if (lpsgSocketGroup->lpFirst == lpSocketList) lpsgSocketGroup->lpFirst = lpSocketList->lpNext;
			if (lpsgSocketGroup->lpLast == lpSocketList) lpsgSocketGroup->lpLast = lpSocketList->lpPrev;

			if (lpSocketList->lpPrev != NULL) lpSocketList->lpPrev = lpSocketList->lpNext;
			if (lpSocketList->lpNext != NULL) lpSocketList->lpNext = lpSocketList->lpPrev;
			
			delete lpSocketList;
		}
	}

	return true;
}

bool SocketGroupClear (LPSOCKETGROUP lpsgSocketGroup)
{
	LPSOCKETLIST lpSocketList, lpSocketListTemp;

	if (lpsgSocketGroup == NULL) return false;

	
	for (lpSocketList = lpsgSocketGroup->lpFirst; lpSocketList != NULL; lpSocketList = lpSocketListTemp)
	{
		lpSocketListTemp = lpSocketList->lpNext;

		delete lpSocketList;
	}
	
	lpsgSocketGroup->lpFirst = NULL;
	lpsgSocketGroup->lpLast = NULL;

	return true;
}

UINT SocketGroupCount (LPSOCKETGROUP lpsgSocketGroup)
{
	LPSOCKETLIST lpSocketList;
	UINT c = 0;

	if (lpsgSocketGroup == NULL) return false;

	
	for (lpSocketList = lpsgSocketGroup->lpFirst; lpSocketList != NULL; lpSocketList = lpSocketList->lpNext)
		c++;

	return c;
}
