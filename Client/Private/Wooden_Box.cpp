#include "stdafx.h"
#include "..\Public\Wooden_Box.h"
#include "Texture.h"
#include "Renderer.h"
#include "VIBuffer_Cube.h"
#include "GameInstance.h"
#include "Collider.h"
#include "Combat.h"
#include "Item_BoundingBox.h"
#include "Shader.h"
#include "Lightning.h"
#include "SoundMgr.h"
#include "UnDead01.h"

CWooden_Box::CWooden_Box(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CGameObject(_pGraphic_Device)
{
}

CWooden_Box::CWooden_Box(const CGameObject & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWooden_Box::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWooden_Box::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	memcpy(&m_WoodenBoxDesc, pArg, sizeof(WOODENBOXDESC));

	SetUp_Components();

	CCombat::COMBATDESC	tagCombatDesc;
	tagCombatDesc.fHp = 1.f;
	tagCombatDesc.fMaxHp = 1.f;
	tagCombatDesc.IsAttacked = false;
	tagCombatDesc.IsDead = false;

	m_pCombatCom->Set_CombatDesc(tagCombatDesc);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_WoodenBoxDesc.vPos);
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(16.4f, 0.3f, 4.7f));
	m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));

	return S_OK;
}

_int CWooden_Box::Tick(_float fTimeDelta)
{
	if (0 >__super::Tick(fTimeDelta))
		return -1;

	if (nullptr == m_pRendererCom)
		return -1;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHA, this);

	m_Colliders[0]->Sync_GameObject(m_pTransformCom);

	Collision_Check_Player();

	if (true == m_pCombatCom->Get_CombatDesc().IsAttacked)
	{
		if (1 == m_WoodenBoxDesc.iIndex)
			Create_Bow();
		else if (2 == m_WoodenBoxDesc.iIndex)
			Create_Coin();
		else if (3 == m_WoodenBoxDesc.iIndex)
			Create_Undead();
		else
			Create_Box();

		return ISDEAD;
	}

	return _int();
}

_int CWooden_Box::LateTick(_float fTimeDelta)
{
	if (0 >__super::LateTick(fTimeDelta))
		return -1;

	SetUp_OnTerrain();

	return _int();
}

HRESULT CWooden_Box::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	_float4x4		WorldMatrix, ViewMatrix, ProjMatrix;
	_float4x4		ViewMatrixInverse;

	WorldMatrix = m_pTransformCom->Get_WorldMatrix();
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrix);

	D3DXMatrixInverse(&ViewMatrixInverse, nullptr, &ViewMatrix);

	m_pShader->SetUp_ValueOnShader("g_WorldMatrix", D3DXMatrixTranspose(&WorldMatrix, &WorldMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_ViewMatrix", D3DXMatrixTranspose(&ViewMatrix, &ViewMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_ProjMatrix", D3DXMatrixTranspose(&ProjMatrix, &ProjMatrix), sizeof(_float4x4));
	m_pShader->SetUp_ValueOnShader("g_vCamPosition", &ViewMatrixInverse.m[3][0], sizeof(_float4));
	m_pLightning->Bind_OnShader_For_Objects(m_pShader, "g_Texture", m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pTextureCom->Bind_OnShader(m_pShader, "g_Texture", 0);

	m_pShader->Begin_Shader(4);

	m_pVIBufferCom->Render();

	m_pShader->End_Shader();

	return S_OK;
}

HRESULT CWooden_Box::SetUp_Components()
{
	//	For.Com_Renderer
	if (FAILED(__super::Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Renderer",
		L"Com_Renderer",
		(CComponent**)&m_pRendererCom,
		nullptr)))
		return E_FAIL;

	//	For.Com_VIBufferCube
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_VIBuffer_Cube",
		L"Com_VIBuffer",
		(CComponent**)&m_pVIBufferCom)))
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
		L"Prototype_Component_WoodenBox",
		L"Com_Texture_WoodenBox",
		(CComponent**)&m_pTextureCom,
		nullptr)))
		return E_FAIL;

	//	For.Com_Combat
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Combat",
		L"Com_Combat",
		(CComponent**)&m_pCombatCom,
		nullptr)))
		return E_FAIL;

	//	For.Com_Shader
	if (FAILED(CGameObject::Add_Component(
		LEVEL_STATIC, 
		L"Prototype_Component_Shader",
		L"Com_Shader", 
		(CComponent**)&m_pShader)))
		return E_FAIL;

	//	For.Lightning
	if (FAILED(CGameObject::Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Lightning",
		L"Com_Lightning", 
		(CComponent**)&m_pLightning)))
		return E_FAIL;

	CCollider::COLLIDERDESC Arg;
	m_Colliders.resize(1);

	Arg.fRadius = 0.4f;
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

HRESULT CWooden_Box::SetUp_OnTerrain()
{
	if (m_pTransformCom == nullptr)
		return E_FAIL;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CVIBuffer_Terrain* pTerrain = (CVIBuffer_Terrain*)pGameInstance->Get_Component(
		LEVEL_GAMEPLAY,
		L"Layer_Terrain",
		L"Com_VIBuffer",
		0);

	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fFixY = pTerrain->Compute_Y(vPos) + 0.3f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(vPos.x, fFixY, vPos.z));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}
_bool CWooden_Box::Collision_Check_Player()
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

	if (fDis < 0.8f)
	{
		m_tagMaterial.Ambient.r = 255.f;
		m_tagMaterial.Ambient.g = 255.f;
		m_tagMaterial.Ambient.b = 255.f;
		m_tagMaterial.Ambient.a = 255.f;

		bResult = true;
	}
	else
	{
		m_tagMaterial.Ambient.r = 1.f;
		m_tagMaterial.Ambient.g = 1.f;
		m_tagMaterial.Ambient.b = 1.f;
		m_tagMaterial.Ambient.a = 1.f;
		bResult = false;
	}

	RELEASE_INSTANCE(CGameInstance);

	return bResult;
}

void CWooden_Box::Create_Box()
{
	_uint	iRand = rand() % 5;

	switch (iRand)
	{
	case 0:
		if (false == m_bItemExist)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CItem_BoundingBox::BOUNDINGBOXDESC	tagBoundingBoxDesc;

			tagBoundingBoxDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			pGameInstance->Add_GameObject(
				LEVEL_GAMEPLAY,
				L"Layer_Item_Box",
				L"Prototype_GameObject_Item_Box",
				&tagBoundingBoxDesc);

			m_bItemExist = true;

			RELEASE_INSTANCE(CGameInstance);
		}
		break;

	case 1:
		if (false == m_bItemExist)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CItem_BoundingBox::BOUNDINGBOXDESC	tagBoundingBoxDesc;

			tagBoundingBoxDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			pGameInstance->Add_GameObject(
				LEVEL_GAMEPLAY,
				L"Layer_Item_Box",
				L"Prototype_GameObject_Item_Box",
				&tagBoundingBoxDesc);

			m_bItemExist = true;

			RELEASE_INSTANCE(CGameInstance);
		}
		break;

	case 2:
		if (false == m_bItemExist)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CItem_BoundingBox::BOUNDINGBOXDESC	tagCoinDesc;

			tagCoinDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
			tagCoinDesc.iIndex = 5;

			pGameInstance->Add_GameObject(
				LEVEL_GAMEPLAY,
				L"Layer_Item_Box",
				L"Prototype_GameObject_Item_Box",
				&tagCoinDesc);

			m_bItemExist = true;

			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(TEXT("drop_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);

			RELEASE_INSTANCE(CGameInstance);
		}
		break;

	case 3:
		if (false == m_bItemExist)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CItem_BoundingBox::BOUNDINGBOXDESC	tagCoinDesc;

			tagCoinDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
			tagCoinDesc.iIndex = 5;

			pGameInstance->Add_GameObject(
				LEVEL_GAMEPLAY,
				L"Layer_Item_Box",
				L"Prototype_GameObject_Item_Box",
				&tagCoinDesc);

			m_bItemExist = true;

			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(TEXT("drop_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);

			RELEASE_INSTANCE(CGameInstance);
		}
		break;

	case 4:
		Create_Undead();
		break;

	}
}

void CWooden_Box::Create_Bow()
{
	if (false == m_bItemExist)
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		CItem_BoundingBox::BOUNDINGBOXDESC	tagBoundingBoxDesc;

		tagBoundingBoxDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		tagBoundingBoxDesc.iIndex = 1;

		pGameInstance->Add_GameObject(
			LEVEL_GAMEPLAY,
			L"Layer_Item_Box",
			L"Prototype_GameObject_Item_Box",
			&tagBoundingBoxDesc);

		m_bItemExist = true;

		RELEASE_INSTANCE(CGameInstance);
	}
}

void CWooden_Box::Create_Coin()
{
	if (false == m_bItemExist)
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		CItem_BoundingBox::BOUNDINGBOXDESC	tagCoinDesc;

		tagCoinDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		tagCoinDesc.iIndex = 5;

		pGameInstance->Add_GameObject(
			LEVEL_GAMEPLAY,
			L"Layer_Item_Box",
			L"Prototype_GameObject_Item_Box",
			&tagCoinDesc);


		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SYSTEM_EFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(TEXT("drop_item.mp3"), CSoundMgr::SYSTEM_EFFECT3, SOUND_MAX);

		m_bItemExist = true;

		RELEASE_INSTANCE(CGameInstance);
	}
}

void CWooden_Box::Create_Undead()
{
	if (false == m_bItemExist)
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		//	튀어나오는 해골 용도
		CUnDead01::UNDEADDESC	tagUndeadDesc;

		tagUndeadDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		tagUndeadDesc.iIndex = 1;

		pGameInstance->Add_GameObject(
			LEVEL_GAMEPLAY,
			L"Layer_Monster",
			L"Prototype_GameObject_UnDead01",
			&tagUndeadDesc);

		m_bItemExist = true;

		RELEASE_INSTANCE(CGameInstance);
	}
}

HRESULT CWooden_Box::Save_Data(HANDLE _hFile)
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

HRESULT CWooden_Box::Load_Data(HANDLE _hFile)
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

CWooden_Box * CWooden_Box::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CWooden_Box* pInstance = new CWooden_Box(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CWooden_Box")
			Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWooden_Box::Clone(void * pArg)
{
	CWooden_Box* pInstance = new CWooden_Box(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CWooden_Box")
			Safe_Release(pInstance);
	}

	return pInstance;
}

void CWooden_Box::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pCombatCom);
	Safe_Release(m_pShader);
	Safe_Release(m_pLightning);

	for (auto pCollider : m_Colliders)
	{
		Safe_Release(pCollider);
	}
}
