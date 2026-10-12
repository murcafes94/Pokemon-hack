PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_PACIFIDLOG_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard:
	.string "¿De qué color es tu FICHA de\nENTRENADOR? ¡La mía es de color cobre!$"
	.string ""

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola:
	.string "PUEBLO OROMAR flota sobre\nuna colonia de CORSOLA.\pSi te digo eso, ¿tú te lo crees?$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats:
	.string "Dicen que los antepasados\nde los habitantes de OROMAR nacían,\lvivían y morían en barcos.\pCreo que vivían de ese modo\nporque iban en busca de algo.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

