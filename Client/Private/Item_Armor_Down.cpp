#include "stdafx.h"
#include "..\Public\Item_Armor_Down.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Armor_Down::CItem_Armor_Down(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Armor_Down::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ARMOR_DOWN;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Armor_Down";

	//m_tagItemDesc.fHealth_Point = 5.f;
	//m_tagItemDesc.iItem_Texture_Index = 114;		//	114 ~ 117

	_uint iArmorDownType = rand() % 4;

	switch (iArmorDownType)
	{
	case ARMORDOWN_BRONZE:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 114;
		m_tagItemDesc.iPrice = 150;
		break;

	case ARMORDOWN_IRON:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 115;
		m_tagItemDesc.iPrice = 250;
		break;

	case ARMORDOWN_GOLD:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 116;
		m_tagItemDesc.iPrice = 350;
		break;

	case ARMORDOWN_EPIC:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 117;
		m_tagItemDesc.iPrice = 450;
		break;
	}

	return S_OK;
}

HRESULT CItem_Armor_Down::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Armor_Down::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Armor_Down::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Armor_Down * CItem_Armor_Down::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Armor_Down*		pInstance = new CItem_Armor_Down(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Armor_Down");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Armor_Down::Free()
{
	__super::Free();
}
