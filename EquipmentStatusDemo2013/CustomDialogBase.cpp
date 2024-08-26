#include "stdafx.h"
#include "CustomDialogBase.h"

/*
	���g�p���@
	�@�ʏ�ʂ�_�C���O���쐬����
	�A�쐬���ꂽ�_�C�A���O�̊��N���X��CDialogEx�ɂȂ��Ă���̂őS��CCustomDialogBase�ɕύX����
	�B�_�C�A���O���Ń_�C�A���O�g�̃��T�C�Y�ɓ���������ɂ�OnInitDialog���œ��N���X��SetControlInfo�֐����g�p����
*/

IMPLEMENT_DYNAMIC(CCustomDialogBase, CDialogEx)

CCustomDialogBase::CCustomDialogBase(UINT IDD, CWnd* pParent /*=NULL*/)
: CDialogEx(IDD, pParent)
{
	mIDD = IDD;
	mModal = false;
	mSaveCx = mSaveCy = 0;
}

CCustomDialogBase::~CCustomDialogBase()
{
}

void CCustomDialogBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomDialogBase, CDialogEx)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/*============================================================================*/
/*! CCustomDialogBase

-# �T�C�Y�ύX����

@breif	�_�C�A���O�̃��T�C�Y�ɓ������Đݒ肳�ꂽ�R���g���[�������T�C�Y���s��
@param
@retval
*/
/*============================================================================*/
void CCustomDialogBase::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_MINIMIZED)
		return;

	if (GetSafeHwnd() == NULL)
		return;

	if (mControl.size() == 0)
		return;

	if (mSaveCx == 0){
		mSaveCx = cx;
		mSaveCy = cy;
		return;
	}

	int dx = cx - mSaveCx;
	int dy = cy - mSaveCy;

	CRect rect, rectClient;
	GetClientRect(rectClient);

	CWnd *pWnd;
	DWORD info;
	WORD anchore;
	TCHAR buf[80];

	::GetClassNameW(m_hWnd, buf, 80);

	vector<DWORD>::iterator itr;
	for (itr = mControl.begin(); itr != mControl.end(); itr++){
		info = (*itr);
		pWnd = GetDlgItem(LOWORD(info));
		if (!pWnd){
			continue;
		}

		if (!HIWORD(info))
			continue;

		anchore = HIWORD(info);
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);

		if (anchore & RESIZE_HOR)
			rect.right += dx;
		else if (anchore & ANCHORE_RIGHT)
			rect.OffsetRect(dx, 0);

		if (anchore & RESIZE_VER)
			rect.bottom += dy;
		else if (anchore & ANCHORE_BOTTOM)
			rect.OffsetRect(0, dy);

		// ����̃R���g���[�������O�Ń��T�C�Y����ꍇ�͈ȉ���OnProcSize���I�[�o�[���C�h���Ă��������B
		if (OnProcSize(pWnd, dx, dy) == FALSE){
			pWnd->MoveWindow(rect);
		}
	}

	mSaveCx = cx;
	mSaveCy = cy;
}

/*============================================================================*/
/*! CCustomDialogBase

-# �T�C�Y�ύX���̍ő�A�ŏ��T�C�Y�����߂�

@breif	�_�C�A���O�̃��T�C�Y���̍ŏ��T�C�Y�����肷��
@param
@retval
*/
/*============================================================================*/
void CCustomDialogBase::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 200;
	lpMMI->ptMinTrackSize.y = 200;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

/*============================================================================*/
/*! CCustomDialogBase

-# ���b�Z�[�W����

@breif	Enter�L�[�iEsc�L�[�j�������Ă����Ȃ��悤�ɂ���B
@param  �Ȃ�
@retval �Ȃ�
*/
/*============================================================================*/
BOOL CCustomDialogBase::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return FALSE;
		case VK_ESCAPE:
			return FALSE;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

/*============================================================================*/
/*! CCustomDialogBase

-# �_�C�A���O�������J�X�^�}�C�Y

@breif
@param
@retval
*/
/*============================================================================*/
void CCustomDialogBase::OnClose()
{
	//CString title;
	//GetWindowText(title);

	//if (IDCANCEL == MessageBoxHooked(this->m_hWnd, _T("�I�����܂��B\n��낵���ł����H"), title, MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
	//	return;

	if (mModal)
	{
		CDialogEx::OnClose();
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}

INT_PTR CCustomDialogBase::DoModal()
{
	mModal = true;
	return CDialogEx::DoModal();
}
