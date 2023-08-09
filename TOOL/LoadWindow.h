#pragma once
#include <afxwin.h>
class MainWin;
class LoadWindow : public CDialog
{
	DECLARE_DYNAMIC(LoadWindow)
public:
	LoadWindow(MainWin* _main);
	virtual void OnOK(); // OnOK() �Լ��� �����մϴ�.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CEdit* m_pFilePath;
	MainWin* m_pMain;
	DECLARE_MESSAGE_MAP()
};

