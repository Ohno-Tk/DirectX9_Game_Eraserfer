/*=============================================================================

		ゲージ[ Gauge.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/02/01
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Gauge.h"
#include "Player.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/Gauge.png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/Gauge_bar.jpg"

#define MAX_TEXTURE ( 2 )	//	テクスチャの最大数

#define MAX_GAUGE ( 2 )	//	最大ゲージ本数

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR2 Pos;	//	座標
	D3DXVECTOR2 Size;	//	大きさ
	D3DXCOLOR Color;	//	色
	int NowLife;		//	現在のライフ
	int MaxLife;		//	最大ライフ
	float Maxlength;	//	最大の大きさ
	bool Use;	//	使用フラグ
}GAUGE;

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

//	頂点の作成
HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice );

//	頂点の変更
void VerTexGauge( VERTEX_2D* pVtx , int Cnt );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGauge = NULL;	//	頂点バッファインタフェースへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureGauge[ MAX_TEXTURE ] = { NULL };	//	テクスチャインターフェース

GAUGE g_Gauge[ MAX_GAUGE ];	//	構造体

/*-----------------------------------------------------------------------------
 関数名:	void InitGauge( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitGauge( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	プレイヤー情報の取得
	PLAYER *Player = GetPlayer();


	//	テクスチャのエラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureGauge[ 0 ] ) ) )
	{
		MessageBox( NULL , "[ Gauge.cpp ]\n POLYGON00_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureGauge[ 1 ] ) ) )
	{
		MessageBox( NULL , "[ Gauge.cpp ]\n POLYGON01_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	構造体初期化

	//	プレイヤー
	g_Gauge[ 0 ].Pos = D3DXVECTOR2( 0.0f , 50.0f );
	g_Gauge[ 0 ].Size = D3DXVECTOR2( 350.0f , 25.0f );
	g_Gauge[ 0 ].Color = D3DXCOLOR( 255 , 255 , 255 , 255 );


	g_Gauge[ 1 ].Pos = D3DXVECTOR2( g_Gauge[ 0 ].Pos.x + 11.0f , g_Gauge[ 0 ].Pos.y + 3.0f );
	g_Gauge[ 1 ].Size = D3DXVECTOR2( g_Gauge[ 0 ].Size.x - 18.0f , g_Gauge[ 0 ].Size.y - 5.0f );
	g_Gauge[ 1 ].Color = D3DXCOLOR( 0 , 0 , 255 , 255 );
	g_Gauge[ 1 ].MaxLife = 10;
	g_Gauge[ 1 ].NowLife = Player -> Life;
	g_Gauge[ 1 ].Maxlength = g_Gauge[ 1 ].Size.x;


	//	頂点の作成
	MakeVertexGauge( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitGauge( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitGauge( void )
{

	if(g_pVtxBufferGauge != NULL)	//頂点バッファのインターフェースポインタの解放
	{
		g_pVtxBufferGauge -> Release();
		g_pVtxBufferGauge  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureGauge[ Cnt ] != NULL )	//	テクスチャポリゴン開放
		{
			g_pTextureGauge[ Cnt ] -> Release();
			g_pTextureGauge[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdateGauge( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateGauge( void )
{

	float Life;

	//	仮想アドレスを取得するポインタ変数
	VERTEX_2D* pVtx;

	//	プレイヤー情報の取得
	PLAYER *Player = GetPlayer();


	//バッファをロックし仮想アドレスを取得する
	g_pVtxBufferGauge -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_GAUGE ; Cnt++ )
	{

		
		//	頂点の変更
		VerTexGauge( pVtx , Cnt );

	}	//	end of for


	g_pVtxBufferGauge -> Unlock(); //これ以降触れてはいけない


	//	ゲージが何割減ったかを求める
	Life = ( float )Player -> Life / g_Gauge[ 1 ].MaxLife;

	//	ゲージの長さを変更
	g_Gauge[ 1 ].Size.x = Life * g_Gauge[ 1 ].Maxlength;


	if( Player -> Life >= 10 )
	{

		g_Gauge[ 1 ].Color = D3DXCOLOR( 255 , 0 , 0 , 255 );

	}	//	end of if
	else
	{

		g_Gauge[ 1 ].Color = D3DXCOLOR( 0 , 0 , 255 , 255 );

	}
	
}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawGauge( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawGauge( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	ストリームを設定する
	pDevice -> SetStreamSource( 0 , g_pVtxBufferGauge , 0 , sizeof( VERTEX_2D ) );


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureGauge[ 0 ] );

	//	ポリゴンの描画
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureGauge[ 1 ] );

	//	ポリゴンの描画
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 , NUM_POLYGON);



}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice	デバイス
 戻り値:	良い場合	return S_OK;
			ダメな場合	return E_FAIL;
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice )
{

	//	仮想アドレスを取得するポインタ変数
	VERTEX_2D* pVtx;


	// FAILEDマクロでエラーチェック
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * MAX_GAUGE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferGauge , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	float Life;

	//	プレイヤー情報の取得
	PLAYER *Player = GetPlayer();

	//	ゲージが何割減ったかを求める
	Life = ( float )Player -> Life / g_Gauge[ 1 ].MaxLife;

	//	ゲージの長さを変更
	g_Gauge[ 1 ].Size.x = Life * g_Gauge[ 1 ].Maxlength;


	// バッファをロックし、仮想アドレスを取得
	g_pVtxBufferGauge -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_GAUGE ; Cnt++ )
	{

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );

		//	座標変換済み頂点フラグの設定
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		//	頂点色の設定
		pVtx[ 0 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 1 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 2 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 3 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );

		//	テクスチャ座標の設定
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;	//	ポインタをずらす

	}	//	end of for



	g_pVtxBufferGauge -> Unlock(); //これ以降触れてはいけない

	return S_OK;


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void VerTexGauge( VERTEX_2D* pVtx , int Cnt )
 引数:		VERTEX_2D* pVtx , int Cnt
 戻り値:	
 説明:		頂点の変更
-----------------------------------------------------------------------------*/
void VerTexGauge( VERTEX_2D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;


	//	頂点座標の設定
	pVtx[ 0 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );


	//	頂点色の設定
	pVtx[ 0 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );

}	//	end of func