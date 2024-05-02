#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Wand : public CItem
{
public:
	typedef enum Wand_Type
	{
		WAND_AMETHYST,
		WAND_EMERALD,
		WAND_RUBY,
		WAND_EPIC,
		MASE_END
	}WAND;

private:
	explicit CItem_Wand(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Wand() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	WAND					m_WandType;

public:
	static CItem_Wand*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END