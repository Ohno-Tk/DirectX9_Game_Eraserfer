/*=============================================================================

		ゲージ[ Gauge.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/02/01
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	二重インクルード防止
-----------------------------------------------------------------------------*/
#ifndef _GAUGE_H_
#define _GAUGE_H_

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
void InitGauge( void );		//	ゲージの初期化
void UninitGauge( void );	//	ゲージの終了
void UpdateGauge( void );	//	ゲージの更新
void DrawGauge( void );		//	ゲージの描画


#endif