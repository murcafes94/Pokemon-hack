DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "¡Recrea la vista en esto!\pEs un PAÑUELO de SEDA.\nEs lo último de lo último.\lUna preciosidad.\pAjá, ya veo que te gusta…\n¡Te brillan los ojos y todo!\p¡Me has caído bien!\n¡Toma, te lo voy a dar!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_House2_Text_NoRoom:
	.string "Anda, ¿no tienes sitio?\pEscúchame bien: todo el mundo tendría\nque tener un PAÑUELO como éste.\l¡Yo daría lo que fuera por tenerlo!$"
	.string ""
	.string ""
	.string ""

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "El PAÑUELO de SEDA aumenta la potencia\nde los movimientos de tipo NORMAL.\pEs un PAÑUELO maravilloso que sienta\nde miedo a casi cualquier POKéMON.$"
	.string ""
	.string ""
	.string ""

DewfordTown_House2_Text_BrawlySoCool:
	.string "¡Guau! ¿Has cruzado todo el mar\npara venir a AZULIZA?\p¿Has venido aquí porque has oído\nhablar de MARCIAL?\pEs tan guay…\nTodos lo veneran.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

