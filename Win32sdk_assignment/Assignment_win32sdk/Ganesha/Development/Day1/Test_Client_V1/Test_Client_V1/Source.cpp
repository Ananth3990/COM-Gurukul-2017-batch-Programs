
#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int GetTextSize(TCHAR);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	RegisterClassEx(&wndclass);
	
	hwnd = CreateWindow(szAppName,
		TEXT("User Of Explicit Sever's Dll"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

int GetTextSize(TCHAR *str)
{
	for (int i=0;;i++)
	{
		if (str[i]=='\0')
		{
			return i;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HMODULE hLib = NULL;
	typedef int(*pFunctionPointer)(int, int);
	pFunctionPointer pfn = NULL;
	int n1, n2, n3;
	TCHAR str[255];

	RECT rc;
	TCHAR show_at_bottom[] = TEXT("Press Spacebar to generate a text file");
	HDC hdc;
	PAINTSTRUCT ps;

	TCHAR FullNameHeader[] = TEXT("FullName   :");
	TCHAR FullName[] = TEXT("Ananth Chandrasekharan");
	TCHAR ContactNumber[] = TEXT("9892980509");
	TCHAR EmailId[] = TEXT("ananthchandrasekharan@gmail.com");
	TCHAR CurrentCompany[] = TEXT("Effortsys Technologies Pvt Ltd");
	TCHAR DurationAttended[] = TEXT("WinRT 2016");
	TCHAR WhyToAttend[] = TEXT("");

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hLib = LoadLibrary(TEXT("Server.dll"));
		if (hLib == NULL)
		{
			MessageBox(hwnd, TEXT("Can Not Load Dll.\nExitting."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
			return -1;
		}
		pfn = (pFunctionPointer)GetProcAddress(hLib, "SumOfTwoIntegers");
		if (pfn == NULL)
		{
			MessageBox(hwnd, TEXT("Can Not Get Address Of SumOfTwoIntegers().\nExitting."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
			return -1;
		}
		n1 = 100;
		n2 = 50;
		n3 = pfn(n1, n2);
		wsprintf(str, TEXT("Sum Of %d And %d = %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);
		pfn = (pFunctionPointer)GetProcAddress(hLib, "SubtractionOfTwoIntegers");
		if (pfn == NULL)
		{
			MessageBox(hwnd, TEXT("Can Not Get Address Of SubtractionOfTwoIntegers().\nExitting."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		n3 = pfn(n1, n2);
		wsprintf(str, TEXT("Subtraction Of %d And %d = %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rc);

		SetTextColor(hdc,RGB(0,0,255));
		SetBkColor(hdc,RGB(128,128,128));
		DrawText(hdc, show_at_bottom,-1,&rc,DT_SINGLELINE|DT_BOTTOM|DT_CENTER);
		
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(128, 128, 128));
		//TextOut(hdc,10,10,FullNameHeader,wcsnlen_s(FullNameHeader,15));
		TextOut(hdc, 10, 10, FullNameHeader,GetTextSize(FullNameHeader));

		SetTextColor(hdc, RGB(0, 255,0));
		SetBkColor(hdc, RGB(125, 128, 128));
		TextOut(hdc,90+GetTextSize(FullNameHeader), 10, FullName, GetTextSize(FullName));
		EndPaint(hwnd, &ps);
		break;


	case WM_DESTROY:
		if (hLib)
			FreeLibrary(hLib);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
