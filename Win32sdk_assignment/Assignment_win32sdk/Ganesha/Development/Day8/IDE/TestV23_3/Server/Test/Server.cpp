#include<windows.h>
#include <strsafe.h>
#include<tchar.h>
#include<stdio.h>
#include<stdlib.h>
#include<comdef.h>

// DllMain
BOOL WINAPI DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}

UINT GetTextSize(TCHAR *str)
{
	for (UINT i = 0;; i++)
	{
		if (str[i] == '\0')
		{
			return i;
		}
	}
}

// exported functions
int GetStringsFromClient(TCHAR **a,TCHAR **b)
{
	int HandleFileIO(TCHAR DataBuffer[]);
	UINT GetTextSize(TCHAR *str);
	int i, j;
	TCHAR buffer[100000];

	for (i = 0, j = 0; *(a + i) != NULL, *(b + i) != NULL; i++, j++)
	{
		wsprintf(buffer, TEXT("%s:%s\n"), *(b + i), *(a + i));
		HandleFileIO(buffer);
	}
	return 0;
}

int HandleFileIO(TCHAR DataBuffer[])
{
	void ErrorExit(LPTSTR lpszFunction);
	HANDLE hFile;
	//DWORD dwBytesToWrite = (DWORD)wcslen(DataBuffer);
	DWORD dwBytesToWrite = (DWORD)GetTextSize(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Ganesha.txt");
	TCHAR str1[100000];
	//char str2[100000];

	//wcstombs_s(NULL, str2, (dwBytesToWrite+1) * sizeof(char), DataBuffer, dwBytesToWrite);
	_bstr_t b(DataBuffer);
	const char *c = b;

	hFile = CreateFile(szBuffer,                // name of the write
		FILE_APPEND_DATA,
		0,                      // do not share
		NULL,                   // default security
		OPEN_ALWAYS,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) 
	{
		ErrorExit(TEXT("CreateFile"));
		return -1;
	}
	else
	{
		MessageBox(NULL, TEXT("File Operations done successfully"), TEXT("Message"), MB_OK);
	}

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		//str2,
		c,
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);            // no overlapped structure

	if (FALSE == bErrorFlag)
	{
		ErrorExit(TEXT("WriteFile"));
		MessageBox(NULL, TEXT("Unable to write to file."), TEXT("Error"), MB_OK);
	}
	else
	{
		if (dwBytesWritten != dwBytesToWrite)
		{
			// This is an error because a synchronous write that results in
			// success (WriteFile returns TRUE) should write all data as
			// requested. This would not necessarily be the case for
			// asynchronous writes.
			MessageBox(NULL, TEXT("dwBytesWritten != dwBytesToWrite"), TEXT("Error"), MB_OK);
		}
		else
		{
			wsprintf(str1, TEXT("Wrote %d bytes to %s successfully"), dwBytesWritten, szBuffer);
			MessageBox(NULL, str1, TEXT("Message"), MB_OK);
		}
	}
	CloseHandle(hFile);
	return 0;
}

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

