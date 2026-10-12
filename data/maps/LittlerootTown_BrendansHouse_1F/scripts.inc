LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 8, 4
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 4, 5
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 9, 8
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_PLAYERS_HOUSE_1F_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MAMÁ: ¿Ves, {PLAYER}?\n¿A que esto es muy bonito?$"
	.string ""

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Los POKéMON del servicio de mudanzas\nhacen todo el trabajo duro y además\lrecogen lo que ensucian. ¡Es perfecto!\p{PLAYER}, tu cuarto está arriba.\n¡Ve a verlo, cariño!\pPAPÁ te ha comprado un nuevo\nreloj para que recuerdes este día.\lNo olvides ponerlo en hora.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MAMÁ: ¿Y bien, {PLAYER}?\n¿No quieres ver tu cuarto?$"
	.string ""
	.string ""

PlayersHouse_1F_Text_GoSetTheClock:
	.string "MAMÁ: {PLAYER}, cielo…\pPon en hora el reloj de tu cuarto.$"
	.string ""

PlayersHouse_1F_Text_OhComeQuickly:
	.string "MAMÁ: ¡{PLAYER}, {PLAYER}!\n¡Ven! ¡Ven rápido!$"
	.string ""

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MAMÁ: ¡Mira! ¡El GIMNASIO de PETALIA!\n¡A ver si sale tu padre!$"
	.string ""

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MAMÁ: Pues no… Qué lástima…\pCreo que estaba hace nada y se\nacaba de ir. Mala suerte.$"
	.string ""
	.string ""

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Ah, sí, una cosa.\nUno de los amigos de tu padre vive aquí.\pSe llama PROF. ABEDUL.\pVive aquí al lado. Creo que deberías\nir a verlo y presentarte, cariño.$"
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_SeeYouHoney:
	.string "MAMÁ: ¡Hasta luego, cielo!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MAMÁ: ¿Has ido a presentarte\nal PROF. ABEDUL?$"
	.string ""

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MAMÁ: ¿Cómo estás, {PLAYER}?\nNo pareces muy en forma.\pCreo que deberías descansar un poco.$"
	.string ""
	.string ""

PlayersHouse_1F_Text_TakeCareHoney:
	.string "MAMÁ: ¡Cuídate, cielo!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MAMÁ: ¡Mira por dónde! ¿Tu padre\nte ha dado esa MEDALLA?\p¡Pues yo también quiero darte algo!$"
	.string ""

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "No te esfuerces demasiado, cielo.\nTienes que saber cuándo hay que parar.\p¡Buena suerte y ven a verme\nde vez en cuando!$"
	.string ""
	.string ""

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MAMÁ: ¿Qué es eso, cariño? ¿Un POKéNAV?\n¿Te lo dio alguien de DEVON?\pEntonces, cielo, tendrás que apuntarme\nen él, ¿no?\pMmm…$"
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_RegisteredMom:
	.string "Acabas de registrar a MAMÁ\nen el POKéNAV.$"
	.string ""

PlayersHouse_1F_Text_Vigoroth1:
	.string "¡Vigoró, vigoró!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Goro, goro-goro…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "ENTREVISTADOR: Y, desde el GIMNASIO\nde PETALIA, nos despedimos de todos.$"
	.string ""

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Hay una peli en la tele.\pDos hombres están bailando sobre\nel teclado de un piano de cola.\pBueno, mejor dejo de ver la tele.$"
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Son las instrucciones de las \nDEPORTIVAS.\p“Pulsa el Botón B cuando lleves las\nDEPORTIVAS para salir pitando.\pPonte las DEPORTIVAS y empieza\na correr por todas partes.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "PAPÁ: ¿Eh?\p¡Pero si es mi {PLAYER}!\pHace un siglo que no te veo…\n¡Si pareces mucho más fuerte!\pÉsa es la impresión que das, ¡pero\ntu padre aún puede dar guerra!\pAh, sí, tengo algo para ti.\nTe lo envía un tal SR. ARENQUE.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "PAPÁ: ¿Un TICKET para el ferry?\pSi recuerdo bien, los puertos donde\natraca son CIUDAD PORTUAL y CALAGUA.$"
	.string ""
	.string ""

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "Mejor vuelvo al GIMNASIO de PETALIA.\pCariño, gracias por ocuparte\nde la casa mientras yo estoy fuera.$"
	.string ""
	.string ""

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MAMÁ: Este padre tuyo…\pCuando por fin viene un poco a casa,\nsólo se le ocurre hablar de POKéMON.\pDebería relajarse un poco y quedarse\nmás tiempo aquí tranquilito…$"
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MAMÁ: ¿Un especial informativo?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "¡Interrumpimos la programación para\ntraerles las últimas noticias!\pHay noticias confusas sobre supuestos\navistamientos de un POKéMON azzzrt…\lvolando en distintos puntos de HOENN.\pActualmente se desconoce la identidad\ndel POKéMON.\pY ahora les dejamos con la programación\nhabitual.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MAMÁ: {PLAYER}, ¿has oído eso?\p¿De qué color ha dicho el de\nla tele que era ese POKéMON?$"
	.string ""
	.string ""

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MAMÁ: ¡Ver para creer!\n¡Aún hay POKéMON desconocidos!$"
	.string ""
