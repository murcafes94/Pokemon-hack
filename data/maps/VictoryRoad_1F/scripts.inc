VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 2, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 3, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "BLASCO: ¡Hola, {PLAYER}!\p¿Te sorprende verme aquí?\pHe conseguido llegar hasta aquí,\n¡y todo gracias a ti!\pDesde que perdí ante ti aquel día,\n{PLAYER}, he mejorado mucho.\p¡Pero esta vez no perderé!\p¡Voy a ganar! ¡Por los POKéMON\nque me han estado apoyando sin cesar!\pMuy bien, ¡allá voy!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "¡Guau!\n{PLAYER}, sí que eres fuerte…$"
	.string ""

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "BLASCO: Hoy no he podido vencerte,\n{PLAYER}, pero uno de estos días…\l¡daremos la vuelta a la tortilla!$"
	.string ""
	.string ""

VictoryRoad_1F_Text_WallyIntro:
	.string "WALLY: Hi! {PLAYER}!\p"
	.string "I've gotten stronger since that last\n"
	.string "time! I wanted to show you, {PLAYER}!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "¡Guau!\n{PLAYER}, sí que eres fuerte…$"
	.string ""

VictoryRoad_1F_Text_WallyPostBattle:
	.string "BLASCO: Hoy no he podido vencerte,\n{PLAYER}, pero uno de estos días…\l¡daremos la vuelta a la tortilla!\p¡Llegaré a la LIGA POKéMON!$"
	.string ""
	.string ""
	.string ""

VictoryRoad_1F_Text_EdgarIntro:
	.string "He llegado hasta aquí un par de veces,\npero el último tramo es tan difícil…$"
	.string ""

VictoryRoad_1F_Text_EdgarDefeat:
	.string "Hala, otra vez he perdido…$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "Has llegado muy lejos. Sigue así\ny llegarás a la cima del CAMPEONATO.\l¡Si alguien puede, eres tú!$"
	.string ""
	.string ""

VictoryRoad_1F_Text_AlbertIntro:
	.string "¡No he llegado hasta aquí para perder\nahora! ¡Eso no es una opción!$"
	.string ""

VictoryRoad_1F_Text_AlbertDefeat:
	.string "No puede ser…\nHe perdido…$"
	.string ""

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "He perdido este combate…\pEso quiere decir que no estoy\ncualificado para ser CAMPEÓN…$"
	.string ""
	.string ""

VictoryRoad_1F_Text_HopeIntro:
	.string "El camino hasta la VICTORIA\nes largo y tortuoso, como esta calle…$"
	.string ""

VictoryRoad_1F_Text_HopeDefeat:
	.string "¡Tú sí que sabes combatir!$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "Parece que tienes madera. Creo que\npuedes hacerte con el CAMPEONATO.$"
	.string ""

VictoryRoad_1F_Text_QuincyIntro:
	.string "¿Que qué es la CALLE VICTORIA?\n¡Te lo diré si me ganas!$"
	.string ""

VictoryRoad_1F_Text_QuincyDefeat:
	.string "¡Perfecto!\n¡Bien hecho!$"
	.string ""

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "Llegar hasta aquí de una pieza es la\nprueba final para cualquier ENTRENADOR\lque quiera hacerse con el CAMPEONATO.\pPor eso se llama CALLE VICTORIA.$"
	.string ""
	.string ""
	.string ""
	.string ""

VictoryRoad_1F_Text_KatelynnIntro:
	.string "No tengo nada que decir a quien\nya ha llegado tan lejos. ¡Adelante!$"
	.string ""

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "Qué vergüenza más grande…$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "En fin, sigue avanzando.\nLo que hagas me importa un comino.$"
	.string ""
