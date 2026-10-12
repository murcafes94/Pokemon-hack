RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
	call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "Soy el SR. PEÑAS, el PRESIDENTE\nde DEVON S.A.\p¿Puedo hablar contigo un segundo?\pNos has salvado no sólo una vez,\n¡sino dos veces!\pEres una persona asombrosa…\ny quisiera pedirte un favor.\pTengo entendido que vas a llevar\nun paquete a los ASTILLEROS\lque hay en CIUDAD PORTUAL.\p¿Podrías parar de camino un\nsegundo en PUEBLO AZULIZA?\pTe agradecería que le entregaras\nuna CARTA a MÁXIMO en AZULIZA.$"
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
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "SR. PEÑAS: No sé si lo sabrás,\npero soy un gran PRESIDENTE.\pNunca me he aprovechado de nadie\ny siempre devuelvo los favores.\p¡Por eso quiero darte esto!$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{PLAYER} recibió un POKéNAV.$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp:
	.string "SR. PEÑAS: Este dispositivo es…\p¡un POKéNAVEGADOR!\nPOKéNAV, para abreviar…\pSe trata de una herramienta esencial\npara todo ENTRENADOR aventurero.\pIncluye un mapa de la región de HOENN.\pPuedes consultar las ubicaciones\nde AZULIZA y CIUDAD PORTUAL\len un abrir y cerrar de ojos.\pPor cierto, he oído que esos siniestros\ndelincuentes, creo que se llaman MAGMA\ly AQUA, no paran de dar problemas.\pMe parece que sería buena idea\nque descansaras antes de seguir.$"
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
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare:
	.string "SR. PEÑAS: En fin, {PLAYER}{KUN},\nve con cuidado.$"
	.string ""

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "SR. PEÑAS: ¡Cuento contigo!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "SR. PEÑAS: ¿Has entregado mi CARTA?\n¡Muchas gracias!\pY también quiero agradecértelo así.\nComo entrenas POKéMON, te vendrá bien.$"
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "SR. PEÑAS: Si un POKéMON tiene\nREPARTIR EXP, obtendrá algunos de los\lpuntos de EXPERIENCIA del combate…\p¡Aunque no haya combatido!\pREPARTIR EXP es de lo más\nútil para fortalecer POKéMON débiles.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "SR. PEÑAS: Desde que era un chaval,\nsiempre he trabajado de sol a sol.\pEso no me ha dejado mucho tiempo\npara estar al tanto de las modas.\p¿Todos los jóvenes de ahora quieren\nser ENTRENADORES en la LIGA POKéMON?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "Éste es el segundo piso de DEVON S.A.\pAquí está el DESPACHO de nuestro\nPRESIDENTE.\pBueno, sólo quería decirte cuánto\naprecio lo que has hecho.\pEh… Por cierto… Ese paquete que\nnos has devuelto…\p¿Podrías llevarlo a los ASTILLEROS\nde CIUDAD PORTUAL?\pSería horrible que nos lo volvieran\na robar…\pAsí que, ejem, ¿puedo contar contigo\npara que te ocupes de eso?\p¡Qué bien!\n¿Puedes esperar un segundo aquí?$"
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
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "Nuestro PRESIDENTE querría hablar\nun momento contigo.\pAcompáñame, por favor.$"
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "Aquí es. Adelante.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "Si vas a los ASTILLEROS\nde CIUDAD PORTUAL, no olvides visitar\lal CAPITÁN BABOR.$"
	.string ""

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "Los nuevos productos de DEVON, la\nACOPIO BALL y la TURNO BALL, están\lhaciendo furor entre los ENTRENADORES.$"
	.string ""
	.string ""

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
	.string "Se trata de una colección de libros\nraros y rocas poco comunes\lque ha reunido el PRESIDENTE.$"
	.string ""

