LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LAVARIDGE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "Creo que los POKéMON se van uniendo\nmás a los ENTRENADORES a medida\lque van pasando más tiempo juntos.\pCuanto más tiempo, mejor.\nEso creo.$"
	.string ""
	.string ""
	.string ""

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "Es increíble cómo pueden devolverte\nla energía estos baños termales.\p¡Cómo me gustaría poder meter\ntambién aquí a mis POKéMON!$"
	.string ""
	.string ""
	.string ""

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "¡Jo, jo, jo! Oye, joven, por aquí\nllegarás a los baños termales.\pLos POKéMON descansan, ¿no?\nPues los ENTRENADORES también.$"
	.string ""
	.string ""
	.string ""

