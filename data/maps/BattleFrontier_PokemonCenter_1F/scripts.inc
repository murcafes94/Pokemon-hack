BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FRONTIER_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker::
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon:
	.string "¡Antes ha estado aquí alguien con un \nPOKéMON que no había visto nunca!\pPor lo menos nadie me habló de él\nen la ESCUELA de ENTRENADORES.\pYa me gustaría saber dónde se pueden\npillar POKéMON como ése…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena:
	.string "¡Vale! Próxima parada, ¡el DOJO BATALLA!\nSerá mejor que escoja bien los POKéMON\ldel Sistema de Almacenamiento del PC.$"
	.string ""
	.string ""

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge:
	.string "¡Ji, ji!… ¡Voy a ganar un combate\ndetrás de otro con este pequeñín!$"
	.string ""

BattleFrontier_PokemonCenter_1F_Text_Skitty:
	.string "SKITTY: ¡Skimiau!$"

