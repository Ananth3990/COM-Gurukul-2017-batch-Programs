#include<windows.h>

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
		MessageBox(NULL,str1, TEXT("Message"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("Didnt get anything"), TEXT("Message"), MB_OK);
	}
	return 0;
}

int HandleFileIO(TCHAR **str)
{
	MessageBox(NULL, TEXT("HandleFileIO() called"), TEXT("Message"), MB_OK);
	return 0;
}
