#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Potion : public CItem
{
public:
	typedef enum Potion_Type
	{
		POTION_ORANGE,
		POTION_RED,
		POTION_BLUE,
		POTION_GREEN,
		POTION_PURPLE,
		POTION_BLACK,
		POTION_YELLOW,
		POTION_END
	}POTION;

private:
	explicit CItem_Potion(LPDIRECT3DDEVICE9 _pGraphicDevice);
	virtual ~CItem_Potion() = default;

public:
	virtual	HRESULT			NativeConstruct();

public:
	virtual	HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual	HRESULT			Load_Data(HANDLE _hFile);

private:
	POTION					m_PotionType;

public:
	static CItem_Potion*	Create(LPDIRECT3DDEVICE9 _pGraphicDevice);
	virtual	void			Free() override;
};

END