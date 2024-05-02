#include "stdafx.h"
#include "..\Public\Item_Bomb.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Bomb::CItem_Bomb(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Bomb::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_USEABLE;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Bomb";

	//m_tagItemDesc.fAttack_Damage = 6.f;
	//m_tagItemDesc.iItem_Texture_Index = 97;		//	97 ~ 104

	_uint iBombType = rand() % 4;

	switch (iBombType)
	{
	case BOMB_BLACK:
		m_tagItemDesc.fAttack_Damage = 6.f;
		m_tagItemDesc.iItem_Texture_Index = 97;		//	97 101
		m_tagItemDesc.iPrice = 100;
		break;

	case BOMB_RED:
		m_tagItemDesc.fAttack_Damage = 6.f;
		m_tagItemDesc.iItem_Texture_Index = 98;		//	98 102
		m_tagItemDesc.iPrice = 120;
		break;

	case BOMB_BLUE:
		m_tagItemDesc.fAttack_Damage = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 99;		//	99 103
		m_tagItemDesc.iPrice = 140;
		break;

	case BOMB_PURPLE:
		m_tagItemDesc.fAttack_Damage = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 100;	//	100 104
		m_tagItemDesc.iPrice = 160;
		break;
	}

	return S_OK;
}

HRESULT CItem_Bomb::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Bomb::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Bomb::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Bomb * CItem_Bomb::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Bomb*		pInstance = new CItem_Bomb(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Bomb");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Bomb::Free()
{
	__super::Free();
}
