Route111_OldLadysRestStop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition:
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady::
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest::
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest::
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere:
	.string "Ay, ay, ay…\nTus POKéMON parecen agotados…\p¿Por qué no descansas aquí?\nEs lo mejor que puedes hacer, en serio.$"
	.string ""
	.string ""
	.string ""

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp:
	.string "Exacto.\nTómate tu tiempo y descansa.$"
	.string ""

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest:
	.string "Ay, ay, ay…\nTus POKéMON siguen hechos polvo…\p¿Por qué no vuelves a descansar aquí?\nEs lo mejor que puedes hacer, en serio.$"
	.string ""
	.string ""
	.string ""

Route111_OldLadysRestStop_Text_DontNeedToBeShy:
	.string "¿Seguro?\nYo que tú me lo pensaría dos veces…$"
	.string ""

