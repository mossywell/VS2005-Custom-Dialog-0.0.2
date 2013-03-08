// Test1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <windowsx.h>
#include <aygshell.h>
#include "resource.h"
#include <strsafe.h>
#include "DialogEx.h"
#include <pm.h>

#define ARRAYSIZE(a)   (sizeof(a)/sizeof(*a))

//
// Globals
//
const TCHAR* g_szAppWndClass = TEXT("Test Dialog App");
const INT g_EditControlLength = 0xFFFF;
HINSTANCE g_hInst = NULL;  // Local copy of hInstance
TCHAR g_szMessage[30];
HWND g_hChild;
HFONT g_hFont;
CDialogEx* g_dlg;
void CreateMyWindow(HWND hwnd);
void DestroyMyWindow();
void SetDialogText(LPTSTR text);
void StartCounter();
void DoFileStuff(HWND hwnd);
void MakeTheBeep();
void DoLight();
LOGFONT MakeLogfont();



LRESULT OnCreate(HWND hwnd, CREATESTRUCT* lParam)
{
  // create the menu bar
  SHMENUBARINFO mbi;
  ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
  mbi.cbSize = sizeof(SHMENUBARINFO);
  mbi.hwndParent = hwnd;
  mbi.nToolBarId = IDR_HELLO_MENUBAR;
  mbi.hInstRes = g_hInst;
  if(!SHCreateMenuBar(&mbi))
  {
    // Couldn't create the menu bar.  Fail creation of the window.
    return(-1);
  }

  // Get our message text.
  if(0 == LoadString(g_hInst, IDS_HELLO_MESSAGE, g_szMessage, ARRAYSIZE(g_szMessage)))
  {
    // Couldn't load the string.  Fail creation of the window.
    return(-1);
  }

  // Do other window creation related things here.
  return(0); // continue creation of the window
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
  LRESULT lResult = TRUE;

  switch(msg)
  {
    case WM_CREATE:
      lResult = OnCreate(hwnd, (CREATESTRUCT*)lp);
      break;

    case WM_COMMAND:
      switch (wp)
      {
        case IDOK:
          DestroyWindow(hwnd);
          break;
        case ID_NEWWINDOW:
          CreateMyWindow(hwnd);
          break;
        case ID_SETTEXT:
          SetDialogText(TEXT("AaBbYyZz"));
          break;
        case ID_GO:
          StartCounter();
          break;
        case ID_CLOSEWINDOW:
          DestroyMyWindow();
          break;
        case ID_BEEP:
          MakeTheBeep();
          break;
        case ID_HIDE:
          g_dlg->Hide();
          break;
        case ID_SHOW:
          g_dlg->Show();
          break;
        case ID_DOFILESTUFF:
          DoFileStuff(hwnd);
          break;
        case ID_LIGHT:
          DoLight();
          break;
        default:
          goto DoDefault;
      }
      break;

    case WM_PAINT:
    {
      HDC hdc;
      PAINTSTRUCT ps;
      RECT rect;
      hdc = BeginPaint(hwnd, &ps);
      GetClientRect(hwnd, &rect);

      DrawText(hdc, g_szMessage, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      EndPaint (hwnd, &ps);
    }
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    DoDefault:
    default:
      lResult = DefWindowProc(hwnd, msg, wp, lp);
      break;
  }
  return(lResult);
}



HRESULT ActivatePreviousInstance(const TCHAR* pszClass, const TCHAR* pszTitle, BOOL* pfActivated)
{
    HRESULT hr = S_OK;
    int cTries;
    HANDLE hMutex = NULL;

    *pfActivated = FALSE;
    cTries = 5;
    while(cTries > 0)
    {
        hMutex = CreateMutex(NULL, FALSE, pszClass); // NOTE: We don't want to own the object.
        if(NULL == hMutex)
        {
            // Something bad happened, fail.
            hr = E_FAIL;
            goto Exit;
        }

        if(GetLastError() == ERROR_ALREADY_EXISTS)
        {
            HWND hwnd;

            CloseHandle(hMutex);
            hMutex = NULL;

            // There is already an instance of this app
            // running.  Try to bring it to the foreground.

            hwnd = FindWindow(pszClass, pszTitle);
            if(NULL == hwnd)
            {
                // It's possible that the other window is in the process of being created...
                Sleep(500);
                hwnd = FindWindow(pszClass, pszTitle);
            }

            if(NULL != hwnd) 
            {
                // Set the previous instance as the foreground window

                // The "| 0x01" in the code below activates
                // the correct owned window of the
                // previous instance's main window.
                SetForegroundWindow((HWND) (((ULONG) hwnd) | 0x01));

                // We are done.
                *pfActivated = TRUE;
                break;
            }

            // It's possible that the instance we found isn't coming up,
            // but rather is going down.  Try again.
            cTries--;
        }
        else
        {
            // We were the first one to create the mutex
            // so that makes us the main instance.  'leak'
            // the mutex in this function so it gets cleaned
            // up by the OS when this instance exits.
            break;
        }
    }

    if(cTries <= 0)
    {
        // Someone else owns the mutex but we cannot find
        // their main window to activate.
        hr = E_FAIL;
        goto Exit;
    }

Exit:
    return(hr);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HWND hwnd = NULL;
    BOOL fActivated;
    WNDCLASS wc;
    HWND hwndMain;
    TCHAR szAppTitle[20];

    g_hInst = hInstance;

    if(0 == LoadString(g_hInst, IDS_HELLO_TITLE, szAppTitle, ARRAYSIZE(szAppTitle)))
    {
      return(0);
    }

    if(FAILED(ActivatePreviousInstance(g_szAppWndClass, szAppTitle, &fActivated)) ||
            fActivated)
    {
      return(0);
    }

    // Register our main window's class.
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;
    wc.hInstance = g_hInst;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szAppWndClass;
    if(!RegisterClass(&wc))
    {
        return(0);
    }

    // Create the main window.    
    hwndMain = CreateWindow(g_szAppWndClass, szAppTitle,
            WS_CLIPCHILDREN, // Setting this to 0 gives a default style we don't want.  Use a benign style bit instead.
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, g_hInst, NULL );
    if(!hwndMain)
    {
        return(0);
    }

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    // Pump messages until a PostQuitMessage.
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}



void CreateMyWindow(HWND hwnd)
{
  if(!g_dlg)
  {
    g_dlg = new CDialogEx(g_hInst, hwnd);
  }
  if(g_dlg->Exists)
  {
    g_dlg->Show();
  }
}



void DestroyMyWindow()
{
  if(g_dlg)
  {
    g_dlg->Destroy();
  }
}


void SetDialogText(LPTSTR text)
{
  if(g_dlg)
  {
    g_dlg->SetText(text);
  }
}



void StartCounter()
{
  int i;
  TCHAR buffer[255];

  for(i = 0; i < 100; i++)
  {
    StringCbPrintf(buffer, sizeof(buffer), TEXT("%d"), i);
    if(g_dlg)
    {
      g_dlg->Append(buffer);
    }
  }
}


void DoFileStuff(HWND hwnd)
{
  HANDLE hFile = CreateFile(
    TEXT("\\Windows\\tmail.exe"),
    GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL);
  DWORD dw1 = GetLastError();
  DWORD atts = GetFileAttributes(TEXT("\\Windows\\tmail.exe"));
  DWORD dw2 = GetLastError();
  CreateMyWindow(hwnd);
  TCHAR buffer[255];
  StringCbPrintf(buffer, sizeof(buffer), TEXT("Open File Error: %d\r\nAttributes: %d\r\nAttributes Error: %d"), dw1, atts, dw2);
  if(g_dlg)
  {
    g_dlg->Append(buffer);
  }
  CloseHandle(hFile);
}


void MakeTheBeep()
{
  MessageBeep(-1);
  Sleep(500);
  MessageBeep(MB_ICONASTERISK);
  Sleep(500);
  MessageBeep(MB_ICONEXCLAMATION);
  Sleep(500);
  MessageBeep(MB_ICONHAND);
  Sleep(500);
  MessageBeep(MB_ICONQUESTION);
  Sleep(500);
  MessageBeep(MB_OK);
}

void DoLight()
{
  HANDLE hPower = SetPowerRequirement(TEXT("BKL1:"), D0, POWER_NAME, NULL, 0); 
}
// end Test1.cpp
