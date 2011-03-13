// EspoSock.h
// Espo Sockets Header File
// By Joe Esposito


#pragma once


// Declarations
// -------------

bool WSAStartup ( BYTE major, BYTE minor, LPWSADATA lpWSAData = NULL );
char *WSAGetLastErrorMessage ();



// Include Header Files
// ---------------------

#include "DFD.h"
#include "SocketGroup.h"



// Implementation File:
// "EspoSock.h"
