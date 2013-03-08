// DialogEx.h: interface for the CDialogEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGEX_H__48C5BE17_71B0_4951_8CFD_682CD9AFF1D9__INCLUDED_)
#define AFX_DIALOGEX_H__48C5BE17_71B0_4951_8CFD_682CD9AFF1D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDialogEx  
{
public:
	void Hide();
	BOOL Exists;
	void SetText(LPCTSTR text);
	void Append(LPCTSTR text);
	void Destroy();
	void Show();
	CDialogEx(HINSTANCE hInstance, HWND hwndParent);
	virtual ~CDialogEx();

private:
	LOGFONT MakeLogfont();
  LPCTSTR CDialogEx::StringCat(LPCTSTR string1, LPCTSTR string2);
};

#endif // !defined(AFX_DIALOGEX_H__48C5BE17_71B0_4951_8CFD_682CD9AFF1D9__INCLUDED_)
