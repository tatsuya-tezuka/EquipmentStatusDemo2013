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
