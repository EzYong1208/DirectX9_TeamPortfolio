#include "stdafx.h"
#include "..\Public\Item_LegendWand.h"

CItem_LegendWand::CItem_LegendWand(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_LegendWand::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_WAND;
	m_tagItemDesc.pItem_Name = L"Item_Wand";
	m_tagItemDesc.iDurability = 5;
	m_tagItemDesc.fAttack_Damage = 15.f;
	m_tagItemDesc.iItem_Texture_Index = 84;
	m_tagItemDesc.iPrice = 600;

	return S_OK;
}

HRESULT CItem_LegendWand::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_LegendWand::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_LegendWand::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_LegendWand * CItem_LegendWand::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_LegendWand*		pInstance = new CItem_LegendWand(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_LegendWand");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_LegendWand::Free()
{
	__super::Free();
}
