#include "pch.h"
#include "MyStatic.h"
#include "WatcherCheater.h"


IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
    //�Ƚ�ͼ��͹��ľ�����ؽ���
    m_hIcon1 = AfxGetApp()->LoadIcon(IDI_ICON1);
    m_hIcon2 = AfxGetApp()->LoadIcon(IDI_ICON2);
    m_hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);

    m_hWndPre = NULL;
    m_hParentWnd = NULL;
    m_bFlag = FALSE;
    m_ChosenWindow = NULL;
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyStatic ��Ϣ�������



//���ƴ���
HDC CMyStatic::DrawWndSPy(HWND hWnd)
{
    HWND v1; // ebx
    HDC result; // eax
    HDC v3; // edi
    HGDIOBJ v4; // eax
    int v5; // esi
    COLORREF v6; // eax
    HBRUSH v7; // esi
    HPEN ho; // [esp+Ch] [ebp-30h]
    HGDIOBJ v9; // [esp+10h] [ebp-2Ch]
    HGDIOBJ h; // [esp+14h] [ebp-28h]
    int v11; // [esp+18h] [ebp-24h]
    int v12; // [esp+18h] [ebp-24h]
    int w; // [esp+1Ch] [ebp-20h]
    int v14; // [esp+20h] [ebp-1Ch]
    int v15; // [esp+20h] [ebp-1Ch]
    HRGN hRgn; // [esp+24h] [ebp-18h]
    struct tagRECT Rect; // [esp+28h] [ebp-14h]

    v1 = hWnd;
    v14 = ::GetSystemMetrics(5);
    v11 = ::GetSystemMetrics(6);
    result = ::GetWindowDC(v1);
    v3 = result;
    if (result)
    {
        hRgn = ::CreateRectRgn(0, 0, 0, 0);
        ho = ::CreatePen(6, 3 * v14, 0);
        v9 = ::SelectObject(v3, ho);
        v4 = ::GetStockObject(5);
        h = ::SelectObject(v3, v4);
        ::SetROP2(v3, 6);
        if (::GetWindowRgn(v1, hRgn))
        {
            v6 = ::GetSysColor(6);
            v7 = ::CreateHatchBrush(5, v6);
            ::FrameRgn(v3, hRgn, v7, 3 * v14, 3 * v11);
            ::DeleteObject(v7);
        }
        else
        {
            w = ::GetSystemMetrics(32);
            v15 = ::GetSystemMetrics(33);
            v12 = ::GetSystemMetrics(0);
            v5 = ::GetSystemMetrics(1);
            ::GetWindowRect(v1, &Rect);
            if (::IsZoomed(v1))
                ::Rectangle(v3, w, v15, w + v12, v5 + v15);
            else
                ::Rectangle(v3, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top);
        }
        ::SelectObject(v3, h);
        ::SelectObject(v3, v9);
        ::DeleteObject(ho);
        ::DeleteObject(hRgn);
        result = (HDC)::ReleaseDC(v1, v3);
    }
    return result;
}


//��ȡ���ھ���󣬽������Ϣ��ʾ
void CMyStatic::GetWndInfo(HWND hWnd)
{
    //��ʽ�����

    char buffer[12] = { 0 };
    wsprintf(buffer, "%08X", hWnd);

    ::SetDlgItemText(m_hParentWnd, STC_WINDOWHANDLE, buffer);

    //��ȡ���ڱ�����ʾ
    CString strFmtText;
    ::GetWindowText(hWnd, strFmtText.GetBufferSetLength(MAXWORD), MAXWORD);
    strFmtText.ReleaseBuffer();
    ::SetDlgItemText(m_hParentWnd, STC_WNDTEXT, strFmtText);

    //��ȡ����������ʾ
    CString strFmtClassName;
    ::GetClassName(hWnd, strFmtClassName.GetBufferSetLength(MAXWORD), MAXWORD);
    strFmtClassName.ReleaseBuffer();
    ::SetDlgItemText(m_hParentWnd, STC_WNDCLASSNAME, strFmtClassName);

    //��ȡ������ʽ��ʾ
    CString strWndStyle;
    WINDOWINFO wi;
    wi.cbSize = sizeof(WINDOWINFO);
    ::GetWindowInfo(hWnd, &wi);
    strWndStyle.Format("%08X", wi.dwStyle);
    ::SetDlgItemText(m_hParentWnd, STC_STYLE, strWndStyle);

    //��ȡ���ھ�����ʾ
    CString strWndRect;
    CRect rc;
    ::GetWindowRect(hWnd, &rc);
    strWndRect.Format("%ld * %ld", rc.Width(), rc.Height());
    ::SetDlgItemText(m_hParentWnd, STC_RECT, strWndRect);
}


//��ȡ�����ھ��
void CMyStatic::SetParentHwnd(HWND hParentWnd)
{
    m_hParentWnd = hParentWnd;
    SetWindowDisplayAffinity(hParentWnd, WDA_EXCLUDEFROMCAPTURE);
}


//����������
void CMyStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_bFlag = TRUE;
    //�����������£�������ͼ���Լ����
    SetIcon(m_hIcon1);
    //�����ϵĹ��
    m_hOldCursor = ::SetCursor(m_hCursor);
    if (m_hWndPre) DrawWndSPy(m_hWndPre);

    //���մ�������Ϣ
    SetCapture();

    CStatic::OnLButtonDown(nFlags, point);
}


//����������
void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_bFlag = FALSE;
    //�����������𣬽�ͼ����ָ�
    SetIcon(m_hIcon2);
    ::SetCursor(m_hOldCursor);
    DrawWndSPy(m_hWndPre);

    //�����մ�������Ϣ
    ReleaseCapture();

    CStatic::OnLButtonUp(nFlags, point);
}


//����ƶ�
void CMyStatic::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bFlag)
    {
        //���ͻ�������ת��Ϊ��Ļ����
        ClientToScreen(&point);

        //ͨ���������������������ڵĴ��ڣ������䴰�ھ��
        HWND hWnd = ::WindowFromPoint(point);

        //��ʽ�����
        char buffer[12] = { 0 };
        wsprintf(buffer, "%08X", hWnd);

        //����ǵ�һ�λ�
        if (m_hWndPre == NULL)
        {
            //���ƴ���
            DrawWndSPy(hWnd);

            //�����������Ϣ��ʾ
            GetWndInfo(hWnd);
            m_hWndPre = hWnd;
            m_ChosenWindow = hWnd;
            return;
        }

        //��ͬ,˵���������ͬ�������ƶ�
        if (m_hWndPre == hWnd)
        {
            return;
        }
        else
        {
            //��ԭԭ���Ĵ���
            DrawWndSPy(m_hWndPre);
            GetWndInfo(hWnd);
            //���´���
            DrawWndSPy(hWnd);
            m_hWndPre = hWnd;
            m_ChosenWindow = hWnd;
        }
    }


    CStatic::OnMouseMove(nFlags, point);
}