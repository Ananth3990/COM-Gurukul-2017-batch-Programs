#include<windows.h>
#include <strsafe.h>
#include<tchar.h>
#include<stdio.h>
#include<stdlib.h>

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
// exported functions
int SumOfTwoIntegers(int num1, int num2)
{
	// variable declarations
	int num3;
	// code
	num3 = num1 + num2;
	return(num3);
}

int SubtractionOfTwoIntegers(int num1, int num2)
{
	// variable declarations
	int num3;
	// code
	num3 = num1 - num2;
	return(num3);
}

int GetStringsFromClient(TCHAR **a,TCHAR **b)
{
	int HandleFileIO(TCHAR DataBuffer[]);
	//int i, j;
	TCHAR buffer[100000];

	/*
	for (i = 0, j = 0; *(a + i) != NULL,*(b+i) != NULL; i++, j++)
	{
		wsprintf(buffer, TEXT("%s:%s\n"), *(b + i), *(a + i));
		HandleFileIO(buffer);
	}
	*/

	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 0), *(a + 0));
	MessageBox(NULL, buffer, TEXT("Message"), MB_OK);
	HandleFileIO(buffer);

	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 1), *(a + 1));
	MessageBox(NULL,buffer,TEXT("Message"),MB_OK);
	HandleFileIO(buffer);

	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 2), *(a + 2));
	MessageBox(NULL, buffer, TEXT("Message"), MB_OK);
	HandleFileIO(buffer);

	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 3), *(a + 3));
	MessageBox(NULL, buffer, TEXT("Message"), MB_OK);
	HandleFileIO(buffer);

	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 4), *(a + 4));
	MessageBox(NULL, buffer, TEXT("Message"), MB_OK);
	HandleFileIO(buffer);

	
	wsprintf(buffer, TEXT("%s:%s\n"), *(b + 5), *(a + 5));
	MessageBox(NULL, buffer, TEXT("Message"), MB_OK);
	HandleFileIO(buffer);

	return 0;
}

/*
int HandleFileIO(TCHAR DataBuffer1[])
{
	//Code taken from msdn
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb540534(v=vs.85).aspx
	void ErrorExit(LPTSTR lpszFunction);

	HANDLE hFile;
	char DataBuffer[] = "This is some test data to write to the file.\r\nI am Ananth Chandrasekharan";
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Ganesha.txt");
	TCHAR str1[100000];
	hFile = CreateFile(szBuffer,                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template


	if (hFile == INVALID_HANDLE_VALUE)
	{
		ErrorExit(TEXT("CreateFile"));
		return -1;
	}
	else
	{
		MessageBox(NULL, TEXT("File Created Successfully"), TEXT("Message"), MB_OK);
	}

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		DataBuffer,      // start of data to write
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
			wsprintf(str1,TEXT("Wrote %d bytes to %s successfully"),dwBytesWritten,szBuffer);
			MessageBox(NULL,str1, TEXT("Message"), MB_OK);
		}
	}

	CloseHandle(hFile);

	return 0;
}
*/

/*
int HandleFileIO(TCHAR DataBuffer[])
{
	//Code taken from msdn
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb540534(v=vs.85).aspx
	void ErrorExit(LPTSTR lpszFunction);

	HANDLE hFile;
	TCHAR str1[100000];
	//char DataBuffer[] = "This is some test data to write to the file.\r\nI am Ananth Chandrasekharan";
	DWORD dwBytesToWrite = (DWORD)wcslen(DataBuffer);
	wsprintf(str1, TEXT("wcslen gave %d"), dwBytesToWrite);
	MessageBox(NULL, str1, TEXT("Message"), MB_OK);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Ganesha.txt");
	hFile = CreateFile(szBuffer,                // name of the write
		GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE,   // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template


	if (hFile == INVALID_HANDLE_VALUE)
	{
		ErrorExit(TEXT("CreateFile"));
		return -1;
	}
	else
	{
		MessageBox(NULL, TEXT("File Created Successfully"), TEXT("Message"), MB_OK);
	}

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		DataBuffer,      // start of data to write
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
*/

/* //Converted TCHAR to char for sake of proper printing in file
int HandleFileIO(TCHAR DataBuffer1[])
{
	//Code taken from msdn
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb540534(v=vs.85).aspx
	void ErrorExit(LPTSTR lpszFunction);

	HANDLE hFile;
	TCHAR DataBuffer[] = TEXT("This is some test data to write to the file.\r\nI am Ananth Chandrasekharan");
	DWORD dwBytesToWrite = (DWORD)wcslen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Ganesha.txt");
	TCHAR str1[100000];
	char str2[100000];

	//wcstombs_s(str2, DataBuffer, wcslen(DataBuffer) + 1);
	wcstombs_s(NULL,str2,100*sizeof(char),DataBuffer, dwBytesToWrite);

	hFile = CreateFile(szBuffer,                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template


	if (hFile == INVALID_HANDLE_VALUE)
	{
		ErrorExit(TEXT("CreateFile"));
		return -1;
	}
	else
	{
		MessageBox(NULL, TEXT("File Created Successfully"), TEXT("Message"), MB_OK);
	}

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		//DataBuffer,      // start of data to write
		str2,
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
*/

int HandleFileIO(TCHAR DataBuffer[])
{
	//Code taken from msdn
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb540534(v=vs.85).aspx
	void ErrorExit(LPTSTR lpszFunction);

	HANDLE hFile;
	//TCHAR DataBuffer[] = TEXT("This is some test data to write to the file.\r\nI am Ananth Chandrasekharan");
	DWORD dwBytesToWrite = (DWORD)wcslen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Ganesha.txt");
	TCHAR str1[100000];
	char str2[100000];

	wcstombs_s(NULL, str2, 100 * sizeof(char), DataBuffer, dwBytesToWrite);

	hFile = CreateFile(szBuffer,                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template


	if (hFile == INVALID_HANDLE_VALUE)
	{
		ErrorExit(TEXT("CreateFile"));
		return -1;
	}
	else
	{
		MessageBox(NULL, TEXT("File Created Successfully"), TEXT("Message"), MB_OK);
	}

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		str2,
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

