// MyClass.cpp: implementation of the MyClass class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "MyClass.h"

//
// Globals
//
WNDCLASS m_wc;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyClass::MyClass()
{

}

MyClass::~MyClass()
{

}


//
// Member functions
//
//
// Function to register the class
//
int MyClass::RegisterTheClass(HINSTANCE hInstance)
{
  // Register the class
  ZeroMemory(&m_wc, sizeof(m_wc));
  m_wc.style = CS_HREDRAW | CS_VREDRAW;
  m_wc.lpfnWndProc = (WNDPROC)WndProc;
  m_wc.cbClsExtra = 0;
  m_wc.cbWndExtra = 0;
  m_wc.hIcon = NULL;
  m_wc.hInstance = hInstance;
  m_wc.hCursor = NULL;
  m_wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  m_wc.lpszMenuName = NULL;
  m_wc.lpszClassName = L"MyClass";
  if(!RegisterClass(&m_wc))
  {
    return(0);
  }
  else
  {
    return(1);
  }
}


//
// The static callback message handler
//
LRESULT CALLBACK MyClass::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
   LRESULT lResult = TRUE;

   switch(msg)
   {
     case WM_DESTROY:
       PostQuitMessage(0);
       break;

     default:
       lResult = DefWindowProc(hwnd, msg, wp, lp);
       break;
   }

   return(lResult);
}


//
// The message pump
//
int MyClass::StartPumping()
{
  MSG msg;

  // Pump messages until a PostQuitMessage.
  while(GetMessage(&msg, NULL, 0, 0))
  {
      TranslateMessage (&msg);
      DispatchMessage(&msg);
  }
  return msg.wParam;
}
