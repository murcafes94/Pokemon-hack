MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Cuando estoy aquí…\nsiento un extraño poder dentro de mí.$"
	.string ""

MtPyre_6F_Text_ValerieDefeat:
	.string "Pues esta vez no lo he sentido mucho…$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Quizás provenga del espíritu de los\nPOKéMON que a veces acuden aquí…$"
	.string ""

MtPyre_6F_Text_ValerieRegister:
	.string "Ji, ji, ji… He perdido el combate, pero…\ntodavía puedo sorprenderte…\pNo hace falta ni que ponga mis manos\nsobre tu POKéNAV… ¡Toma ya!$"
	.string ""
	.string ""
	.string ""

MtPyre_6F_Text_ValerieRematchIntro:
	.string "¡Detrás de ti!\n¿Qué es eso?$"
	.string ""

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "Pues juraría que había algo…$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "Los POKéMON que descansan aquí\npueden ser muy juguetones.$"
	.string ""

MtPyre_6F_Text_CedricIntro:
	.string "¿Has perdido el norte?\n¡No te preocupes, que aquí estoy yo!$"
	.string ""

MtPyre_6F_Text_CedricDefeat:
	.string "¿Pero tú no te habías perdido?$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Pensaba que era más fácil derrotar\na los ENTRENADORES que se pierden.\pNo volveré a intentar un truco\ntan sucio nunca más…$"
	.string ""
	.string ""

