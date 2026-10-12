BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "¿Es la primera vez que vienes?\n¡Entonces por aquí, por favor!$"
	.string ""

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "¡Éste es el FRENTE de BATALLA!\n¡La prueba final de los ENTRENADORES!$"
	.string ""

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "Como es la primera vez que nos visitas,\nte entregaremos el PASE del FRENTE.\pTe permitirá entrar y competir en todos\nlos edificios del FRENTE de BATALLA.\p¡Aquí tienes!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{PLAYER} obtuvo el PASE del FRENTE.$"
	.string ""

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{PLAYER} colocó su FICHA de ENTRENADOR\ndentro del PASE del FRENTE.$"
	.string ""

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "¡Y ahora, disfruta al máximo de todo lo\nque te ofrece el FRENTE de BATALLA!$"
	.string ""

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "(?): Bueno, bueno, ¡pero si es {PLAYER}{KUN}!\n¡Al final has venido!$"
	.string ""

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "GUÍA: ¡Oh! ¡Don TRETO! ¡Está usted aquí!\n¡Muy buenas! ¡Muy buenas tenga usted!$"
	.string ""

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "TRETO: ¡Me alegra mucho verte,\npor supuesto que sí!\pEspero que tengas tiempo de\necharle un vistazo a todo esto.\pY, por supuesto, espero que no vengas\nsólo a mirar, sino también a combatir.\pAquí tengo mi rinconcito, así que\npuedes venir a verme cuando quieras.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "¿Buscas información sobre algún\nedificio del FRENTE de BATALLA?$"
	.string ""

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "¿Sobre cuál?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "Esta torre es para muchos el edificio\nemblemático del FRENTE de BATALLA.\pEn ella se disputan cuatro tipos\nde combates: INDIVIDUALES,\lDOBLES, MÚLTIPLES y\lMULTIJUGADOR con CONEXIÓN.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "La CÚPULA BATALLA es un enorme\nedificio con forma de huevo gigante.\pDentro de ella se disputan los llamados\nTORNEOS de COMBATES, en dos\lmodalidades: INDIVIDUAL y DOBLES.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "El PALACIO BATALLA es un edificio rojo\nsituado al este del FRENTE de BATALLA.\pEn él se celebran los llamados\nCOMBATES sin TUTELA, en dos\lmodalidades: INDIVIDUAL y DOBLES.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "El DOJO BATALLA es el edificio\nde aspecto oriental situado en la\lzona central del FRENTE de BATALLA.\pLos denominados TORNEOS con JUEZ\ntienen lugar en el DOJO BATALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "La FÁBRICA BATALLA es ese enorme\nedificio que está nada más salir\la la izquierda.\pAllí se celebran los famosos COMBATES\ncon TRUEQUE, tanto en la modalidad\lINDIVIDUAL como en la de DOBLES.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "La SIERPE BATALLA es ese edificio con\nla forma de un POKéMON que está situado\len el centro del FRENTE de BATALLA.\pEl desafío conocido como\nELECCIÓN de COMBATES se celebra allí.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "La PIRÁMIDE BATALLA es la gran\npirámide que está al noreste\ldel FRENTE de BATALLA.\pAllí podrás emprender las llamadas\nEXPEDICIONES de COMBATES.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "El HALL de las CLASIFICACIONES\nse halla junto a la TORRE BATALLA.\pEn él podrás ver los récords logrados\npor los más grandes ENTRENADORES\len los distintos desafíos que ofrece\lel FRENTE de BATALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "El CENTRO del SERVICIO de CANJE está\njunto a la entrada de la TORRE BATALLA.\pLos PUNTOS de BATALLA que hayas\nganado en el FRENTE de BATALLA podrás\lcanjearlos allí por fabulosos premios.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "Mi trabajo es informar sobre las reglas\nbásicas comunes a todos los desafíos\la los que puedes enfrentarte en los\lescenarios del FRENTE de BATALLA.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "¿Sobre qué quieres que te hable?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "Todos los desafíos del FRENTE\nde BATALLA están disponibles\len el nivel 50 y el nivel libre.$"
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "El nivel 50 está abierto a los POKéMON\ncuyo nivel sea igual o inferior a 50.\pPero debes saber que ninguno de los\nENTRENADORES a los que te enfrentes\ltendrá POKéMON por debajo del nivel 50.\pEs el nivel básico para enfrentarse a\nlos desafíos del FRENTE de BATALLA.\pPara empezar, te recomendamos\nque elijas este nivel.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "El nivel libre, como su nombre indica,\nno impone límite alguno al nivel de los\lPOKéMON con los que se combate.\pLos niveles de tus rivales se ajustarán\npara igualarse a los de tus POKéMON.\pCon todo, ningún ENTRENADOR\nal que te enfrentes tendrá POKéMON\lpor debajo del nivel 60.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Prácticamente cualquier POKéMON podrá\nparticipar en los desafíos que ofrece\lcualquiera de los escenarios que hay.\pNo obstante, los HUEVOS y ciertos\nPOKéMON no podrán hacerlo.\pEl número de POKéMON necesario para\nparticipar dependerá del escenario.\pSin embargo, lo que no podrás hacer en\nninguno de los escenarios es participar\lcon dos POKéMON iguales.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "Antes de afrontar cualquier desafío\nen un escenario del FRENTE de BATALLA,\lcomprueba que no haya dos de tus\lPOKéMON sosteniendo el mismo objeto.\pAsegúrate de que todos los POKéMON\nque vayan a entrar en un combate\lsostienen objetos diferentes.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "Estaré encantado de explicarte lo que\nquieras sobre el PASE del FRENTE.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "¿Te explico algo en especial?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "Hay siete escenarios diferentes\nen el FRENTE de BATALLA.\pCuando un ENTRENADOR demuestra\nsus habilidades y triunfa en uno de los\ledificios, puede que reciba su símbolo.\pPara ganar un símbolo, puede que haya\nque derrotar a varios ENTRENADORES\lconsecutivamente y puede que en varias\locasiones.\pNo es nada fácil ganar estos símbolos.\n¡Que tengas suerte!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "En tu PASE del FRENTE puedes\ngrabar un combate.\pPuedes grabar un combate en el que te\nhayas enfrentado a uno o varios amigos.\pO puedes grabar uno de tus combates\ndel FRENTE de BATALLA, salvo los de la\lSIERPE BATALLA y la PIRÁMIDE BATALLA.\pLa opción de grabarlos aparece\nal terminar el combate.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Cuando un ENTRENADOR lucha de manera\nextraordinaria en el FRENTE de BATALLA,\lrecibe PUNTOS de BATALLA como premio.\pLuego, esos PUNTOS de BATALLA\npueden canjearse por objetos en\lel CENTRO del SERVICIO de CANJE.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

