#include<windows.h>
#include <strsafe.h>
#include<tchar.h>
#include<stdio.h>

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

int GetStringsFromClient(TCHAR **str)
{
	TCHAR str1[255];
	if (*str!=NULL)
	{
		wsprintf(str1,TEXT("Message got is %c"),*str);
		MessageBox(NULL, str1, TEXT("Message"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("Didnt get anything"), TEXT("Message"), MB_OK);
	}
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

int HandleFileIO()
{
	void ErrorExit(LPTSTR lpszFunction);

	HANDLE hFile;
	char DataBuffer[] = "This is some test data to write to the file.";
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	//TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment");

	TCHAR szBuffer[MAX_PATH + 1] = TEXT("C:\\Users\\Ganesha\\Desktop\\Ganesha_assignment\\Test.txt");
	hFile = CreateFile(szBuffer,                // name of the write
		GENERIC_READ|GENERIC_WRITE| GENERIC_EXECUTE,          // open for writing
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

	return 0;
}

