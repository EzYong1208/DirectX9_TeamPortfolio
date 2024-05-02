#include "stdafx.h"
#include "..\Public\Item_Lantern.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Lantern::CItem_Lantern(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Lantern::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_LEFT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Lantern";
	m_tagItemDesc.iItem_Texture_Index = 130;
	m_tagItemDesc.iPrice = 200;
	return S_OK;
}

HRESULT CItem_Lantern::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Lantern::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Lantern::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Lantern * CItem_Lantern::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Lantern*		pInstance = new CItem_Lantern(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Lantern");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Lantern::Free()
{
	__super::Free();
}
