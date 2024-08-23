#include "stdafx.h"
#include "EquipmentStatusDemo2013.h"
#include "CustomDataManager.h"

//------------------------------------------------------------------------------------ 
//	�T�v�F�c���[�^�f�[�^�N���X
//------------------------------------------------------------------------------------

CTreeNode::CTreeNode(HTREEITEM id, CWnd* pwnd, CWnd* ptree)
: treeitem(id)
{
	memset(&wininfo, 0, sizeof(stWindowInfo));
	memset(&monctrl, 0, sizeof(stMonCtrlData));
	memset(&color, 0, sizeof(stColorData));
	color.back = GetSysColor(COLOR_WINDOW);
	color.textback = GetSysColor(COLOR_WINDOW);
	color.text = GetSysColor(COLOR_BTNTEXT);
	color.value = GetSysColor(COLOR_BTNTEXT);
	color.unit = GetSysColor(COLOR_BTNTEXT);
	CFont font;
	font.CreateStockObject(DEFAULT_GUI_FONT);
	if (font.GetLogFont(&color.font)){
		color.font.lfHeight = -mTreeFontHeight;
		color.font.lfWeight = FW_BOLD;
		font.DeleteObject();
	}

	wininfo.wnd = pwnd;
	wininfo.tree = ptree;
	parent = NULL;
	children.clear();
}

CTreeNode::~CTreeNode()
{
	// ���ׂĂ̎q�A�C�e�����X�g���폜����
	vector<CTreeNode *>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {
		delete (*itr);
	}
	parent = NULL;
	children.clear();
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �c���[�m�[�h�̍쐬

@param  parent			�e�m�[�h
@param  child			�쐬����q�m�[�h
@param  hInsertAfter	�o�^���̈ʒu���

@retval CTreeNode	�m�[�h�N���X�|�C���^
*/
/*============================================================================*/
CTreeNode* CTreeNode::CreateTreeNode(HTREEITEM parent, HTREEITEM child, HTREEITEM hInsertAfter/* = TVI_FIRST*/)
{
	if (treeitem != parent)
		return NULL;

	// �q�A�C�e�����X�g�ɑ��݂��邩�m�F����
	vector<CTreeNode *>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {
		if ((*itr)->treeitem == child) {
			// ���Ɏq�A�C�e�����X�g�ɑ��݂���
			return (*itr);
		}
	}

	// �q�A�C�e�����X�g�ɑ��݂��Ȃ��̂ŐV���ɍ쐬����
	CTreeNode *childitem = new CTreeNode(child, wininfo.wnd, wininfo.tree);
	childitem->parent = this;
	if (hInsertAfter == TVI_LAST){
		children.push_back(childitem);
	}
	else{
		children.insert(children.begin(), childitem);
	}
	return childitem;
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �c���[�m�[�h�̍폜

@param  target	�폜�Ώۃm�[�h

@retval	bool
*/
/*============================================================================*/
bool CTreeNode::DeleteTreeNode(HTREEITEM target)
{
	if (treeitem == target){
		// �擪�m�[�h�Ȃ̂ŉ������Ȃ�
		return false;
	}

	CTreeNode* pnode = SearchTreeNode(target);
	if (pnode == NULL)
		return false;

	deleteNode(pnode);

	// �q���X�g����폜����
	vector<CTreeNode *>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {

		if ((*itr) == pnode){
			children.erase(itr);
			break;
		}
	}
	delete pnode;

	return true;
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �c���[�m�[�h�̌���

@param  target	�����Ώۃm�[�h

@retval CTreeNode	�m�[�h�N���X�|�C���^
*/
/*============================================================================*/
CTreeNode* CTreeNode::SearchTreeNode(HTREEITEM target)
{
	if (treeitem == target)
		return this;

	// �q�A�C�e�����X�g�ɑ��݂��邩�m�F����
	vector<CTreeNode *>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {
		if ((*itr)->treeitem == target) {
			// ���Ɏq�A�C�e�����X�g�ɑ��݂���
			return (*itr);
		}
		CTreeNode* pnode = (*itr)->SearchTreeNode(target);
		if (pnode != NULL)
			return pnode;
	}
	return NULL;
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �c���[�m�[�h�̌���

@param  target	�����Ώۃm�[�h���

@retval CTreeNode	�m�[�h�N���X�|�C���^
*/
/*============================================================================*/
CTreeNode* CTreeNode::SearchTreeNodeType(UINT target)
{
	if (wininfo.type == target)
		return this;

	// �q�A�C�e�����X�g�ɑ��݂��邩�m�F����
	vector<CTreeNode *>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {
		if ((*itr)->GetWindowInfo().type == target) {
			// ���Ɏq�A�C�e�����X�g�ɑ��݂���
			return (*itr);
		}
		CTreeNode* pnode = (*itr)->SearchTreeNodeType(target);
		if (pnode != NULL)
			return pnode;
	}
	return NULL;
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �c���[�m�[�h�̍폜

@param  target	�폜�Ώۃm�[�h

@retval
*/
/*============================================================================*/
void CTreeNode::deleteNode(CTreeNode* pnode)
{
	// �q�m�[�h�����݂���̂ō폜����
	vector<CTreeNode *>::iterator itr;
	for (itr = pnode->children.begin(); itr != pnode->children.end(); itr++) {
		deleteNode((*itr));
		delete (*itr);
	}
	pnode->children.clear();
}



//------------------------------------------------------------------------------------ 
//	�J�X�^�}�C�Y�@�\�̃f�[�^�}�l�[�W���[�N���X
//------------------------------------------------------------------------------------

CCustomDataManager::CCustomDataManager()
{
}


CCustomDataManager::~CCustomDataManager()
{
	// �E�B���h�E�A�m�[�h�̍폜
	DeleteAllWnd();
	DeleteAllNode();
}

/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �e��F���̎擾

@param

@retval
*/
/*============================================================================*/
bool CCustomDataManager::GetNodeColor(CWnd* pwnd, UINT type, UINT subtype, stColorData& color)
{
	CTreeNode* pnode = SearchWndNode(pwnd);
	if (pnode == NULL)
		return false;

	switch (type){
	case	eTreeItemType_Window:
	case	eTreeItemType_Title:
		color = pnode->GetColor();
		return true;
		break;
	}

	bool ret = getNodeTypeColor(pnode, type, subtype, color);

	return ret;
}

/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �e��F���̐ݒ�

@param

@retval
*/
/*============================================================================*/
bool CCustomDataManager::SetNodeColor(CWnd* pwnd, UINT type, UINT subtype, stColorData& color)
{
	CTreeNode* pnode = SearchWndNode(pwnd);
	if (pnode == NULL)
		return false;

	switch (type){
	case	eTreeItemType_Window:
	case	eTreeItemType_Title:
		pnode->GetColor() = color;
		return true;
		break;
	}

	bool ret = setNodeTypeColor(pnode, type, subtype, color);

	return ret;
}

/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �e��F���̎擾

@param	pnode		�Ώۃm�[�h���
@param	type		�Ώۃm�[�h���
@param	subtype		�Ώۃm�[�h�Z�����
@param	color		�F���

@retval
*/
/*============================================================================*/
bool CCustomDataManager::getNodeTypeColor(CTreeNode* pnode, UINT type, UINT subtype, stColorData& color)
{
	if (pnode->GetWindowInfo().type == type){
		color = pnode->GetColor();
		return true;
	}

	bool ret;
	vector<CTreeNode*>::iterator itr;
	for (itr = pnode->GetChildren().begin(); itr != pnode->GetChildren().end(); itr++) {
		ret = getNodeTypeColor((*itr), type, subtype, color);
		if (ret == true)
			return true;
	}
	return false;
}
/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �e��F���̐ݒ�

@param	pnode		�Ώۃm�[�h���
@param	type		�Ώۃm�[�h���
@param	subtype		�Ώۃm�[�h�Z�����
@param	color		�F���

@retval
*/
/*============================================================================*/
bool CCustomDataManager::setNodeTypeColor(CTreeNode* pnode, UINT type, UINT subtype, stColorData& color)
{
	if (pnode->GetWindowInfo().type == type){
		pnode->GetColor() = color;
		return true;
	}

	bool ret;
	vector<CTreeNode*>::iterator itr;
	for (itr = pnode->GetChildren().begin(); itr != pnode->GetChildren().end(); itr++) {
		ret = setNodeTypeColor((*itr), type, subtype, color);
	}
	return true;
}




/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �c���[�f�[�^���̕ۑ�

@param		strFile	�ۑ��t�@�C��

@retval
*/
/*============================================================================*/
bool CCustomDataManager::SaveTreeData(CString strFile, CWnd* pTargetWnd/* = NULL*/)
{
	//=====================================================//
	//������������������������ Log ������������������������//
	CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("SaveTreeData"), _T("Start"), _T(""), nLogEx::debug);
	//������������������������ Log ������������������������//
	//=====================================================//
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary) == NULL) {
		//=====================================================//
		//������������������������ Log ������������������������//
		CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("SaveTreeData"), _T("Open Error"), _T(""), nLogEx::error);
		//������������������������ Log ������������������������//
		//=====================================================//
		return false;
	}

	CArchive mArc(&file, CArchive::store);
	// �o�[�W�����ۑ�
	mArc << (UINT)EN_FILE_VERSION_MAJOR;

	if (pTargetWnd == NULL) {
		mArc << (UINT)mTreeNode.size();
	}
	else {
		mArc << (UINT)1;
	}

	// �X�̃f�[�^��ۑ�
	vector<CTreeNode*>::iterator itr;
	for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++) {
		if (pTargetWnd != NULL && pTargetWnd != (*itr)->GetWindowInfo().wnd) {
			continue;
		}
		(*itr)->SaveTreeNode(mArc);
	}

	mArc.Flush();
	mArc.Close();
	file.Close();
	//=====================================================//
	//������������������������ Log ������������������������//
	CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("SaveTreeData"), _T("Stop"), _T(""), nLogEx::debug);
	//������������������������ Log ������������������������//
	//=====================================================//

	return true;
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h���̕ۑ�

@param		ar	CArchive�N���X

@retval
*/
/*============================================================================*/
bool CTreeNode::SaveTreeNode(CArchive& ar)
{
	// �E�B���h�E�ʒu���擾
	if (wininfo.wnd != NULL) {
		memset(&wininfo.placement, 0, sizeof(WINDOWPLACEMENT));
		wininfo.placement.length = sizeof(WINDOWPLACEMENT);
		wininfo.wnd->GetWindowPlacement(&wininfo.placement);
		//��((CCustomDetail*)wininfo.wnd)->GetHeaderWidth(wininfo.hwidth, mHeaderSize);
	}

	// �E�B���h�E���
	ar << wininfo.type;
	if (wininfo.type == eTreeItemType_Title) {
		ar << CString(wininfo.title);
		ar << wininfo.monitor;
		ar << wininfo.placement.flags;
		if (wininfo.wnd == NULL)
			ar << FALSE;
		else
			ar << wininfo.wnd->IsWindowVisible();
		savePoint(ar, wininfo.placement.ptMinPosition);
		savePoint(ar, wininfo.placement.ptMaxPosition);
		saveRect(ar, wininfo.placement.rcNormalPosition);
		ar << (UINT)mHeaderSize;
		for (int i = 0; i < mHeaderSize; i++) {
			ar << wininfo.hwidth[i];
		}
		ar << wininfo.zorder;
	}
	//��wininfo.treeopen = ((CCustomDetail*)wininfo.wnd)->GetTreeExpandState(treeitem);
	ar << wininfo.treeopen;

	// �Ď�������
	ar << CString(monctrl.display);
	if (wininfo.type == eTreeItemType_Item) {
		ar << CString(monctrl.mname);
		ar << CString(monctrl.cname);
		ar << CString(monctrl.unit);
		ar << monctrl.formattype;
		ar << CString(monctrl.format);
		ar << CString(monctrl.group);
	}

	// �F���
	ar << color.back;
	ar << color.textback;
	ar << color.text;
	ar << color.value;
	ar << color.unit;
	// �t�H���g
	ar << color.font.lfHeight;
	ar << color.font.lfWidth;
	ar << color.font.lfWeight;
	ar << CString(color.font.lfFaceName);

	// �q�m�[�h�̕ۑ�
	ar << (UINT)children.size();
	vector<CTreeNode*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->SaveTreeNode(ar);
	}

	return true;
}

/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �c���[�f�[�^���̓Ǎ�

@param		strFile	�Ǎ��t�@�C��

@retval
*/
/*============================================================================*/
bool CCustomDataManager::LoadTreeData(CString strFile, bool bClear)
{
	//=====================================================//
	//������������������������ Log ������������������������//
	CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("LoadTreeData"), _T("Start"), _T(""), nLogEx::debug);
	//������������������������ Log ������������������������//
	//=====================================================//
	CFile file;
	if (file.Open(strFile, CFile::modeRead | CFile::typeBinary) == NULL) {
		//=====================================================//
		//������������������������ Log ������������������������//
		CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("LoadTreeData"), _T("Open Error"), _T(""), nLogEx::error);
		//������������������������ Log ������������������������//
		//=====================================================//
		return false;
	}

	CArchive mArc(&file, CArchive::load);

	// �o�[�W����
	UINT version;
	mArc >> version;
	if (version != EN_FILE_VERSION_MAJOR) {
		//=====================================================//
		//������������������������ Log ������������������������//
		CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("LoadTreeData"), _T("Version Error"), _T(""), nLogEx::error);
		//������������������������ Log ������������������������//
		//=====================================================//
		return false;
	}

	if (bClear == true) {
		// ���s�̃f�[�^���폜����
		DeleteAllWnd();
		DeleteAllNode();
	}

	UINT size;
	mArc >> size;
	mTreeNode.reserve(size);
	for (UINT i = 0; i < size; i++) {
		CTreeNode* pnode = new CTreeNode((HTREEITEM)i, NULL, NULL);
		if (pnode->LoadTreeNode(mArc) == false) {
			delete pnode;
			break;
		}
		mTreeNode.push_back(pnode);
	}
	mArc.Close();
	file.Close();
	//=====================================================//
	//������������������������ Log ������������������������//
	CLogTraceEx::Write(_T("***"), _T("CCustomDataManager"), _T("LoadTreeData"), _T("Stop"), _T(""), nLogEx::debug);
	//������������������������ Log ������������������������//
	//=====================================================//
	return true;
}
/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h���̓Ǎ�

@param		ar	CArchive�N���X

@retval
*/
/*============================================================================*/
bool CTreeNode::LoadTreeNode(CArchive& ar)
{
	CString str;
	// �E�B���h�E���
	ar >> wininfo.type;
	if (wininfo.type == eTreeItemType_Title) {
		ar >> str;
		swprintf_s(wininfo.title, mTitleSize, _T("%s"), (LPCTSTR)str);
		ar >> wininfo.monitor;
		wininfo.placement.length = sizeof(WINDOWPLACEMENT);
		ar >> wininfo.placement.flags;
		ar >> wininfo.placement.showCmd;
		loadPoint(ar, wininfo.placement.ptMinPosition);
		loadPoint(ar, wininfo.placement.ptMaxPosition);
		loadRect(ar, wininfo.placement.rcNormalPosition);
		UINT hsize;
		ar >> hsize;
		for (int i = 0; i < (int)hsize; i++) {
			ar >> wininfo.hwidth[i];
		}
		ar >> wininfo.zorder;
	}
	ar >> wininfo.treeopen;;

	// �Ď�������
	ar >> str;
	swprintf_s(monctrl.display, mNameSize, _T("%s"), (LPCTSTR)str);
	if (wininfo.type == eTreeItemType_Item) {
		ar >> str;
		swprintf_s(monctrl.mname, mNameSize, _T("%s"), (LPCTSTR)str);
		ar >> str;
		swprintf_s(monctrl.cname, mNameSize, _T("%s"), (LPCTSTR)str);
		ar >> str;
		swprintf_s(monctrl.unit, mUnitSize, _T("%s"), (LPCTSTR)str);
		ar >> monctrl.formattype;
		ar >> str;
		swprintf_s(monctrl.format, mFormatSize, _T("%s"), (LPCTSTR)str);
		ar >> str;
		swprintf_s(monctrl.group, mNameSize, _T("%s"), (LPCTSTR)str);
	}

	// �F���
	ar >> color.back;
	ar >> color.textback;
	ar >> color.text;
	ar >> color.value;
	ar >> color.unit;
	// �t�H���g
	ar >> color.font.lfHeight;
	ar >> color.font.lfWidth;
	ar >> color.font.lfWeight;
	ar >> str;
	swprintf_s(color.font.lfFaceName, LF_FACESIZE, _T("%s"), (LPCTSTR)str);

	// �q�m�[�h�̎擾
	UINT size;
	ar >> size;
	children.reserve(size);
	for (UINT i = 0; i < size; i++) {
		CTreeNode* child = new CTreeNode((HTREEITEM)i, NULL, NULL);
		child->LoadTreeNode(ar);
		children.push_back(child);
	}

	return true;
}


/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �c���[�f�[�^���̕ۑ�

@param		strFile		�ۑ��t�@�C��
@param		pTargetWnd	�J�X�^����ʃn���h��

@retval
*/
/*============================================================================*/
bool CCustomDataManager::SaveTreeDataXml(CString strFile, CWnd* pTargetWnd/* = NULL*/)
{
	CString	decl = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	CMarkup xml(decl);

	SetTreeZorder();

	// ���s�R�[�h��ݒ�
	xml.SetEOL(MCD_T("\n"));
	xml.SetEOLLEN(sizeof(MCD_T("\n")) / sizeof(MCD_CHAR)-1);

	// BOM�𖢏o��
	xml.SetBOM(false);

	xml.SetDocFlags(CMarkup::MDF_UTF8PREAMBLE);

	// <ROOT>���o��
	xml.AddElem(_T("ROOT"));
	xml.IntoElem();
	xml.AddElem(_T("VERSION"), EN_FILE_VERSION_MAJOR);

	if (pTargetWnd == NULL){
		xml.AddElem(_T("SIZE"), (UINT)mTreeNode.size());
	}
	else{
		xml.AddElem(_T("SIZE"), (UINT)1);
	}

	vector<CTreeNode*>::iterator itr;
	for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
		if (pTargetWnd != NULL && pTargetWnd != (*itr)->GetWindowInfo().wnd){
			continue;
		}
		xml.AddElem(_T("EQUIPMENT"));
		xml.IntoElem();
		(*itr)->SaveTreeNodeXml(xml);
		xml.OutOfElem();
	}
	xml.OutOfElem();
	xml.Save(strFile);
	return true;
}
/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h�E�B���h�E��Z�I�[�_�[�̐ݒ�

@param

@retval
*/
/*============================================================================*/
void CCustomDataManager::SetTreeZorder()
{
	CWnd* pWnd = theApp.GetMainWnd()->GetWindow(GW_ENABLEDPOPUP);
	UINT pos = 0;
	while (pWnd){
		vector<CTreeNode*>::iterator itr;
		for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
			if (pWnd == (*itr)->GetWindowInfo().wnd){
				(*itr)->GetWindowInfo().zorder = pos++;
				break;
			}
		}
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
}
/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h�E�B���h�E��Z�I�[�_�[�X�V

@param

@retval
*/
/*============================================================================*/
void CCustomDataManager::ResetTreeZorder()
{
	map<UINT, CWnd*> winmap;
	vector<CTreeNode*>::iterator itr;
	for (itr = mTreeNode.begin(); itr != mTreeNode.end(); itr++){
		winmap.insert(map<UINT, CWnd*>::value_type((*itr)->GetWindowInfo().zorder, (*itr)->GetWindowInfo().wnd));
	}

	map<UINT, CWnd*>::reverse_iterator ritr;
	for (ritr = winmap.rbegin(); ritr != winmap.rend(); ++ritr){
		SetWindowPos((*ritr).second->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h���̕ۑ�

@param		xml	XML�N���X

@retval
*/
/*============================================================================*/
bool CTreeNode::SaveTreeNodeXml(CMarkup& xml)
{
	// �E�B���h�E�ʒu���擾
	if (wininfo.wnd != NULL){
		memset(&wininfo.placement, 0, sizeof(WINDOWPLACEMENT));
		wininfo.placement.length = sizeof(WINDOWPLACEMENT);
		wininfo.wnd->GetWindowPlacement(&wininfo.placement);
		//��((CCustomDetail*)wininfo.wnd)->GetHeaderWidth(wininfo.hwidth, mHeaderSize);
	}

	// �E�B���h�E���
	xml.AddElem(_T("WINDOWINFO"));
	xml.IntoElem();
	xml.AddElem(_T("TYPE"), wininfo.type);
	if (wininfo.type == eTreeItemType_Title){
		xml.AddElem(_T("TITLE"), wininfo.title);
		xml.AddElem(_T("MONITOR"), wininfo.monitor);
		xml.AddElem(_T("FLAGS"), wininfo.placement.flags);
		xml.AddElem(_T("SHOWCMD"), (wininfo.wnd == NULL) ? 0 : wininfo.wnd->IsWindowVisible()/*wininfo.placement.showCmd*/);
		savePointXml(xml, wininfo.placement.ptMinPosition);
		savePointXml(xml, wininfo.placement.ptMaxPosition);
		saveRectXml(xml, wininfo.placement.rcNormalPosition);
		for (int i = 0; i < mHeaderSize; i++){
			CString str;
			str.Format(_T("HWIDTH%d"), i + 1);
			xml.AddElem(str, wininfo.hwidth[i]);
		}
		xml.AddElem(_T("ZORDER"), wininfo.zorder);
	}
	//��wininfo.treeopen = ((CCustomDetail*)wininfo.wnd)->GetTreeExpandState(treeitem);
	xml.AddElem(_T("TREEOPEN"), wininfo.treeopen);
	xml.OutOfElem();

	// �Ď�������
	xml.AddElem(_T("MONCTRLINFO"));
	xml.IntoElem();
	xml.AddElem(_T("DISPLAY"), monctrl.display);
	if (wininfo.type == eTreeItemType_Item){
		xml.AddElem(_T("MONNAME"), monctrl.mname);
		xml.AddElem(_T("CTRLNAME"), monctrl.cname);
		xml.AddElem(_T("UNIT"), monctrl.unit);
		xml.AddElem(_T("FORMATTYPE"), monctrl.formattype);
		xml.AddElem(_T("FORMAT"), monctrl.format);
		xml.AddElem(_T("GROUP"), monctrl.group);
	}
	xml.OutOfElem();

	// �F���
	xml.AddElem(_T("COLORINFO"));
	xml.IntoElem();
	xml.AddElem(_T("BACK"), color.back);
	xml.AddElem(_T("TEXTBACK"), color.textback);
	xml.AddElem(_T("TEXT"), color.text);
	xml.AddElem(_T("VALUE"), color.value);
	xml.AddElem(_T("UNIT"), color.unit);
	// �t�H���g
	xml.AddElem(_T("LFHEIGHT"), color.font.lfHeight);
	xml.AddElem(_T("LFWIDTH"), color.font.lfWidth);
	xml.AddElem(_T("LFWEIGHT"), color.font.lfWeight);
	xml.AddElem(_T("LFFACENAME"), color.font.lfFaceName);
	xml.OutOfElem();

	// �q�m�[�h�̕ۑ�
	xml.AddElem(_T("SIZE"), (UINT)children.size());
	vector<CTreeNode*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++){
		xml.AddElem(_T("NODE"));
		xml.IntoElem();
		(*itr)->SaveTreeNodeXml(xml);
		xml.OutOfElem();
	}

	return true;
}

/*============================================================================*/
/*! �J�X�^���f�[�^�Ǘ��N���X

-# �c���[�f�[�^���̓Ǎ�

@param		strFile	�Ǎ��t�@�C��
@param		bClear	���s�f�[�^�̍폜�t�^�O

@retval
*/
/*============================================================================*/
bool CCustomDataManager::LoadTreeDataXml(CString strFile, bool bClear)
{
	CMarkup xml;
	CString str;

	// XML�t�@�C����ǂݍ���
	xml.Load(strFile);
	xml.FindElem(_T("ROOT"));
	xml.IntoElem();
	xml.FindElem(_T("VERSION"));
	UINT version = _wtoi(xml.GetData());
	if (version != EN_FILE_VERSION_MAJOR){
		return false;
	}

	if (bClear == true){
		// ���s�̃f�[�^���폜����
		DeleteAllWnd();
		DeleteAllNode();
	}

	xml.FindElem(_T("SIZE"));
	UINT size = _wtoi(xml.GetData());
	for (UINT i = 0; i < size; i++){
		xml.FindElem(_T("EQUIPMENT"));
		xml.IntoElem();
		CTreeNode* pnode = new CTreeNode((HTREEITEM)i, NULL, NULL);
		if (pnode->LoadTreeNodeXml(xml) == false){
			delete pnode;
			xml.OutOfElem();
			break;
		}
		mTreeNode.push_back(pnode);
		xml.OutOfElem();
	}
	return true;
}
/*============================================================================*/
/*! �c���[�m�[�h

-# �m�[�h���̓Ǎ�

@param		xml	XML�N���X

@retval
*/
/*============================================================================*/
bool CTreeNode::LoadTreeNodeXml(CMarkup& xml)
{
	// �E�B���h�E���
	xml.FindElem(_T("WINDOWINFO"));
	xml.IntoElem();
	xml.FindElem(_T("TYPE"));
	wininfo.type = _wtoi(xml.GetData());
	if (wininfo.type == eTreeItemType_Title){
		xml.FindElem(_T("TITLE"));
		swprintf_s(wininfo.title, mTitleSize, _T("%s"), xml.GetData());
		xml.FindElem(_T("MONITOR"));
		wininfo.monitor = _wtoi(xml.GetData());
		wininfo.placement.length = sizeof(WINDOWPLACEMENT);
		xml.FindElem(_T("FLAGS"));
		wininfo.placement.flags = _wtoi(xml.GetData());
		xml.FindElem(_T("SHOWCMD"));
		wininfo.placement.showCmd = _wtoi(xml.GetData());
		loadPointXml(xml, wininfo.placement.ptMinPosition);
		loadPointXml(xml, wininfo.placement.ptMaxPosition);
		loadRectXml(xml, wininfo.placement.rcNormalPosition);
		for (int i = 0; i < mHeaderSize; i++){
			CString str;
			str.Format(_T("HWIDTH%d"), i + 1);
			xml.FindElem(str);
			wininfo.hwidth[i] = _wtoi(xml.GetData());
		}
		xml.FindElem(_T("ZORDER"));
		wininfo.zorder = _wtoi(xml.GetData());
	}
	xml.FindElem(_T("TREEOPEN"));
	wininfo.treeopen = _wtoi(xml.GetData());
	xml.OutOfElem();

	// �Ď�������
	xml.FindElem(_T("MONCTRLINFO"));
	xml.IntoElem();
	xml.FindElem(_T("DISPLAY"));
	swprintf_s(monctrl.display, mNameSize, _T("%s"), xml.GetData());
	if (wininfo.type == eTreeItemType_Item){
		xml.FindElem(_T("MONNAME"));
		swprintf_s(monctrl.mname, mNameSize, _T("%s"), xml.GetData());
		xml.FindElem(_T("CTRLNAME"));
		swprintf_s(monctrl.cname, mNameSize, _T("%s"), xml.GetData());
		xml.FindElem(_T("UNIT"));
		swprintf_s(monctrl.unit, mUnitSize, _T("%s"), xml.GetData());
		xml.FindElem(_T("FORMATTYPE"));
		monctrl.formattype = _wtoi(xml.GetData());
		xml.FindElem(_T("FORMAT"));
		swprintf_s(monctrl.format, mFormatSize, _T("%s"), xml.GetData());
		xml.FindElem(_T("GROUP"));
		swprintf_s(monctrl.group, mNameSize, _T("%s"), xml.GetData());
	}
	xml.OutOfElem();

	// �F���
	xml.FindElem(_T("COLORINFO"));
	xml.IntoElem();
	xml.FindElem(_T("BACK"));
	color.back = _wtoi(xml.GetData());
	xml.FindElem(_T("TEXTBACK"));
	color.textback = _wtoi(xml.GetData());
	xml.FindElem(_T("TEXT"));
	color.text = _wtoi(xml.GetData());
	xml.FindElem(_T("VALUE"));
	color.value = _wtoi(xml.GetData());
	xml.FindElem(_T("UNIT"));
	color.unit = _wtoi(xml.GetData());
	// �t�H���g
	xml.FindElem(_T("LFHEIGHT"));
	color.font.lfHeight = _wtoi(xml.GetData());
	xml.FindElem(_T("LFWIDTH"));
	color.font.lfWidth = _wtoi(xml.GetData());
	xml.FindElem(_T("LFWEIGHT"));
	color.font.lfWeight = _wtoi(xml.GetData());
	xml.FindElem(_T("LFFACENAME"));
	swprintf_s(color.font.lfFaceName, LF_FACESIZE, _T("%s"), xml.GetData());
	xml.OutOfElem();

	// �q�m�[�h�̎擾
	UINT size;
	xml.FindElem(_T("SIZE"));
	size = _wtoi(xml.GetData());
	for (UINT i = 0; i < size; i++) {
		xml.FindElem(_T("NODE"));
		xml.IntoElem();
		CTreeNode* child = new CTreeNode((HTREEITEM)i, NULL, NULL);
		child->LoadTreeNodeXml(xml);
		children.push_back(child);
		xml.OutOfElem();
	}

	return true;
}
