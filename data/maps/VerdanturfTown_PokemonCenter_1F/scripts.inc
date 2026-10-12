VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_VERDANTURF_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "¡Nadie puede considerarse ENTRENADOR\nsi no tiene fe en sus POKéMON!\pSólo aquellos que confían plenamente\nen la habilidad de sus POKéMON podrán\lllegar hasta el final.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "La razón por la que todo el mundo\nestá viniendo a VERDEGAL…\pEs su TIENDA de BATALLA.\nNo hace falta que lo diga.\p¿O es que has venido a ver a alguien?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

