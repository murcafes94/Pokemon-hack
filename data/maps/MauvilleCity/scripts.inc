MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_MAUVILLE_WALLY
	removeobject LOCALID_MAUVILLE_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_MAUVILLE_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_MAUVILLE_SCOTT, 12, 13
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
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

MauvilleCity_Movement_ScottExitEast:
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

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "TÍO: Creo que este chico está tan vital\núltimamente gracias a los POKéMON.\lPero es que ya es demasiado…$"
	.string ""
	.string ""

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "BLASCO: Eh… ¿TÍO?\pQuiero desafiar al LÍDER de este\nGIMNASIO y ver cuánto he mejorado.\p¿Puedo? ¿Puedo? Porfaaaa…$"
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_UncleYourePushingIt:
	.string "TÍO: Espera un poco, BLASCO…\pEs cierto que desde que vives con\nPOKéMON eres mucho más fuerte.\p¿Pero no crees que exageras\nun poco cuando hablas de desafiar\la un LÍDER de GIMNASIO?$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "BLASCO: No exagero…\p¡Si RALTS y yo unimos fuerzas,\npodemos con todo!$"
	.string ""
	.string ""

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "BLASCO: Oh, hola, {PLAYER}.\pSoy mogollón más fuerte que la última\nvez que nos vimos.\p{PLAYER}, quiero que mi TÍO y tú no\ntengáis ninguna duda al respecto.\p{PLAYER}, ¿querrías luchar conmigo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Oh… If you won't battle me,\n"
	.string "{PLAYER}, my UNCLE won't know that I've\l"
	.string "become really strong.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "TÍO: {PLAYER}{KUN}, ¿verdad?\nEn nombre de BLASCO, ¿puedo pedirte\lque os enfrentéis sólo esta vez?\pEstá tan empeñado que no habrá\nmanera de convencerle de lo contrario.$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "BLASCO: {PLAYER}, porfa…\n¡Lucha conmigo, anda!$"
	.string ""

MauvilleCity_Text_WallyHereICome:
	.string "BLASCO: Gracias, {PLAYER}.\pMuy bien… ¡Allá vamos!$"
	.string ""

MauvilleCity_Text_WallyDefeat:
	.string "BLASCO: Pues…\pPues…\pPues he perdido…$"
	.string ""
	.string ""

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "BLASCO: TÍO…\nMe vuelvo a VERDEGAL…$"
	.string ""

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "Gracias, {PLAYER}.\nEs duro ser un ENTRENADOR, ¿no?\pNo basta con tener POKéMON\ny hacerlos combatir.\lSer ENTRENADOR es más que eso…$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "TÍO: BLASCO, no debes venirte abajo\npor esto…\pA ver, ¿qué te impide mejorar cada\nvez más?\pVenga, vamos a casa.\nTodos te están esperando.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_UncleVisitUsSometime:
	.string "TÍO: {PLAYER}{KUN}, acabo de darme cuenta\nde que tú fuiste quien ayudó a BLASCO\la atrapar su POKéMON.\p¿Por qué no vienes a visitarnos\na VERDEGAL algún día?\lA BLASCO le haría ilusión.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""


MauvilleCity_Text_WallyPokenavCall:
	.string "¡Bip!\pBLASCO: ¡Hey, hola, {PLAYER}!\p¡Sólo quería decirte que mi TÍO\nme ha comprado un POKéNAV!\p¡Así que ya puedo hablar contigo\nsiempre que quiera, {PLAYER}!\p¡Clic!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_RegisteredWally:
	.string "Acabas de registrar a BLASCO\nen el POKéNAV.$"
	.string ""

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "TRETO: Je, je…\n¡He presenciado ese enfrentamiento!\pTienes amistad con ese tal BLASCO,\n¿verdad?\pPues no te has cortado ni un pelo.\nLe has vencido de forma impresionante.\p¡Ése es el verdadero espíritu de los\ncombates POKéMON, sí, señor!\p¡Admiro a la gente que entrena como tú!\p¡Seguiré animándote!$"
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

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "ERICO: ¡Anda, {PLAYER}{KUN}!\n¡Te veo muy en forma!\lMe parece genial, ja, ja, ja.\pVale. Está decidido.\nNecesito que me hagas un favor.\pEn CIUDAD MALVALONA hay una zona\nsubterránea llamada MALVALANOVA.\p{PLAYER}{KUN}, necesito que vayas allí\ny apagues el GENERADOR.\pEl GENERADOR ha estado funcionando\nde cualquier manera. No es seguro.\pToma. Ésta es la LLAVE para entrar\nen MALVALANOVA.$"
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

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "ERICO: No te preocupes. No creo\nque te suponga ningún problema.\pLa entrada a MALVALANOVA está\ncerca. Sólo hay que ir a la RUTA 110 \ly hacer un poco de SURF.\pPues eso es. Cuento contigo.\n¡Jua, jua, jua, jua!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "ERICO: ¡Jua, jua, jua, jua!\p¡Lo sabía, {PLAYER}{KUN}!\n¡Sabía que no me equivocaba contigo!\pY quiero agradecértelo: toma la MT\nque contiene RAYO.\p¡Te la has ganado!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "ERICO: ¡Jua, jua, jua, jua!\pMe alegra mucho ver cómo los jóvenes\nvan avanzando hasta la cumbre.$"
	.string ""
	.string ""

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Es verdad. Mola entablar combates\nPOKéMON y todo eso, pero recuerda:\psi tu POKéMON se hace daño, debes\ncuidarlo hasta que se ponga bueno.$"
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Las carreteras de este pueblo van\nen todas las direcciones.\pPor eso viene tanta gente\ndiferente continuamente.$"
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_RydelVeryGenerous:
	.string "¿Ya has estado en la TIENDA de BICIS\nde ANACLETO?\pANACLETO, el dueño, es muy generoso.$"
	.string ""
	.string ""

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Aunque montes en BICI, los POKéMON\nsalvajes pueden atacarte.$"
	.string ""

MauvilleCity_Text_CitySign:
	.string "CIUDAD MALVALONA\n“¡Una ciudad que rebosa diversión!”$"
	.string ""

MauvilleCity_Text_GymSign:
	.string "GIMNASIO POKéMON de CIUDAD MALVALONA\nLÍDER: ERICO\l“¡Una personalidad electrificante!”$"
	.string ""
	.string ""

MauvilleCity_Text_BikeShopSign:
	.string "TIENDA de BICIS de ANACLETO\n“¡Todo para ir sobre ruedas!”$"
	.string ""
	.string ""

MauvilleCity_Text_GameCornerSign:
	.string "CASINO de MALVALONA\n“¡Juega a lo que te apetezca!”$"
	.string ""

MauvilleCity_Text_ExplainTV:
	.string "Hola. ¿Tú ves la tele?\pÚltimamente hay un montón de programas\nmuy buenos.\pEs superguay. Hasta han salido\nmis amigos.\pY, a veces, tú también sales,\naunque no lo sepas.\pMe gustaría salir un día…\p¡Por eso voy a ver la tele cada\ndos por tres!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Hola. ¿Has estado viendo la tele?$"
