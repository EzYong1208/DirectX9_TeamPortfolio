#include "stdafx.h"
#include "..\Public\Npc_Oldman.h"
#include "Texture.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "Lightning.h"
#include "Shader.h"
#include "GameInstance.h"
#include "UI_Conversation.h"

CNpc_Oldman::CNpc_Oldman(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CGameObject(_pGraphic_Device)
{
}

CNpc_Oldman::CNpc_Oldman(const CNpc_Oldman & rhs)
	: CGameObject(rhs)
{
}

HRESULT CNpc_Oldman::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CNpc_Oldman::NativeConstruct(void * _pArg)
{
	if (FAILED(__super::NativeConstruct(_pArg)))
		return E_FAIL;

	SetUp_Components();

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(8.5f, 0.5f, 18.5f));
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));

	return S_OK;
}

_int CNpc_Oldman::Tick(_float _fTimeDelta)
{
	if (0 >__super::Tick(_fTimeDelta))
		return -1;

	m_fFrame += 5.0f * _fTimeDelta * 0.3f;

	if (m_fFrame >= 5.0f)
		m_fFrame = 0.f;

	if (true == Collision_Check_Player())
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		if (pGameInstance->Key_Down('Z'))
		{
			if (0 == m_iCount)
			{
				CUI_Conversation* UI_Conversation = dynamic_cast<CUI_Conversation*>
					(CGameInstance::GetInstance()->Get_UI(
						LEVEL_GAMEPLAY, TEXT("UI_Conversation")));
				UI_Conversation->Set_Conversation_Text(
					TEXT("�̰��� �ſ� ������ ���̴�"),
					TEXT("�� �ָ� ������ �ִ�"),
					TEXT("�ܰ˰� ������ �������Գ�."));
				UI_Conversation->Set_UI_On();
			}

			if (0 < m_iCount)
			{
				CUI_Conversation* UI_Conversation = dynamic_cast<CUI_Conversation*>
					(CGameInstance::GetInstance()->Get_UI(
						LEVEL_GAMEPLAY, TEXT("UI_Conversation")));
				UI_Conversation->Set_Conversation_Text(
					TEXT(""),
					TEXT("����� ���."),
					TEXT(""));
				UI_Conversation->Set_UI_On();
			}

			++m_iCount;
		}

		RELEASE_INSTANCE(CGameInstance);
	}

	return _int();
}

_int CNpc_Oldman::LateTick(_float _fTimeDelta)
{
	if (0 >__super::LateTick(_fTimeDelta))
		return -1;

	if (nullptr == m_pRendererCom)
		return -1;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHA, this);

	return _int();
}

HRESULT CNpc_Oldman::Render()
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
	m_pTextureCom->Bind_OnShader(m_pShader, "g_Texture", (_uint)m_fFrame);
	m_pShader->Begin_Shader(0);

	m_pVIBufferCom->Render();

	m_pShader->End_Shader();

	return S_OK;
}

HRESULT CNpc_Oldman::SetUp_Components()
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
		L"Prototype_Component_Texture_Npc_Oldman",
		L"Com_Texture_Npc",
		(CComponent**)&m_pTextureCom,
		nullptr)))
		return E_FAIL;

	//Com_Shader ������Ʈ�� �ο��Ѵ�
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Shader",
		L"Com_Shader",
		(CComponent**)&m_pShader,
		nullptr)))
		return E_FAIL;

	//Com_Lightning ������Ʈ�� �ο��Ѵ�
	if (FAILED(Add_Component(
		LEVEL_STATIC,
		L"Prototype_Component_Lightning",
		L"Com_Lightning",
		(CComponent**)&m_pLightning,
		nullptr)))
		return E_FAIL;

	return S_OK;
}

_bool CNpc_Oldman::Collision_Check_Player()
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

HRESULT CNpc_Oldman::Save_Data(HANDLE _hFile)
{
	if (_hFile == INVALID_HANDLE_VALUE)
	{
		MSGBOX("INVALID_HANDLE_VALUE");
		return E_FAIL;
	}

	// m_Transform ������Ʈ�� ������� m_WorldMatrix �� ������ ����
	DWORD dwBytes = 0;
	WriteFile(_hFile, m_pTransformCom->Get_WorldMatrix(), sizeof(_float4x4), &dwBytes, nullptr);

	return S_OK;
}

HRESULT CNpc_Oldman::Load_Data(HANDLE _hFile)
{
	if (_hFile == INVALID_HANDLE_VALUE)
	{
		MSGBOX("INVALID_HANDLE_VALUE");
		return E_FAIL;
	}

	// m_pTransform ������Ʈ�� WorldMatrix �� ����� �����ͷ� ����
	DWORD dwBytes = 0;
	_float4x4 worldMatrix;

	ReadFile(_hFile, &worldMatrix, sizeof(_float4x4), &dwBytes, nullptr);

	m_pTransformCom->Set_WorldMatrix(worldMatrix);

	return S_OK;
}

CNpc_Oldman * CNpc_Oldman::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CNpc_Oldman* pInstance = new CNpc_Oldman(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CNpc_Oldman")
			Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CNpc_Oldman::Clone(void * _pArg)
{
	CNpc_Oldman* pInstance = new CNpc_Oldman(*this);

	if (FAILED(pInstance->NativeConstruct(_pArg)))
	{
		MSGBOX("Failed to Creating CNpc_Oldman")
			Safe_Release(pInstance);
	}

	return pInstance;
}

void CNpc_Oldman::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pLightning);
	Safe_Release(m_pShader);
}
