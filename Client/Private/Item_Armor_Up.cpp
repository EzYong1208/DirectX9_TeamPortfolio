#include "stdafx.h"
#include "..\Public\Item_Armor_Up.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Armor_Up::CItem_Armor_Up(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Armor_Up::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ARMOR_UP;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Armor_Up";

	//m_tagItemDesc.fHealth_Point = 5.f;
	//m_tagItemDesc.iItem_Texture_Index = 110;		//	110 ~ 113

	_uint iArmorUpType = rand() % 4;

	switch (iArmorUpType)
	{
	case ARMORUP_BRONZE:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 110;
		m_tagItemDesc.iPrice = 150;
		break;

	case ARMORUP_IRON:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 111;
		m_tagItemDesc.iPrice = 250;
		break;

	case ARMORUP_GOLD:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 112;
		m_tagItemDesc.iPrice = 350;
		break;

	case ARMORUP_EPIC:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 113;
		m_tagItemDesc.iPrice = 450;
		break;
	}

	return S_OK;
}

HRESULT CItem_Armor_Up::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Armor_Up::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Armor_Up::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Armor_Up * CItem_Armor_Up::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Armor_Up*		pInstance = new CItem_Armor_Up(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Armor_Up");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Armor_Up::Free()
{
	__super::Free();
}
