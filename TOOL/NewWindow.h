#pragma once
#include <afxwin.h>
class MainWin;
class NewWindow :
    public CDialog
{
	DECLARE_DYNAMIC(NewWindow)
public:
	NewWindow(MainWin* _main);
	virtual void OnOK(); // OnOK() �Լ��� �����մϴ�.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CEdit* m_pTileWidth;
	CEdit* m_pTileHeight;
	MainWin* m_pMain;
	DECLARE_MESSAGE_MAP()
};

