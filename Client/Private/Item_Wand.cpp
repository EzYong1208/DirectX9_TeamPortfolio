#include "stdafx.h"
#include "..\Public\Item_Wand.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Wand::CItem_Wand(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Wand::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_WAND;
	m_tagItemDesc.pItem_Name = L"Item_Wand";

	//m_tagItemDesc.fAttack_Damage = 7.f;
	//m_tagItemDesc.iItem_Texture_Index = 72;		//	72 ~ 86

	_uint iWandType = rand() % 4;

	switch (iWandType)
	{
	case WAND_AMETHYST:
		m_tagItemDesc.iDurability = 5;
		m_tagItemDesc.fAttack_Damage = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 74;		//	72 ~ 74
		m_tagItemDesc.iPrice = 200;
		break;

	case WAND_EMERALD:
		m_tagItemDesc.iDurability = 5;
		m_tagItemDesc.fAttack_Damage = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 77;		//	75 ~ 77
		m_tagItemDesc.iPrice = 300;
		break;

	case WAND_RUBY:
		m_tagItemDesc.iDurability = 5;
		m_tagItemDesc.fAttack_Damage = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 80;		//	78 ~ 80
		m_tagItemDesc.iPrice = 400;
		break;

	case WAND_EPIC:
		m_tagItemDesc.iDurability = 5;
		m_tagItemDesc.fAttack_Damage = 13.f;
		m_tagItemDesc.iItem_Texture_Index = 83;
		m_tagItemDesc.iPrice = 500;
		break;
	}

	return S_OK;
}

HRESULT CItem_Wand::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Wand::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Wand::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Wand * CItem_Wand::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Wand*		pInstance = new CItem_Wand(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Wand");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Wand::Free()
{
	__super::Free();
}
