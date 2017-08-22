#include<windows.h>
#include<stdio.h>

#define LINES 50

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
UINT GetTextSize(TCHAR*);

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
	for (UINT i = 0;; i++)
	{
		if (str[i] == '\0')
		{
			return i;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR show_at_bottom[] = TEXT("Press Spacebar to generate a text file");

	TCHAR *val[] = { TEXT("  Ananth Chandrasekharan\r\n"), TEXT("  9892980509\r\n"),TEXT("  ananthchandrasekharan@gmail.com\r\n"),TEXT("  Effortsys Technologies Pvt Ltd\r\n"),TEXT("  WinRT 2016\r\n"),TEXT("  Sir always gives new insights about any topic which generates interest in me to learn more.I am in current RTR batch.I want to relearn Win32 SDK,COM and WinRT from sir before proceeding to learn DirectX11 for Desktop and Mobile platform.I want to grasp any information sir gives about OpenGL in this Win32 SDK-COM-WinRT-.NET Framework Architecture 2017 batch.I am currently working in COM domain and i get to learn the pathway and frame of mind by which I should approach projects.I get to learn the internals of what i am doing.\r\n"),NULL };
	TCHAR *headings[] = { TEXT("FullName   "),TEXT("ContactNumber   "),TEXT("EmailId   "),TEXT("CurrentCompany   "),TEXT("Duration Attended   "),TEXT(" WhyToAttend   "),NULL };

	HDC hdc;
	SIZE sz;
	PAINTSTRUCT ps;
	int X = 5, Y = 5, i;
	int p;

	TEXTMETRIC tm;
	static int cxChar, cyChar, cxCaps, iMaxWidth, nVertPos, nHorzPos;
	static int iPaintBeg, iPaintEnd, cxClient, cyClient;
	SCROLLINFO si;

	static HMODULE hLib = NULL;
	typedef int(*pFunctionPointer)(TCHAR**,TCHAR**);
	pFunctionPointer pfn = NULL;
	int ret;
	RECT rc;

	static int button_press = 0;
	static BOOL PressedSpaceBarTwice = FALSE;
	static BOOL PressedSpaceBarOnce = FALSE;
	HBRUSH hBrush;

	switch (iMsg)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		iMaxWidth = 52;
		if ((tm.tmPitchAndFamily & 1) != 0)
		{
			cxCaps = 3 * cxChar / 2;
		}
		else
		{
			cxCaps = cxChar;
		}
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		//Vertical scroll settings are done below
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = LINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		//Horizontal Scrolling settings done here
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = iMaxWidth - 1;
		si.nPage = iMaxWidth / cxChar + 2;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		break;

	case WM_VSCROLL:
		//Get Current Scrolling information
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL; //Given to get Scroll info of SIF_RANGE,SIF_POS,SIF_PAGE,SIF_TRACKPOS
		GetScrollInfo(hwnd, SB_VERT, &si);
		nVertPos = si.nPos; //Declare nVertPos variable before getting current position of thumb.

		switch (LOWORD(wParam))
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEUP:
			si.nPos = si.nPos - 1;
			break;

		case SB_LINEDOWN:
			si.nPos = si.nPos + 1;
			break;

		case SB_PAGEUP:
			si.nPos = si.nPos - si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos = si.nPos + si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		//According to value of si.nPos in each case...break,we have to set the thumb
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		/*Windows OS sets the positionof the thumb, according to above call,
		but it sets the value according to current size of window.
		Hence retreive the Window's adjusted thumb position again
		*/

		GetScrollInfo(hwnd, SB_VERT, &si);

		/*
		Now compare saved variables value nVertPos with reteived nPos
		and do painting only if these valus are different
		*/
		if (nVertPos != si.nPos)
		{
			ScrollWindow(hwnd, 0, cyChar*(nVertPos - si.nPos), NULL, NULL);
			UpdateWindow(hwnd);
		}
		break;

	case WM_HSCROLL:
		//Get current scrolling information
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL; // to get scroll info of SIF_RANGE,SIF_POS,SIF_PAGE,SIF_TRACKPOS
		GetScrollInfo(hwnd, SB_HORZ, &si);
		nHorzPos = si.nPos; //Declare nHorzPos variable before getting current position of thumb

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			si.nPos = si.nPos - 1;
			break;

		case SB_LINERIGHT:
			si.nPos = si.nPos + 1;
			break;

		case SB_PAGERIGHT:
			si.nPos = si.nPos + si.nPage;
			break;

		case SB_PAGELEFT:
			si.nPos = si.nPos - si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_HOME:
			SendMessage(hwnd, WM_VSCROLL, SB_TOP, 0);
			break;

		case VK_END:
			SendMessage(hwnd, WM_VSCROLL, SB_BOTTOM, 0);
			break;

		case VK_UP:
			SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
			break;

		case VK_DOWN:
			SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
			break;

		case VK_LEFT:
			SendMessage(hwnd, WM_HSCROLL, SB_LINELEFT, 0);
			break;

		case VK_RIGHT:
			SendMessage(hwnd, WM_HSCROLL, SB_LINERIGHT, 0);
			break;

		case VK_PRIOR:
			SendMessage(hwnd, WM_VSCROLL, SB_PAGEUP, 0);
			break;

		case VK_NEXT:
			SendMessage(hwnd, WM_VSCROLL, SB_PAGEDOWN, 0);
			break;

		case VK_SPACE:
			MessageBox(hwnd, TEXT("Spacebar key is pressed"), TEXT("Message"), MB_OK);

			button_press++;
			if (button_press>1)
			{
				PressedSpaceBarTwice = TRUE;
				MessageBox(hwnd, TEXT("File Is already created with data"), TEXT("Message"), MB_OK);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else 
			{
				PressedSpaceBarOnce = TRUE;

				hLib = LoadLibrary(TEXT("Server.dll"));
				if (hLib == NULL)
				{
					MessageBox(hwnd, TEXT("Can Not Load Dll.\nExitting."), TEXT("Error"), MB_OK);
					PostQuitMessage(0);
					return -1;
				}
				else
				{
					MessageBox(hwnd, TEXT("Dll Loaded"), TEXT("Message"), MB_OK);
				}

				pfn = (pFunctionPointer)GetProcAddress(hLib, "GetStringsFromClient");
				if (pfn == NULL)
				{
					MessageBox(hwnd, TEXT("Can Not Get Address Of GetStringsFromClient().\nExitting."), TEXT("Error"), MB_OK);
					PostQuitMessage(0);
					return -1;
				}
				else
				{
					MessageBox(hwnd, TEXT("Got Address of GetStringsFromClient()"), TEXT("Message"), MB_OK);
				}

				ret = pfn(val, headings);
				if (ret < 0)
				{
					MessageBox(hwnd, TEXT("GetStringsFromClient() failed"), TEXT("Error"), MB_OK);
				}
				else
				{
					MessageBox(hwnd, TEXT("GetStringsFromClient() successful"), TEXT("Message"), MB_OK);
				}
				InvalidateRect(hwnd, NULL, TRUE);
			}
			break;

		default:
			break;
		}
		//According to the value of si.nPos in case...break we have to sert the thumb
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

		GetScrollInfo(hwnd, SB_HORZ, &si);

		if (nHorzPos != si.nPos)
		{
			ScrollWindow(hwnd, cxChar*(nHorzPos - si.nPos), 0, NULL, NULL);
			UpdateWindow(hwnd);
		}
		break;

	case WM_PAINT:
		if (PressedSpaceBarTwice !=TRUE && PressedSpaceBarOnce!=TRUE)
		{
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rc);

			//Getting vertical scroll thum position
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			GetScrollInfo(hwnd, SB_VERT, &si);
			nVertPos = si.nPos;

			//Getting horizontal thumb position
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			GetScrollInfo(hwnd, SB_HORZ, &si);
			nHorzPos = si.nPos;

			//Setting painting limits
			iPaintBeg = max(0, nVertPos + ps.rcPaint.top / cyChar);
			iPaintEnd = min(LINES - 1, nVertPos + ps.rcPaint.bottom / cyChar);

			for (p = iPaintBeg; p <= iPaintEnd; p++)
			{
				X = cxChar*(1 - nHorzPos);
				Y = cyChar*(1 - nVertPos);

				GetTextExtentPoint32(hdc, headings[0], GetTextSize(headings[0]), &sz);
				for (i = 0; i <= 5; i++)
				{
					SetBkColor(hdc, RGB(128, 128, 128));
					SetTextColor(hdc, RGB(255, 255, 255));
					TextOut(hdc, X, Y, headings[i], GetTextSize(headings[i]));
					Y = Y + (2 * sz.cy);
				}

				Y = cyChar*(1 - nVertPos);
				for (i = 0; i <= 5; i++)
				{
					SetBkColor(hdc, RGB(128, 128, 128));
					SetTextColor(hdc, RGB(0, 255, 0));
					TextOut(hdc, 2 * (GetTextSize(headings[0]) + GetTextSize(headings[1]) + GetTextSize(headings[2]) + GetTextSize(headings[3]) + GetTextSize(headings[4]) + GetTextSize(headings[5])), Y, val[i], GetTextSize(val[i]));
					Y = Y + (2 * sz.cy);
				}
			}
		}
		else 
		{
				hdc = BeginPaint(hwnd, &ps);
				GetClientRect(hwnd, &rc);

				hBrush = CreateSolidBrush(RGB(128, 128, 128));
				FillRect(hdc, &rc, hBrush);

				if (PressedSpaceBarOnce == TRUE)
				{
					SetBkColor(hdc, RGB(128, 128, 128));
					SetTextColor(hdc, RGB(139, 0, 139));
					DrawText(hdc, TEXT("File Creation is successfully Completed"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					DeleteObject(hBrush);
				}

				if (PressedSpaceBarTwice == TRUE)
				{
					hBrush = CreateSolidBrush(RGB(128, 128, 128));
					FillRect(hdc, &rc, hBrush);
					SetBkColor(hdc, RGB(128, 128, 128));
					SetTextColor(hdc, RGB(255, 0, 0));
					DrawText(hdc, TEXT("You have pressed space bar twice!!!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					DeleteObject(hBrush);
				}
				EndPaint(hwnd, &ps);
			}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
