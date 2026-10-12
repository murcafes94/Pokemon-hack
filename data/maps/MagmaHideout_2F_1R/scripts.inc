MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "¿Y esto? Pero vamos a ver…\p¡Los únicos que pueden estar aquí son\nlos miembros del EQUIPO MAGMA!\pY tú no llevas el uniforme\ndel EQUIPO MAGMA…\p¡Has levantado mis sospechas!\n¡Te voy a dar para el pelo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Ay, ay, ay…\nMe has machacado el orgullo…$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "Si siempre tienes frío, deberías\nunirte al EQUIPO MAGMA.$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "¡Los pies quietos!\p¿No esperarás que cierre el pico y\ndeje que te pires por tu cara bonita?$"
	.string ""
	.string ""

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "¡Vale, vale, vale!\n¡Me rindo!$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "Quizás hubiera sido mejor hacer\ncomo que no te había visto…$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "¡Ajá!\n¡Tú te has colado!$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "¡Aaaaah!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "Perder, ya he perdido.\p¿Qué sentido tiene seguir\ndando vueltas?$"
	.string ""
	.string ""

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "¡Vaya, vaya, vaya!\n¡Si se nos ha infiltrado alguien!$"
	.string ""

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Me has dejado sin palabras…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "La verdad es que no se me da bien\nluchar…$"

