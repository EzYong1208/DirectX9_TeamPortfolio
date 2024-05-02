#include "stdafx.h"
#include "..\Public\Item_Bow.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Bow::CItem_Bow(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Bow::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_BOW;
	m_tagItemDesc.pItem_Name = L"Item_Bow";

	//m_tagItemDesc.fAttack_Damage = 5.f;
	//m_tagItemDesc.iItem_Texture_Index = 35;		//	35 ~ 70, 71 : È­»ì

	_uint iBowType = rand() % 4;

	switch (iBowType)
	{
	case BOW_IRON:
		m_tagItemDesc.fAttack_Damage = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 35;		//	35 ~ 38
		m_tagItemDesc.iPrice = 300;
		break;

	case BOW_STEEL:
		m_tagItemDesc.fAttack_Damage = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 59;		//	59 ~ 62
		m_tagItemDesc.iPrice = 400;
		break;

	case BOW_GOLD:
		m_tagItemDesc.fAttack_Damage = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 63;		//	63 ~ 66
		m_tagItemDesc.iPrice = 500;
		break;

	case BOW_EPIC:
		m_tagItemDesc.fAttack_Damage = 13.f;
		m_tagItemDesc.iItem_Texture_Index = 67;		//	67 ~ 70
		m_tagItemDesc.iPrice = 600;
		break;
	}

	return S_OK;
}

HRESULT CItem_Bow::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Bow::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Bow::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Bow * CItem_Bow::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Bow*		pInstance = new CItem_Bow(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Bow");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Bow::Free()
{
	__super::Free();
}
