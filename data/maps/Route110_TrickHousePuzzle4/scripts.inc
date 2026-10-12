Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} escribió el código secreto\nen la puerta.\p“El MAESTRO TRETA\nes guay.”\lY…\p¡la puerta se ha abierto!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Me duele la cabeza de pensar…\n¡Luchar cuesta menos trabajo!$"
	.string ""

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Me da igual haber perdido…\n¡Luchar sigue siendo lo mejor!$"
	.string ""

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "¡Por supuesto! Yo iría a cualquier sitio\ndonde hubiera un ENTRENADOR.$"
	.string ""

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "¡Eh, tú! ¿Ves estas rocas tan gordas?\n¡Pues yo las muevo con el dedo meñique!$"
	.string ""

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Puedo mover rocas, pero no\npuedo resolver acertijos…$"
	.string ""

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "No basta con ser musculoso,\n¡también hay que ser ingenioso!$"
	.string ""

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "La CASA TRETA es cada vez más\ntraicionera, ¿no te parece?$"
	.string ""

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "¡Ayyyy!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "Yo creo que nadie ha logrado\nllegar hasta el final…$"

