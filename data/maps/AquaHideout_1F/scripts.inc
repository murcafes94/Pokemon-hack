AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "¿Qué haces aquí? ¿Por qué vienes\na dar la lata al EQUIPO AQUA?\p¡Nuestro JEFE no está aquí!\n¡Ha ido a birlar algo muy importante!\p¿Qué?\n¿Que adónde ha ido?\p¡Jua, jua, jua! ¿Pero tú crees que te\ndiría algo tan sumamente importante?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "¿Cómo? ¿Qué?\n¿Eres un secuaz del EQUIPO MAGMA?\pMe han dicho que el EQUIPO MAGMA\nestá intentado despertar a un POKéMON\limpresionante en su GUARIDA.\pPero ¿dónde estará su GUARIDA?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "¿Qué haces aquí? ¿Por qué vienes\na dar la lata al EQUIPO AQUA?\p¡Nuestro JEFE no está aquí!\n¡Ha ido a mangar un submarino!\p¿Qué?\n¿Que adónde ha ido?\p¡Jua, jua, jua! ¿Pero tú crees que te\ndiría algo tan sumamente importante?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "¿Qué haces aquí? ¿Por qué vienes\na dar la lata al EQUIPO AQUA?\p¡Nuestro JEFE no está aquí! ¡Está en\nla RUTA 122, de camino al MONTE PÍRICO!\p¿Qué?\n¿Que por qué se ha ido?\p¡Jua, jua, jua! ¿Pero tú crees que te\ndiría algo tan sumamente importante?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "¿Cómo? ¿Qué?\n¿Eres un secuaz del EQUIPO MAGMA?\pMe han dicho que el EQUIPO MAGMA\nanda detrás de un POKéMON,\lallá por el MONTE CENIZO.\pPero ¿cómo será ese POKéMON?$"
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "¿Qué haces aquí? ¿Por qué vienes\na dar la lata al EQUIPO AQUA?\p¡Nuestro JEFE no está aquí!\n¡Está de camino a CIUDAD PORTUAL!\p¿Qué?\n¿Que por qué se ha ido?\p¡Jua, jua, jua! ¿Pero tú crees que te\ndiría algo tan sumamente importante?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_1F_Text_Grunt1Intro:
	.string "¡Personaje sospechoso a la vista!$"
	.string ""

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Brrr…\n¡He perdido!$"
	.string ""

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "El EQUIPO no estará satisfecho,\npero yo he hecho lo que he podido…$"
	.string ""

