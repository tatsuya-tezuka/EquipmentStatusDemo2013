
// EquipmentStatusDemo2013.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CEquipmentStatusDemo2013App:
// ���̃N���X�̎����ɂ��ẮAEquipmentStatusDemo2013.cpp ���Q�Ƃ��Ă��������B
//

class CEquipmentStatusDemo2013App : public CWinApp
{
public:
	CEquipmentStatusDemo2013App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CEquipmentStatusDemo2013App theApp;