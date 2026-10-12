Route110_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Route110_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} escribió el código secreto\nen la puerta.\p“El MAESTRO TRETA\nes fabuloso.”\lY…\p¡la puerta se ha abierto!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route110_TrickHousePuzzle1_Text_SallyIntro:
	.string "Me voy a hacer con la victoria gracias\nal movimiento que acabo de aprender.$"
	.string ""

Route110_TrickHousePuzzle1_Text_SallyDefeat:
	.string "Vaya, contigo no funciona…$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "Este nuevo movimiento es estupendo.\n¡No me canso de usarlo!$"
	.string ""

Route110_TrickHousePuzzle1_Text_EddieIntro:
	.string "He llegado hasta esta casa tan\nrara sin querer…$"
	.string ""

Route110_TrickHousePuzzle1_Text_EddieDefeat:
	.string "Y encima voy y pierdo…$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "Me he perdido, he perdido luchando\ny ahora… ¡no sé ni cómo volver a casa!$"
	.string ""

Route110_TrickHousePuzzle1_Text_RobinIntro:
	.string "¿Pero quién es ese MAESTRO TRETA?$"

Route110_TrickHousePuzzle1_Text_RobinDefeat:
	.string "¡Has vencido porque estaba sumida\nen mis pensamientos, que conste!$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "¡Qué fuerte eres!\n¿De dónde sales?$"
	.string ""

