MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Comprendo las razones del JEFE,\npero ¿sabes una cosa?\pEsto de desenterrar POKéMON antiguos\ny birlarle un METEORITO\la un pobre inocente…\pNo sé yo, igual estamos yendo\ndemasiado lejos. ¿Tú qué crees?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Sí, me parece que estamos haciendo\nalgo mal.$"
	.string ""

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "Esta derrota me ha aclarado las ideas.\pLa próxima vez que vea al JEFE, le voy\na pedir explicaciones sobre todo esto.$"
	.string ""
	.string ""

