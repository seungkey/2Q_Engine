#pragma once
#include <afxwin.h>
class MainWin;
class SaveWindow : public CDialog
{
	DECLARE_DYNAMIC(SaveWindow)
public:
	SaveWindow(MainWin* _main);
	virtual void OnOK(); // OnOK() �Լ��� �����մϴ�.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CEdit* m_pFilePath;
	MainWin* m_pMain;
	DECLARE_MESSAGE_MAP()

};

