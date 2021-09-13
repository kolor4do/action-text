#if defined action_text_included
	#endinput
#endif
#define action_text_included

/*
	Functions:

		ShowActionText(playerid, const message[], time = 2000, color = -1);
        HideActionText(playerid);
        IsPlayerViewingActionText(playerid);
*/

#include <a_samp>

static
PlayerText: act_Textdraw[MAX_PLAYERS],
bool:       act_Viewing[MAX_PLAYERS],
            act_Timer[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
	act_Textdraw[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 320.000000, "_");
    PlayerTextDrawFont              (playerid, act_Textdraw[playerid], 1);
    PlayerTextDrawLetterSize        (playerid, act_Textdraw[playerid], 0.500000, 2.000000);
    PlayerTextDrawTextSize          (playerid, act_Textdraw[playerid], 160.000000, 480.000000);
    PlayerTextDrawSetOutline        (playerid, act_Textdraw[playerid], 1);
    PlayerTextDrawSetShadow         (playerid, act_Textdraw[playerid], 1);
    PlayerTextDrawAlignment         (playerid, act_Textdraw[playerid], 2);
    PlayerTextDrawColor             (playerid, act_Textdraw[playerid], -1);
    PlayerTextDrawBackgroundColor   (playerid, act_Textdraw[playerid], 127);
    PlayerTextDrawBoxColor          (playerid, act_Textdraw[playerid], 0);
    PlayerTextDrawUseBox            (playerid, act_Textdraw[playerid], 0);
    PlayerTextDrawSetProportional   (playerid, act_Textdraw[playerid], 1);
    PlayerTextDrawSetSelectable     (playerid, act_Textdraw[playerid], 0);
    act_Viewing[playerid] = false;
	#if defined act_OnPlayerConnect
		return act_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect act_OnPlayerConnect
#if defined act_OnPlayerConnect
	forward act_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    PlayerTextDrawDestroy(playerid, act_Textdraw[playerid]);
    #if defined act_OnPlayerDisconnect
		return act_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect act_OnPlayerDisconnect
#if defined act_OnPlayerDisconnect
	forward act_OnPlayerDisconnect(playerid, reason);
#endif

stock ShowActionText(playerid, const message[], time = 2000, color = -1)
{
    KillTimer(act_Timer[playerid]);
    act_Timer[playerid] = SetTimerEx("HideActionText", time, false, "d", playerid);
    PlayerTextDrawSetString         (playerid, act_Textdraw[playerid], message);
    PlayerTextDrawColor             (playerid, act_Textdraw[playerid], color);
    PlayerTextDrawShow              (playerid, act_Textdraw[playerid]);
    act_Viewing[playerid] = true;

    return 1;
}

forward HideActionText(playerid);
public HideActionText(playerid)
{
    if(IsPlayerConnected(playerid))
    {
        PlayerTextDrawHide(playerid, act_Textdraw[playerid]);
        act_Viewing[playerid] = false;
    }
}

stock bool:IsPlayerViewingActionText(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return false;
	}

	return act_Viewing[playerid];
}
