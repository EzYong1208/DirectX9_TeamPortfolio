#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Bone : public CItem
{
public:
	typedef enum Bone_Type
	{
		BONE_HEAD,
		BONE_LEG,
		BONE_CHEST,
		BONE_END
	}BONE;

private:
	explicit CItem_Bone(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Bone() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	BONE					m_BoneType;

public:
	static CItem_Bone*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END