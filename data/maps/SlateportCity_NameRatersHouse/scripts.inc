SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	chooseboxmon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "¡Je, je! ¡Hola! ¡Soy el INSPECTOR\nde los MOTES! ¡El adivinador de nombres!\pEstaré encantado de evaluar\nel nombre de tu POKéMON, je, je.$"
	.string ""
	.string ""
	.string ""

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "¿Qué nombre de POKéMON\nquieres que adivine y evalúe?$"
	.string ""

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Mmmmm… {STR_VAR_1}, ¿a que sí?\nNo está mal, no está mal…\pPero ¿no crees que podríamos\nencontrar un nombre aún mejor?$"
	.string ""
	.string ""
	.string ""

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Así me gusta. A ver…\n¿Cuál será el nuevo nombre?$"
	.string ""

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "¡Ya está! ¡A partir de ahora, el nombre\nde este POKéMON será {STR_VAR_1}!\pEs un nombre mucho mejor que\nel anterior, ¡qué suerte tienes!$"
	.string ""
	.string ""
	.string ""

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
	.string "Entiendo…\nEntonces vuelve cuando quieras.$"
	.string ""

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "¡Ya está! ¡A partir de ahora, el nombre\nde este POKéMON será {STR_VAR_1}!\pNo parece muy diferente del anterior\ny, sin embargo, es muchísimo mejor.\l¡Qué suerte tienes!$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_NameRatersHouse_Text_MagnificentName:
	.string "Mmmm… ¡Será {STR_VAR_1}!\p¡He aquí un mote magnífico!\n¡Absolutamente irreprochable!\pHarás bien en querer mucho\na tu {STR_VAR_1} de ahora en adelante.$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "Pero vamos a ver…\n¡Esto es sólo un HUEVO!$"
	.string ""

