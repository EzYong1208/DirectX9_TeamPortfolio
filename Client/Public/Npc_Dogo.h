#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Item.h"

BEGIN(Engine)
class CRenderer;
class CTexture;
class CVIBuffer_Rect;
class CTransform;
class CCollider;
class CItemSlot;
class CShader;
class CLightning;
class CShop;
END

BEGIN(Client)

class CNpc_Dogo	: public CGameObject
{
public:
	explicit CNpc_Dogo(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CNpc_Dogo(const CNpc_Dogo& rhs);
	virtual ~CNpc_Dogo() = default;

public:
	virtual	HRESULT				NativeConstruct_Prototype() override;
	virtual	HRESULT				NativeConstruct(void* _pArg) override;
	virtual	_int				Tick(_float _fTimeDelta) override;
	virtual	_int				LateTick(_float _fTimeDelta) override;
	virtual	HRESULT				Render() override;

public:
	HRESULT						SetUp_Components();

public:
	_bool						Collision_Check_Player();

public:
	virtual HRESULT				Save_Data(HANDLE _hFile) override;
	virtual HRESULT				Load_Data(HANDLE _hFile) override;

protected:
	CRenderer*					m_pRendererCom = nullptr;
	CVIBuffer_Rect*				m_pVIBufferCom = nullptr;
	CTexture*					m_pTextureCom = nullptr;
	CTransform*					m_pTransformCom = nullptr;
	vector<CCollider*>			m_Colliders;
	CItemSlot*					m_pItemSlotCom = nullptr;
	CItem*						m_pItem = nullptr;
	CShader*					m_pShader = nullptr;
	CLightning*					m_pLightning = nullptr;
	CGameObject*				m_pShop = nullptr;

private:
	_float						m_fFrame = 0.f;

public:
	static CNpc_Dogo*			Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject*		Clone(void* _pArg);
	virtual void				Free() override;
};

END