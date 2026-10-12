PacifidlogTown_House4_MapScripts::
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl::
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman::
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogTown_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes::
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No::
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon:
	.string "La gente dice que han visto un POKéMON\nde tipo VOLADOR sobre HOENN.\pDicen que no para de dar vueltas…\n¿No necesita descansar nunca?$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House4_Text_SkyPokemon:
	.string "¡Hay un POKéMON en el cielo!\n¡Hay un POKéMON en el cielo!$"
	.string ""

PacifidlogTown_House4_Text_WhereDidYouComeFrom:
	.string "¿De dónde vienes?$"

PacifidlogTown_House4_Text_YesTown:
	.string "¿Ah, sí?\n¿Del PUEBLO SÍ?\pQué nombre tan raro para un pueblo…$"
	.string ""
	.string ""

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere:
	.string "¿De NO? ¿No qué? No entiendo nada…\nTendrás que venir de algún sitio, ¿no?\pA ver… No irás a meterme el rollo de que\nnaciste en el fondo del mar, matarile…$"
	.string ""
	.string ""
	.string ""

