BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "¿Y tú qué es lo que quieres?\p¿No ves que estamos ocupados?\n¿O es que no puedes esperar?$"
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "Anda, mira, a primera vista\nse ve que ENTRENAS con fiereza.\pJe, je, je…\nOye, te propongo una cosa.\pHemos formado un grupillo aquí,\ny solemos jugar a un juego que va\lsobre el FRENTE de BATALLA.\pLas reglas son muy sencillas.\pPrimero, elegimos uno de los escenarios\nque hay en el FRENTE de BATALLA.\pLuego, cada uno elige a un ENTRENADOR\nque vaya a participar en el desafío\lde ese escenario y apostamos por él\lnuestros PUNTOS de BATALLA.\pEl que apueste por el ENTRENADOR que\nconsiga el mejor resultado, se lleva\llos PUNTOS de BATALLA de los demás.\p¿Fácil, verdad?\nPues eso.$"
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
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "Estoy buscando a un ENTRENADOR que\nquiera luchar en el COMBATE INDIVIDUAL\lde la TORRE BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "Estoy buscando a un ENTRENADOR que\nquiera luchar en el COMBATE DOBLE\lde la TORRE BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "Estoy buscando a un ENTRENADOR que\nquiera luchar en el COMBATE MÚLTIPLE\lde la TORRE BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en el TORNEO de COMBATES\lINDIVIDUALES de la CÚPULA BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en el TORNEO de COMBATES\lDOBLES de la CÚPULA BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en el TORNEO de COMBATES\lcon TRUEQUE INDIVIDUALES\len la FÁBRICA BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en el TORNEO de COMBATES\lcon TRUEQUE DOBLES\len la FÁBRICA BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "Estoy buscando a un ENTRENADOR que\nquiera luchar en el COMBATE sin TUTELA\lINDIVIDUAL del PALACIO BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "Estoy buscando a un ENTRENADOR que\nquiera luchar en el COMBATE sin TUTELA\lDOBLE del PALACIO BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en el TORNEO con JUEZ\len el DOJO BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en la ELECCIÓN\lde COMBATES en la SIERPE BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "Estoy buscando a un ENTRENADOR que\nquiera entrar en la EXPEDICIÓN\lde COMBATES en la PIRÁMIDE BATALLA.\pPero, hasta ahora, no he visto a nadie\nque me inspire la suficiente confianza.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "Creo que tú también podrías ganar algo.\nAsí que, ¿qué me dices?\l¿Aceptarías ese desafío por mí?$"
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "Perfecto… ¿Qué tal si me prestas\nalgunos de tus PUNTOS de BATALLA?\pConfía en mí, sé agradecer los favores\ncon creces.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "¡Genial, genial!\n¿Cuántos me puedes prestar?$"
	.string ""

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "¡Oh, no, no, no! ¡No tienes suficientes\nPUNTOS de BATALLA!\p¡Yo que tú no iría por ahí burlándome de\nla gente ni haciéndole perder el tiempo!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "¡Je, je, je! ¡Muchas gracias!\n¡Venga, adelante!$"
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "¡Te espera el COMBATE INDIVIDUAL\nde la TORRE BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡Nuestra fortuna está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "¡Te espera el COMBATE DOBLE\nde la TORRE BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "¡Te espera el COMBATE MÚLTIPLE\nde la TORRE BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "¡Te espera el TORNEO de COMBATES\nINDIVIDUALES de la CÚPULA BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "¡Te espera el TORNEO de COMBATES\nDOBLES de la CÚPULA BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "¡Te espera el TORNEO de COMBATES\ncon TRUEQUE INDIVIDUALES\lde la FÁBRICA BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "¡Te espera el TORNEO de COMBATES\ncon TRUEQUE DOBLES\lde la FÁBRICA BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "¡Te espera el COMBATE sin TUTELA\nINDIVIDUAL del PALACIO BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "¡Te espera el COMBATE sin TUTELA\nDOBLE del PALACIO BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "¡Te espera el TORNEO con JUEZ\ndel DOJO BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "¡Te espera la ELECCIÓN de COMBATES\nde la SIERPE BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "¡Te espera la EXPEDICIÓN de COMBATES\nde la PIRÁMIDE BATALLA!\p¡No puedes perder!\n¡No me falles!\l¡El futuro de los dos está en tus manos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "Ah, eres tú…\nBuen intento…\pSiento decírtelo, pero no puedo\ndevolverte tus PUNTOS de BATALLA…\p¡Tendremos que motivarnos para\nhacerlo mejor la próxima vez!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "¡Eh, hola!\p¡Sabía que podías!\n¡Sabía que lo harías!\lGracias a ti, ¡hemos ganado los dos!\pToma, tus PUNTOS de BATALLA\ny, por supuesto, ¡tu recompensa!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "{PLAYER} obtuvo\n{STR_VAR_1} PUNTOS de BATALLA.$"
	.string ""

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "Antes de aceptar otro desafío,\n¡habla antes conmigo!$"
	.string ""

BattleFrontier_Lounge3_Text_NotInterested::
	.string "¡¿No te interesa?!\n¡No deberías tener miedo de probar!$"
	.string ""

BattleFrontier_Lounge3_Text_Oh::
	.string "Oh…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "¡He apostado otra vez por\nel ENTRENADOR equivocado!\pQuizás debería combatir yo misma,\ncomo hacen los demás…$"
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "Ese ENTRENADOR…\pEs bueno, pero no lo veo con el aguante\nnecesario para la CÚPULA BATALLA…$"
	.string ""
	.string ""

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "¡Yo reconozco a un ENTRENADOR\nganador nada más verlo! ¡Ji, ji, ji!$"
	.string ""

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "Pero esos ENTRENADORES…\n¿Qué están haciendo?\lDeberían estar combatiendo, ¿no?$"
	.string ""
	.string ""
