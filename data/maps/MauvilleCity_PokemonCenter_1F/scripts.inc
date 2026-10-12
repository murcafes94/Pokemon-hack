MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_MAUVILLE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings:
	.string "¡Ese hombre de ahí dice unas cosas\nmuy raras!\pEn cierto modo tiene gracia.\nCreo que no le olvidaré fácilmente.$"
	.string ""
	.string ""
	.string ""

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
	.string "Cuando accedí al CENTRO de RÉCORDS,\nse actualizaron los datos de lo que\lmás mola en AZULIZA.\p¡Ahora esos datos son los mismos\nque los de mis amigos!$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
	.string "Han abierto un CENTRO de RÉCORDS\nen la planta de arriba del CENTRO\lPOKéMON.\pNo sé de qué va, pero suena díver.\n¡Voy a echar un ojo!$"
	.string ""
	.string ""
	.string ""

