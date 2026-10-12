TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy LOCALID_PLAYER, 9, 6
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_TRAINER_HILL_NURSE
	addobject LOCALID_TRAINER_HILL_ATTENDANT
	addobject LOCALID_TRAINER_HILL_MAN
	addobject LOCALID_TRAINER_HILL_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_TRAINER_HILL_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 0
	special ShowTrainerHillRecords
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_Text_StillGettingReady:
	.string "Ésta es la COLINA DESAFÍO.\nAquí podrás enfrentarte a otros\lENTRENADORES en una carrera\lpor llegar arriba lo antes posible.\pPor desgracia, aún no está preparado\ntodo. Pásate por aquí en otro momento.$"
	.string ""
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "¡Te damos la bienvenida!\pÉsta es la COLINA DESAFÍO.\nAquí podrás enfrentarte a otros\lENTRENADORES en una carrera\lpor llegar arriba lo antes posible.$"
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "¿Es la primera vez que vienes?\pAntes de entrar, debes\nguardar la partida.$"
	.string ""
	.string ""

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "Veamos…\nLos ENTRENADORES están ahora…\pHasta el nivel {STR_VAR_1}.$"
	.string ""
	.string ""

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "Veamos…\nLos ENTRENADORES están ahora…\p¡Vaya, parece que hay ENTRENADORES\nen todos los niveles!$"
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "¿Quieres enfrentarte a ellos?$"
	.string ""

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "Cronometraré tu tiempo.\n¡Suerte!\pA la una…\pA las dos…\p¡Y a las tres!$"
	.string ""
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "¡Vuelve cuando quieras!$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "Qué pena…\pLa verdad es que te has esforzado\nmucho.\p¡Bueno, otra vez será!$"
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "¡Demuestra lo que sabes!$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "Cuando los ENTRENADORES se\ncambian de sitio, organizan una…\ltremenda.\pPara evitar tanto follón pusimos\nla recepción aquí.\pDisculpa las molestias.$"
	.string ""
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "¡Gracias por participar!$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "En la COLINA DESAFÍO, los participantes\ncompiten en la llamada “contrarreloj”.\pEs una carrera donde se cuenta\nel tiempo que tardas en llegar\ldesde aquí hasta la azotea,\ldonde te espera el dueño del local.\pLos récords de cada categoría están\nexpuestos en el PANEL de TIEMPOS.\l¡Demuestra que no hay nadie\lmás veloz que tú!\pEn los combates que libres contra\nlos ENTRENADORES que te encuentres\len el ascenso, no ganarás ni dinero\lni puntos de EXPERIENCIA.$"
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

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "Oh, I’m sorry, but you appear to have\nonly one POKéMON with you.\pYou will need at least two POKéMON\nto enter this event.$"
	.string ""
	.string ""
	.string ""

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "¡Mmm!\p¡Por fin has llegado!\n¡Ya estás aquí!\p¡Espera! ¡No me lo digas!\n¡Ya sé por qué has subido\lcorriendo hasta aquí!\pQuerías verme a mí, al propietario\nde la COLINA DESAFÍO, porque…\p¡Quieres luchar a mi lado!\n¡¿A que sí?!\p¿Mmm?\n¿Cómo? ¿Que no ha sido por eso?\pBueno, da igual, he visto cómo subías.\n¡Bien luchado! ¡Bravo! ¡Bravo!$"
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

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "Para alguien tan extraordinario,\n¡tengo un regalo extraordinario!$"
	.string ""

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "Oh, no, ¡no tienes sitio para nada!\n¡Vuelve cuando lo tengas!$"
	.string ""

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "¡Oh, espera un momento! ¿De verdad\nhas conseguido llegar aquí tan rápido?\p¡Espléndido! ¡Pero no tenías que\ncorrer tanto para venir a verme!\pAunque es un detalle, claro.\n¡Le pediré a la chica de recepción\lque actualice el PANEL de TIEMPOS!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "Pero bueno…\nNo parece que hayas corrido mucho…$"
	.string ""

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "¿Sabes? Creo que me alegraría más\nsi llegases más rápido la próxima vez.\p¡Seguro que hasta me animaba\na formar un equipo contigo!\p¡Hasta entonces!$"
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "I had the TRAINER HILL built for but\n"
	.string "one reason and one only!\p"
	.string "To find the most suitable partner\n"
	.string "with whom I may form a tag team!$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{STR_VAR_1} min {STR_VAR_2},{STR_VAR_3} s$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "No sé qué clase de ENTRENADORES\ny de POKéMON esperan ahí arriba.\p¡Lo que sí sé es que no dejaré que\nnadie se interponga en mi camino!$"
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "He oído que a esta COLINA DESAFÍO\nvienen ENTRENADORES de todas partes.\p¡Estoy deseando probar!\p¡Voy a quitar de en medio a todos\nlos que se me pongan por delante!$"
	.string ""
	.string ""
	.string ""
	.string ""

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "¿Has visto el PANEL de TIEMPOS de ahí?\pMis amigos y yo estamos a ver quién\nconsigue llegar arriba en menos tiempo.$"
	.string ""
	.string ""

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "¿Tienes idea de cuándo\nvan a abrir este sitio?\p¡Quiero ser la primera de todos\nen competir aquí!$"
	.string ""
	.string ""
	.string ""

TrainerHill_Elevator_Text_ReturnToReception:
	.string "¿Quieres volver a la recepción?$"
	.string ""
