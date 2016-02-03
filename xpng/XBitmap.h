////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// simple bitmap wrapper
///
/// - 라이선스 : zlib license (http://www.kippler.com/etc/zlib_license/ 참고)
/// 
/// @author   parkkh
/// @date     Thursday, November 11, 2010  10:01:03 AM
/// 
/// Copyright(C) 2010 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
                 -= History =-

* 2010/11/11 - 작업 시작
* 2011/01/03 - PNG 로드 기능 추가

*/


#pragma once

enum PIXELFORMAT
{
	PIXELFORMAT_24 = 24,
	PIXELFORMAT_32 = 32,
};

interface XBitmapStream;
class XBitmap
{
public :
	XBitmap();
	~XBitmap();

	BOOL		CreateDib(int width, int height, PIXELFORMAT pixelFormat, BOOL bBottomUpDib=TRUE);
	void		Delete();
	BOOL		LoadPNG(LPCTSTR szFilePathName);
	BOOL		LoadPNG(HANDLE hFile);
	BOOL		LoadPNG(LPBYTE data, int length);
	BOOL		LoadPNG(XBitmapStream* pInput);

	HDC			GetDC();
	void		ReleaseDC();
	HBITMAP		GetBitmap() { return m_hBitmap; }
	
	int			Width() { return m_width; }
	int			Height() { return m_height; }

	BOOL		DrawTo(HWND hWnd, int dx = 0, int dy = 0, int sx = 0, int sy = 0, int sw = -1, int sh = -1, DWORD rop = SRCCOPY);
	BOOL		DrawTo(HDC hdc, int dx = 0, int dy = 0, int sx = 0, int sy = 0, int sw = -1, int sh = -1, DWORD rop = SRCCOPY);

private :
	void		Init();
	void		DeleteDC();

private :
	HBITMAP		m_hBitmap;					// bitmap 핸들
	int			m_stride;					// 한줄당 바이트수
	int			m_paddingByte;				// 한줄당 padding 바이트 수
	int			m_width;					// 폭 pixel
	int			m_height;					// 높이 pixel
	PIXELFORMAT	m_pixelFormat;				// 픽셀당 비트 수
	LPBYTE		m_pixel;					// 픽셀 메모리 시작 값

private :
	HDC			m_hDC;
	HBITMAP		m_hOldBitmap;
	int			m_dcLockCount;				// GetDC() 호출 카운트
};

