
// EquipmentStatusDemo2013.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��
#include "LogTraceEx.h"
#include "CustomDataManager.h"

// CEquipmentStatusDemo2013App:
// ���̃N���X�̎����ɂ��ẮAEquipmentStatusDemo2013.cpp ���Q�Ƃ��Ă��������B
//

class CEquipmentStatusDemo2013App : public CWinApp
{
public:
	CEquipmentStatusDemo2013App();

	void	InitializeApp();
	void	TerminateApp();

	/// ���W���[���t�@�C���p�X
	CString					mAppPath;
	/// AppData�p�X
	CString					mAppDataPath;

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CEquipmentStatusDemo2013App theApp;