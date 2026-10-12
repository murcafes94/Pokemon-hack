Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} escribió el código secreto\nen la puerta.\p“El MAESTRO TRETA\nes amable.”\lY…\p¡la puerta se ha abierto!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "No hay muchos ENTRENADORES\nque hayan llegado hasta aquí…$"
	.string ""

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "Así que debes de ser muy fuerte…$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "¿Has vencido al CAMPEÓN de la LIGA\nPOKéMON? ¡Menos lobos!$"
	.string ""

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "¡Puedes darte con un canto en los\ndientes por luchar contra mí!$"
	.string ""

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "¡Esto no puede ser!\n¡Yo nunca había perdido antes!$"
	.string ""

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "Me has vencido de pura chorra.\nPuede darte para fardar un rato…$"
	.string ""

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "Te las has apañado bien en el desafío\nde la CASA TRETA…$"
	.string ""

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "Ya entiendo…\nPosees un estilo único e inimitable…$"
	.string ""

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Alguien como tú le tiene que gustar\npor fuerza al MAESTRO TRETA.$"
	.string ""

