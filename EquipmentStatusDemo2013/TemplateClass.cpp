// TemplateClass.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "TemplateClass.h"

//------------------------------------------------------------------------------------ 
//	�T�v�F
//------------------------------------------------------------------------------------
CTemplateClass::CTemplateClass()
{
}

CTemplateClass::~CTemplateClass()
{
}

/*============================================================================*/
/*! �e���v���[�g�N���X

-# �쐬

@param	val		�쐬���̎��ʎq

@retval	���������ꍇ��true�A����ȊO��false��Ԃ�
*/
/*============================================================================*/
bool CTemplateClass::Create(UINT val)
{
#ifdef _DEBUG
	// �f�o�b�O�p�R�[�h
	createItem(10);
#else
	createItem(val);
#endif
	return true;
}

/*============================================================================*/
/*! �e���v���[�g�N���X

-# �쐬

@param	val		�쐬���̎��ʎq

@retval	���������ꍇ��true�A����ȊO��false��Ԃ�
*/
/*============================================================================*/
bool CTemplateClass::createItem(UINT val)
{
	return true;
}
