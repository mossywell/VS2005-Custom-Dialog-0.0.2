// DialogEx.cpp: implementation of the CDialogEx class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "DialogEx.h"

//
// Globals
//
const INT g_EditControlLength = 0xFFFF;
HWND  m_hWnd;
HFONT m_hFont;


//
// Construction/Destruction
//
CDialogEx::CDialogEx(HINSTANCE hInstance, HWND hwndParent)
{
  // Get the client dimensions
  RECT rectDesk;
  GetClientRect(GetDesktopWindow(), &rectDesk);

  // Create the edit control as a window
  m_hWnd = CreateWindow(
    TEXT("EDIT"),
    TEXT(""),
    ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_BORDER,
    rectDesk.left + 10,
    rectDesk.top + 10,
    rectDesk.right - 20,
    rectDesk.bottom - 46,
    hwndParent,
    NULL,
    hInstance,
    NULL);

  // Check it worked and set the Exists flag appropriately
  if(m_hWnd)
  {
    Exists = TRUE;
    
    // Set the max characters to the default (0xFFFF)
    SendMessage(m_hWnd, EM_SETLIMITTEXT, (WPARAM)g_EditControlLength, 0);
  
    // Create a font and send it to the window
    LOGFONT logFont = this->MakeLogfont();
    m_hFont = CreateFontIndirect(&logFont);
    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)m_hFont, (LPARAM)TRUE);
  }
  else
  {
    Exists = FALSE;
  }
}


CDialogEx::~CDialogEx()
{

}


//
// Private member functions
//
LOGFONT CDialogEx::MakeLogfont()
{
  LOGFONT logFont;
	logFont.lfHeight = -11;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = 400;
	logFont.lfItalic = (DWORD)0;
	logFont.lfUnderline = (DWORD)0;
	logFont.lfStrikeOut = (DWORD)0;
	logFont.lfCharSet = (DWORD)0;
	logFont.lfOutPrecision = (DWORD)3;
	logFont.lfClipPrecision = (DWORD)2;
	logFont.lfQuality = (DWORD)1;
	logFont.lfPitchAndFamily = (DWORD)34;
  StringCchCopy(logFont.lfFaceName, LF_FACESIZE, TEXT("Nina")); 
  logFont.lfFaceName[LF_FACESIZE - 1] = TEXT('\0');

  return logFont;
}


LPCTSTR CDialogEx::StringCat(LPCTSTR string1, LPCTSTR string2)
{
  // Get the size IN CHARACTERS of string1 and string2 excluding the nul
  size_t sizeString1;
  StringCchLength(string1, STRSAFE_MAX_CCH, &sizeString1);
  size_t sizeString2;
  StringCchLength(string2, STRSAFE_MAX_CCH, &sizeString2);

  // Create a new string = bytes * number of bytes per character
  TCHAR* newString;
  newString = (TCHAR*)malloc((sizeString1 + sizeString2 + 1) * sizeof(TCHAR));

  // Copy string1 to the new string
  StringCchCopy(newString, sizeString1 + 1, string1);

  // Append string2 (already nul terminated)
  StringCchCat(newString, sizeString1 + sizeString2 + 1, string2);

  return newString;
}


//
// Public member functions
//
void CDialogEx::Show()
{
  // Show, update and set the focus
  if(Exists)
  {
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    SetFocus(m_hWnd);
  }
}


void CDialogEx::Destroy()
{
  DestroyWindow(m_hWnd);
  Exists = FALSE;
}


void CDialogEx::Append(LPCTSTR text)
{
  if(Exists)
  {
    // Some variables
    LPCTSTR cr = TEXT("\r\n");

    // Move the caret to the end
    SendMessage(m_hWnd, EM_SETSEL, (WPARAM)g_EditControlLength, (LPARAM)-1);

    // Pop a CR on the end
    LPCTSTR newString = StringCat(text, cr);

    // Send the message
    SendMessage(m_hWnd, EM_REPLACESEL, FALSE, (LPARAM)newString);
  }
}


void CDialogEx::SetText(LPCTSTR text)
{
  if(Exists)
  {
    SetWindowText(m_hWnd, text);
  }
}

void CDialogEx::Hide()
{
  if(Exists)
  {
    ShowWindow(m_hWnd, SW_HIDE);
  }
}
