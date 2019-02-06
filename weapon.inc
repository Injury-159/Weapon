#if defined inc_weapon_
	#endinput
#endif 
#define _inc_weapon	


#include <a_samp>
#include <pawn.raknet>
#include <YSI_Coding\y_hooks>


//
//	 DEFINES
//


#define IsWeaponClipBased(%0)				(-21 < (%0) < 35 || (%0) == 38)


//
//	DATA
//



static player_WeaponMaxClip[MAX_PLAYERS][sizeof weaponDefaultClip];
static weap_Clip[MAX_PLAYERS][13];
static weap_Extra[MAX_PLAYERS][13];


//
//	CALLBACKS
//


hook OnPlayerConnect(playerid)
{
	for(new x; x < sizeof player_WeaponMaxClip[]; x++)
		player_WeaponMaxClip[playerid][x] = weaponDefaultClip[x];
}


hook OnPlayerDisconnect(playerid, reason)
{
	memset(weap_Clip[playerid], 0, 13);
	memset(weap_Extra[playerid], 0, 13);
}


public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	if(packetid == 204)
	{
		new ammo, weaponid;
		BS_SetReadOffset(bs, 48);
		BS_ReadValue(bs, PR_UINT8, weaponid, PR_UINT16, ammo);

		if(weaponid == GetPlayerWeapon(playerid) && (GetPlayerAmmo(playerid) - ammo) == 1)
		{
			if(player_WeaponMaxClip[playerid][weaponid] != weaponDefaultClip[weaponid])
			{

			}
			else 
			{

			}
		}

		if(GetPlayerAnimationIndex(playerid))
	}

    #if defined WEA_OnIncomingPacket
        return WEA_OnIncomingPacket(playerid, packetid, bs);
    #else
        return 1;
    #endif
}


stock WEA_GivePlayerWeapon(playerid, weaponid, ammo)
{
	GivePlayerWeapon(playerid, weaponid, ammo);
	return IsWeaponClipBased(weaponid) ?Weapon_ReloadSync(playerid) : 1;
}


stock GetPlayerWeaponClipAmmo(playerid)
{
	new weapon = GetPlayerWeapon(playerid);
	return IsWeaponClipBased(weapon) ? weap_Clip[playerid][weaponSlot[weapon]] : 1;
}

stock SetPlayerWeaponClipSize(playerid, weaponid, size)
{
	if(!IsWeaponClipBased(weaponid))
		return;

}


//
//	INTERNAL
//


static stock Weapon_ReloadSync(playerid, ammo = cellmin)
{
	if(ammo == cellmin)
		ammo = GetPlayerAmmo(playerid);


	new 
		weapon = GetPlayerWeapon(playerid),
		clip = GetPlayerSkillLevel(playerid, GetSkillFromWeapon(weapon)) == 999 ? (weapClipSize[weapon] * 2) : weapClipSize[weapon]; 

		
	weap_Clip[playerid][weaponSlot[weapon]] = clip;
	weap_Extra[playerid][weaponSlot[weapon]] = ammo - clip;

	return 1;
}


//
//	HOOKS
//

#if defined _ALS_OnIncomingPacket
	#undef OnIncomingPacket
#else
	#define _ALS_OnIncomingPacket
#endif
#define OnIncomingPacket WEA_OnIncomingPacket

#if defined WEA_OnIncomingPacket
	forward WEA_OnIncomingPacket(playerid, packetid, BitStream:bs);
#endif



#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif

#define GivePlayerWeapon WEA_GivePlayerWeapon	
