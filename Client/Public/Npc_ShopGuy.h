#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTexture;
class CVIBuffer_Rect;
class CTransform;
class CShader;
class CLightning;
END

BEGIN(Client)

class CNpc_ShopGuy : public CGameObject
{
public:
	explicit CNpc_ShopGuy(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CNpc_ShopGuy(const CNpc_ShopGuy& rhs);
	virtual ~CNpc_ShopGuy() = default;

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
	CShader*					m_pShader = nullptr;
	CLightning*					m_pLightning = nullptr;
	CGameObject*				m_pShop = nullptr;

private:
	_float						m_fFrame = 0.f;
	_int						m_iCount = 0;

public:
	static CNpc_ShopGuy*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject*		Clone(void* _pArg);
	virtual void				Free() override;
};

END