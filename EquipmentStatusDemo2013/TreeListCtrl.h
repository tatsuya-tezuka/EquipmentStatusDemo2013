#pragma once

#include "afxcmn.h"

//=============================================================================
// ��CTreeEdit
//=============================================================================
//!< ���X�g���Ŏg�p����G�f�B�b�g�R���g���[��
class CTreeEdit : public CEdit
{
	// Construction
public:
	CTreeEdit(HTREEITEM iItem, int iSubItem, CString sInitText);

	enum eTreeEditType
	{
		eTreeEditType_Other,		// ���͕������`�F�b�N���Ȃ�
		eTreeEditType_Char,
		eTreeEditType_Float,
		eTreeEditType_Int,
	};

	// Attributes
public:
	BOOL	m_bKeyReturn;
	BOOL    m_bKeyShift;
	UINT	m_nNumberLimit;

	// Operations
public:
	void		SetNumberLimit(UINT len);
	HTREEITEM	GetItem() { return m_iItem; }
	int			GetSubItem() { return m_iSubItem; }

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CTreeEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM	m_iItem;
	int			m_iSubItem;
	CString		m_sInitText;
	BOOL		m_bESC;         // To indicate whether ESC key was pressed
	BOOL		m_bNotify;
};


// �}�E�X�N���b�N�i���x���ҏW�j�p�R�[���o�b�N�֐���`
typedef BOOL(CALLBACK *CLICKCALLBACK)(CWnd* pwnd, HTREEITEM hItem, UINT nSubItem, CPoint point);
// �h���b�O���h���b�v�p�R�[���o�b�N�֐���`
typedef BOOL(CALLBACK *DRAGCALLBACK)(CWnd* pwnd, UINT status, HTREEITEM hItem, LPARAM lParam1, LPARAM lParam2, LPARAM lParam3);

#define abs(x)		((x) < 0 ? (-(x)) : (x))

//=============================================================================
// ��CTreeListCtrl
//=============================================================================
class CTreeListCtrl : public CTreeCtrl
{
public:
	CTreeListCtrl();
	~CTreeListCtrl();

	/* ------------------------------------------------------------------------------------ */
	/* ��`                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:
	enum eTreeIDs { eHeaderID = 1, eTreeID = 2 };
	enum eStatus { eEnable = 1, eSelect = 2, eDrop = 3 };
	enum { eItem, eValue, eUnit, eControl, eMax };
protected:

	/* ------------------------------------------------------------------------------------ */
	/* �����o�ϐ�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
protected:
	/// �c���[���
	CWnd*				mTreeParent;
	/// �w�b�_�[���
	CHeaderCtrl			mHeaderCtrl;
	int					mcyHeader;
	int					mcxTotal;
	int					mxPos;
	int					mxOffset;
	int					myOffset;
	vector<int>			mColWidths;
	int					mcxFirstCol;

	CImageList			mDragImageList;

	///���x���ҏW
	CEdit*				mpEdit;
	BOOL				mbInplace;
	CLICKCALLBACK		mClickCallback;

	/// �h���b�O���h���b�v

	/// �m�[�h�p�t�H���g
	CFont				mNodeTitleFont;
	CFont				mNodeMainFont;
	CFont				mNodeSubFont;
	CFont				mNodeLeafFont;

	/// ����p�t�H���g
	CFont				mControlFont;

	/// �c�[���`�b�v
	CToolTipCtrl		mToolTip;

	/// �I���A�C�e�����X�g
	vector<HTREEITEM>	mSelectItems;
	HTREEITEM			mLastSelectItem;

	/* ------------------------------------------------------------------------------------ */
	/* �����o�֐�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	CWnd*	GetParent() { return mTreeParent; }
	void	Create(CWnd* parent, CFont& font);
	void	ResizeControl(int dx, int dy);

	int		GetPosX() { return mxPos; }
	void	SetPosX(int val) { mxPos = val; }
	int		GetTotalCX() { return mcxTotal; }


	/// �w�b�_�[���
	int		GetHeaderHeight() { return mcyHeader; }
	void	SetHeaderItem(int item, CString title, int width);
	void	AdjustColumnWidth(int nColumn, BOOL bIgnoreCollapsed);
	int		GetHeaderWidth(int col = -1);

	///���x���ҏW
	void SetClickCallback(CLICKCALLBACK callback)
	{
		mClickCallback = callback;
	}
	CString	GetSubItemText(HTREEITEM hItem, int col);
	void	SetSubItemText(HTREEITEM hItem, int col, CString strText);
	bool	IsControl(CPoint point);
	BOOL	SwitchEditMode(HTREEITEM hItem, UINT col, CPoint point);

	/// �h���b�O���h���b�v

	void	UpdateColumns();
	void	UpdateScroller();
	void	RepositionControls();
	HTREEITEM	HitTestEx(CPoint &point, UINT& col);

	void	GetHeaderWidth(UINT *width, int max)
	{
		int nColsCnt = mHeaderCtrl.GetItemCount();
		for (int i = 0; i < nColsCnt; i++){
			if (i >= max)
				break;
			width[i] = mColWidths[i];
		}
	}

	void	SetHeaderWidth(UINT *width, int max)
	{
		HDITEM hditem;
		hditem.mask = HDI_WIDTH;
		int nColsCnt = mHeaderCtrl.GetItemCount();
		for (int i = 0; i < nColsCnt; i++){
			if (i >= max)
				break;
			hditem.cxy = width[i];
			mHeaderCtrl.SetItem(i, &hditem);
		}
	}

	vector<HTREEITEM>& GetSelectedItems() { return mSelectItems; }

protected:
	int		_GetMaxColumnWidth(HTREEITEM hItem, int nColumn, int nDepth, BOOL bIgnoreCollapsed);
	HTREEITEM	_HitControl(CPoint point);

	/// ���x���ҏW
	CEdit*	_EditSubLabel(HTREEITEM hItem, int col);

	/// �h���b�O���h���b�v
	CImageList*	_CreateDragImageEx(HTREEITEM hItem);
	bool	_IsDropExecute(HTREEITEM hItemDrag, HTREEITEM hItemDrop);
	bool	_IsChildNodeOf(HTREEITEM hItemDrop, HTREEITEM hItemDrag);

	BOOL	_PtInRectPointCell(CPoint point);
	bool	_GetColumnsRect(HTREEITEM hItem, UINT col, CRect& rect);

	void	_SelectMultiItem(HTREEITEM hClickedItem, UINT nFlags);

	inline void _ExtractSubString(CString strText, vector<CString>& list)
	{
		list.clear();
		CString temp;
		int index = 0;
		while (AfxExtractSubString(temp, strText, index++, '\t')) {
			list.push_back(temp);
		}
	}

	inline COLORREF _CalcContrastColor(COLORREF color)
	{
		int a = (int)abs((int)color);

		if (abs((int)((color)& 0xFF) - 0x80) <= (UINT)0x40 &&
			abs((int)((color >> 8) & 0xFF) - 0x80) <= (UINT)0x40 &&
			abs((int)((color >> 16) & 0xFF) - 0x80) <= (UINT)0x40 )
			return (COLORREF)((0x7F7F7F + color) & 0xFFFFFF);
		else
			return (COLORREF)(color ^ 0xFFFFFF);
	}

	void	ProcControlKeyPress(HTREEITEM hCurItem);
	void	ProcShiftKeyPress(HTREEITEM hCurItem);
	bool	IsSameLevel(HTREEITEM hItem);
	void	RemoveFromSelectList(HTREEITEM hItem);
	void	ClearSelection();

	CString	CreateDragString(HTREEITEM hDragItem);

	/* ------------------------------------------------------------------------------------ */


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
};

