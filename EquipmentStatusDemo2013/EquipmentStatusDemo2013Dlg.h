
// EquipmentStatusDemo2013Dlg.h : ヘッダー ファイル
//

#pragma once


// CEquipmentStatusDemo2013Dlg ダイアログ
class CEquipmentStatusDemo2013Dlg : public CDialogEx
{
// コンストラクション
public:
	CEquipmentStatusDemo2013Dlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_EQUIPMENTSTATUSDEMO2013_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDebug();
};
