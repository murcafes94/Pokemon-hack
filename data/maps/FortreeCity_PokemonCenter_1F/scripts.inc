FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FORTREE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Oye, dime, ¿estás intentando\ncompletar tu POKéDEX?\pPues entonces ve a la ZONA SAFARI,\nen la RUTA 121. No te arrepentirás.$"
	.string ""
	.string ""
	.string ""

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "¿Has hecho algo en el CENTRO\nde RÉCORDS?\pEstá bastante bien. Mezcla y combina\nlos récords de los ENTRENADORES.\pNo estoy seguro de cómo funciona,\npero es de lo mejorcito que hay.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "¡Anda, si tienes un POKéNAV!\nEs igualito que el mío.\p¿Has oído hablar de la AGENDA\ndel MÓVIL del POKéNAV?\pConsúltala cuando quieras charlar\ncon los ENTRENADORES registrados.\pTambién te indicará qué ENTRENADORES\nquieren volver a luchar contigo.\p¿No es estupendo?\n¡Y todo gracias a DEVON!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

