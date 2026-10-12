MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MOSSDEEP_MAXIE
	removeobject LOCALID_MOSSDEEP_GRUNT_1
	removeobject LOCALID_MOSSDEEP_GRUNT_2
	removeobject LOCALID_MOSSDEEP_GRUNT_3
	removeobject LOCALID_MOSSDEEP_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_MOSSDEEP_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "MÁXIMO me ha dado esto,\npero no sé para qué sirve.\pCreo que se llama ROCA del REY.\n¿La quieres?$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_YouCanKeepIt:
	.string "¿Y para qué la quieres?\nMira que la gente es rara…\pBueno, quédatela, pero no\nse lo digas a MÁXIMO.$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_StevensHouseOverThere:
	.string "¡La casa de MÁXIMO está justo ahí!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "¡Justamente eso digo yo! ¿Qué se\npuede hacer con una roca rara?$"
	.string ""

MossdeepCity_Text_WailmerWatching:
	.string "Cerca de ALGARIA, puedes ver\nWAILMER salvajes.\pEl sitio en cuestión se llama…\n¿Cómo se llama…?\pPuesto…, puesto de algo…\p¡Puesto de observación de WAILMER!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "El CENTRO ESPACIAL de esta isla\nha estado lanzando cohetes enormes.\pEs que andan bastante alborotados\na causa de una carta que han recibido.$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "El CENTRO ESPACIAL de esta isla\nha estado lanzando cohetes enormes.$"
	.string ""

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Un MARINERO me ha dicho que el EQUIPO\nAQUA la ha montado gorda en CALAGUA.\p¡También he oído que alguien\nles ha dado una buena paliza!\pPero ahora CIUDAD ALGARIA ha pasado\na ser un objetivo del EQUIPO MAGMA.\pSi quieres saber qué están tramando,\nve a visitar el CENTRO ESPACIAL.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_FeelReliefOnLand:
	.string "Soy un MARINERO, así que el mar\nes muy importante para mí.\pPero cuando vuelvo a tierra después\nde un viaje, respiro tranquilo, ¿sabes?$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "Qué bonito sería…\psi el mundo entero estuviera cubierto\nde flores y plantas como las de aquí.$"
	.string ""
	.string ""

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Todo ser vivo necesita el mar,\naunque viva en la tierra.\pTodo ser vivo, con el tiempo, se\nconvierte en polvo y vuelve a la tierra.\pEl mar y la tierra están conectados…,\pbasta mirar la costa para darse cuenta.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_SurfExhilarating:
	.string "Un viaje en barco es divertido.\pPero cruzar el mar con un POKéMON\nque hace SURF…\p¡Eso sí que es un puntazo!\n¿A que sí?$"
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Esta roca tiene un significado especial\npara la gente del CENTRO ESPACIAL.\pEs como un talismán para que los\ncohetes despeguen sin problemas.\pY tú, cuando formulas un deseo,\n¿usas algún amuleto?\pYo tengo una frase mágica…\n¡y siempre funciona!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_ItsAWhiteRock:
	.string "Es una roca blanca.$"

MossdeepCity_Text_GymSign:
	.string "GIMNASIO POKéMON de CIUDAD ALGARIA\nLÍDERES: LETI Y VITO\p“¡Una combinación mística!”$"
	.string ""
	.string ""

MossdeepCity_Text_CitySign:
	.string "CIUDAD ALGARIA\p“Nuestra divisa: ¡quiere\na los POKéMON!”$"
	.string ""

MossdeepCity_Text_SpaceCenterSign:
	.string "CENTRO ESPACIAL de ALGARIA\p“¡A un paso del espacio exterior!”$"
	.string ""

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "TRETO: {PLAYER}{KUN}, ¿cómo estás?\n¡Yo estoy estupendamente!\pHe oído que los LÍDERES de GIMNASIO\nde CIUDAD ALGARIA son bastante\lfuertes, así que quiero comprobarlo.\pPero hay algo en esta ciudad\nque no me da buena espina.\pTodos hablan de una misteriosa carta\nde advertencia y del CENTRO ESPACIAL…\pAunque yo creo que todo eso\na mí no me atañe.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Aaah… Qué bien se está con\nel mar acariciándote los pies…\pHablando de olas, ¿conoces la\nciudad-isla de ARRECÍPOLIS?\pCreo que el GIMNASIO de allí\ntiene un nuevo LÍDER.\pAl parecer, el nuevo LÍDER fue\nel mentor de PLUBIO en su día.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

