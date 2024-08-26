#pragma once


// CDebugDialog ダイアログ

#include "CustomDialogBase.h"
#include "afxcmn.h"

class CDebugDialog : public CCustomDialogBase
{
	DECLARE_DYNAMIC(CDebugDialog)

public:
	CDebugDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDebugDialog();

// ダイアログ データ
	enum { IDD = IDD_DEBUG_DIALOG };

	int mdx, mdy;
	virtual BOOL OnProcSize(CWnd* pWnd, int dx, int dy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CListCtrl mList;
};
