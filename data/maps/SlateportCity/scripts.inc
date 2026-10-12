SlateportCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

SlateportCity_OnTransition:
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_MovePeopleForSternInterview
	call_if_eq VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport::
	setflag FLAG_VISITED_SLATEPORT_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	return

SlateportCity_EventScript_MovePeopleForSternInterview::
	setobjectxyperm LOCALID_SLATEPORT_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_SLATEPORT_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_SLATEPORT_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_SLATEPORT_COOK, 27, 16
	setobjectxyperm LOCALID_SLATEPORT_GIRL, 28, 16
	setobjectxyperm LOCALID_SLATEPORT_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_SLATEPORT_MAN_1, 31, 14
	setobjectmovementtype LOCALID_SLATEPORT_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_SLATEPORT_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 30, SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft::
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame:
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.2byte 0

SlateportCity_EventScript_ScottScene::
	lockall
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ScottApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru::
	lock
	faceplayer
	message SlateportCity_Text_EnergyGuruSellWhatYouNeed
	waitmessage
	pokemart SlateportCity_Pokemart_EnergyGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_EnergyGuru:
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	pokemartlistend

SlateportCity_EventScript_EffortRibbonWoman::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox SlateportCity_Text_OhYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, LeadMonHasEffortRibbon
	call_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_MonHasEffortRibbon
	specialvar VAR_RESULT, Special_AreLeadMonEVsMaxedOut
	call_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_MonEVsNotMaxed
	msgbox SlateportCity_Text_PleaseGiveItThisEffortRibbon, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_Text_ReceivedEffortRibbon
	waitfanfare
	msgbox SlateportCity_Text_PutEffortRibbonOnMon, MSGBOX_DEFAULT
	special GiveLeadMonEffortRibbon
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed::
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon::
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_CookSternInterview
	msgbox SlateportCity_Text_SeaweedFullOfLife, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview::
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWoman::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview::
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview::
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase::
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview::
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan::
	goto_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview::
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview::
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone::
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign::
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion::
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete::
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign::
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign::
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign::
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign::
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete::
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign::
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

@ Unclear if the text here was meant to be different, but its not
SlateportCity_EventScript_ManiacSternInterview::
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2::
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1::
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2::
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF::
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_NPC
	end

SlateportCity_EventScript_Man2::
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5::
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7::
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt:
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10::
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11::
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Dolls:
	.2byte DECOR_AZURILL_DOLL
	.2byte DECOR_MARILL_DOLL
	.2byte DECOR_SKITTY_DOLL
	pokemartlistend

SlateportCity_EventScript_ComeBackWithSecretPower::
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor:
	.2byte DECOR_RED_BRICK
	.2byte DECOR_BLUE_BRICK
	.2byte DECOR_YELLOW_BRICK
	.2byte DECOR_RED_BALLOON
	.2byte DECOR_BLUE_BALLOON
	.2byte DECOR_YELLOW_BALLOON
	.2byte DECOR_C_LOW_NOTE_MAT
	.2byte DECOR_D_NOTE_MAT
	.2byte DECOR_E_NOTE_MAT
	.2byte DECOR_F_NOTE_MAT
	.2byte DECOR_G_NOTE_MAT
	.2byte DECOR_A_NOTE_MAT
	.2byte DECOR_B_NOTE_MAT
	.2byte DECOR_C_HIGH_NOTE_MAT
	pokemartlistend

SlateportCity_EventScript_PowerTMClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs:
	.2byte ITEM_TM_HIDDEN_POWER
	.2byte ITEM_TM_SECRET_POWER
	pokemartlistend

@ Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine
SlateportCity_EventScript_CaptStern::
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GABBY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 10
	applymovement LOCALID_SLATEPORT_TY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_SLATEPORT_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_SLATEPORT_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_GABBY
	removeobject LOCALID_SLATEPORT_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_COOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_FAT_MAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_SLATEPORT_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_SLATEPORT_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_SLATEPORT_CAPT_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setvar VAR_SLATEPORT_CITY_STATE, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern:
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ManConcern:
	emote_question_mark
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_GabbyExit:
	delay_16
	walk_left
	walk_left
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

SlateportCity_Movement_TyExit:
	walk_down
	walk_left
	walk_left
	walk_left
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

SlateportCity_Movement_Unused:
	walk_down
	walk_in_place_faster_up
	step_end

SlateportCity_Movement_SternEnterHarbor:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor:
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_EventScript_Ty::
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby::
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3::
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	giveitem ITEM_POWDER_JAR
	setflag FLAG_RECEIVED_POWDER_JAR
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder::
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem::
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect::
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem::
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder::
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit:
	delay_16
	walk_in_place_faster_right
	step_end

SlateportCity_Movement_ScottExitBattleTent:
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign::
	lockall
	special ShowBerryCrushRankings
	releaseall
	end

SlateportCity_Text_EnergyGuruSellWhatYouNeed:
	.string "¡Soy CURRO!\n¡Se me va la olla y te vendo todo\llo que necesitas barato, barato!$"
	.string ""

SlateportCity_Text_OhYourPokemon:
	.string "¿Eh?\nTu {STR_VAR_1}…$"
	.string ""

SlateportCity_Text_PleaseGiveItThisEffortRibbon:
	.string "¡Se esfuerza cantidad, sí, señor!\pComo recompensa, dale esta\nCINTA ESFUERZO.$"
	.string ""
	.string ""

SlateportCity_Text_ReceivedEffortRibbon:
	.string "{PLAYER} recibió la CINTA ESFUERZO.$"

SlateportCity_Text_PutEffortRibbonOnMon:
	.string "{PLAYER} dio la CINTA ESFUERZO\na {STR_VAR_1}.$"
	.string ""

SlateportCity_Text_GoForItLittleHarder:
	.string "Tienes que esforzarte un poco más…\pSi lo haces, le daré algo muy chulo\na tu POKéMON.$"
	.string ""
	.string ""

SlateportCity_Text_EffortRibbonLooksGoodOnIt:
	.string "¡Oh! ¡La CINTA ESFUERZO le sienta\nestupendamente a tu {STR_VAR_1}!$"
	.string ""

SlateportCity_Text_WonderIfLighthouseStartlesPokemon:
	.string "La luz del faro llega lejísimos…\pMe pregunto si no ciega a los\nPOKéMON que viven en el mar…$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SeaweedFullOfLife:
	.string "¡Eh, mira esto!\pEl pescado que consigues por aquí\nestá fresquísimo. ¡Todavía colea!\p¡Vamos, si parece que te va a morder\ny todo!$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_HowTownIsBornAndGrows:
	.string "Cuando el agua está limpia, la tierra\nda sus frutos con generosidad.\pAllá donde hay comida, se concentra\nla gente y pronto se abre un mercado.\pY así es como nace y crece una ciudad.$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SlateportWonderfulPlace:
	.string "Comprar en un lugar donde el aire\nes fresco y limpio es genial.\p¡CIUDAD PORTUAL es un lugar\nmaravilloso!$"
	.string ""
	.string ""

SlateportCity_Text_BuyBricksSoDecorWontGetDirty:
	.string "Si pones los MUÑECOS y los COJINES\ndirectamente en el suelo, se ensucian.\pVoy a comprar algunos LADRILLOS\npara poner mis MUÑECOS y COJINES\lencima y mantenerlos bien limpios.$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_GoingToCompeteInBattleTent:
	.string "¡Toma ya! ¡Yo también voy a competir\nen la TIENDA de BATALLA!\pPero antes tengo que atrapar\nalgunos POKéMON…$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_BushedHikingFromMauville:
	.string "Uf… Esto es impresionante…\pHe venido a patita desde CIUDAD\nMALVALONA, pero este sitio es enorme…\pSi lo hubiera sabido, me habría\ntraído la BICI…$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_EveryoneCallsHimCaptStern:
	.string "BABOR, el hombre que fundó el MUSEO,\ntambién es el jefe de un equipo\lde exploración submarina.\pPor eso todos le llaman CAP. BABOR.$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_WhatsLongLineOverThere:
	.string "¿Qué es eso de allí?\nEsa cola tan larga…$"
	.string ""

SlateportCity_Text_VisitedMuseumOften:
	.string "Cuando era pequeña, venía mucho\nal MUSEO.\pDespués de ver las colecciones, soñaba\ndespierta con los misterios del mar…$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_QuitPushing:
	.string "¡Oye, tú! ¡No te cueles!\n¿No ves que hay una cola?$"
	.string ""

SlateportCity_Text_AquaHasPolicy:
	.string "El EQUIPO AQUA suele reunirse\nen los lugares donde van a realizar\lalguna operación.$"
	.string ""
	.string ""

SlateportCity_Text_BossIsBrilliant:
	.string "Nuestro JEFE es un genio.\p¿Qué querrá hacer con un MUSEO?$"
	.string ""
	.string ""

SlateportCity_Text_WhatsNewSchemeIWonder:
	.string "¿Cuál será el nuevo plan?\pNuestro JEFE da miedo cuando\nse enfada, así que mejor procuro\lno meter la pata.$"
	.string ""
	.string ""

SlateportCity_Text_ShouldTakeItAll:
	.string "¡Si hay algo que nos interesa en el\nMUSEO, deberíamos llevárnoslo entero!$"
	.string ""

SlateportCity_Text_DontButtIn:
	.string "¡Oye, tú!\n¡Aquí no pintas nada! ¡Aire!$"
	.string ""

SlateportCity_Text_RemindsMeOfLongLineForGames:
	.string "Vaya cola, ¿eh?\pMe recuerda a aquellos tiempos cuando\nhacía cola en la tienda de videojuegos\lpara comprar la última novedad.$"
	.string ""
	.string ""

SlateportCity_Text_WhyAreWeLiningUp:
	.string "¿Y por qué hacemos cola y pagamos\nentrada y todo? ¡Deberíamos colarnos!$"
	.string ""

SlateportCity_Text_WhatDoYouWant:
	.string "¿Qué?\n¿Qué quieres?$"
	.string ""

SlateportCity_Text_IllReadSignForYou:
	.string "¿Quieres leer este cartel?\n¡Deja, ya lo hago yo!$"
	.string ""

SlateportCity_Text_SaysSomethingLikeSeaIsEndless:
	.string "Vamos a ver…\pMmm… Creo que pone esto:\n“La vida en el mar es infinita”.\pSí, sí, segurísimo que pone eso.$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_ShouldveBroughtMyGameBoy:
	.string "Ufff…\pCómo me aburro… Debería haberme\ntraído mi consola Game Boy Advance.\pDónde tendré la cabeza…$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_HotSpringsAfterOperation:
	.string "¡Cuando esto acabe, el JEFE\nnos va a llevar de excursión!\pLo ha prometido.\n¡Qué ganas tengo!$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SeaIsSoWet:
	.string "El mar es tan, tan inmenso…\p¿Saldrá toda esta agua de las lágrimas\nderramadas por los POKéMON?$"
	.string ""
	.string ""

SlateportCity_Text_SinkOldBoats:
	.string "¿Sabes qué se hace con los barcos que\nestán demasiado viejos para navegar?\pLos hunden en el mar para que\nlos POKéMON puedan vivir en ellos.$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_BuyTooMuch:
	.string "Cada vez que vengo aquí me entran\nganas de comprarlo todo.$"
	.string ""

SlateportCity_Text_GetNameRaterToHelpYou:
	.string "Si quieres cambiar el nombre de tu\nPOKéMON, ve a ver al INSPECTOR\lde los MOTES.$"
	.string ""
	.string ""

SlateportCity_Text_CantChangeTradeMonName:
	.string "Cuando recibes un POKéMON por\nintercambio, no puedes cambiarle\lel nombre. ¿Sabes por qué?\pEl cariño que el ENTRENADOR de ese\nPOKéMON le tenía está reflejado\len el nombre que lleva. Por eso.$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_BattleTentBuiltRecently:
	.string "Han construido una TIENDA de\nBATALLA en CIUDAD PORTUAL.\pLos GIMNASIOS molan, pero las TIENDAS\nde BATALLA tienen algo especial.\p¡Deberías hacerte con POKéMON\nfuertes antes de entrar en una!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_CaptSternBeingInterviewed:
	.string "Pensaba que igual era una estrella\nde cine y podría pedirle un autógrafo.\pPero ¿a quién están entrevistando?\n¿No es el CAP. BABOR?$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_InterviewerSoCool:
	.string "Ser periodista parece guay.\p¡Cuando sea mayor, yo también quiero\ntener un trabajo así de chulo!$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SternSaysDiscoveredSomething:
	.string "El CAP. BABOR dice que han descubierto\nalgo en el fondo del mar.\p¿Qué será?$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_CaptainComeBackWithBigFish:
	.string "¿Qué pasa aquí?\p¿El CAPITÁN ha pescado algo gordo\nen el fondo del mar?$"
	.string ""
	.string ""

SlateportCity_Text_AmIOnTV:
	.string "¡Eh! ¿Ves la imagen en la cámara?\n¿Salgo en la tele? ¿Salgo?$"
	.string ""

SlateportCity_Text_CaptainsACelebrity:
	.string "¡Una entrevista para la tele!\n¡El CAPITÁN tiene que ser famosísimo!$"
	.string ""

SlateportCity_Text_BigSmileForCamera:
	.string "TEO: ¡CAP. BABOR, regale una gran\nsonrisa a nuestros telespectadores!$"
	.string ""

SlateportCity_Text_MostInvaluableExperience:
	.string "GABI: Ya veo… Ha sido una\nexperiencia inolvidable…$"
	.string ""

SlateportCity_Text_SternMoveAheadWithExploration:
	.string "CAP. BABOR: Así es. Y queremos seguir\navanzando con la investigación.$"
	.string ""

SlateportCity_Text_GabbyWonderfulThanksForInterview:
	.string "GABI: ¡Qué gran noticia, CAP. BABOR!\nMuchísimas gracias por sacar un rato de\lsu apretada agenda para dedicárnoslo.\pEsperamos poder seguir disfrutando de\nsus fascinantes historias en próximas\lentrevistas.$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SternWhewFirstInterview:
	.string "CAP. BABOR: Uf…\pEra la primera vez que me grababan\npara la tele… ¡Qué nervios!$"
	.string ""
	.string ""

SlateportCity_Text_OhPlayerWeMadeDiscovery:
	.string "¡Oh, {PLAYER}{KUN}!\n¡Qué buen aspecto tienes!\pEn nuestro último viaje de exploración\nhicimos un gran descubrimiento.\pEncontramos una caverna submarina\nen la RUTA 128.\pPensamos que en ella viven POKéMON\nque se creían extintos.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_AquaWillAssumeControlOfSubmarine:
	.string "¡Jua, jua, jua!\nEl CAP. BABOR, supongo.\p¡Nosotros, el EQUIPO AQUA, vamos\na tomar el control de su submarino!\p¡No hay objeción que valga!\n¡Confiamos en que coopere!\p¡Jua, jua, jua!\nMire lo que ha planeado\lel EQUIPO AQUA…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SternWhatWasAllThat:
	.string "CAP. BABOR: ¿De qué va todo esto?\pParece como si alguien estuviera\nhablando por un megáfono…\p¿De dónde viene esa voz?…$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_FromHarborTryingToTakeSub:
	.string "¡Viene del PUERTO!\p¡El submarino!\n¡Están intentando llevárselo!$"
	.string ""
	.string ""

SlateportCity_Text_PleaseComeWithMe:
	.string "¡{PLAYER}{KUN}!\n¡Ven conmigo!$"
	.string ""

SlateportCity_Text_BattleTentSign:
	.string "TIENDA de BATALLA de CIUDAD PORTUAL\n“¡Hazte con el POKéMON definitivo!”$"
	.string ""

SlateportCity_Text_SternsShipyardWantedSign:
	.string "ASTILLEROS BABOR\p“Se busca marinero con experiencia\nen los siete mares.”$"
	.string ""
	.string ""

SlateportCity_Text_SternsShipyardNearsCompletion:
	.string "ASTILLEROS BABOR\p“El ferry S.S. MAREA pronto\npodrá cubrir el trayecto entre\lCIUDAD PORTUAL y CALAGUA.”$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_SternsShipyardFerryComplete:
	.string "ASTILLEROS BABOR\p“Dirigíos al PUERTO para embarcar\na bordo del ferry S.S. MAREA, con\lrecorrido CIUDAD PORTUAL-CALAGUA.”$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_PokemonFanClubSign:
	.string "CLUB de FANS de POKéMON\n“¡Reunión de fans de POKéMON!”$"
	.string ""

SlateportCity_Text_OceanicMuseumSign:
	.string "MUSEO OCEÁNICO\p“El vasto mar es la fuente de toda\nla vida.”$"
	.string ""
	.string ""

SlateportCity_Text_CitySign:
	.string "CIUDAD PORTUAL\p“El puerto donde se cruzan los caminos\nde ENTRENADORES y POKéMON.”$"
	.string ""
	.string ""

SlateportCity_Text_MarketSign:
	.string "MERCADO de CIUDAD PORTUAL\n“¡El mercado más completo y\lexclusivo del mundo!”$"
	.string ""

SlateportCity_Text_HarborFerryUnderConstruction:
	.string "PUERTO de CIUDAD PORTUAL\p“El ferry S.S. MAREA está siendo\nconstruido en los ASTILLEROS.\pEl servicio entrará en funcionamiento\nen breve.”$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_HarborSign:
	.string "PUERTO de CIUDAD PORTUAL\p“Disfruta de un maravilloso crucero\nen el S.S. MAREA.”$"
	.string ""
	.string ""

SlateportCity_Text_NameRatersHouseSign:
	.string "CASA del INSPECTOR de los MOTES\n“Evalúa el nombre de tu POKéMON.”$"
	.string ""

SlateportCity_Text_ExplainBerries:
	.string "Cuando un POKéMON salvaje está herido,\nse cura comiendo BAYAS.\p¿Lo sabías?\pAlguien lo vio y tuvo la idea de\nelaborar medicinas con BAYAS.\p¿Lo sabías?\pPara usarlas con fines medicinales, hay\nque MACHACARLAS y extraer un POLVO.\p¿Lo sabías?\p¡Se diría que las BAYAS\nte interesan una barbaridad!\pPues tengo algo ideal para alguien\ncomo tú.$"
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

SlateportCity_Text_ExplainBerryPowder:
	.string "Hace poco hice instalar unas máquinas\nen los CENTROS POKéMON que sirven\lpara MACHACAR BAYAS.\pLas máquinas machacadoras de BAYAS\nestán arriba, en la ZONA DIRECTA.\p¿Lo sabías?\p¿Podrías hacer POLVO de BAYA\nusando esas máquinas?\pSi me traes mucho POLVO de BAYA,\nelaboraré diversas medicinas para ti.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_BroughtMeSomeBerryPowder:
	.string "¿Me has traído POLVO de BAYA?$"
	.string ""

SlateportCity_Text_ExchangeWhatWithIt:
	.string "¿Por qué quieres que te lo cambie?$"
	.string ""

SlateportCity_Text_ExchangeBerryPowderForItem:
	.string "Vale, te cambio el POLVO de BAYA\npor una unidad de {STR_VAR_1}.$"
	.string ""

SlateportCity_Text_DontHaveEnoughBerryPowder:
	.string "¿Eh?\nNo tienes suficiente POLVO de BAYA.$"
	.string ""

SlateportCity_Text_FineBerryPowderTradeSomethingElse:
	.string "Este POLVO de BAYA es excelente.\nVa a salir una medicina buenísima.\p¿Quieres cambiar más POLVO de BAYA\npor alguna otra cosilla?$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_WhenYouGetMoreBringItToMe:
	.string "¡Muy bien! Cuando consigas más POLVO\nde BAYA, tráemelo. Hasta la próxima.$"
	.string ""

SlateportCity_Text_ComeBackToTradeBerryPowder:
	.string "Ven a verme cuando quieras cambiar\nPOLVO de BAYA por alguna medicina.\pTengo montado un negocio aquí.\p¿Lo sabías?$"
	.string ""
	.string ""
	.string ""

SlateportCity_Text_YouDroveTeamAquaAway:
	.string "TRETO: ¿Eh?\nTu cara me suena muchísimo.\p¿Ya nos hemos presentado?\nSi no es así, me llamo TRETO.\pAcabo de ver al EQUIPO AQUA\nsalir de aquí a todo correr.\pA ver si lo adivino, ¿es obra tuya?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_MaybeThisTrainer:
	.string "TRETO: Mmm… Puede que, pero\nsólo es una posibilidad…$"
	.string ""

SlateportCity_Text_LetsRegisterEachOther:
	.string "TRETO: ¡Muy bien! Creo que éste\nes el inicio de una bella amistad.\pAsí que vamos a registrarnos\nen nuestros POKéNAV.\pA ver…$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_RegisteredScott:
	.string "Acabas de registrar al tal TRETO\nen el POKéNAV.$"
	.string ""

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou:
	.string "TRETO: Me encantaría seguirte de cerca,\npero no debo perder de vista\la otros ENTRENADORES con talento.\pAsí que voy a seguir pateando\nrutas y pueblos un poco más.\p¡Hasta la próxima, {PLAYER}{KUN}!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_Text_TakingBattleTentChallenge:
	.string "TRETO: ¡Eh, tú!\n¡Pero si eres {PLAYER}{KUN}!\p{PLAYER}{KUN}, a ver si lo adivino,\n¿vas a luchar en la TIENDA de BATALLA?\p¡Qué buena idea!\n¡No podría ser mejor!\p¡Al fin y al cabo, todo ENTRENADOR\nfuerte debe aceptar ese desafío!\p¡Esfuérzate al máximo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
