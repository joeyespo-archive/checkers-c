// DFD.cpp
// Dynamic FD Implementation File
// By Joe Esposito


#pragma once



// Adds a single socket in the set, and updates the secondary set
bool DFD_Add (SOCKET s, LPDFD_SET lpdfds)
{
	LPUINT lpTempFDS;
	UINT nCount, i;

	if (lpdfds == NULL) return false;
	if ((lpdfds->fds == NULL) || (lpdfds->fds2 == NULL)) DFD_Zero(lpdfds);

	lpTempFDS = (LPUINT)lpdfds->fds;
	nCount = *lpTempFDS;

	for (i = 1; i <= nCount; i++)
		if (lpTempFDS[i] == (s)) return false;


	lpdfds->fds = new UINT [(nCount + 2)];	// current count + 1 (new) + 1 (count var)
	if (lpdfds->fds == NULL) {
		lpdfds->fds = lpTempFDS;
		return false;
	}

	if (nCount > 0)
		memcpy( (&(((LPUINT)lpdfds->fds)[1])), (&(lpTempFDS[1])), (nCount * 4) );
	
	delete [(nCount * 4) + 4] lpTempFDS;

	((LPUINT)lpdfds->fds)[++nCount] = (UINT)s;
	((LPUINT)lpdfds->fds)[0] = nCount;


	if (lpdfds->fds2 != NULL)
	{
		lpTempFDS = (LPUINT)lpdfds->fds2; lpdfds->fds2 = new UINT [(nCount + 1)];
		nCount = *lpTempFDS;
		memcpy(lpdfds->fds2, lpTempFDS, ((nCount * 4) + 4) );
		delete [(nCount * 4) + 4] lpTempFDS;
	}
	
	return true;
}

// Removes a single socket in the set, and updates the secondary set
bool DFD_Remove (SOCKET s, LPDFD_SET lpdfds)
{
	LPUINT lpTempFDS;
	UINT nCount, i;

	if (lpdfds == NULL) return false;
	if ((lpdfds->fds == NULL) || (lpdfds->fds2 == NULL)) if (!DFD_Zero(lpdfds)) { DFD_DELETE(lpdfds); return false; }


	lpTempFDS = (LPUINT)lpdfds->fds;
	nCount = *lpTempFDS;
	
	if (nCount == 0) return true;
	
	for (i = 1; i <= nCount; i++)
	{
		if (lpTempFDS[i] == (s))
		{
			if (nCount > 1)
			{
				if ((lpdfds->fds = new UINT [(nCount)]) == NULL) { DFD_DELETE(lpdfds); return false; }
				if (i > 1) memcpy( (&(((LPUINT)lpdfds->fds)[1])), (&(lpTempFDS[1])), ((i - 1) * 4) );
				if (i < nCount) memcpy( (&(((LPUINT)lpdfds->fds)[i])), (&(lpTempFDS[(i + 1)])), ((nCount - i) * 4) );
				*((LPUINT)lpdfds->fds) = (nCount - 1);
				delete [(nCount + 1)] lpTempFDS;

				lpTempFDS = (LPUINT)lpdfds->fds2;
				if ((lpdfds->fds2 = new UINT [(nCount)]) == NULL) { DFD_DELETE(lpdfds); return false; }
				if (i > 1) memcpy( (&(((LPUINT)lpdfds->fds2)[1])), (&(lpTempFDS[1])), ((i - 1) * 4) );
				if (i < nCount) memcpy( (&(((LPUINT)lpdfds->fds2)[i])), (&(lpTempFDS[(i + 1)])), ((nCount - i) * 4) );
				*((LPUINT)lpdfds->fds2) = (nCount - 1);
				delete [(nCount + 1)] lpTempFDS;
			}
			else
			{
				if ((lpdfds->fds = new UINT [1]) == NULL) { DFD_DELETE(lpdfds); return false; }
				*(LPUINT)lpdfds->fds = 0;
				delete [(nCount + 1)] lpTempFDS;

				lpTempFDS = (LPUINT)lpdfds->fds2;
				if ((lpdfds->fds2 = new UINT [1]) == NULL) { DFD_DELETE(lpdfds); return false; }
				*(LPUINT)lpdfds->fds2 = 0;
				delete [(nCount + 1)] lpTempFDS;
			}
			
			return true;
		}
	}

	return true;
}

bool DFD_Zero (LPDFD_SET lpdfds)
{
	LPUINT lpTempFDS;
	UINT nCount = 0;
	
	if (lpdfds == NULL) return false;


	lpTempFDS = (LPUINT)lpdfds->fds;
	
	try { if (lpTempFDS != NULL) nCount = *lpTempFDS; }
	catch(...) { nCount = 0; lpTempFDS = NULL; }

	lpdfds->fds = new UINT [1];
	*((LPUINT)lpdfds->fds) = 0;
	if (lpdfds->fds == NULL) {
		lpdfds->fds = lpTempFDS;
		return false;
	}

	if (lpTempFDS != NULL) delete [(nCount + 1)] lpTempFDS;


	lpTempFDS = (LPUINT)lpdfds->fds2;
	try { if (lpTempFDS != NULL) nCount = *lpTempFDS; }
	catch(...) { nCount = 0; lpTempFDS = NULL; }
	lpdfds->fds2 = new UINT [1];
	*((LPUINT)lpdfds->fds2) = 0;
	if (lpTempFDS != NULL) delete [(nCount + 1)] lpTempFDS;

	return true;
}



int select (int nfds, dfd_set *readdfds, dfd_set *writedfds, dfd_set *exceptdfds, const timeval *timeout)
{
	return select(nfds,
		(fd_set *)((readdfds) ? (memcpy( ((dfd_set *)(readdfds))->fds2, ((dfd_set *)(readdfds))->fds, (((*((LPUINT)(((dfd_set *)readdfds)->fds))) * 4) + 4) )) : (NULL)),
		(fd_set *)((writedfds) ? (memcpy( ((dfd_set *)(writedfds))->fds2, ((dfd_set *)(writedfds))->fds, (((*((LPUINT)(((dfd_set *)writedfds)->fds))) * 4) + 4) )) : (NULL)),
		(fd_set *)((exceptdfds) ? (memcpy( ((dfd_set *)(exceptdfds))->fds2, ((dfd_set *)(exceptdfds))->fds, (((*((LPUINT)(((dfd_set *)exceptdfds)->fds))) * 4) + 4) )) : (NULL)),
		timeout);
}
