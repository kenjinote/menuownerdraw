#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>
#include"resource.h"

TCHAR szClassName[]=TEXT("Menu Bar");

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_EXIT:
			SendMessage(hWnd,WM_CLOSE,0,0);
			break;
		}
		break;
	case WM_MEASUREITEM:
		{
			HDC hdc=GetDC(hWnd);
			SIZE size;
			GetTextExtentPoint32(hdc,TEXT("終了(&X)"),lstrlen(TEXT("終了(&X)"))-1,&size);
			((LPMEASUREITEMSTRUCT)lParam)->itemWidth=size.cx;
			((LPMEASUREITEMSTRUCT)lParam)->itemHeight=size.cy;
			ReleaseDC(hWnd,hdc);
		}
		return TRUE;
	case WM_DRAWITEM:
		switch(((LPDRAWITEMSTRUCT)lParam)->itemID)
		{
		case IDM_EXIT:
			if(((LPDRAWITEMSTRUCT)lParam)->itemState&ODS_SELECTED)
			{
				FillRect(((LPDRAWITEMSTRUCT)lParam)->hDC,&((LPDRAWITEMSTRUCT)lParam)->rcItem,(HBRUSH)(COLOR_HIGHLIGHT+1));
				SetBkMode(((LPDRAWITEMSTRUCT)lParam)->hDC,TRANSPARENT);
				SetTextColor(((LPDRAWITEMSTRUCT)lParam)->hDC,RGB(255,255,255));
			}
			else
			{
				FillRect(((LPDRAWITEMSTRUCT)lParam)->hDC,&((LPDRAWITEMSTRUCT)lParam)->rcItem,(HBRUSH)(COLOR_MENU+1));
				SetBkMode(((LPDRAWITEMSTRUCT)lParam)->hDC,TRANSPARENT);
				SetTextColor(((LPDRAWITEMSTRUCT)lParam)->hDC,RGB(0,0,0));
			}
			DrawText(((LPDRAWITEMSTRUCT)lParam)->hDC,TEXT("終了(&X)"),-1,&((LPDRAWITEMSTRUCT)lParam)->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			return TRUE;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	HINSTANCE hInstance=GetModuleHandle(0);
	WNDCLASS wndclass={CS_HREDRAW|CS_VREDRAW,WndProc,0,0,hInstance,0,LoadCursor(0,IDC_ARROW),(HBRUSH)(COLOR_WINDOW+1),MAKEINTRESOURCE(IDR_MENU1),szClassName};
	RegisterClass(&wndclass);
	HWND hWnd=CreateWindow(szClassName,TEXT("Menu Bar"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,CW_USEDEFAULT,0,0,0,hInstance,0);
	HMENU hMenu=GetMenu(hWnd);
	ModifyMenu(hMenu,IDM_EXIT,MF_BYCOMMAND|MF_OWNERDRAW,IDM_EXIT,TEXT("終了(&X)"));
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(0);
}

#if _DEBUG
void main(){}
#endif