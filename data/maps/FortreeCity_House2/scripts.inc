FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_HIDDEN_POWER, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_HIDDEN_POWER
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
	.string "Los poderes ocultos de la gente y de\nlos POKéMON salen a la luz cuando\lviven en contacto con la naturaleza.$"
	.string ""
	.string ""

FortreeCity_House2_Text_CoinInWhichHand:
	.string "Deja que compruebe si tus poderes\nocultos han despertado…\pTengo una moneda en una mano.\pAhora dime, ¿está en la mano derecha?\n¿O quizás en la izquierda?$"
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
	.string "¡Has acertado!\pVolvamos a intentarlo.\p¿Dónde guardo la moneda?\n¿En la mano derecha o en la izquierda?$"
	.string ""
	.string ""
	.string ""

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
	.string "¡Has acertado!\pVolvamos a intentarlo.\p¿Dónde guardo la moneda?\n¿En la mano derecha o en la izquierda?$"
	.string ""
	.string ""
	.string ""

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
	.string "¡Magnífico!\n¡Tus poderes ocultos están activos!\pMira, te voy a dar esto para que puedas\nhacer lo mismo con tus POKéMON.$"
	.string ""
	.string ""
	.string ""

FortreeCity_House2_Text_ExplainHiddenPower:
	.string "PODER OCULTO es un movimiento\nque se adapta a cada POKéMON.$"
	.string ""

FortreeCity_House2_Text_YouGuessedWrong:
	.string "Pues no. Te has equivocado.$"
	.string ""

