/*=============================================================================

		ゲーム[ game.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/12/15
-------------------------------------------------------------------------------
	■　Update
=============================================================================*/
/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

#include "camera.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "skydome.h"
#include "Shadow.h"
#include "Player.h"
#include "Enemy1.h"
#include "Cleaner.h"
#include "Born.h"
#include "JumpRamp.h"
#include "Help.h"
#include "Particle.h"

#include "HelpNumber.h"
#include "Gauge.h"
#include "CountDown.h"
#include "Pause.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 関数名:	void InitGame( void )
 引数:		なし
 戻り値:	なし
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitGame( void )
{

	InitCamera();	//	カメラの初期化

	InitMeshField();		//	メッシュフィールドの初期化

	InitMeshWall();		//	メッシュウォールの初期化

	InitSkydome();		//	スカイドームの初期化

	InitShadow();	//	影の初期化

	InitHelpNumber();

	InitHelp();		//	ヘルプの初期化

	InitBorn();		//	助け人の初期化

	InitPlayer();		//	プレイヤーの初期化

	InitEnemy1();	//	汚れ増やす敵の初期化

	InitCleaner();	//	黒板消しクリーナーの初期化

	InitJumpRamp();		//	ジャンプ台の初期化

	InitParticle();		//	パーティクルの初期化

	InitCountDown();		//	カウントダウンの初期化

	InitGauge();		//	ゲージの初期化

	InitPause();		//	ポーズの初期化


	//	音楽再生
	PlaySound( SOUND_LABEL_BGM_GAME );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitGame( void )
 引数:		なし
 戻り値:	なし
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitGame( void )
{

	UninitMeshField();		//	メッシュフィールドの終了

	UninitMeshWall();	//	メッシュウォールの終了

	UninitSkydome();		//	スカイドームの終了

	UninitShadow();	//	影の終了

	UninitPlayer();	//	プレイヤーの終了

	UninitEnemy1();	//	汚れ増やす敵の終了

	UninitCleaner();	//	黒板消しクリーナーの終了

	UninitBorn();	//	助け人の終了

	UninitJumpRamp();	//	ジャンプ台の終了

	UninitHelp();	//	ヘルプの終了

	UninitParticle();	//	パーティクルの終了

	UninitHelpNumber();

	UninitGauge();	//	ゲージの終了

	UninitCountDown();	//	カウントダウンの終了

	UninitPause();	//	ポーズの終了


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdateGame( void )
 引数:		なし
 戻り値:	なし
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateGame( void )
{

	//	スタートしたかの情報取得
	bool *Start = GetStart();


	//	ポーズフラグ情報の取得
	bool *Pause = GetPauseFlag();

	int *HelpNumber = GetHelpNumber();


	if( *Start == true && *Pause == false )
	{

		UpdateMeshField();		//	メッシュフィールドの更新

		UpdateMeshWall();	//	メッシュウォールの更新

		UpdateSkydome();		//	スカイドームの更新

		UpdateShadow();	//	影の更新

		UpdatePlayer();	//	プレイヤーの更新

		UpdateEnemy1();	//	汚れ増やす敵の更新

		UpdateCleaner();	//	黒板消しクリーナーの更新

		UpdateBorn();	//	助け人の更新

		UpdateJumpRamp();	//	ジャンプ台の更新

		UpdateHelp();	//	ヘルプの更新

		UpdateParticle();	//	パーティクルの更新

		UpdateHelpNumber();

		UpdateGauge();	//	ゲージの更新

	}	//	end of if

	UpdateCountDown();	//	カウントダウンの更新

	UpdatePause();	//	ポーズの更新



	ENEMY *Enemy = GetEnemy1();

	//	画面遷移
	if( *HelpNumber <= 0  )
	{

		*HelpNumber = 0;

		Enemy -> Use = false;


		SetFade( FADE_OUT , MODE_RESULT );

		//	何番目の音を止める
		StopSound( SOUND_LABEL_BGM_GAME );

	}

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawGame( void )
 引数:		なし
 戻り値:	なし
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawGame( void )
{

	DrawMeshField();		//	メッシュフィールドの描画

	DrawSkydome();		//	スカイドームの描画

	DrawMeshWall();		//	メッシュウォールの描画

	DrawShadow();	//	影の描画

	DrawPlayer();		//	プレイヤーの描画

//	DrawEnemy1();	//	汚れ増やす敵の描画

	DrawCleaner();	//	黒板消しクリーナーの描画

	DrawBorn();		//	助け人の描画

//	DrawJumpRamp();		//	ジャンプ台の描画

	DrawHelp();		//	ヘルプの描画

	DrawParticle();		//	パーティクルの描画

	DrawHelpNumber();

	DrawGauge();		//	ゲージの描画

	DrawCountDown();		//	カウントダウンの描画

	DrawPause();		//	ポーズの描画


}	//	end of func