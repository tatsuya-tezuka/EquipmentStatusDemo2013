#pragma once

#include "CustomDialogBase.h"

// CCustomManager �_�C�A���O

class CCustomManager : public CCustomDialogBase
{
	DECLARE_DYNAMIC(CCustomManager)

public:
	CCustomManager(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CCustomManager();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
