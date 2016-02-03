////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// simple bitmap wrapper
///
/// - ���̼��� : zlib license (http://www.kippler.com/etc/zlib_license/ ����)
/// 
/// @author   parkkh
/// @date     Thursday, November 11, 2010  10:01:03 AM
/// 
/// Copyright(C) 2010 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
                 -= History =-

* 2010/11/11 - �۾� ����
* 2011/01/03 - PNG �ε� ��� �߰�

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
	HBITMAP		m_hBitmap;					// bitmap �ڵ�
	int			m_stride;					// ���ٴ� ����Ʈ��
	int			m_paddingByte;				// ���ٴ� padding ����Ʈ ��
	int			m_width;					// �� pixel
	int			m_height;					// ���� pixel
	PIXELFORMAT	m_pixelFormat;				// �ȼ��� ��Ʈ ��
	LPBYTE		m_pixel;					// �ȼ� �޸� ���� ��

private :
	HDC			m_hDC;
	HBITMAP		m_hOldBitmap;
	int			m_dcLockCount;				// GetDC() ȣ�� ī��Ʈ
};

