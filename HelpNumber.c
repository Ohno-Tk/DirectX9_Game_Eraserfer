/*=============================================================================

		汚れ数[ HelpNumber.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "main.h"
#include "HelpNumber.h"
#include "Born.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/number000.png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/yogore.png"

#define MAX_TEXTURE ( 2 )	//	最大テクスチャ数

#define SCORE_DIGIT ( 2 )	//	何桁の数字の表示

#define SCORE_MAX ( 9999 )	//	スコアの最大値

#define ADD_SCORE ( 10 )	//	加算するスコアの値


#define POLYGON00_X ( SCREEN_WIDTH - 80.0f )		//	スコアのX
#define POLYGON00_Y ( 50.0f )		//	スコアのY
#define POLYGON00_WIDTH  ( 70.0f )	//	スコアのWidth
#define POLYGON00_HEIGHT ( 70.0f )	//	スコアのHeight

#define POLYGON01_X ( SCREEN_WIDTH - 220.0f )		//	スコア文字のX
#define POLYGON01_Y ( -10.0f )		//	スコア文字のY
#define POLYGON01_WIDTH  ( 150.0f )	//	スコア文字のWidth
#define POLYGON01_HEIGHT ( 75.0f )	//	スコア文字のHeight

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

//	頂点の作成
HRESULT MakeVertexHelpNumber( LPDIRECT3DDEVICE9 pDevice );

//	頂点の変更
void VerTexHelpNumber( VERTEX_2D* pVtx , int Cnt , int num );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferScore = NULL;	//	頂点バッファインタフェースへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureScore[ MAX_TEXTURE ] = { NULL };//	テクスチャインターフェース

D3DXCOLOR g_ScoreColor;	//	色

int g_Number;	//	人数

/*-----------------------------------------------------------------------------
 関数名:	void InitHelpNumber( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitHelpNumber( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	テクスチャのエラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureScore[ 0 ] ) ) )
	{

		MessageBox( NULL , "[ HelpNumber.cpp ]\n POLYGON00_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureScore[ 1 ] ) ) )
	{

		MessageBox( NULL , "[ HelpNumber.cpp ]\n POLYGON01_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	頂点の作成
	MakeVertexHelpNumber( pDevice );


	//	変数初期化

	//	色
	g_ScoreColor = D3DXCOLOR( 255 , 255 , 255 , 255 );

	//	スコア
	g_Number = 11;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitHelpNumber( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitHelpNumber( void )
{

	if(g_pVtxBufferScore != NULL)	//頂点バッファのインターフェースポインタの解放
	{
		g_pVtxBufferScore -> Release();
		g_pVtxBufferScore  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureScore[ Cnt ] != NULL )	//	テクスチャポリゴン開放
		{
			g_pTextureScore[ Cnt ] -> Release();
			g_pTextureScore[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdateHelpNumber( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateHelpNumber( void )
{

	int num;	//	数字を表示する変数
	int value = g_Number;


	//	仮想アドレスを取得するポインタ変数
	VERTEX_2D* pVtx;


	//バッファをロックし仮想アドレスを取得する
	g_pVtxBufferScore -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		num = value % 10;
		value /= 10;

		//	頂点の変更
		VerTexHelpNumber( pVtx , Cnt , num );

	}	//	end of for


	g_pVtxBufferScore -> Unlock(); //これ以降触れてはいけない


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawHelpNumber( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawHelpNumber( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	ストリームを設定する
	pDevice -> SetStreamSource( 0 , g_pVtxBufferScore , 0 , sizeof( VERTEX_2D ) );

	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureScore[ 0 ] );


	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		//	ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON);

	}	//	end of for


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureScore[ 1 ] );

	//	ポリゴンの描画
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , SCORE_DIGIT * NUM_VERTEX , NUM_POLYGON);


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	HRESULT MakeVertexScore( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice	デバイス
 戻り値:	良い場合	return S_OK;
			ダメな場合	return E_FAIL;
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelpNumber( LPDIRECT3DDEVICE9 pDevice )
{

	int num;	//	数字を表示する変数
	int value = g_Number;


	//	仮想アドレスを取得するポインタ変数
	VERTEX_2D* pVtx;


	// FAILEDマクロでエラーチェック
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * SCORE_DIGIT * MAX_TEXTURE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferScore , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	// バッファをロックし、仮想アドレスを取得
	g_pVtxBufferScore -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		num = value % 10;
		value /= 10;

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( POLYGON00_X                   - Cnt * POLYGON00_WIDTH , POLYGON00_Y                    , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( POLYGON00_X + POLYGON00_WIDTH - Cnt * POLYGON00_WIDTH , POLYGON00_Y                    , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( POLYGON00_X                   - Cnt * POLYGON00_WIDTH , POLYGON00_Y + POLYGON00_HEIGHT , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( POLYGON00_X + POLYGON00_WIDTH - Cnt * POLYGON00_WIDTH , POLYGON00_Y + POLYGON00_HEIGHT , 0.0f );

		//	座標変換済み頂点フラグの設定
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		//	頂点色の設定
		pVtx[ 0 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 1 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 2 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 3 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );

		//	テクスチャ座標の設定
		pVtx[ 0 ].tex = D3DXVECTOR2( 0.1f * num        , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0.1f * num        , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 1 );

		pVtx += 4;	//	ポインタをずらす

	}	//	end of for


	//	頂点座標の設定
	pVtx[ 0 ].pos = D3DXVECTOR3( POLYGON01_X                   , POLYGON01_Y                    , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( POLYGON01_X + POLYGON01_WIDTH , POLYGON01_Y                    , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( POLYGON01_X                   , POLYGON01_Y + POLYGON01_HEIGHT , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( POLYGON01_X + POLYGON01_WIDTH , POLYGON01_Y + POLYGON01_HEIGHT , 0.0f );

	//	座標変換済み頂点フラグの設定
	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	//	頂点色の設定
	pVtx[ 0 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
	pVtx[ 1 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
	pVtx[ 2 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
	pVtx[ 3 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );

	//	テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );


	g_pVtxBufferScore -> Unlock(); //これ以降触れてはいけない

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void VerTexScore( VERTEX_2D* pVtx , int Cnt , int num )
 引数:		VERTEX_2D* pVtx		仮想アドレスを取得するポインタ変数
			int Cnt				スコアのカウンタ
			int num				テクスチャをずらす変数
 戻り値:	
 説明:		頂点の変更
-----------------------------------------------------------------------------*/
void VerTexHelpNumber( VERTEX_2D* pVtx , int Cnt , int num )
{

	//	pVtxをCnt分ずらす
	pVtx += Cnt * NUM_VERTEX;


	//	頂点色の設定
	pVtx[ 0 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );

	//	テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.1f * num        , 0 );
	pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 0 );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.1f * num        , 1 );
	pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 1 );


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	int *GetHelpNumber( void )
 引数:		
 戻り値:	return &g_Number;
 説明:		スコア情報の取得
-----------------------------------------------------------------------------*/
int *GetHelpNumber( void )
{

	return &g_Number;

}	//	end of func
