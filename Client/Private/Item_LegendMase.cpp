#include "stdafx.h"
#include "..\Public\Item_LegendMase.h"


CItem_LegendMase::CItem_LegendMase(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_LegendMase::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_MASE;
	m_tagItemDesc.pItem_Name = L"Item_Mase";
	m_tagItemDesc.iDurability = 15;
	m_tagItemDesc.fAttack_Damage = 20.f;
	m_tagItemDesc.iItem_Texture_Index = 30;
	m_tagItemDesc.iPrice = 750;

	return S_OK;
}

HRESULT CItem_LegendMase::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_LegendMase::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_LegendMase::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_LegendMase * CItem_LegendMase::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_LegendMase*	pInstance = new CItem_LegendMase(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_LegendMase");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_LegendMase::Free()
{
	__super::Free();
}
