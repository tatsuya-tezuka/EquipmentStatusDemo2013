// DebugDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "DebugDialog.h"
#include "afxdialogex.h"


// CDebugDialog ダイアログ

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


// CDebugDialog メッセージ ハンドラー


BOOL CDebugDialog::OnInitDialog()
{
	CCustomDialogBase::OnInitDialog();

	SetControlInfo(IDC_LIST1, ANCHORE_LEFTTOP | RESIZE_BOTH);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
