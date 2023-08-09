#include "pch.h"
#include "ObjWin.h"

#include "pch.h"
#include "TOOL.h"
#include "MainWin.h"
#include "TempProcess.h"
#include "CompWin.h"


IMPLEMENT_DYNAMIC(ObjWin, CDialog)

BEGIN_MESSAGE_MAP(ObjWin, CDialog)
    ON_WM_CREATE()
    ON_CONTROL(BN_CLICKED, ID_CREATE_GAMEOBJECT_BUTTON, ObjWin::OnCreateGameObject)
    ON_NOTIFY(NM_CLICK, IDC_OBJECT_LIST, ObjWin::OnSelectObject)
    ON_NOTIFY(NM_RCLICK, IDC_OBJECT_LIST, ObjWin::OnRenameObject)
END_MESSAGE_MAP()

ObjWin::ObjWin(CWnd* pParent)
    :CDialog(IDD_ABOUTBOX, pParent)
{
}

ObjWin::~ObjWin()
{
}

int ObjWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    // ��ư ����
    CRect buttonRect(10, 10, 120, 40);
    CButton* pCreateButton = new CButton;
    pCreateButton->Create(_T("Create"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, ID_CREATE_GAMEOBJECT_BUTTON);

    // ����Ʈ ��Ʈ�� ����
    CRect listRect(10, 50, 200, 250);
    m_ObjectList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL, listRect, this, IDC_OBJECT_LIST);

    // ����Ʈ �÷� �߰�
    m_ObjectList.InsertColumn(0, _T("GameObject Name"), LVCFMT_LEFT, 150);

    //for (int i = 0; i < g_process->GetObjCount(); i++)
    //{
    //    // tag�� �޾ƿͼ� ����ȯ
    //    std::string sTag = g_process->GetTag(i);
    //    CString cTag(sTag.c_str());

    //    m_ObjectList.InsertItem(i, cTag);
    //}
    return 0;
}

void ObjWin::OnCreateGameObject()
{
    // ������Ʈ �߰�
    int itemIndex = m_ObjectList.GetItemCount();
    CString newItemName;
    newItemName.Format(_T("New GameObject %d"), itemIndex);

    m_ObjectList.InsertItem(itemIndex, newItemName);
    std::string tag = std::string(CT2CA(newItemName));
    //g_process->CreateObject(tag);

}

void ObjWin::OnSelectObject(NMHDR* pNMHDR, LRESULT* pResult)
{
    // ������ �׸� cast
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    // ���õ� �׸� �ε��� ���
    int selectedIndex = pNMLV->iItem;

    if (selectedIndex == -1) return;
    //if (selectedIndex >= g_process->GetObjCount()) return;

    // ���õ� �׸��� ���� ���
    CString itemName = m_ObjectList.GetItemText(selectedIndex, 0);

    if (m_comp)
    {
        m_comp->DestroyWindow();
        delete m_comp;
    }

    // ������Ʈ ���̾�α� ����
    m_comp = new CompWin(itemName);
    m_comp->Create(IDD_ABOUTBOX, this);
    m_comp->SetWindowText(itemName);
    m_comp->SetWindowPos(NULL, 0, 300, 250, 600, SWP_SHOWWINDOW);

    *pResult = 0;
}

void ObjWin::OnRenameObject(NMHDR* pNMHDR, LRESULT* pResult)
{
    // ���õ� �׸��� �ε��� �ҷ�����
    int selectedIndex = m_ObjectList.GetNextItem(-1, LVNI_SELECTED);
    if (selectedIndex == -1) return;
    //if (selectedIndex >= g_process->GetObjCount()) return;
    // input box ����
    //InputBox inputBox;

    // Ȯ�� ������ ���
    //if (inputBox.DoModal() == IDOK)
    //{
    //    // ���� �̸� �ҷ�����
    //    const int bufferSize = 256;
    //    TCHAR buffer[bufferSize];
    //    CString oldName;
    //    m_ObjectList.GetItemText(selectedIndex, 0, buffer, bufferSize);
    //    oldName = buffer;

    //    // �Էµ� ���ο� �̸� �ҷ�����
    //    CString newName = inputBox.m_inputText;

    //    // �׸� �̸� ����
    //    m_ObjectList.SetItemText(selectedIndex, 0, newName);

    //    // ���ڿ� ���� ��ȯ
    //    CT2CA old(oldName);
    //    CT2CA _new(newName);
    //    std::string oldStr(old);
    //    std::string newStr(_new);

    //    // ���� ������Ʈ �̸� ����
    //    g_app->SetName(oldStr, newStr);
    //}
}



