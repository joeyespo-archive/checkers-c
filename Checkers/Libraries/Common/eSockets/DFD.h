// DFD.h
// Dynamic FD Header File
// By Joe Esposito


#pragma once



// Dynamic FD set structure
// -------------------------

typedef struct dfd_set
{
	LPVOID fds;			// FD set to check socket state
	LPVOID fds2;		// FD set after select()
} dfd_set, *lpdfd_set, DFD_SET, *LPDFD_SET;

#define DFD_SET(s, dfds)	DFD_Add((SOCKET)s, (dfd_set *)dfds)
#define DFD_CLR(s, dfds)	DFD_Remove((SOCKET)s, (dfd_set *)dfds)
#define DFD_ZERO(dfds)		DFD_Zero((dfd_set *)dfds)
#define DFD_ISSET(s, dfds)	FD_ISSET((SOCKET)s, (fd_set *)(((dfd_set *)dfds)->fds2))
#define DFD_CHECK(dfds)		(fd_set *)memcpy( ((dfd_set *)(dfds))->fds2, ((dfd_set *)(dfds))->fds, (((*((LPUINT)(((dfd_set *)dfds)->fds))) * 4) + 4) )
#define DFD_DELETE(dfds)	delete [((*((LPUINT)((dfds)->fds))) + 1)] ((LPUINT)((dfds)->fds2)); (dfds)->fds2 = NULL;  delete [((*((LPUINT)((dfds)->fds))) + 1)] ((LPUINT)((dfds)->fds)); (dfds)->fds = NULL;

bool DFD_Add ( SOCKET s, LPDFD_SET lpdfds );
bool DFD_Remove ( SOCKET s, LPDFD_SET lpdfds );
bool DFD_Zero ( LPDFD_SET lpdfds );

int select ( int nfds, dfd_set *readdfds, dfd_set *writedfds, dfd_set *exceptdfds, const timeval *timeout );


// Implementation File:
// "DFD.cpp"
