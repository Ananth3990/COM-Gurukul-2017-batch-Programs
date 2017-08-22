#include<Windows.h>
#include<stdio.h>
#define LINES 26

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Windows");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		AppName,
		TEXT("Ananths Scrolling Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
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
	UINT GetTextSize(TCHAR *str);

	HDC hdc;
	TEXTMETRIC tm;
	static int cxChar, cyChar,iMaxWidth,nVertPos,nHorzPos,cxCaps;
	static int iPaintBeg, iPaintEnd, cxClient, cyClient;
	int i, X, Y;
	PAINTSTRUCT ps;
	SCROLLINFO si;

	TCHAR *str[] = { TEXT("Ananth Chandrasekharan") };

	switch (iMsg)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		iMaxWidth = 52;
		if ((tm.tmPitchAndFamily&1)!=0)
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

		//Vertical Scroll Settings
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nMin = 0;
		si.nMax = LINES - 1;
		si.nPage = cyClient / cxClient;
		SetScrollInfo(hwnd,SB_VERT,&si,TRUE);

		//Horizontal Scroll Settings
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nMin = iMaxWidth - 1;
		si.nMax = iMaxWidth / cxChar + 2;
		SetScrollInfo(hwnd,SB_HORZ,&si,TRUE);
		break;

	case WM_VSCROLL:
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd,SB_VERT,&si);
		nVertPos = si.nPos;

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
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
		GetScrollInfo(hwnd,SB_VERT,&si);

		if (nVertPos!=si.nPos)
		{
			ScrollWindow(hwnd,0,cyChar*(nVertPos-si.nPos),NULL,NULL);
			UpdateWindow(hwnd);
		}
		break;

	case WM_HSCROLL:
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd,SB_HORZ,&si);
		nHorzPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			si.nPos = si.nPos - 1;
			break;

		case SB_LINERIGHT:
			si.nPos = si.nPos + 1;
			break;

		case SB_PAGELEFT:
			si.nPos = si.nPos - si.nPage;
			break;

		case SB_PAGERIGHT:
			si.nPos = si.nPos + si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_HOME:
				SendMessage(hwnd,WM_VSCROLL,SB_TOP,0);
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
				SendMessage(hwnd,WM_VSCROLL,SB_PAGEUP,0);
				break;

			case VK_NEXT:
				SendMessage(hwnd,WM_VSCROLL,SB_PAGEDOWN,0);
				break;

			default:
				break;
		}
		si.nPos = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		SetScrollInfo(hwnd,SB_HORZ,&si,TRUE);
		GetScrollInfo(hwnd,SB_HORZ,&si);
		if (nHorzPos!=si.nPos)
		{
			ScrollWindow(hwnd,cxChar*(nHorzPos-si.nPos),0,NULL,NULL);
			UpdateWindow(hwnd);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd,SB_VERT,&si);
		nVertPos = si.nPos;

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd,SB_HORZ,&si);
		nHorzPos = si.nPos;

		iPaintBeg = max(0,nVertPos+ps.rcPaint.top/cyChar);
		iPaintEnd = min(LINES-1,nVertPos+ps.rcPaint.bottom/cyChar);

		for (i=iPaintBeg;i<=iPaintEnd;i++)
		{
			X = cxChar*(1-nHorzPos);
			Y = cyChar*(1-nVertPos);
			TextOut(hdc,X,Y,str[i], GetTextSize(str[i]));
		}
		EndPaint(hwnd,&ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}