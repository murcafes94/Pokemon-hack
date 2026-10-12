Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} escribió el código secreto\nen la puerta.\p“El MAESTRO TRETA\nes mi inspiración.”\lY…\p¡la puerta se ha abierto!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "Cuando oí que había una casa rara\npor aquí, vine a ver cómo era.$"
	.string ""

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "¡Y me encontré con alguien\nque me ha dado una paliza!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "Me lo paso de miedo cotilleando\npor la casa.\p¡Es un reto que no dudo en repetir!$"
	.string ""
	.string ""
	.string ""

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "Quizás pueda conseguir que mi POKéMON\nPÁJARO sobrevuele el muro…$"
	.string ""

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "¡Aaaaah! ¡La pifié!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Ejem, ejem… Creo que he perdido\nporque he intentado hacer trampa…$"
	.string ""

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "Estas puertas giratorias me están\nrevolviendo el estómago…$"
	.string ""

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Todo gira y gira y gira…\nAy, ay, ay, no puedo más…$"
	.string ""

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "No entiendo, a ti no te da ni fu ni fa…\n¿O estás poniendo cara de póquer?$"
	.string ""

