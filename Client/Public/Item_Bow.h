#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Bow : public CItem
{
public:
	typedef enum Bow_Type
	{
		BOW_IRON,
		BOW_STEEL,
		BOW_GOLD,
		BOW_EPIC,
		BOW_END
	}BOW;

private:
	explicit CItem_Bow(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Bow() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	BOW						m_BowType;

public:
	static CItem_Bow*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END