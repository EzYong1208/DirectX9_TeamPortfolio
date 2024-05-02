#include "stdafx.h"
#include "..\Public\Item_Key.h"


CItem_Key::CItem_Key(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Key::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_USEABLE;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Key";

	m_tagItemDesc.iItem_Texture_Index = 170;

	return S_OK;
}

HRESULT CItem_Key::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Key::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Key::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Key * CItem_Key::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Key*	pInstance = new CItem_Key(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Key");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Key::Free()
{
	__super::Free();
}
