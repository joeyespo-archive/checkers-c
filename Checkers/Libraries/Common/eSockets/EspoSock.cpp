// EspoSock.cpp
// Espo Sockets Implementation File
// By Joe Esposito


#pragma once



// Include Header File:
#include "EspoSock.h"



// Include Source Files
// ---------------------

#include "DFD.cpp"
#include "SocketGroup.cpp"



bool WSAStartup (BYTE major, BYTE minor, LPWSADATA lpWSAData)
{
	WSADATA wsaData;

	if (!WSAStartup(MAKEWORD(major, minor), &wsaData)) return false;
	if ((LOBYTE(wsaData.wVersion) != major) || ((HIBYTE(wsaData.wVersion) != minor)))
	{
		WSACleanup();
		return false;
	}

	if (lpWSAData != NULL) memcpy(lpWSAData, &wsaData, sizeof(WSADATA));

	return true;
}


char *WSAGetLastErrorMessage ()
{
	switch (WSAGetLastError())
	{

	// Windows Sockets definitions of regular Microsoft C error constants
	case WSAEINTR:				return "WSAEINTR";
	case WSAEBADF:				return "WSAEBADF";
	case WSAEACCES:				return "WSAEACCES";
	case WSAEFAULT:				return "WSAEFAULT";
	case WSAEINVAL:				return "WSAEINVAL";
	case WSAEMFILE:				return "WSAEMFILE";

    // Windows Sockets definitions of regular Berkeley error constants
	case WSAEWOULDBLOCK:		return "WSAEWOULDBLOCK";
	case WSAEINPROGRESS:		return "WSAEINPROGRESS";
	case WSAEALREADY:			return "WSAEALREADY";
	case WSAENOTSOCK:			return "WSAENOTSOCK";
	case WSAEDESTADDRREQ:		return "WSAEDESTADDRREQ";
	case WSAEMSGSIZE:			return "WSAEMSGSIZE";
	case WSAEPROTOTYPE:			return "WSAEPROTOTYPE";
	case WSAENOPROTOOPT:		return "WSAENOPROTOOPT";
	case WSAEPROTONOSUPPORT:	return "WSAEPROTONOSUPPORT";
	case WSAESOCKTNOSUPPORT:	return "WSAESOCKTNOSUPPORT";
	case WSAEOPNOTSUPP:			return "WSAEOPNOTSUPP";
	case WSAEPFNOSUPPORT:		return "WSAEPFNOSUPPORT";
	case WSAEAFNOSUPPORT:		return "WSAEAFNOSUPPORT";
	case WSAEADDRINUSE:			return "WSAEADDRINUSE";
	case WSAEADDRNOTAVAIL:		return "WSAEADDRNOTAVAIL";
	case WSAENETDOWN:			return "WSAENETDOWN";
	case WSAENETUNREACH:		return "WSAENETUNREACH";
	case WSAENETRESET:			return "WSAENETRESET";
	case WSAECONNABORTED:		return "WSAECONNABORTED";
	case WSAECONNRESET:			return "WSAECONNRESET";
	case WSAENOBUFS:			return "WSAENOBUFS";
	case WSAEISCONN:			return "WSAEISCONN";
	case WSAENOTCONN:			return "WSAENOTCONN";
	case WSAESHUTDOWN:			return "WSAESHUTDOWN";
	case WSAETOOMANYREFS:		return "WSAETOOMANYREFS";
	case WSAETIMEDOUT:			return "WSAETIMEDOUT";
	case WSAECONNREFUSED:		return "WSAECONNREFUSED";
	case WSAELOOP:				return "WSAELOOP";
	case WSAENAMETOOLONG:		return "WSAENAMETOOLONG";
	case WSAEHOSTDOWN:			return "WSAEHOSTDOWN";
	case WSAEHOSTUNREACH:		return "WSAEHOSTUNREACH";
	case WSAENOTEMPTY:			return "WSAENOTEMPTY";
	case WSAEPROCLIM:			return "WSAEPROCLIM";
	case WSAEUSERS:				return "WSAEUSERS";
	case WSAEDQUOT:				return "WSAEDQUOT";
	case WSAESTALE:				return "WSAESTALE";
	case WSAEREMOTE:			return "WSAEREMOTE";

	case WSAEDISCON:			return "WSAEDISCON";
	
	// Extended Windows Sockets error constant definitions
	case WSASYSNOTREADY:		return "WSASYSNOTREADY";
	case WSAVERNOTSUPPORTED:	return "WSAVERNOTSUPPORTED";
	case WSANOTINITIALISED:		return "WSANOTINITIALISED";
	
	// Other
	case WSAHOST_NOT_FOUND:		return "WSAHOST_NOT_FOUND";
	case WSATRY_AGAIN:			return "WSATRY_AGAIN";
	case WSANO_RECOVERY:		return "WSANO_RECOVERY";
	case WSANO_DATA:			return "WSANO_DATA";

	// Default
	case 0: return "NO ERROR";
	default: return "UNKNOWN ERROR";
	}
}



/* 
char *GetLocalIP()
{
	hostent *HostEnt;
	in_addr addr_in;
	char *LocalHost;

	LocalHost = new char[256];

	gethostname(LocalHost, 256);
	HostEnt = gethostbyname(LocalHost);

	addr_in.S_un.S_un_b.s_b1 = HostEnt->h_addr_list[0][0];
	addr_in.S_un.S_un_b.s_b2 = HostEnt->h_addr_list[0][1];
	addr_in.S_un.S_un_b.s_b3 = HostEnt->h_addr_list[0][2];
	addr_in.S_un.S_un_b.s_b4 = HostEnt->h_addr_list[0][3];

	LocalHost = inet_ntoa(addr_in);

	return LocalHost;
}
*/
