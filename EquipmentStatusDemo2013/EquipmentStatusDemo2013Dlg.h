
// EquipmentStatusDemo2013Dlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CEquipmentStatusDemo2013Dlg �_�C�A���O
class CEquipmentStatusDemo2013Dlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CEquipmentStatusDemo2013Dlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_EQUIPMENTSTATUSDEMO2013_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDebug();
};
