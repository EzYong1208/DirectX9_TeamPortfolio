#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Dagger : public CItem
{
public:
	typedef enum Dagger_Type
	{
		DAGGER_IRON,
		DAGGER_STEEL,
		DAGGER_EPIC,
		DAGGER_LEGEND,
		DAGGER_END
	}DAGGER;

private:
	explicit CItem_Dagger(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Dagger() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	DAGGER					m_DaggerType;

public:
	static CItem_Dagger*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END