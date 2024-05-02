#include "stdafx.h"
#include "..\Public\Item_Bone.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Bone::CItem_Bone(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Bone::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ETC;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Bone";
	//m_tagItemDesc.iItem_Texture_Index = 166;		//	166 ~ 168

	_uint	iBoneType = rand() % 3;

	switch (iBoneType)
	{
	case BONE_HEAD:
		m_tagItemDesc.iItem_Texture_Index = 166;
		m_tagItemDesc.iPrice = 10;
		break;

	case BONE_LEG:
		m_tagItemDesc.iItem_Texture_Index = 167;
		m_tagItemDesc.iPrice = 10;
		break;
		
	case BONE_CHEST:
		m_tagItemDesc.iItem_Texture_Index = 168;
		m_tagItemDesc.iPrice = 10;
		break;
	}

	return S_OK;
}

HRESULT CItem_Bone::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Bone::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Bone::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Bone * CItem_Bone::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Bone*		pInstance = new CItem_Bone(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Bone");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Bone::Free()
{
	__super::Free();
}
