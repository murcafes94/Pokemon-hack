BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FRONTIER_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_FRONTIER_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "¡Ésta es la CÚPULA BATALLA!\n¡La ruta a la fama pasa por aquí!$"
	.string ""

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "¡Ésta es la FÁBRICA BATALLA!\n¡Hazte con el POKéMON más fuerte!$"
	.string ""

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "¡Ésta es la SIERPE BATALLA!\n¡Elige el mejor de los tres caminos!$"
	.string ""

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "Ésta es la TORRE BATALLA.\pLos ENTRENADORES traen a sus mejores\nPOKéMON para luchar en combates\leliminatorios.$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Buenas, ¿vienes para coger el ferry?\n¿Puedo ver tu TICKET?$"
	.string ""

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{PLAYER} no tiene ningún TICKET…\pCuánto lo lamento.\pNecesitas un TICKET para poder\nsubir a bordo del ferry.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{PLAYER} enseñó el TICKET…\pPerfecto. Todo está en regla.\p¿Adónde te gustaría ir?$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "Muy bien, rumbo a CIUDAD PORTUAL.$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "Muy bien, rumbo a CIUDAD CALAGUA.$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "¡Esperamos que vuelvas a navegar\ncon nosotros!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Sube a bordo y espera a que zarpemos.$"
	.string ""

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "Sube. ¿Adónde te gustaría ir?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "Les doy mil vueltas a todos mis amigos.\nPero aquí…\lHe hecho el ridículo.$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "Quiero ir a la TORRE BATALLA,\npero no la encuentro, y eso que tengo\lun mapa del FRENTE de BATALLA…\p¡Es que este sitio es muy grande!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "Quería llegar lo antes posible\npara ponerme a luchar.\pPero me he mareado en el barco…\nUajjj…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "No te creas que al FRENTE de BATALLA\npuede venir cualquiera, ¿eh?\pAquí sólo invitan a los ENTRENADORES\nque han demostrado que valen.\pPor eso muchos ENTRENADORES\nni han oído hablar de este lugar.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Eh, colega…\p¿Seguro que podemos combatir\naunque no tengamos ni un POKéMON?$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "¡Claro! ¡Seguro que no pasa nada!\pCreo…\pRecuerda lo que dijo el gorila ese del\nmostrador: “¡Yo te presto\llos POKéMON!”.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "Eso de ahí es la FÁBRICA BATALLA.\nAhí te prestan POKéMON muy fuertes.\pSiempre me he preguntado quién será\nel guapo que los entrena…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "Me da miedo entrar en la SIERPE\nBATALLA con todos esos SEVIPER…\pPe-pero, ya que he llegado hasta aquí,\ntendré que conquistarlo todo, ¿no?\lAy, ay, ay…$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "¡Vamos a jugar a piedra, papel o tijeras!\nUna, dos, y…\p¡tres!\pMmm…$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "¡Sí! ¡Gané!\n¡Entraré en la SIERPE BATALLA!$"
	.string ""

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Oh, no…\nHe perdido.\pHoy no es mi día de suerte.\nCreo que tendré que dejar lo de\lla SIERPE BATALLA para mañana.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "Creo que soy el único de por aquí que, \npor alguna razón que se me escapa,\lprefiere pescar a combatir.\p¿Cómo?…\p¿Que aquí no pica nada?\nVaya, qué fastidio…$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "¡Hoy no pienso parar de combatir hasta\nque no haya ganado un símbolo! ¡Ea!$"
	.string ""

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "¿Eh? ¿Tú también piensas entrar\nen la CÚPULA BATALLA?\pPues te deseo toda la suerte del mundo.\nOjalá ganemos los dos\ly nos encontremos en la final.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "¡Abuelito, por aquí!\n¡La CÚPULA BATALLA está aquí!\l¡Venga, a por ellos, abuelito!$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Ah, conque esto es la CÚPULA BATALLA…\n¡No pienso dejarme ganar por ninguno\lde esos a los que llaman CABALLEROS!\pPero ¿por dónde se entra a este sitio?$"
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "Todavía me acuerdo de cuando aquí\nno había nada.\pPero mira ahora… ¡Increíble!\n¡Esto tiene que verlo mi madre!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "¡Por fin estoy en el FRENTE de BATALLA!\p¡Ya verás cómo triunfo aquí con\ntodos mis encantos y habilidades!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Ñam, ñam…\pEsta plaza está llena de tipos duros,\n¿no crees?\pÑam, ñam…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Ñam, ñam…\pEl otro día me encontré con una chica\nen la SIERPE BATALLA.\pTenía unos ojos que daban miedo.\pÑam, ñam…\pEstaba indignada: “¡¿Vas a dejar de\ncomer de una vez?!”, me dijo.\lY luego me machacó.\pLo pasé fatal, menuda experiencia tan\ntraumática, oye. Qué mal lo pasé…\pÑam, ñam…$"
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

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "Pero ¡¿qué estás diciendo, chaval?!\n¡Menuda tontería!\p¿Sabes lo que te digo?\n¡Que era a mí a quien miraba!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "¡¿Que qué?!\n¡Bah!\p¡Eso fue porque estabas\nsentada a mi lado, lista!\p¡El ASTRO de la CÚPULA me estaba\nmirando a mí! ¡Y sólo a mí!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "¡Venga, ya!\n¡Dejad de discutir! ¡Parecéis críos!\p¡Menudos fans de pacotilla!\n¡No os merecéis animar\lni a un LÍDER de GIMNASIO!\p¡El ASTRO de la CÚPULA es para mí!\n¡Es mi único ídolo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Mira a ésos de ahí discutiendo…\pResulta difícil de creer, pero antes\neran ENTRENADORES, y de los buenos.\pVamos, que eran famosos y todo.\pPero en un torneo, hubo un ENTRENADOR\nque los eclipsó completamente.\pLes dio una paliza tremenda a todos.\pY ahora son sus fans incondicionales\ny van a animarlo a la CÚPULA BATALLA\lsiempre que participa en un torneo.$"
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

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "Dicen que han visto a un POKéMON\nque tiene una cola larguísima en algún\lsitio del FRENTE de BATALLA.\pTiene que ser adorable, seguro…\pLos desafíos pueden esperar.\n¡Yo quiero encontrar a ese POKéMON!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

