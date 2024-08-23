
// EquipmentStatusDemo2013.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "LogTraceEx.h"
#include "CustomDataManager.h"

// CEquipmentStatusDemo2013App:
// このクラスの実装については、EquipmentStatusDemo2013.cpp を参照してください。
//

class CEquipmentStatusDemo2013App : public CWinApp
{
public:
	CEquipmentStatusDemo2013App();

	void	InitializeApp();
	void	TerminateApp();

	/// モジュールファイルパス
	CString					mAppPath;
	/// AppDataパス
	CString					mAppDataPath;

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CEquipmentStatusDemo2013App theApp;