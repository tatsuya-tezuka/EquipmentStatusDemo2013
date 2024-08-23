#pragma once


// CDebugDialog ダイアログ

#include "CustomDialogBase.h"

class CDebugDialog : public CCustomDialogBase
{
	DECLARE_DYNAMIC(CDebugDialog)

public:
	CDebugDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDebugDialog();

// ダイアログ データ
	enum { IDD = IDD_DEBUG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
