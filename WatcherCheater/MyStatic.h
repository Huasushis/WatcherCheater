#pragma once
#include <afxwin.h>
class CMyStatic : public CStatic
{
    DECLARE_DYNAMIC(CMyStatic)

public:
    CMyStatic();
    virtual ~CMyStatic();

protected:
    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon1;
    HICON m_hIcon2;
    HCURSOR m_hCursor;
    HCURSOR m_hOldCursor;

    HWND m_hWndPre;
    HWND m_hParentWnd;

    //���ñ�ǣ�������״̬
    BOOL m_bFlag;
protected:
    //���ƴ���
    HDC DrawWndSPy(HWND hWnd);

    //��ȡ���ھ���󣬽������Ϣ��ʾ
    void GetWndInfo(HWND hWnd);

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    //��ȡ�����ھ��
    void SetParentHwnd(HWND hParentWnd);
    HWND m_ChosenWindow;
};

