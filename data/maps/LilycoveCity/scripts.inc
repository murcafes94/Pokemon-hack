LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "AURA: ¡Mira por donde!\n{PLAYER}{KUN}, ¿también estás de compras?\pHe comprado un montón de MUÑECOS\ny PÓSTERS.\pY por supuesto también he atrapado\nun montón de POKéMON y los estoy\lentrenando como se debe hacer.\pDe hecho, me preocupa pensar que igual\ntú no entrenas los tuyos como debes…\pVoy a luchar contigo para que puedas\nmostrarme tus POKéMON, {PLAYER}{KUN}.$"
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

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "AURA: ¡Pero bueno! {PLAYER}{KUN}, ¿acaso\nno has estado entrenando tus POKéMON?\pPues todo ENTRENADOR que se precie\ndebería hacerlo…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MayBattleMe:
	.string "AURA: Venga, lucha conmigo, que quiero\nver cómo entrenas tus POKéMON…$"
	.string ""

LilycoveCity_Text_MayWontBeBeaten:
	.string "AURA: Los POKéMON que he entrenado\ndan mil vueltas a los tuyos, {PLAYER}{KUN}.$"
	.string ""

LilycoveCity_Text_MayDefeat:
	.string "Ejem…\pRecuerdo el combate que tuve contigo,\n{PLAYER}{KUN}, en la RUTA 103.\p¿A que ese combate te ayudó\na ser así de fuerte, {PLAYER}{KUN}?$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "AURA: Creo que voy a volver pronto\na VILLA RAÍZ.\pHe atrapado un buen grupo de POKéMON\ny mi POKéDEX está bastante completa.\lQuiero enseñar todo esto a mis padres.$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p¿Conseguir todas las MEDALLAS\nde GIMNASIO e ir a la LIGA POKéMON?\pBueno, mientras tú ganas MEDALLAS,\nyo voy a trabajar en mi POKéDEX.\l¡La voy a completar antes que tú!\p¡Nos vemos!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p¿Conseguir todas las MEDALLAS\nde GIMNASIO e ir a la LIGA POKéMON?\p¿O vas a completar tu POKéDEX?\pPuede que haya perdido luchando contra\nti, ¡pero la voy a llenar antes que tú!\p¡Nos vemos!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p¿Vas a aceptar el desafío\ndel FRENTE de BATALLA?\p¿O vas a completar tu POKéDEX?\pPuede que haya perdido luchando contra\nti, ¡pero la voy a llenar antes que tú!\p¡Nos vemos!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRUNO: Eh, hola, {PLAYER}.\pLe estoy haciendo un recado a mi\npadre, no estoy comprando MUÑECOS.\pPero ya llevo mucho tiempo dando\nvueltas…\p¿Qué te parece si combatimos para ver\nquién entrena POKéMON mejor?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRUNO: ¿Qué te pasa?\n¿Sabes que vas a perder?$"
	.string ""

LilycoveCity_Text_BrendanBattleMe:
	.string "BRUNO: ¿Quieres luchar para ver\nquién entrena POKéMON mejor?$"
	.string ""

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRENDAN: Aww, but you know I'm not\n"
	.string "going to lose to no {PLAYER}.$"

LilycoveCity_Text_BrendanDefeat:
	.string "Sí, sí…\nHas mejorado mucho.\pQué rollo… Yo antes te llevaba ventaja\nentrenando POKéMON…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRUNO: Bueno…\nTengo pensado volver a VILLA RAÍZ.\pSabes que estoy ayudando a mi padre\na completar su POKéDEX. Ya está\lcasi llena y quiero enseñársela.$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{PLAYER}, ¿qué vas a hacer?\p¿Conseguir todas las MEDALLAS\nde GIMNASIO e ir a la LIGA POKéMON?\pPuede que yo haga lo mismo…\pBueno, da igual. ¡Tú, persevera!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{PLAYER}, ¿qué vas a hacer?\pYa que eres tan fuerte, ¿vas a aceptar\nel desafío de la LIGA POKéMON?\pPero que conste: si entreno un poco\nmás a mis POKéMON, seré más fuerte\lque tú, {PLAYER}.\pBueno, da igual. ¡Tú, persevera!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{PLAYER}, ¿qué vas a hacer?\p¿Vas a aceptar el desafío\ndel FRENTE de BATALLA?\p¿O vas a completar tu POKéDEX?\pYa que eres tan fuerte, deberías\npasarte por el FRENTE de BATALLA.\pPero que conste: si entreno algo más a\nmis POKéMON, seré mejor que tú, {PLAYER}.\pDe hecho, quizás debería ir al\nFRENTE de BATALLA.\pBueno, da igual. ¡Tú, aguanta!$"
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

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Jua, jua, jua…\pHoy hemos llevado más botín\na nuestra GUARIDA secreta…\p¡¿Qui-quién eres tú?!\n¡Yo no he dicho nada!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Soy sólo un SOLDADO, así que no sé\nnada de los planes del JEFE…\p¡Pero, siendo parte del EQUIPO AQUA,\nsé que vamos a hacer grandes cosas!\p¡¿Qui-quién eres tú?!\n¡Yo no he dicho nada!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "¡Eh, tú!\p¡Ni se te ocurra acercarte a la cueva\nque hay en la ensenada!\p¿Por qué? ¡Porque lo digo yo!\n¡Soy mayor que tú, así que obedece!$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Si los del EQUIPO AQUA nos apoderamos\ndel mundo entero, será un lugar mejor\lpara todos, POKéMON incluidos.$"
	.string ""
	.string ""

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "¡Eh! ¡WAILMER!\n¡Salid del agua ahora mismo!$"
	.string ""

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "¿Mmm? ¿Qué quieres?\pEstás fastidiando el entrenamiento,\nasí que ¿por qué no te pierdes?$"
	.string ""
	.string ""

LilycoveCity_Text_ContestHallInTown:
	.string "Hay una SALA de CONCURSOS\nPOKéMON en esta misma ciudad.\pEso quiere decir que POKéMON fabulosos\nllegan desde cada rincón de la región.\p¡Estoy deseando verlos en acción!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_StrangeCaveInCove:
	.string "¿Has visto esa extraña cueva que hay\nen la ensenada, al otro lado del pueblo?$"
	.string ""

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "Voy a enseñar a mi POKéMON algún\nmovimiento nuevo para que participe\len algún CONCURSO.\pPara eso tengo que visitar al QUITA-\nMOVIMIENTOS y hacerle olvidar algún\lmovimiento de MO.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_ImFromKanto:
	.string "Vengo desde KANTO.\pMe parece que HOENN, con tanta agua\ny tanto verde, es realmente precioso.\pPero una duda me corroe…\p¿Es posible que haya POKéMON raros\nque sólo vivan aquí?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "El EQUIPO AQUA ha estado entrenando\nsus WAILMER en la ensenada.\pY, como están en medio, no nos dejan\na nosotros, los MARINEROS, sacar\lnuestras barcas al mar…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "¿Te has enterado?\p¡Alguien ha dado su merecido\nal EQUIPO AQUA por nosotros!\p¡Los WAILMER han salido de la\nensenada y por fin podemos\lsacar nuestras barcas tranquilos!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Estaba echándome una siestecita\nen la posada de la costa, arrullada\lpor el sonido de las olas…\p¡cuando alguien robó mi POKéMON!\p¿Quién ha sido, quién?\n¿El EQUIPO AQUA? ¿Serán ellos?$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Mi pobre POKéMON desaparecido…\nVolvió solito cuando no lo esperaba.$"
	.string ""

LilycoveCity_Text_ImArtDealer:
	.string "Soy un MARCHANTE de ARTE.\pCompro y vendo arte del bueno,\nsobre todo cuadros.\pMe han dicho que el MUSEO de aquí\nexpone unas obras magníficas…$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Nosotros envejecemos y nos arrugamos,\npero el mar continúa joven y bravío,\llleno de vida, por siempre…\pQué pensamiento tan profundo, ¿eh?$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Hace sesenta años que mi marido se me\ndeclaró aquí… El mar sigue tan hermoso\lcomo en aquel entonces…\pAy, que me emociono…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Dime, ¿has oído hablar de esa gruta\nque hay en la ensenada?\pSe ha creado de forma natural,\npero el dichoso EQUIPO AQUA llegó\ly tuvo que hacer reformas, claro.\p¡Y se atreven a llamarse el “equipo\namante de la naturaleza”!\pLo que dicen no tiene nada que ver\ncon lo que hacen en realidad…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Esa cueva en la ensenada…\pNo me di cuenta enseguida, pero\nse ve que está completamente vacía.\pLos del EQUIPO AQUA deben de\nhaberse largado. Ya era hora…$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_CitySign:
	.string "CIUDAD CALAGUA\p“Allí donde acaba la tierra\ny empieza el mar.”$"
	.string ""
	.string ""

LilycoveCity_Text_ContestHallSign:
	.string "SALA de CONCURSOS POKéMON\p“¡Un punto de encuentro para\ngrandes ENTRENADORES!”$"
	.string ""

LilycoveCity_Text_MotelSign:
	.string "MOTEL AGUACALA\p“¡El único lugar de CALAGUA\ndonde el agua no cala!”$"
	.string ""
	.string ""

LilycoveCity_Text_MuseumSign:
	.string "MUSEO de CALAGUA\p“Contempla la magnífica exposición\nde obras de arte POKéMON.”$"
	.string ""
	.string ""

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "MUSEO de CALAGUA\p“Contempla la magnífica exposición\nde obras de arte POKéMON de {PLAYER}.”$"
	.string ""
	.string ""

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "PUERTO de CIUDAD CALAGUA\p“El ferry S.S. MAREA está siendo\nconstruido en CIUDAD PORTUAL.\pSe espera que el servicio entre\nen funcionamiento en breve.”$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_HarborSign:
	.string "PUERTO de CIUDAD CALAGUA\p“Disfruta de un agradable crucero\na bordo del ferry S.S. MAREA.”$"
	.string ""
	.string ""

LilycoveCity_Text_TrainerFanClubSign:
	.string "CLUB de FANS de ENTRENADORES POKéMON\pEn el cartel hay garabateados un\nmontón de nombres de ENTRENADORES…$"
	.string ""
	.string ""

LilycoveCity_Text_DepartmentStoreSign:
	.string "CENTRO COMERCIAL de CALAGUA\p“¡Un lugar donde comprar\ny divertirse hasta la saciedad!\pBusques lo que busques…,\n¡lo encontrarás aquí!”$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "CASA del QUITA-MOVIMIENTOS\p“Si no te gusta un movimiento\nPOKéMON, ¡bórralo!”$"
	.string ""

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "¿Sabes algo de la LICUABAYAS?$"
	.string ""

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "La gente tiene que trabajar en equipo\npara hacer que gire más rápido.\pCuanto más rápido gira, mejor salen\nlos {POKEBLOCK}S. Eso dicen.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_ExplainBerryBlender:
	.string "Se usa para crear una especie\nde caramelo que se llama {POKEBLOCK}.\pSi le das un buen {POKEBLOCK} a un POKéMON,\néste mejorará un montón.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "He oído que hay una torre en\nalguna de las rutas marítimas.\pCreo que se llama PILAR CELESTE.$"
	.string ""
	.string ""

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "Vi una torre muy alta en algún\npunto de la RUTA 131.\p¿Podría tratarse de…?$"
	.string ""
	.string ""

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Acabamos de llegar y estamos\nde luna de miel.\pY justo hemos visto un POKéMON\nde tipo DRAGÓN volando en el cielo.\p¿Hay muchos POKéMON de ese tipo\nen la región de HOENN?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "Durante nuestra luna de miel,\nintentamos ver tantos POKéMON\lraros como fuera posible.\pPor eso nos alegró tanto ver a ese\nextraño POKéMON nada más llegar.\p¡Ha sido muy emocionante!$"
	.string ""
	.string ""
	.string ""
	.string ""

