
// EquipmentStatusDemo2013.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "LogTraceEx.h"
#include "CustomDataManager.h"
#include "CustomManager.h"
#include "CustomDetail.h"

// CEquipmentStatusDemo2013App:
// このクラスの実装については、EquipmentStatusDemo2013.cpp を参照してください。
//

class CEquipmentStatusDemo2013App : public CWinApp
{
public:
	CEquipmentStatusDemo2013App();

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
protected:
	/// モジュールファイルパス
	CString		mAppPath;
	/// AppDataパス
	CString		mAppDataPath;

	/// カスタムデータ管理関連 
	CCustomDataManager		mDataManager;
	CCustomManager			mCustomManager;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void	InitializeApp();
	void	TerminateApp();

	/// カスタムデータ管理関連
	CCustomDataManager&	GetDataManager() { return mDataManager; }

	CCustomDetail*	CreateEquipment(CTreeNode* pnode);

protected:

	/* ------------------------------------------------------------------------------------ */


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CEquipmentStatusDemo2013App theApp;