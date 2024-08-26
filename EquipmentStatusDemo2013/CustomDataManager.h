#pragma once
//------------------------------------------------------------------------------------ 
//	�֘A�w�b�_�[�t�@�C��
//------------------------------------------------------------------------------------
#include "Markup.h"

//------------------------------------------------------------------------------------ 
//	�O���[�o����`
//------------------------------------------------------------------------------------
enum eFileVersionMajor
{
	EN_FILE_VERSION_MAJOR = 100, /*1.00*/
};

static const int mTitleSize = 128;
static const int mNameSize = 64;
static const int mUnitSize = 10;
static const int mFormatSize = 10;
static const int mHeaderSize = 5;
/// �t�@�C���֘A
static const TCHAR* mAppDataSystem = { _T("NEC") };
static const TCHAR* mAppDataDataPath = { _T("DATA") };
static const TCHAR* mAppDataLogPath = { _T("LOG") };
static const TCHAR* mAppSaveEquipmentFile = { _T("AppEquipment.xml") };

/// �J�X�^����ʊ֘A
static const TCHAR* mDefaultCustomTitle = { _T("�^�C�g��") };
static const TCHAR* mDefaultCustomRoot = { _T("���[�g") };
static const TCHAR* mDefaultCustomMainText = { _T("���C���m�[�h") };
static const TCHAR* mDefaultCustomSubText = { _T("�T�u�m�[�h") };
static const TCHAR* mDefaultCustomItemText = { _T("���[�t") };
static const int mTreeHeaderSize = 100;
static const int mTreeHeaderItemSize = 200;
static const int mTreeFontHeight = 16;
static const int mListFontHeight = 16;
static const COLORREF mRootNodeBackColor = RGB(180, 180, 180);
static const COLORREF mDragBackColor = RGB(250, 250, 250);
static const COLORREF mDragTextColor = RGB(0, 0, 0);
static const TCHAR* mCOntrolSignString = { _T("#CNTL#") };
static const TCHAR* mCOntrolSignStringDisplay = { _T("����") };

static const int mMonMax = 5000;			// �Ď��̍ő吔
static const int mCtrlMax = 5000;			// ����̍ő吔

/// �e�탁�b�Z�[�WID
enum eUserMessage{
	eUserMessage_Manger_New = (WM_USER + 1),
	eUserMessage_Manager_Update,
	eUserMessage_Manager_Delete,
	eUserMessage_Manager_ResizeFit,
	eUserMessage_Manager_Reset,
	eUserMessage_Manager_Grid,

	eUserMessage_Drag_Select,
	eUserMessage_Drag_DropTarget,
	eUserMessage_Drag_GetIndex,

	eUserMessage_TreeMonEventFirst = (WM_USER + 100),
	eUserMessage_TreeMonEventLast = (eUserMessage_TreeMonEventFirst + mMonMax),
	eUserMessage_TreeCtrlEventFirst = (eUserMessage_TreeMonEventLast + 1),
	eUserMessage_TreeCtrlEventLast = (eUserMessage_TreeCtrlEventFirst + mCtrlMax),
};

/// �c���[�f�[�^
enum eTreeItemType{
	eTreeItemType_Window = 0x00000000,
	eTreeItemType_Title = 0x00000001,
	eTreeItemType_Main = 0x00000002,
	eTreeItemType_Sub = 0x00000003,
	eTreeItemType_Item = 0x00000004,
};

enum eTreeItemSubType{
	eTreeItemSubType_Item = 0x00000000,
	eTreeItemSubType_Value = 0x00000001,
	eTreeItemSubType_Unit = 0x00000002,
	eTreeItemSubType_Control = 0x00000003,
};

enum eColorType {
	eColorType_Window,
	eColorType_TitleBack,
	eColorType_TitleText,
	eColorType_MainBack,
	eColorType_MainText,
	eColorType_SubBack,
	eColorType_SubText,
	eColorType_ItemBack,
	eColorType_ItemText,
	eColorType_ValueText,
	eColorType_UnitText,

	eColorType_Max,
};

typedef struct{
	CWnd*			wnd;				// �ݔ��ڍ׃E�B���h�E�n���h��
	CWnd*			tree;				// �ݔ��ڍ׃c���[�n���h���h��
	CWnd*			manager;			// �Ǘ��E�B���h�E�n���h���iCCustomManager�ŃZ�b�g�j
	UINT			type;				// �\������ʁFeTreeItemType
	TCHAR			title[mTitleSize];	// �E�B���h�E�^�C�g��
	WINDOWPLACEMENT	placement;			// �E�B���h�E�ʒu���
	UINT			treeopen;			// �c���[�A�C�e���̊J���
	UINT			hwidth[mHeaderSize]; // �ڍ׉�ʃw�b�_�[��
	UINT			zorder;				// Z�I�[�_�[
	UINT			monitor;			// ���j�^����
} stWindowInfo;

typedef struct{
	TCHAR			display[mNameSize];	// �\����
	TCHAR			mname[mNameSize];	// �Ď���
	TCHAR			cname[mNameSize];	// ���䖼
	TCHAR			unit[mUnitSize];	// �P��
	UINT			formattype;			// �t�H�[�}�b�g��ʁFeControl
	TCHAR			format[mFormatSize];// �t�H�[�}�b�g����������
	TCHAR			group[mNameSize];	// �O���[�v
} stMonCtrlData;

typedef struct{
	COLORREF		back;				// �w�i�F
	COLORREF		textback;			// �e�L�X�g�w�i�F
	COLORREF		text;				// �e�L�X�g�F
	COLORREF		value;				// �l�e�L�X�g�F
	COLORREF		unit;				// �P�ʃe�L�X�g�F
	LOGFONT			font;				// �ڍ׉�ʃt�H���g
} stColorData;

//------------------------------------------------------------------------------------ 
//	�c���[�^�f�[�^�N���X
//------------------------------------------------------------------------------------
class CTreeNode {
public:
	// �w�肳�ꂽ id �� Node �����B
	CTreeNode(HTREEITEM id, CWnd* pwnd, CWnd* ptree);
	virtual ~CTreeNode();

	/* ------------------------------------------------------------------------------------ */
	/* ��`                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:

protected:

	/* ------------------------------------------------------------------------------------ */
	/* �����o�ϐ�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	HTREEITEM			treeitem;			// �m�[�h�A�C�e��
	CTreeNode*			parent;				// �e�m�[�h
	vector<CTreeNode*>	children;			// �q�A�C�e�����X�g

	stWindowInfo		wininfo;			// �ݔ��ڍ׃E�B���h�E���
	stMonCtrlData		monctrl;			// �Ď�����f�[�^
	stColorData			color;				// �F�E�t�H���g���

	/* ------------------------------------------------------------------------------------ */
	/* �����o�֐�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	HTREEITEM			GetTreeItem()	{ return treeitem; }
	void				SetTreeItem(HTREEITEM val)	{ treeitem = val; }
	stWindowInfo&		GetWindowInfo() { return wininfo; }
	stMonCtrlData&		GetMonCtrl() { return monctrl; }
	stColorData&		GetColor() { return color; }
	CTreeNode*			GetParentNode() { return parent; }
	void				SetParentNode(CTreeNode* val)	{ parent = val; }
	vector<CTreeNode*>&	GetChildren() { return children; }

	// �w�肵�� childID �̎qNode�����݂��Ȃ���΁A�qNode���쐬���qNode��Ԃ�
	// �w�肵�� childID �̎qNode�����݂��Ă���΁A���ɑ��݂���qNode��Ԃ�
	CTreeNode*	CreateTreeNode(HTREEITEM parent, HTREEITEM child, HTREEITEM hInsertAfter = TVI_FIRST);

	// �c���[�m�[�h�̍폜
	bool DeleteTreeNode(HTREEITEM target);

	// �c���[�m�[�h�̌���
	CTreeNode* SearchTreeNode(HTREEITEM target);
	CTreeNode* SearchTreeNodeType(UINT target);

	void	CopyItem(CTreeNode* copyNode, bool bColorOnly = false)
	{
		if (bColorOnly == false){
			memcpy(&wininfo, &(copyNode->wininfo), sizeof(stWindowInfo));
			memcpy(&monctrl, &(copyNode->monctrl), sizeof(stMonCtrlData));
		}
		memcpy(&color, &(copyNode->color), sizeof(stColorData));
	}

	/// ���ݔ�����ڍ׉�ʃ��C�A�E�g
	bool	SaveTreeNode(CArchive& ar);
	bool	LoadTreeNode(CArchive& ar);
	bool	SaveTreeNodeXml(CMarkup& xml);
	bool	LoadTreeNodeXml(CMarkup& xml);

protected:
	void	deleteNode(CTreeNode* pnode);

	/// ���ݔ�����ڍ׉�ʃ��C�A�E�g
	//bool	saveChildNodeXml(CMarkup& ar, CTreeNode* pnode);
	//bool	loadChildNodeXml(CMarkup& ar, CTreeNode* pnode);

	/// CArchive
	// ��`�̓Ǎ�
	void loadRect(CArchive& ar, RECT& rect)
	{
		ar >> rect.left;
		ar >> rect.top;
		ar >> rect.right;
		ar >> rect.bottom;
	}
	// �|�C���g�̓Ǎ�
	void loadPoint(CArchive& ar, POINT& point) const
	{
		ar >> point.x;
		ar >> point.y;
	}

	// ��`�̕ۑ�
	void saveRect(CArchive& ar, RECT& rect) const
	{
		ar << rect.left;
		ar << rect.top;
		ar << rect.right;
		ar << rect.bottom;
	}
	// �|�C���g�̕ۑ�
	void savePoint(CArchive& ar, POINT& point) const
	{
		ar << point.x;
		ar << point.y;
	}

	/// XML
	// ��`�̓Ǎ�
	void loadRectXml(CMarkup& xml, RECT& rect)
	{
		xml.FindElem(_T("LEFT"));
		rect.left = _wtoi(xml.GetData());
		xml.FindElem(_T("TOP"));
		rect.top = _wtoi(xml.GetData());
		xml.FindElem(_T("RIGHT"));
		rect.right = _wtoi(xml.GetData());
		xml.FindElem(_T("BOTTOM"));
		rect.bottom = _wtoi(xml.GetData());
	}
	// �|�C���g�̓Ǎ�
	void loadPointXml(CMarkup& xml, POINT& point) const
	{
		xml.FindElem(_T("X"));
		point.x = _wtoi(xml.GetData());
		xml.FindElem(_T("Y"));
		point.y = _wtoi(xml.GetData());
	}

	// ��`�̕ۑ�
	void saveRectXml(CMarkup& xml, RECT& rect) const
	{
		xml.AddElem(_T("LEFT"), rect.left);
		xml.AddElem(_T("TOP"), rect.top);
		xml.AddElem(_T("RIGHT"), rect.right);
		xml.AddElem(_T("BOTTOM"), rect.bottom);
	}
	// �|�C���g�̕ۑ�
	void savePointXml(CMarkup& xml, POINT& point) const
	{
		xml.AddElem(_T("X"), point.x);
		xml.AddElem(_T("Y"), point.y);
	}

	/* ------------------------------------------------------------------------------------ */
};

//------------------------------------------------------------------------------------ 
//	�J�X�^�}�C�Y�@�\�̃f�[�^�}�l�[�W���[�N���X
//------------------------------------------------------------------------------------
class CCustomDataManager
{
public:
	CCustomDataManager();
	~CCustomDataManager();

	/* ------------------------------------------------------------------------------------ */
	/* ��`                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:

protected:

	/* ------------------------------------------------------------------------------------ */
	/* �����o�ϐ�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	/// �c���[�m�[�h
	vector<CTreeNode*>		mTreeNode;

	/* ------------------------------------------------------------------------------------ */
	/* �����o�֐�                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	/// �c���[�m�[�h�擾
	vector<CTreeNode*>&	GetTreeNode() { return mTreeNode; }
	// �c���[�m�[�h�擾
	void	AddTreeNode(CTreeNode* val)
	{
		//val->getColor().textback = mRootNodeBackColor;
		mTreeNode.push_back(val);
	}
	/// �c���[�m�[�h���̃A�C�e���̌���
	CTreeNode* SearchItemNode(CWnd* pTarget, HTREEITEM target)
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr)->GetWindowInfo().wnd == pTarget){
				return (*itr)->SearchTreeNode(target);
			}
		}
		return NULL;
	}
	/// �c���[�m�[�h���̃A�C�e����ʂ̌���
	CTreeNode* SearchItemNodeType(CWnd* pTarget, UINT target)
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr)->GetWindowInfo().wnd == pTarget){
				return (*itr)->SearchTreeNodeType(target);
			}
		}
		return NULL;
	}
	/// �c���[�m�[�h���̐ݔ��ڍ׃E�B���h�E����
	CTreeNode* SearchWndNode(CWnd* pTarget)
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr)->GetWindowInfo().wnd == pTarget){
				return (*itr);
			}
		}
		return NULL;
	}
	/// �S�ẴE�B���h�E�n���h���̍폜
	void DeleteAllWnd()
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr)->GetWindowInfo().wnd != NULL){
				delete (*itr)->GetWindowInfo().wnd;
			}
		}
	}
	/// �ʃE�B���h�E�n���h���̍폜
	void DeleteItemWnd(CWnd* p)
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr)->GetWindowInfo().wnd == p){
				if ((*itr)->GetWindowInfo().wnd != NULL){
					delete (*itr)->GetWindowInfo().wnd;
				}
				break;
			}
		}
	}

	// �S�Ẵm�[�h�̍폜
	void DeleteAllNode()
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr) != NULL){
				delete (*itr);
			}
		}
		mTreeNode.clear();
	}
	// �ʃm�[�h�̍폜
	void DeleteItemNode(CTreeNode* p)
	{
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if ((*itr) == p){
				if ((*itr) != NULL){
					delete (*itr);
				}
				mTreeNode.erase(itr);
				break;
			}
		}
	}
	// �m�[�h�̌���
	void SwapItemNode(UINT pos1, UINT pos2)
	{
		swap(mTreeNode[pos1], mTreeNode[pos2]);
	}
	void SwapItemNode(vector<CTreeNode*>::iterator itr1, vector<CTreeNode*>::iterator itr2)
	{
		iter_swap(itr1, itr2);
	}

	/// ���J���[���
	bool	GetNodeColor(CWnd* pwnd, UINT type, UINT subtype, stColorData& color);
	bool	SetNodeColor(CWnd* pwnd, UINT type, UINT subtype, stColorData& color);

	/// ���ݔ�����ڍ׉�ʃ��C�A�E�g
	bool	SaveTreeData(CString strFile, CWnd* pTargetWnd = NULL);
	bool	LoadTreeData(CString strFile, bool bClear);
	bool	SaveTreeDataXml(CString strFile, CWnd* pTargetWnd = NULL);
	bool	LoadTreeDataXml(CString strFile, bool bClear);

	/// Z�I�[�_�[�ݒ�
	void	SetTreeZorder();
	void	ResetTreeZorder();

protected:
	/// �J���[���
	bool	getNodeTypeColor(CTreeNode* pnode, UINT type, UINT subtype, stColorData& color);
	bool	setNodeTypeColor(CTreeNode* pnode, UINT type, UINT subtype, stColorData& color);

	/* ------------------------------------------------------------------------------------ */
};

