OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_OLDALE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "Ese PC de la esquina es para el uso\nde cualquier ENTRENADOR POKéMON.\pEso quiere decir que tú también\nlo puedes usar, claro.$"
	.string ""
	.string ""
	.string ""

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "¡Los CENTROS POKéMON son guays!\pPuedes usar sus servicios todas\nlas veces que quieras y siempre\les gratis. ¡Es una pasada!$"
	.string ""
	.string ""
	.string ""

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "Empezaron a construir el CLUB del CABLE\nPOKéMON del primer piso hace poco.\pY cualquiera sabe cuándo\nacabarán las obras…$"
	.string ""
	.string ""
	.string ""

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "Acabaron de construir el CLUB del CABLE\nPOKéMON del primer piso hace poco.\p¡Vengo de intercambiar un POKéMON!$"
	.string ""
	.string ""

