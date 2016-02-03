#include "stdafx.h"
#include "MainWnd.h"
#include "resource.h"

#define	APP_NAME				_T("XPngTest")
#define APP_CLASS_NAME			_T("XPngTest")
#define APP_TITLE				_T("XPngTest")

// 경로 구하기..
CString  GetThisPath()
{
	static TCHAR szModuleName[MAX_PATH*4];
	static BOOL bIsFirst = TRUE;
	if(bIsFirst)
	{
		::GetModuleFileName(NULL,szModuleName,MAX_PATH*4);
		*(_tcsrchr( szModuleName, '\\' ) + 1) = NULL;
		bIsFirst = FALSE;
	}
	return CString(szModuleName);
}



CMainWnd::CMainWnd(void)
{
}


CMainWnd::~CMainWnd(void)
{
}


BOOL CMainWnd::Create(WCHAR* argv[], int argc)
{
	// atl 윈도우 생성
	CWndClassInfo &winInfo = GetWndClassInfo();
	winInfo.m_wc.lpszClassName = APP_CLASS_NAME;
	winInfo.m_wc.style = 0;
	winInfo.m_wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	__super::Create(NULL, CWindow::rcDefault,  APP_NAME, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	::DragAcceptFiles(m_hWnd, TRUE);

	if(argc>=2)
		m_bitmap.LoadPNG(argv[1]);

	// 보이기
	ShowWindow(SW_SHOW);

//	PostMessage(WM_COMMAND, ID_TEST_XPNGSPEEDTEST);

	return TRUE;
}


LRESULT CMainWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0);
	return 0;
}

BOOL CMainWnd::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
}

LRESULT CMainWnd::OnDropFiles(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	HDROP hDrop = (HDROP)wParam;
	TCHAR szPathFileName[MAX_PATH];
	DragQueryFile(hDrop, 0, szPathFileName, MAX_PATH);

	if(m_bitmap.LoadPNG(szPathFileName)==FALSE)
		::MessageBox(m_hWnd, L"Error occurred.", APP_NAME, MB_OK | MB_ICONSTOP);
	else
	{
		::InvalidateRect(m_hWnd, NULL, TRUE);
		m_bitmap.DrawTo(m_hWnd);
	}


	return 0;
}

LRESULT CMainWnd::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PAINTSTRUCT ps;
	::BeginPaint(m_hWnd, &ps);

	if(m_bitmap.GetBitmap())
		m_bitmap.DrawTo(ps.hdc);
	else
	{
		WCHAR* str = L"드래그&드롭으로 PNG 파일을 열 수 있습니다.";
		::TextOut(ps.hdc, 0, 0, str, wcslen(str));
	}

	::EndPaint(m_hWnd, &ps);

	return 0;
}

LRESULT CMainWnd::OnTestXpngspeedtest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString sampleFile = GetThisPath() + L"sample.png";
	DWORD tick = GetTickCount();

	for(int i=0;i<10; i++)
	{
		m_bitmap.LoadPNG(sampleFile);
		m_bitmap.DrawTo(m_hWnd);
	}

	CString result;
	result.Format(L"xpng speed test result: %dms", GetTickCount() - tick);
	MessageBox(result);

	return 0;
}



#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

LRESULT CMainWnd::OnTestGdiplusspeedtest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken,&gpsi,NULL) != Ok) {
		MessageBox(TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."));
		return 0;
	}

	{
		Graphics G(m_hWnd);

		{
			CString sampleFile = GetThisPath() + L"sample.png";
			DWORD tick = GetTickCount();
			Color	color;

			for(int i=0;i<10; i++)
			{
				Bitmap bitmap(sampleFile);
				bitmap.SetPixel(0, 0, color);	  // 이미지 로드를 위해서 강제로 조작을 한다.
			}

			CString result;
			result.Format(L"gdi+ speed test result: %dms", GetTickCount() - tick);

//			Image image(sampleFile);
//			G.DrawImage(&image, 0,0, image.GetWidth(), image.GetHeight());

			MessageBox(result);
		}
	}


	GdiplusShutdown(gpToken);


	return 0;
}

