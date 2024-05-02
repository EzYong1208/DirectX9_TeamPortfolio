#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Head : public CItem
{
public:
	typedef enum Head_Type
	{
		HEAD_BRONZE,
		HEAD_IRON,
		HEAD_GOLD,
		HEAD_EPIC,
		HEAD_LEGEND,
		HEAD_END
	}HEAD;

private:
	explicit CItem_Head(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Head() = default;

public:
	virtual HRESULT				NativeConstruct();

public:
	virtual HRESULT				Activate(CGameObject* _pTarget);

public:
	virtual HRESULT				Save_Data(HANDLE _hFile);
	virtual HRESULT				Load_Data(HANDLE _hFile);

private:
	HEAD						m_HeadTypes;

public:
	static CItem_Head*			Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void				Free() override;
};

END