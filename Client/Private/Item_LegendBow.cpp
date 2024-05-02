#include "stdafx.h"
#include "..\Public\Item_LegendBow.h"

CItem_LegendBow::CItem_LegendBow(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_LegendBow::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_BOW;
	m_tagItemDesc.pItem_Name = L"Item_Bow";
	m_tagItemDesc.fAttack_Damage = 15.f;
	m_tagItemDesc.iItem_Texture_Index = 55;		//	55 ~ 58
	m_tagItemDesc.iPrice = 700;

	return S_OK;
}

HRESULT CItem_LegendBow::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_LegendBow::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_LegendBow::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_LegendBow * CItem_LegendBow::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_LegendBow*	pInstance = new CItem_LegendBow(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_LegendBow");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_LegendBow::Free()
{
	__super::Free();
}
