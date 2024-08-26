
// EquipmentStatusDemo2013.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "EquipmentStatusDemo2013Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEquipmentStatusDemo2013App

BEGIN_MESSAGE_MAP(CEquipmentStatusDemo2013App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEquipmentStatusDemo2013App �R���X�g���N�V����

CEquipmentStatusDemo2013App::CEquipmentStatusDemo2013App()
{
	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CEquipmentStatusDemo2013App �I�u�W�F�N�g�ł��B

CEquipmentStatusDemo2013App theApp;


// CEquipmentStatusDemo2013App ������

BOOL CEquipmentStatusDemo2013App::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// �_�C�A���O�ɃV�F�� �c���[ �r���[�܂��̓V�F�� ���X�g �r���[ �R���g���[����
	// �܂܂�Ă���ꍇ�ɃV�F�� �}�l�[�W���[���쐬���܂��B
	CShellManager *pShellManager = new CShellManager;

	// MFC �R���g���[���Ńe�[�}��L���ɂ��邽�߂ɁA"Windows �l�C�e�B�u" �̃r�W���A�� �}�l�[�W���[���A�N�e�B�u��
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));

	InitializeApp();

	CEquipmentStatusDemo2013Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <�L�����Z��> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "�x��: �_�C�A���O�̍쐬�Ɏ��s���܂����B�A�v���P�[�V�����͗\�������ɏI�����܂��B\n");
		TRACE(traceAppMsg, 0, "�x��: �_�C�A���O�� MFC �R���g���[�����g�p���Ă���ꍇ�A#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS ���w��ł��܂���B\n");
	}

	// ��ō쐬���ꂽ�V�F�� �}�l�[�W���[���폜���܂��B
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	TerminateApp();

	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	//  �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}


/*============================================================================*/
/*! �A�v���P�[�V����

-# �A�v���P�[�V�����̏�����

@param
@retval

*/
/*============================================================================*/
void CEquipmentStatusDemo2013App::InitializeApp()
{
	// ���W���[��������EXE�����݂���p�X���擾����
	TCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, sizeof(path));
	PathRemoveFileSpec(path);
	mAppPath = path;

	// AppData�p�X�̍쐬���擾
	SHGetSpecialFolderPath(NULL, path, CSIDL_APPDATA, TRUE);
	CString strPath = path;
	strPath += _T("\\") + CString(mAppDataSystem);
	CreateDirectory(strPath, NULL);
	strPath += _T("\\") + CString(mAppDataDataPath);
	CreateDirectory(strPath, NULL);
	mAppDataPath = strPath;

	//=====================================================//
	//������������������������ Log ������������������������//
	CString logpath = path;
	logpath += _T("\\") + CString(mAppDataSystem);
	CreateDirectory(logpath, NULL);
	logpath += _T("\\") + CString(mAppDataLogPath);
	CreateDirectory(logpath, NULL);
	logpath += _T("\\");
	CLogTraceEx::Create(logpath, _T("CCustomEquipment"), nLogEx::debug, nLogEx::text);
	CLogTraceEx::Write(_T("###"), _T("CCustomEquipment"), _T("Start"), _T(""), _T(""), nLogEx::info);
	//������������������������ Log ������������������������//
	//=====================================================//
}

/*============================================================================*/
/*! �A�v���P�[�V����

-# �A�v���P�[�V�����̏I��

@param
@retval

*/
/*============================================================================*/
void CEquipmentStatusDemo2013App::TerminateApp()
{
	//=====================================================//
	//������������������������ Log ������������������������//
	CLogTraceEx::Write(_T("###"), _T("CCustomEquipment"), _T("Finish"), _T(""), _T(""), nLogEx::info);
	CLogTraceEx::Close();
	CLogTraceEx::Delete();
	//������������������������ Log ������������������������//
	//=====================================================//
}

/*============================================================================*/
/*! �A�v���P�[�V����

-# �ݔ��ڍ׃E�B���h�E�̍쐬

@param		pnode		�m�[�h���
@retval

*/
/*============================================================================*/
CCustomDetail* CEquipmentStatusDemo2013App::CreateEquipment(CTreeNode* pnode)
{
	// �ݔ��ڍ׉�ʂ̍쐬
	CCustomDetail *pitem = new CCustomDetail(theApp.GetMainWnd(), (pnode == NULL) ? false : true);
	if (pnode != NULL){
		pnode->GetWindowInfo().wnd = pitem;
		pnode->GetWindowInfo().manager = &mCustomManager;
	}
	// �ݔ��ڍ׉�ʂ̍쐬
	pitem->Create(IDD_DIALOG_EQDETAIL, theApp.GetMainWnd());
	pitem->ShowWindow((pnode == NULL) ? SW_SHOW : pnode->GetWindowInfo().placement.showCmd);

	// �Ǘ��E�B���h�E�̐ݒ�
	if (pnode == NULL){
		CTreeNode* pnodeitem = theApp.GetDataManager().SearchWndNode(pitem);
		pnodeitem->GetWindowInfo().wnd = pitem;
		pnodeitem->GetWindowInfo().manager = &mCustomManager;
	}
	return pitem;
}
