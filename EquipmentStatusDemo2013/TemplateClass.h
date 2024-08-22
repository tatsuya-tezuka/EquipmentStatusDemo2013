#pragma once

//------------------------------------------------------------------------------------ 
//	関連ヘッダーファイル
//------------------------------------------------------------------------------------
//#include "Markup.h"

//------------------------------------------------------------------------------------ 
//	グローバル定義
//------------------------------------------------------------------------------------
//static const int mTitleSize = 128;


class CTemplateClass
{
public:

	CTemplateClass();
	virtual ~CTemplateClass();

	/* ------------------------------------------------------------------------------------ */
	/* 定義                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:
	enum { ePopMon = 1, ePopCon };

protected:

	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	UINT			mData;
protected:
	UINT			mNum;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	bool	Create(UINT val);

protected:
	bool	createItem(UINT val);

	/* ------------------------------------------------------------------------------------ */

};

