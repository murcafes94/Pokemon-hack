LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "AURA: ¡{PLAYER}{KUN}, cuánto tiempo!\p¡Anda! Mientras yo estaba en los baños\ntermales, tú has ganado la MEDALLA\ldel GIMNASIO de LAVACALDA.\pDebes de haber atrapado buenos\nPOKéMON… ¿O no? ¿Es más\lbien que los has entrenado tú?\pCreo que te mereces esto…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "AURA: Con estas GAFAS AISLANTES,\nno tendrás problemas para atravesar el\ldesierto que hay cerca de la RUTA 111.\pPero hay que ver, {PLAYER}{KUN}…\nNada menos que luchando en GIMNASIOS…\pEstás esforzándote tanto para\nasegurarte de no perder contra mí…\p{PLAYER}{KUN}, ¿sabes?, voy a ir a retar\na tu padre al GIMNASIO de PETALIA.\p¡Nos vemos!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRUNO: ¡{PLAYER}! ¡Ya hace un tiempo\nque no nos vemos! ¿Qué tal te va?\pAjá…\n¡Qué buena colección de MEDALLAS!\pMuy bien, te lo has ganado.\nTe voy a dar esto…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRUNO: Póntelas si piensas acercarte\nal desierto que hay por la RUTA 111.\pAlgunos POKéMON viven exclusivamente\nen el desierto. Búscalos.\pEn cuanto a mí…\nEstoy pensándome desafiar a NORMAN,\lel LÍDER del GIMNASIO de PETALIA.\pAl contrario que tú, {PLAYER}, tu padre\nsí que parece un tipo duro.\p¡Ya nos veremos!$"
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

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Tengo un HUEVO.\pPensé que cubriéndolo con arena\ncaliente en los baños termales se\labriría, pero qué va…\pMe han dicho que sería mejor que\nestuviera con otros POKéMON.\pTú entrenas POKéMON, ¿no? Y tus\nPOKéMON parecen estar en forma.\pAsí que ¿qué me dices?\n¿Llevarías este HUEVO contigo?$"
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

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "¡Bien! ¡Espero que corras muchas\naventuras junto a mi HUEVO!$"
	.string ""

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{PLAYER} recibió un HUEVO.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "Oooh… Tienes demasiados POKéMON.\nNo te queda sitio para este HUEVO…$"
	.string ""

LavaridgeTown_Text_AsYouWishThen:
	.string "Como desees…\pPero si cambias de opinión sobre el\nHUEVO, ven a verme.$"
	.string ""
	.string ""

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "De vez en cuando, aparece un HUEVO\nen la GUARDERÍA POKéMON.\pVamos, eso dicen por ahí…$"
	.string ""
	.string ""

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "Extraemos toda el agua caliente que\nnecesitamos, pero la fuente no se seca.\p¿A que parece magia?\pEstos baños termales parecen casi\nvolcanes. Los canales de agua\lsubterránea se calientan con el\lmagma y luego salen a la superficie.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Aquí enterradito en la arena caliente\nestoy tan…, ay…\pTan calentito, tan a gustito…\p¿Eh? ¡Ayyyyy!\p¡Un POKéMON me ha dado un pellizco\nen el trasero!$"
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "¿A ti también te gustan los baños\ntermales?\pEs curioso, la gente joven no suele\ninteresarse por esto…$"
	.string ""
	.string ""

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "Yo me baño en las aguas termales\ncada día del año.\pSon tan benéficas que sin duda me\nconvertirán en una LÍDER de GIMNASIO\ltan fuerte como CANDELA.$"
	.string ""
	.string ""

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "Imagínate que la gente metiera a los\nPOKéMON en los baños termales…\p¡Tendríamos baños eléctricos, baños\nde burbujas, baños de lava…!$"
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_HotSpringsClaims:
	.string "Aseguran que estos baños termales\nson buenos para los nervios, los dolores\lmusculares, los problemas amorosos,\llos granos, los bolsillos sin blanca…$"
	.string ""
	.string ""
	.string ""
	.string ""

LavaridgeTown_Text_TownSign:
	.string "PUEBLO LAVACALDA\pBAÑOS TERMALES del CENTRO POKéMON\n“¡No hay nada más relajante!”$"
	.string ""
	.string ""

LavaridgeTown_Text_GymSign:
	.string "GIMNASIO POKéMON de PUEBLO LAVACALDA\nLÍDER: CANDELA\l“¡No te acerques mucho, que quemo!”$"
	.string ""
	.string ""

LavaridgeTown_Text_HerbShopSign:
	.string "HERBOLARIO POKéMON\n“Sabe fatal, pero te sienta genial.”$"
	.string ""

