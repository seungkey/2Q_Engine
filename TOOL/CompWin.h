#pragma once
#include <vector>
class CompWin : public CDialog
{

    DECLARE_DYNAMIC(CompWin)

public:
    CompWin(CString _name);
    virtual ~CompWin();

    void SetName(CString _name);

    //BOOL PreTranslateMessage(MSG* _pMsg);
public:
    

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnAssign();

    std::string m_objTag;

private:
    void TransCtr();
    void RenderCtr();
    void CompCtr();

    LPWSTR CastDtoS(double _d);
    LPWSTR CastDtoS_DOWN(double _d); // ��������

    // Ʈ������ ����
    CStatic* m_pTextTransform;
    CEdit* m_pEditTransform;
    CButton* m_pAssignButton;

    // ���� ����
    CButton* m_pRadioButton;
    CStatic* m_pRadioText;
    CEdit* m_pEditTexKey;

    // �� �� ������Ʈ �߰�
    CButton* m_pCheckButton;
    CStatic* m_pCheckText;

    std::vector<LPCTSTR> m_compTags;
    std::vector<UINT> m_compIDs;

    DECLARE_MESSAGE_MAP()
};

