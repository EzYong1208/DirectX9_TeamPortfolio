#include "stdafx.h"
#include "..\Public\Item_RedOrb.h"
#include "Texture.h"
#include "Item.h"

CItem_RedOrb::CItem_RedOrb(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_RedOrb::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ETC;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_RedOrb";
	m_tagItemDesc.iItem_Texture_Index = 169;
	m_tagItemDesc.iPrice = 50000;

	return S_OK;
}

HRESULT CItem_RedOrb::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_RedOrb::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_RedOrb::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_RedOrb * CItem_RedOrb::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_RedOrb*		pInstance = new CItem_RedOrb(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_RedOrb");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_RedOrb::Free()
{
	__super::Free();
}
