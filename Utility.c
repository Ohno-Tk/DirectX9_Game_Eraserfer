/*=============================================================================

		[ Utility.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "Utility.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 �֐���:	bool RectangleCollision( D3DXVECTOR2 Pos_A , D3DXVECTOR2 Size_A , D3DXVECTOR2 Pos_B , D3DXVECTOR2 Size_B )
 ����:		D3DXVECTOR2 Pos_A	����A�̍��W
			D3DXVECTOR2 Size_A	����A�̑傫��
			D3DXVECTOR2 Pos_B	����B�̍��W
			D3DXVECTOR2 Size_B	����B�̑傫��

 �߂�l:	�������Ă���ꍇ	return true;
			�������Ă��Ȃ��ꍇ	return false;

 ����:		��`�Ƌ�`�̓����蔻��
-----------------------------------------------------------------------------*/
bool RectangleCollision( D3DXVECTOR2 Pos_A , D3DXVECTOR2 Size_A , D3DXVECTOR2 Pos_B , D3DXVECTOR2 Size_B )
{

	float x[] = { Pos_A.x , Pos_A.x +  Size_A.x , Pos_B.x , Pos_B.x +  Size_B.x };
	float y[] = { Pos_A.y , Pos_A.y +  Size_A.y , Pos_B.y , Pos_B.y +  Size_B.y };

	//	��`�Ƌ�`�̓����蔻��
	if( x[ 0 ] < x[ 3 ] && x[ 2 ] < x[ 1 ] && y[ 0 ] < y[ 3 ] && y[ 2 ] < y[ 1 ] )
	{

		return true;

	}	//	end of if

	return false;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	bool CircleCollision( D3DXVECTOR2 Pos_A , D3DXVECTOR2 Pos_B , float Radius_A , float Radius_B )
 ����:		D3DXVECTOR2 Pos_A	����A�̍��W
			D3DXVECTOR2 Pos_B	����B�̍��W
			float Radius_A		����A�̔��a
			float Radius_B		����B�̔��a

 �߂�l:	�������Ă���ꍇ	return true;
			�������Ă��Ȃ��ꍇ	return false;

 ����:		�~�Ɖ~�̓����蔻��
-----------------------------------------------------------------------------*/
bool CircleCollision( D3DXVECTOR2 Pos_A , D3DXVECTOR2 Pos_B , float Radius_A , float Radius_B )
{

	//	�~�Ɖ~�̓����蔻��
	if( ( Pos_B.x - Pos_A.x ) * ( Pos_B.x - Pos_A.x ) + ( Pos_B.y - Pos_A.y ) * ( Pos_B.y - Pos_A.y ) <= ( Radius_A + Radius_B ) * ( Radius_A + Radius_B ) )
	{

		return true;

	}	//	end of if

	return false;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	bool SphereCollision( D3DXVECTOR3 Pos_A , D3DXVECTOR3 Pos_B , float Radius_A , float Radius_B )
 ����:		D3DXVECTOR3 Pos_A	����A�̍��W
			D3DXVECTOR3 Pos_B	����B�̍��W
			float Radius_A		����A�̔��a
			float Radius_B		����B�̔��a

 �߂�l:	�������Ă���ꍇ	return true;
			�������Ă��Ȃ��ꍇ	return false;

 ����:		���Ƌ��̓����蔻��
-----------------------------------------------------------------------------*/
bool SphereCollision( D3DXVECTOR3 Pos_A , D3DXVECTOR3 Pos_B , float Radius_A , float Radius_B )
{

	//	���Ƌ��̓����蔻��
	if( ( Pos_B.x - Pos_A.x ) * ( Pos_B.x - Pos_A.x ) + ( Pos_B.y - Pos_A.y ) * ( Pos_B.y - Pos_A.y ) + ( Pos_B.z - Pos_A.z ) * ( Pos_B.z - Pos_A.z ) <= ( Radius_A + Radius_B ) * ( Radius_A + Radius_B ) )
	{

		return true;

	}	//	end of if

	return false;

}	//	end of func