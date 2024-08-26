// DebugDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "DebugDialog.h"
#include "afxdialogex.h"


// CDebugDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CDebugDialog, CCustomDialogBase)

CDebugDialog::CDebugDialog(CWnd* pParent /*=NULL*/)
: CCustomDialogBase(CDebugDialog::IDD, pParent)
{

}

CDebugDialog::~CDebugDialog()
{
}

void CDebugDialog::DoDataExchange(CDataExchange* pDX)
{
	CCustomDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList);
}


BEGIN_MESSAGE_MAP(CDebugDialog, CCustomDialogBase)
END_MESSAGE_MAP()


// CDebugDialog ���b�Z�[�W �n���h���[


BOOL CDebugDialog::OnInitDialog()
{
	CCustomDialogBase::OnInitDialog();

	SetControlInfo(IDC_LIST1, ANCHORE_LEFTTOP | RESIZE_BOTH);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}


BOOL CDebugDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	if (CCustomDialogBase::PreCreateWindow(cs) == FALSE)
		return FALSE;

	if (cs.lpszName){
		WNDCLASS wc;
		::GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wc);
		wc.lpszClassName = _T("CDebugDialog");
		AfxRegisterClass(&wc);
		cs.lpszClass = wc.lpszClassName;
	}

	return TRUE;
}

BOOL CDebugDialog::OnProcSize(CWnd* pWnd, int dx, int dy)
{
	CRect rect;

	mList.GetWindowRect(rect);
	ScreenToClient(rect);
	rect.right += dx;
	rect.bottom += dy;
	mList.MoveWindow(rect);
	Invalidate();
	return TRUE;
}
