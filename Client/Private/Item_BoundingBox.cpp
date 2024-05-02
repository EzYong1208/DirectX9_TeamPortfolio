#include "stdafx.h"
#include "..\Public\Item_BoundingBox.h"
#include "Texture.h"
#include "Renderer.h"
#include "VIBuffer_Rect.h"
#include "GameInstance.h"
#include "Player.h"
#include "Item_Bomb.h"
#include "Item_Food.h"
#include "Item_Potion.h"
#include "Item_Bow.h"
#include "Item_Dagger.h"
#include "Item_Mase.h"
#include "Item_Sword.h"
#include "Item_Wand.h"
#include "Item_Lantern.h"
#include "Item_Shield.h"
#include "Item_Armor_Down.h"
#include "Item_Armor_Up.h"
#include "Item_Head.h"
#include "Item_Necklace.h"
#include "Item_Ring.h"
#include "Item_Bone.h"
#include "Item_Book.h"
#include "Item_Coin.h"
#include "ItemSlot.h"
#include "Lightning.h"
#include "Shader.h"
#include "State_Machine.h"
#include "Item.h"
#include "State_Jump.h"
#include "SoundMgr.h"
#include "Item_LegendSword.h"
#include "Item_LegendMase.h"
#include "Item_LegendWand.h"
#include "Item_LegendBow.h"
#include "Item_Key.h"

CItem_BoundingBox::CItem_BoundingBox(LPDIRECT3DDEVICE9 _pGraphicDevice)
	: CGameObject(_pGraphicDevice)
{
}

CItem_BoundingBox::CItem_BoundingBox(const CItem_BoundingBox & rhs)
	: CGameObject(rhs)
{
}

HRESULT CItem_BoundingBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CItem_BoundingBox::NativeConstruct(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	memcpy(&m_BoxDesc, pArg, sizeof(BOUNDINGBOXDESC));
	ZeroMemory(&m_ItemDesc, sizeof(CItem::ITEMDESC));

	if (1 == m_BoxDesc.iIndex)
		Create_Bow();
	else if (2 == m_BoxDesc.iIndex)
		Create_Dagger();
	else if (3 == m_BoxDesc.iIndex)
		Create_Lantern();
	else if (4 == m_BoxDesc.iIndex)
		Create_Wand();
	else if (5 == m_BoxDesc.iIndex)
		Create_Coin();
	else if (6 == m_BoxDesc.iIndex)
		Create_Sword();
	else if (7 == m_BoxDesc.iIndex)
		Create_Key();
	else if (8 == m_BoxDesc.iIndex)
		Create_LegendSword();
	else if (9 == m_BoxDesc.iIndex)
		Create_LegendMase();
	else if (10 == m_BoxDesc.iIndex)
		Create_LegendWand();
	else if (11 == m_BoxDesc.iIndex)
		Create_LegendBow();
	else 
	{
		Set_ItemTexture();

		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(TEXT("drop_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);
	}

	SetUp_Components();

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_BoxDesc.vPos);
	m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));


	if (8 == m_BoxDesc.iIndex ||
		9 == m_BoxDesc.iIndex ||
		10 == m_BoxDesc.iIndex ||
		11 == m_BoxDesc.iIndex)
	{

	}
	else 
	{
		m_pState_MachineCom->Bind_State(
			CState_Machine::STATETYPE_INPUT,
			L"State_Jump",
			CState_Jump::Create(_float3(0.0f, 1.f, 0.0f)*0.03f));
	}

	return S_OK;
}

_int CItem_BoundingBox::Tick(_float fTimeDelta)
{
	if (0 >__super::Tick(fTimeDelta))
		return -1;

	m_Colliders[0]->Sync_GameObject(m_pTransformCom);

	m_pState_MachineCom->Action(fTimeDelta, this);
	m_pTransformCom->Reset_Momentum();


	if (true == Collision_Check_Player())
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		if (pGameInstance->Key_Down('Z') && m_bAnimateCVaild ==false)
		{
			CTransform* pTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_GAMEPLAY, L"Layer_Player", L"Com_Transform", 0);
			m_bAnimateCVaild = true;
			m_vStartPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
			m_vEndPos = pTransform->Get_State(CTransform::STATE_POSITION);

		}

		RELEASE_INSTANCE(CGameInstance);
	}

	if (m_bAnimateCVaild)
	{
		m_fAlpha += fTimeDelta*2.f;
		_float fFixAlpha = NONG::EaseInBack(m_fAlpha);
		m_pTransformCom->Interpolation_Motion(m_vStartPos, m_vEndPos, fFixAlpha);
		//_float3 vScale = m_pTransformCom->Get_Scale();
		//m_pTransformCom->Scaled(_float3(1.f,1.f,1.f)*0.5f*(1.f- m_fAlpha));
		//도달시 넣음
		if(m_fAlpha >= 1.f)
		{
			m_bAnimateCVaild = false;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(TEXT("grab_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);

			//	돈이면 가방에 넣지않고 소지금에 더함
			if (true == m_bCoin)
			{
				_int iGold = m_pItem->Get_ItemDesc().iGold;
				m_pItemSlotCom->Set_Gold(iGold);
				m_bCoin = false;
				_int iCoin = m_pItemSlotCom->Get_Gold();
				return ISDEAD;
			}
			//	그 외에는 가방에 넣음
			else if(m_pItem->Get_ItemDesc().eItem_Type == CItem::ITEMTYPE_RIGHT)
			{
				m_pItem = m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_QUICK);

				if(m_pItem !=nullptr)
				{
					m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_BACKPACK);
				}

				return ISDEAD;
			}
			else
			{
				m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_BACKPACK);
				return ISDEAD;

			}
		}
	}

	return _int();
}

_int CItem_BoundingBox::LateTick(_float fTimeDelta)
{
	if (0 >__super::LateTick(fTimeDelta))
		return -1;

	if (nullptr == m_pRendererCom)
		return -1;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHA, this);

	if (8 == m_BoxDesc.iIndex ||
		9 == m_BoxDesc.iIndex ||
		10 == m_BoxDesc.iIndex ||
		11 == m_BoxDesc.iIndex)
	{

	}
	else if (m_pState_MachineCom->Check_State(CState_Machine::STATETYPE_INPUT) != L"State_Jump")
		SetUp_OnTerrain();

	return _int();
}

HRESULT CItem_BoundingBox::Render()
{
	__super::Render();

	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	////Billboarding
	_float4x4		ViewMatrix, BillboardMatrix, ProjMatrix, ViewMatrixInverse;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrix);
	D3DXMatrixInverse(&ViewMatrixInverse, nullptr, &ViewMatrix);

	BillboardMatrix = m_pTransformCom->Get_WorldMatrix();


	*(_float3*)BillboardMatrix.m[0] = (*(_float3*)ViewMatrixInverse.m[0])*m_pTransformCom->Get_Scale().x;
	*(_float3*)BillboardMatrix.m[2] = (*(_float3*)ViewMatrixInverse.m[2])*m_pTransformCom->Get_Scale().z;

	m_pShader->SetUp_ValueOnShader("g_WorldMatrix", D3DXMatrixTranspose(&BillboardMatrix, &BillboardMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_ViewMatrix", D3DXMatrixTranspose(&ViewMatrix, &ViewMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_ProjMatrix", D3DXMatrixTranspose(&ProjMatrix, &ProjMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_vCamPosition", &ViewMatrixInverse.m[3][0], sizeof(_float4));
	m_pLightning->Bind_OnShader_For_Objects(m_pShader, "g_Texture", m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pTextureCom->Bind_OnShader(m_pShader, "g_Texture", m_iTexture);

	//거리재기 추가
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_GAMEPLAY, L"Layer_Player", L"Com_Transform", 0);
	RELEASE_INSTANCE(CGameInstance);

	_float3 vDir = pTransform->Get_State(CTransform::STATE_POSITION) - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDis = D3DXVec3Length(&vDir);

	if(fDis >=1.3f)
		m_pShader->Begin_Shader(0);
	else
		m_pShader->Begin_Shader(9);

	m_pVIBufferCom->Render();

	m_pShader->End_Shader();

	return S_OK;
}

HRESULT CItem_BoundingBox::SetUp_Components()
{
	//	For.Com_Renderer
	if (FAILED(__super::Add_Component(
		LEVEL_STATIC,						
		L"Prototype_Component_Renderer",	
		L"Com_Renderer",					
		(CComponent**)&m_pRendererCom,		
		nullptr)))							
		return E_FAIL;

	//	For.Com_VIBuffer
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_VIBuffer_Rect",
		L"Com_VIBuffer",
		(CComponent**)&m_pVIBufferCom,
		nullptr)))
		return E_FAIL;

	//	For.Com_Transform
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransformCom,
		nullptr)))
		return E_FAIL;

	//	For.Com_Texture
	if (FAILED(Add_Component(
		LEVEL_GAMEPLAY,
		L"Prototype_Component_Texture_Item",
		L"Com_Texture_Item",
		(CComponent**)&m_pTextureCom,
		nullptr)))
		return E_FAIL;

	//	For.ItemSlotCom
	if (FAILED(__super::Add_Component(
		LEVEL_GAMEPLAY,
		L"Prototype_Component_ItemSlot",
		L"Com_ItemSlot",
		(CComponent**)&m_pItemSlotCom)))
		return E_FAIL;

	//Com_Shader 컴포넌트를 부여한다
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Shader",
		L"Com_Shader",
		(CComponent**)&m_pShader,
		nullptr)))
		return E_FAIL;

	//Com_Lightning 컴포넌트를 부여한다
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Lightning",
		L"Com_Lightning",
		(CComponent**)&m_pLightning,
		nullptr)))
		return E_FAIL;

	//State_Machine 컴포넌트를 부여한다
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_State_Machine",
		L"Com_State_Machine",
		(CComponent**)&m_pState_MachineCom,
		nullptr)))
		return E_FAIL;

	CCollider::COLLIDERDESC Arg;
	m_Colliders.resize(1);

	Arg.fRadius = 0.2f;
	Arg.vOffset = _float3(0.f, 0.f, 0.f);

	//Collider 컴포넌트를 부여한다(Body)
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Collider",
		L"Com_Collider",
		(CComponent**)&m_Colliders[0],
		&Arg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CItem_BoundingBox::SetUp_OnTerrain()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CComponent* pTerrainCom = pGameInstance->Get_Component(LEVEL_GAMEPLAY, L"Layer_Terrain", L"Com_VIBuffer", 0);

	_float fY = dynamic_cast<CVIBuffer_Terrain*>(pTerrainCom)->Compute_Y(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	_float3 vFixPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	vFixPos.y = fY + 0.3f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vFixPos);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

_bool CItem_BoundingBox::Collision_Check_Player()
{
	_bool bResult = false;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_float3 vPlayerPos = dynamic_cast<CTransform*>(pGameInstance->Get_Component(
		pGameInstance->Get_LevelIndex(),
		L"Layer_Player",
		L"Com_Transform",
		0))->Get_State(CTransform::STATE_POSITION);

	_float3 vDis_To_Player = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDis = fDis = D3DXVec3Length(&vDis_To_Player);

	if (fDis < 1.2f)
	{
		bResult = true;
	}
	else
	{

		bResult = false;
	}

	RELEASE_INSTANCE(CGameInstance);

	return bResult;

}

HRESULT CItem_BoundingBox::Save_Data(HANDLE _hFile)
{
	if (_hFile == INVALID_HANDLE_VALUE)
	{
		MSGBOX("INVALID_HANDLE_VALUE");
		return E_FAIL;
	}

	DWORD	dwBytes = 0;
	WriteFile(_hFile, m_pTransformCom->Get_WorldMatrix(), sizeof(_float4x4), &dwBytes, nullptr);

	return S_OK;
}

HRESULT CItem_BoundingBox::Load_Data(HANDLE _hFile)
{
	if (_hFile == INVALID_HANDLE_VALUE)
	{
		MSGBOX("INVALID_HANDLE_VALUE");
		return E_FAIL;
	}

	DWORD	dwBytes = 0;
	_float4x4 worldMatrix;

	ReadFile(_hFile, &worldMatrix, sizeof(_float4x4), &dwBytes, nullptr);

	m_pTransformCom->Set_WorldMatrix(worldMatrix);

	return S_OK;
}

HRESULT CItem_BoundingBox::Set_ItemTexture()
{
	_uint		iTypeItem = rand() % 6;

	switch (iTypeItem)
	{
	case TYPEITEM_USEABLE:
		Create_Useable();
		break;

	case TYPEITEM_RIGHT:
		Create_Right();
		break;

	case TYPEITEM_LEFT:
		Create_Left();
		break;

	case TYPEITEM_ARMOR:
		Create_Armor();
		break;

	case TYPEITEM_ACCESSORY:
		Create_Accessory();
		break;

	case TYPEITEM_ETC:
		Create_Etc();
		break;
	}

	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Useable()
{
	_uint	iUseableType = rand() % 3;

	switch (iUseableType)
	{
	case ITEM_BOMB:
		m_pItem = CItem_Bomb::Create(m_pGraphic_Device);
		break;

	case ITEM_FOOD:
		m_pItem = CItem_Food::Create(m_pGraphic_Device);
		break;

	case ITEM_POTION:
		m_pItem = CItem_Potion::Create(m_pGraphic_Device);
		break;
	}

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Right()
{
	_uint	iRightType = rand() % 5 + 3;

	switch (iRightType)
	{
	case ITEM_BOW:
		m_pItem = CItem_Bow::Create(m_pGraphic_Device);
		break;

	case ITEM_DAGGER:
		m_pItem = CItem_Dagger::Create(m_pGraphic_Device);
		break;

	case ITEM_MASE:
		m_pItem = CItem_Mase::Create(m_pGraphic_Device);
		break;

	case ITEM_SWORD:
		m_pItem = CItem_Sword::Create(m_pGraphic_Device);
		break;

	case ITEM_WAND:
		m_pItem = CItem_Wand::Create(m_pGraphic_Device);
		break;
	}

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Left()
{
	//	실드 생성
	m_pItem = CItem_Shield::Create(m_pGraphic_Device);

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Armor()
{
	_uint	iArmorType = rand() % 3 + 10;

	switch (iArmorType)
	{
	case ITEM_ARMOR_DOWN:
		m_pItem = CItem_Armor_Down::Create(m_pGraphic_Device);
		break;

	case ITEM_ARMOR_UP:
		m_pItem = CItem_Armor_Up::Create(m_pGraphic_Device);
		break;

	case ITEM_HEAD:
		m_pItem = CItem_Head::Create(m_pGraphic_Device);
		break;
	}

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Accessory()
{
	_uint	iAccessoryType = rand() % 2 + 13;

	switch (iAccessoryType)
	{
	case ITEM_NECKLACE:
		m_pItem = CItem_Necklace::Create(m_pGraphic_Device);
		break;

	case ITEM_RING:
		m_pItem = CItem_Ring::Create(m_pGraphic_Device);
		break;
	}

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Etc()
{
	_uint	iEctType = rand() % 3 + 15;

	switch (iEctType)
	{
	case ITEM_BONE:
		m_pItem = CItem_Bone::Create(m_pGraphic_Device);
		break;

	case ITEM_BOOK:
		m_pItem = CItem_Book::Create(m_pGraphic_Device);
		break;

	case ITEM_COIN:
		m_pItem = CItem_Coin::Create(m_pGraphic_Device);
		m_bCoin = true;
		break;
	}

	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Bow()
{
	m_pItem = CItem_Bow::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;

	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
	CSoundMgr::Get_Instance()->PlaySound(TEXT("drop_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Dagger()
{
	m_pItem = CItem_Dagger::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Lantern()
{
	m_pItem = CItem_Lantern::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Coin()
{
	m_pItem = CItem_Coin::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	m_bCoin = true;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Wand()
{
	m_pItem = CItem_Wand::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Sword()
{
	m_pItem = CItem_Sword::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_LegendSword()
{
	m_pItem = CItem_LegendSword::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_LegendMase()
{
	m_pItem = CItem_LegendMase::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_LegendWand()
{
	m_pItem = CItem_LegendWand::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_LegendBow()
{
	m_pItem = CItem_LegendBow::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

HRESULT CItem_BoundingBox::Create_Key()
{
	m_pItem = CItem_Key::Create(m_pGraphic_Device);
	memcpy(&m_ItemDesc, &m_pItem->Get_ItemDesc(), sizeof(CItem::ITEMDESC));
	m_iTexture = m_pItem->Get_ItemDesc().iItem_Texture_Index;
	return S_OK;
}

CItem_BoundingBox * CItem_BoundingBox::Create(LPDIRECT3DDEVICE9 _pGraphicDevice)
{
	CItem_BoundingBox* pInstance = new CItem_BoundingBox(_pGraphicDevice);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CItem_BoundingBox")
			Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CItem_BoundingBox::Clone(void * pArg)
{
	CItem_BoundingBox* pInstance = new CItem_BoundingBox(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CItem_BoundingBox")
			Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_BoundingBox::Free()
{
	__super::Free();

	Safe_Release(m_pItemSlotCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pLightning);
	Safe_Release(m_pShader);
	Safe_Release(m_pState_MachineCom);

	for (auto pCollider : m_Colliders)
	{
		Safe_Release(pCollider);
	}
}