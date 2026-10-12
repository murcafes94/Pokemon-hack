MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "Cuando el EQUIPO MAGMA pasa lista,\nasignan las tareas más importantes\la los que llegan primero.\pPor eso estoy pringando aquí,\n¡porque siempre llego tarde!$"
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "¡También llego tarde a las sesiones\nde entrenamiento!\pOdio tener que reconocerlo,\npero no valgo para gran cosa…$"
	.string ""
	.string ""

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Bueno, voy a intentar esforzarme\nmás de ahora en adelante…$"
	.string ""

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Nuestro líder nos dijo que caváramos\nen el MONTE CENIZO, y eso hicimos.\pCavando, cavando, nos encontramos\ncon algo absolutamente alucinante.\p¿Que qué era?\p¡Jua, jua, jua!\n¡Te lo diré si me ganas!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "¡Aaaargh!\n¡Me has ganado!$"
	.string ""

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Pues pensándolo bien, no te lo voy a\ndecir. Ya lo verás con tus propios ojos.\pNo querrás que te fastidie la sorpresa,\n¿no?$"
	.string ""
	.string ""
	.string ""

