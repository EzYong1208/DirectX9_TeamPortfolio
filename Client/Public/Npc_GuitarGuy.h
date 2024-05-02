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
class CItemSlot;
END

BEGIN(Client)

class CNpc_GuitarGuy : public CGameObject
{
public:
	explicit CNpc_GuitarGuy(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CNpc_GuitarGuy(const CNpc_GuitarGuy& rhs);
	virtual ~CNpc_GuitarGuy() = default;

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
	CItemSlot*					m_pItemSlotCom = nullptr;

private:
	_float						m_fFrame = 0.f;

public:
	static CNpc_GuitarGuy*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject*		Clone(void* _pArg);
	virtual void				Free() override;
};

END