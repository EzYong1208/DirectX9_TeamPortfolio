#include "stdafx.h"
#include "..\Public\Item_Sword.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Sword::CItem_Sword(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Sword::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_SWORD;
	m_tagItemDesc.pItem_Name = L"Item_Sword";

	_uint iSwordType = rand() % 2;

	switch (iSwordType)
	{
	case SWORD_GOLD:
		m_tagItemDesc.iDurability = 15;
		m_tagItemDesc.fAttack_Damage = 15.f;
		m_tagItemDesc.iItem_Texture_Index = 9;
		m_tagItemDesc.iPrice = 550;
		break;

	case SWORD_EPIC:
		m_tagItemDesc.iDurability = 15;
		m_tagItemDesc.fAttack_Damage = 18.f;
		m_tagItemDesc.iItem_Texture_Index = 13;
		m_tagItemDesc.iPrice = 650;
		break;
	}

	return S_OK;
}

HRESULT CItem_Sword::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Sword::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Sword::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Sword * CItem_Sword::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Sword*		pInstance = new CItem_Sword(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Sword");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Sword::Free()
{
	__super::Free();
}
