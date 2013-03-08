// MyClass.h: interface for the MyClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLASS_H__802257E7_52B9_4DE9_B4A5_30293AFC0AC0__INCLUDED_)
#define AFX_MYCLASS_H__802257E7_52B9_4DE9_B4A5_30293AFC0AC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyClass
{
public:
	int StartPumping();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
  int MyClass::RegisterTheClass(HINSTANCE hInstance);
	MyClass();
	virtual ~MyClass();

};

#endif // !defined(AFX_MYCLASS_H__802257E7_52B9_4DE9_B4A5_30293AFC0AC0__INCLUDED_)
