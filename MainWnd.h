////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// 메인 윈도우
/// 
/// @author   parkkh
/// @date     Friday, November 19, 2010  4:15:21 PM
/// 
/// Copyright(C) 2010 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"
#include "xpng/XBitmap.h"

class CMainWnd  : public CWindowImpl<CMainWnd, CWindow>
{
public:
	CMainWnd();
	virtual ~CMainWnd();

	BOOL			Create(WCHAR* argv[], int argc);
	BOOL			PreTranslateMessage(MSG* pMsg);

private :
	XBitmap			m_bitmap;



public :
	BEGIN_MSG_MAP(CMainWnd)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		COMMAND_ID_HANDLER(ID_TEST_GDIPLUSSPEEDTEST, OnTestGdiplusspeedtest)
		COMMAND_ID_HANDLER(ID_TEST_XPNGSPEEDTEST, OnTestXpngspeedtest)
	END_MSG_MAP()

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDropFiles(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTestGdiplusspeedtest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTestXpngspeedtest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


