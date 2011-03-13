// Winsock.h - Net Eye
// Winsock Information Header File
// By Joe Esposito


#pragma once



// Structs
// --------

struct _SOCKETLIST;
struct _SOCKETGROUP;

typedef struct _SOCKETLIST
{
	_SOCKETLIST *lpNext;
	_SOCKETLIST *lpPrev;
	SOCKET skSocket;
} SOCKETLIST, *LPSOCKETLIST;

typedef struct _SOCKETGROUP
{
	_SOCKETLIST *lpFirst;
	_SOCKETLIST *lpLast;
} SOCKETGROUP, *LPSOCKETGROUP;



// Declarations
// -------------

bool SocketGroupAdd ( LPSOCKETGROUP lpSocketGroup, SOCKET skSocket );
bool SocketGroupRemove ( LPSOCKETGROUP lpSocketGroup, SOCKET skSocket );
bool SocketGroupClear ( LPSOCKETGROUP lpSocketGroup );
UINT SocketGroupCount ( LPSOCKETGROUP lpSocketGroup );



// Implementation File:
// "Socket.h"
