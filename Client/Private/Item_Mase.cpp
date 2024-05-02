#include "stdafx.h"
#include "..\Public\Item_Mase.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Mase::CItem_Mase(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Mase::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_MASE;
	m_tagItemDesc.pItem_Name = L"Item_Mase";

	_uint iMaseType = rand() % 3;

	switch (iMaseType)
	{
	case MASE_IRON:
		m_tagItemDesc.iDurability = 15;
		m_tagItemDesc.fAttack_Damage = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 22;
		m_tagItemDesc.iPrice = 450;
		break;

	case MASE_STEEL:
		m_tagItemDesc.iDurability = 15;
		m_tagItemDesc.fAttack_Damage = 13.f;
		m_tagItemDesc.iItem_Texture_Index = 26;
		m_tagItemDesc.iPrice = 550;
		break;

	case MASE_EPIC:
		m_tagItemDesc.iDurability = 15;
		m_tagItemDesc.fAttack_Damage = 18.f;
		m_tagItemDesc.iItem_Texture_Index = 33;
		m_tagItemDesc.iPrice = 650;
		break;
	}

	return S_OK;
}

HRESULT CItem_Mase::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Mase::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Mase::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Mase * CItem_Mase::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Mase*		pInstance = new CItem_Mase(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Mase");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Mase::Free()
{
	__super::Free();
}
