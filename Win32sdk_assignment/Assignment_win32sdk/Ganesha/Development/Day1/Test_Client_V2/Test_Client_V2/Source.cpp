
#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int GetTextSize(TCHAR);

TCHAR *val[] = { TEXT("Ananth Chandrasekharan"), TEXT("9892980509"),TEXT("ananthchandrasekharan@gmail.com"),TEXT("Effortsys Technologies Pvt Ltd"),TEXT("WinRT 2016"),TEXT("Sir always gives new insights about any topic which generates interest in me to learn more.I am in current RTR batch.I want to relearn Win32 SDK,COM and WinRT from sir before proceeding to learn DirectX11 for Desktop and Mobile platform.I want to grasp any information sir gives about OpenGL in this Win32 SDK-COM-WinRT-.NET Framework Architecture 2017 batch.I am currently working in COM domain and i get to learn the pathway and frame of mind by which I should approach projects.I get to learn the internals of what i am doing.")};
TCHAR *headings[] = { TEXT("FullName          "),TEXT("ContactNumber          "),TEXT("EmailId           "),TEXT("CurrentCompany          "),TEXT("Duration Attended          "),TEXT(" WhyToAttend          ") };

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
		TEXT("Ganesha"),
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

UINT GetTextSize(TCHAR *str)
{
	for (UINT i=0;;i++)
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

	TCHAR show_at_bottom[] = TEXT("Press Spacebar to generate a text file");
	HDC hdc;
	SIZE sz;
	PAINTSTRUCT ps;
	int X=5, Y=5, i;

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
		GetTextExtentPoint32(hdc,headings[0],GetTextSize(headings[0]),&sz);
		X = Y= 50;
		for (i=0;i<=5;i++)
		{
			SetBkColor(hdc, RGB(128, 128, 128));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc,X,Y,headings[i], GetTextSize(headings[i]));
			Y = Y + (2*sz.cy);
		}

		Y = 50;
		for (i = 0; i <= 5; i++)
		{
			SetBkColor(hdc,RGB(128,128,128));
			SetTextColor(hdc,RGB(0,255,0));
			TextOut(hdc, 2*(GetTextSize(headings[0]) + GetTextSize(headings[1]) + GetTextSize(headings[2]) + GetTextSize(headings[3]) + GetTextSize(headings[4]) + GetTextSize(headings[5])), Y, val[i], GetTextSize(val[i]));
			Y = Y + (2 * sz.cy);
		}
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
