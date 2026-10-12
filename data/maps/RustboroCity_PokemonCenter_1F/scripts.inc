RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "Mi POKéMON tiene una naturaleza\nINGENUA y el de mi amigo tiene\luna naturaleza ALEGRE.\p¡Es increíble ver cómo cada POKéMON\ntiene una personalidad diferente!$"
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Los POKéMON también pueden ser\nmachos o hembras.\pLo que no está claro es cuál\nes la diferencia entre unos y otros.$"
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "¡El hombre de ahí al lado me ha dado\nuna MO!\pLa he usado para enseñar a mi POKéMON\na usar CORTE con los árboles.$"
	.string ""
	.string ""

