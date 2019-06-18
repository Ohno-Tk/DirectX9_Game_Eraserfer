/*=============================================================================

		パーティクル[ Particle.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/11/16
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
						scanf のwarning防止 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "particle.h"
#include "input.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/effect000.jpg"

#define MAX_PARTICLE ( 500 )	//	パーティクル最大数

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/
typedef struct
{
	WORLD World;	//	ワールド変換用変数
	D3DXVECTOR3 Move;	//	移動量
	D3DXCOLOR Color;	//	カラー
	int Life;	//	寿命
	float length;	//	長さ
	float Radius;	//半径
	float RadiusValue;	//半径の変化量
	bool Use;	//	使用フラグ
}PARTICLE;

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

//	頂点の作成
HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice );

//	座標変更
void VerTexParticle( VERTEX_3D* pVtx , int Cnt );

//	デバッグ用
void DegubParticle( void );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferParticle = NULL;	//	頂点バッファインタフェースへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;//	テクスチャインターフェース

#ifdef _DEBUG

	LPD3DXFONT g_pFontParticle = NULL;

#endif	//	_DEBUG

PARTICLE g_Particle[ MAX_PARTICLE ];

D3DXVECTOR3 g_Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
float g_ScatteringWidth  = 1.0f;	//	飛散幅
float g_Legth  = 100.0f;	//	長さ

/*-----------------------------------------------------------------------------
 関数名:	void InitParticle( void )
 引数:		なし
 戻り値:	なし
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitParticle( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	現在の時刻を取得
	srand((unsigned)time(NULL));


	//	エラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureParticle  ) ) )
	{

		MessageBox( NULL , "[ Particle.cpp ]\n POLYGON00_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	頂点の作成
	MakeVertexParticle( pDevice );


	//	構造体初期化
	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		//	座標
		g_Particle[ Cnt ].World.Pos.x = 0.0f;
		g_Particle[ Cnt ].World.Pos.y = 0.0f;
		g_Particle[ Cnt ].World.Pos.z = 0.0f;

		//	回転量
		g_Particle[ Cnt ].World.Rot.x = 0.0f;
		g_Particle[ Cnt ].World.Rot.y = 0.0f;
		g_Particle[ Cnt ].World.Rot.z = 0.0f;

		//	拡大率
		g_Particle[ Cnt ].World.Scl.x = 1.0f;
		g_Particle[ Cnt ].World.Scl.y = 1.0f;
		g_Particle[ Cnt ].World.Scl.z = 1.0f;

		//	移動量
		g_Particle[ Cnt ].Move.x = 0.0f;
		g_Particle[ Cnt ].Move.y = 0.0f;
		g_Particle[ Cnt ].Move.z = 0.0f;

		//	カラー
		g_Particle[ Cnt ].Color.r = 10;
		g_Particle[ Cnt ].Color.g = 10;
		g_Particle[ Cnt ].Color.b = 10;
		g_Particle[ Cnt ].Color.a = 255;

		//	寿命
		g_Particle[ Cnt ].Life = 50;

		//	長さ
		g_Particle[ Cnt ].length = 0.5f;

		//半径
		g_Particle[ Cnt ].Radius = 3.0f;

		//半径の変化量
		g_Particle[ Cnt ].RadiusValue = 0.0f;

		//	使用フラグ
		g_Particle[ Cnt ].Use = false;

	}	//	end of for

#ifdef _DEBUG
	//	フォントの設定
	D3DXCreateFont( pDevice ,
				18 ,	//	文字高さ
				0 ,	//	文字幅
				0 ,	//	文字の太さ
				0 ,	//	ミップマップ
				FALSE ,	//	イタリック
				SHIFTJIS_CHARSET ,
				OUT_DEFAULT_PRECIS ,
				DEFAULT_QUALITY ,
				DEFAULT_PITCH ,
				"Terminal" ,
				&g_pFontParticle );
#endif


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitParticle( void )
 引数:		なし
 戻り値:	なし
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitParticle( void )
{

	if( g_pVtxBufferParticle != NULL )	//	頂点バッファインタフェース開放
	{
		g_pVtxBufferParticle -> Release();
		g_pVtxBufferParticle = NULL;

	}	//	end of if

	if( g_pTextureParticle != NULL )	//	テクスチャポリゴン開放
	{
		g_pTextureParticle -> Release();
		g_pTextureParticle = NULL;

	}	//	end of if

#ifdef _DEBUG

	if( g_pFontParticle != NULL )
	{

		g_pFontParticle -> Release();
		g_pFontParticle = NULL;

	}	//	end of if

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdateParticle( void )
 引数:		なし
 戻り値:	なし
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateParticle( void )
{

	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;


	//	バッファをロックし仮想アドレスを取得する
	g_pVtxBufferParticle -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		if( g_Particle[ Cnt ].Use == true )
		{
			//	座標移動
			g_Particle[ Cnt ].World.Pos += g_Particle[ Cnt ].Move;

			//	半径を減らす
			g_Particle[ Cnt ].Radius -= g_Particle[ Cnt ].RadiusValue;

			//	寿命を減らす
			g_Particle[ Cnt ].Life--;

			if( g_Particle[ Cnt ].Life <= 0 )
			{
				g_Particle[ Cnt ].Use = false;

			}	//	end of if

			//	頂点変更
			VerTexParticle( pVtx , Cnt );

		}	//	end of if

	}	//	end of for

	//	バッファのアンロック
	g_pVtxBufferParticle -> Unlock();

#ifdef _DEBUG


//	SetParticle( D3DXVECTOR3( 0.0f ,15.0f , -800.0f ) , g_Rot , D3DXCOLOR( 0.0f , 0.0f , 1.0f , 1.0f ) , g_ScatteringWidth , 100 , g_Legth , 2.0f );


	if( GetKeyboardPress( DIK_1 ) )
	{
		g_Rot.x += 0.1f;
	}
	if( GetKeyboardPress( DIK_2 ) )
	{
		g_Rot.x -= 0.1f;
	}
	if( GetKeyboardPress( DIK_3 ) )
	{
		g_Legth += 0.1f;
	}
	if( GetKeyboardPress( DIK_4 ) )
	{
		g_Legth -= 0.1f;
	}
	if( GetKeyboardPress( DIK_5 ) )
	{
		g_ScatteringWidth += 0.01f;
	}
	if( GetKeyboardPress( DIK_6 ) )
	{
		g_ScatteringWidth -= 0.01f;
	}

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawParticle( void )
 引数:		なし
 戻り値:	なし
 説明:		パーティクルの描画
-----------------------------------------------------------------------------*/
void DrawParticle( void )
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	パイプラインのストリーム
	pDevice -> SetStreamSource( 0 , g_pVtxBufferParticle , 0 , sizeof( VERTEX_3D ));

	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureParticle );

	//	aブレンド（加算合成）
	pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );	//	Initに書いてあるので省略可
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );	//	Initに書いてあるので省略可
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );

	//	Zバッファ
	pDevice -> SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE );
	pDevice -> SetRenderState( D3DRS_ZWRITEENABLE , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{

		//	逆行列ありのワールド座標変換
		SetWorldInv( g_Particle[ Cnt ].World.Pos , g_Particle[ Cnt ].World.Scl );


		if( g_Particle[ Cnt ].Use == true )
		{
			//	ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}	//	end of for


	//	元に戻す
	pDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

	pDevice -> SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE );
	pDevice -> SetRenderState( D3DRS_ZWRITEENABLE , TRUE );


#ifdef _DEBUG

	DegubParticle();

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice
 戻り値:	なし
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	仮想アドレスを取得するポインタ変数

	//	頂点バッファの生成
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_PARTICLE , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferParticle , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	バッファをロックし仮想アドレスを取得する
	g_pVtxBufferParticle -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int CntParticle = 0 ; CntParticle < MAX_PARTICLE ; CntParticle++ )
	{

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( -g_Particle[ CntParticle ].Radius , g_Particle[ CntParticle ].Radius  , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( g_Particle[ CntParticle ].Radius  , g_Particle[ CntParticle ].Radius  , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -g_Particle[ CntParticle ].Radius , 0.0f                              , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( g_Particle[ CntParticle ].Radius  , 0.0f                              , 0.0f );

		//	法線の設定
		pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );

		//	頂点色の設定
		pVtx[ 0 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 1 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 2 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 3 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );

		//	テクスチャ座標の設定
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;	//	pVtxをずらす

	}	//	end of for

	//	バッファのアンロック
	g_pVtxBufferParticle -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void VerTexParticle( VERTEX_3D* pVtx , int Cnt )
 引数:		VERTEX_3D* pVtx
			int CntParticle
 戻り値:	なし
 説明:		頂点変更
-----------------------------------------------------------------------------*/
void VerTexParticle( VERTEX_3D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;

	//	頂点座標の設定
	pVtx[ 0 ].pos = D3DXVECTOR3( -g_Particle[ Cnt ].Radius , g_Particle[ Cnt ].Radius  , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3(  g_Particle[ Cnt ].Radius , g_Particle[ Cnt ].Radius  , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( -g_Particle[ Cnt ].Radius , 0.0f                      , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3(  g_Particle[ Cnt ].Radius , 0.0f                      , 0.0f );


	//	頂点色の設定
	pVtx[ 0 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void SetParticle( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXCOLOR Color , float ScatteringWidth , int Life , float Length , float Radius )
 引数:		D3DXVECTOR3 Pos			座標
			D3DXVECTOR3 Rot			角度
			D3DXCOLOR Color			カラー
			float ScatteringWidth	飛散幅( 1.0f ~ 6.28 )
			int Life				寿命
			float Length			長さ
			float Radius			半径
 戻り値:	なし
 説明:		パーティクルのセット
-----------------------------------------------------------------------------*/
void SetParticle( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXCOLOR Color , float ScatteringWidth , int Life , float Length , float Radius )
{

	int ScatWidth = ( int )( ScatteringWidth * 100 );	//	飛散幅の数値を整数にする

	//	角度をランダムで求める
	float Dam = ( rand()%ScatWidth - 314 ) * 0.01f;


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		if( g_Particle[ Cnt ].Use == false )
		{

			//	座標
			g_Particle[ Cnt ].World.Pos = Pos;

			//	移動量
			g_Particle[ Cnt ].Move.x = cosf( Dam + Rot.x ) * g_Particle[Cnt].length;
			g_Particle[ Cnt ].Move.y = sinf( Dam + Rot.x ) * g_Particle[Cnt].length;

			//	カラー
			g_Particle[ Cnt ].Color = Color;

			//	寿命
			g_Particle[ Cnt ].Life = Life;

			//半径
			g_Particle[ Cnt ].Radius = Radius;

			//半径の変化量
			g_Particle[ Cnt ].RadiusValue = g_Particle[ Cnt ].Radius / g_Particle[ Cnt ].Life;

			//	使用フラグ
			g_Particle[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func

#ifdef _DEBUG

/*-----------------------------------------------------------------------------
 関数名:	void DegubParticle( void )
 引数:		
 戻り値:	なし
 説明:		デバッグ用
-----------------------------------------------------------------------------*/
void DegubParticle( void )
{

	int Height = 200;
	D3DXCOLOR Color = D3DXCOLOR( 255 , 255 , 255 , 255 );

	RECT rect00 = { 0 , Height , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect01 = { 0 , Height + 15 , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect02 = { 0 , Height + 30 , SCREEN_WIDTH , SCREEN_HEIGHT };

	char aStr00[ 256 ] , aStr01[ 256 ] , aStr02[ 256 ];

	sprintf( &aStr00[ 0 ] , "[ 角度 ] ( %f : %f : %f )" , g_Rot.x , g_Rot.y , g_Rot.z );
	sprintf( &aStr01[ 0 ] , "[ 飛散幅 ] ( %.3f )" , g_ScatteringWidth );
	sprintf( &aStr02[ 0 ] , "[ 長さ ] ( %.3f )" , g_Legth );

	g_pFontParticle -> DrawText( NULL ,
						&aStr00[ 0 ] ,
						-1 ,
						&rect00 ,
						DT_LEFT ,
						Color );

	g_pFontParticle -> DrawText( NULL ,
						&aStr01[ 0 ] ,
						-1 ,
						&rect01 ,
						DT_LEFT ,
						Color );

	g_pFontParticle -> DrawText( NULL ,
						&aStr02[ 0 ] ,
						-1 ,
						&rect02 ,
						DT_LEFT ,
						Color );


}	//	end of func

#endif