#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Bomb : public CItem
{
public:
	typedef enum Bomb_Type
	{
		BOMB_BLACK,
		BOMB_RED,
		BOMB_BLUE,
		BOMB_PURPLE,
		BOMB_END
	}BOMB;

private:
	explicit CItem_Bomb(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Bomb() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	BOMB					m_BombType;

public:
	static CItem_Bomb*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END