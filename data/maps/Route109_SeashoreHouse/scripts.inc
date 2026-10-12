Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hidemoneybox
	giveitem ITEM_SODA_POP
.else
	giveitem ITEM_SODA_POP
	hidemoneybox
.endif
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "Soy el dueño de la CASA de la PLAYA,\npero me puedes llamar SR. MARINO.\pLo que más me gusta del mundo es ver\ncombates POKéMON bien candentes.\p¡A ver si tú también peleas con pasión!\pSi logras derrotar a todos los\nENTRENADORES, tendrás una recompensa.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "¡Me encantan los combates al rojo vivo!\pTengo esta CASA de la PLAYA sólo\ny exclusivamente por eso.$"
	.string ""
	.string ""

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "¡Eres como un volcán en erupción!\n¡Esos combates han sido tremendos!\l¡Estoy la mar de satisfecho!\pQué bien que te haya podido ver\nen racha. Toma esto como regalo.\p¡Son seis botellas de REFRESCO!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route109_SeashoreHouse_Text_BagFull:
	.string "Eh, tienes la MOCHILA que va a estallar.\nTe las voy a guardar mientras…$"
	.string ""

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "¿Quieres comprar un REFRESCO?\n¡A los POKéMON les chifla!\p¡Sólo son 300¥ la botella!\n¡Está tirado!$"
	.string ""
	.string ""
	.string ""

Route109_SeashoreHouse_Text_HereYouGo:
	.string "¡Aquí tienes!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "Oye, estás sin blanca…$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "¿No quieres?\n¡Tú te lo pierdes!$"
	.string ""

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "¡Si buscas combates en alta mar, yo\nsoy el ENTRENADOR adecuado, grumete!$"
	.string ""
	.string ""

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "¡Éste ha sido un señor combate!\n¡Acepto la derrota, grumete!$"
	.string ""

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "Ir a CIUDAD PORTUAL es sinónimo\nde combates al rojo vivo y REFRESCOS\lhelados. ¡Todo un contraste!$"
	.string ""

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Las peleas aburridas no valen la pena.\pLos combates feroces sí que hacen\nmejorar a ENTRENADORES y POKéMON.$"
	.string ""
	.string ""

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "¡Más feroz que el lobo de Caperucita!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Bueno, tengo una sed que me muero.\nVoy a comprarme un REFRESCO.$"
	.string ""

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Te voy a demostrar que mis POKéMON\nno tienen rival. ¡Luego no te quejes!$"
	.string ""

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "He perdido, pero no me quejo…$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Si alguno de mis POKéMON supiera\nel movimiento que te transporta por\lel agua, podría olvidarme del flotador…$"
	.string ""
	.string ""

