#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTexture;
class CVIBuffer_Cube;
class CCollider;
class CCombat;
class CLightning;
class CShader;
END

BEGIN(Client)

class CWooden_Box : public CGameObject
{
public:
	typedef	struct tagWoodenBoxDescription
	{
		_int		iIndex = 0;
		_float3		vPos;
	}WOODENBOXDESC;

public:
	explicit CWooden_Box(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CWooden_Box(const CGameObject& rhs);
	virtual ~CWooden_Box() = default;

public:
	virtual HRESULT						NativeConstruct_Prototype();
	virtual HRESULT						NativeConstruct(void* pArg);
	virtual _int						Tick(_float fTimeDelta);
	virtual _int						LateTick(_float fTimeDelta);
	virtual HRESULT						Render();

public:
	HRESULT								SetUp_Components();
	HRESULT								SetUp_OnTerrain();

public:
	_bool								Collision_Check_Player();
	virtual vector<class CCollider*>*	Get_Colliders() { return &m_Colliders; };

public:
	void								Create_Box();
	_bool								m_bItemExist = false;
	void								Create_Bow();
	void								Create_Coin();
	void								Create_Undead();

public:
	virtual HRESULT						Save_Data(HANDLE _hFile);
	virtual HRESULT						Load_Data(HANDLE _hFile);

protected:
	CRenderer*							m_pRendererCom = nullptr;
	CVIBuffer_Cube*						m_pVIBufferCom = nullptr;
	CTexture*							m_pTextureCom = nullptr;
	CTransform*							m_pTransformCom = nullptr;
	CCombat*							m_pCombatCom = nullptr;
	vector<CCollider*>					m_Colliders;
	CShader*							m_pShader = nullptr;
	CLightning*							m_pLightning = nullptr;
	WOODENBOXDESC						m_WoodenBoxDesc;

public:
	static CWooden_Box*					Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject*				Clone(void* pArg);
	virtual	void						Free() override;
};

END