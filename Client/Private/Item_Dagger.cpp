#include "stdafx.h"
#include "..\Public\Item_Dagger.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Dagger::CItem_Dagger(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Dagger::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RIGHT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_DAGGER;
	m_tagItemDesc.pItem_Name = L"Item_Dagger";

	//m_tagItemDesc.iDurability = 10;
	//m_tagItemDesc.fAttack_Damage = 5.f;
	//m_tagItemDesc.iItem_Texture_Index = 17;		//	17 ~ 20

	//if (0 == m_tagItemDesc.iDurability)
	//{
	//	m_tagItemDesc.fAttack_Damage = 1.f;
	//	m_tagItemDesc.iItem_Texture_Index = 18;
	//}

	_uint iDaggerType = rand() % 4;

	switch (iDaggerType)
	{
	case DAGGER_IRON:
		m_tagItemDesc.iDurability = 8;
		m_tagItemDesc.fAttack_Damage = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 2;
		m_tagItemDesc.iPrice = 200;
		break;

	case DAGGER_STEEL:
		m_tagItemDesc.iDurability = 8;
		m_tagItemDesc.fAttack_Damage = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 6;
		m_tagItemDesc.iPrice = 300;
		break;

	case DAGGER_EPIC:
		m_tagItemDesc.iDurability = 8;
		m_tagItemDesc.fAttack_Damage = 13.f;
		m_tagItemDesc.iItem_Texture_Index = 17;
		m_tagItemDesc.iPrice = 400;
		break;

	case DAGGER_LEGEND:
		m_tagItemDesc.iDurability = 8;
		m_tagItemDesc.fAttack_Damage = 15.f;
		m_tagItemDesc.iItem_Texture_Index = 19;
		m_tagItemDesc.iPrice = 500;
		break;
	}

	return S_OK;
}

HRESULT CItem_Dagger::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Dagger::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Dagger::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Dagger * CItem_Dagger::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Dagger*		pInstance = new CItem_Dagger(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Dagger");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Dagger::Free()
{
	__super::Free();
}
