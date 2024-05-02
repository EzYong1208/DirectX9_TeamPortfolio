#include "stdafx.h"
#include "..\Public\Item_LegendSword.h"


CItem_LegendSword::CItem_LegendSword(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_LegendSword::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_SWORD;
	m_tagItemDesc.pItem_Name = L"Item_Sword";
	m_tagItemDesc.iDurability = 15;
	m_tagItemDesc.fAttack_Damage = 20.f;
	m_tagItemDesc.iItem_Texture_Index = 15;
	m_tagItemDesc.iPrice = 750;

	return S_OK;
}

HRESULT CItem_LegendSword::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_LegendSword::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_LegendSword::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_LegendSword * CItem_LegendSword::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_LegendSword*	pInstance = new CItem_LegendSword(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_LegendSword");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_LegendSword::Free()
{
	__super::Free();
}
