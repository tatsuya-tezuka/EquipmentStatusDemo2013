// CustomManager.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "CustomManager.h"
#include "afxdialogex.h"


// CCustomManager �_�C�A���O

IMPLEMENT_DYNAMIC(CCustomManager, CCustomDialogBase)

CCustomManager::CCustomManager(CWnd* pParent /*=NULL*/)
: CCustomDialogBase(CCustomManager::IDD, pParent)
{

}

CCustomManager::~CCustomManager()
{
}

void CCustomManager::DoDataExchange(CDataExchange* pDX)
{
	CCustomDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomManager, CCustomDialogBase)
END_MESSAGE_MAP()


// CCustomManager ���b�Z�[�W �n���h���[
