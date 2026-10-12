SlateportCity_PokemonFanClub_MapScripts::
	.byte 0

SlateportCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_unset FLAG_ENTERED_CONTEST, SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest
	call_if_unset FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_MeetChairman
	switch VAR_SLATEPORT_FAN_CLUB_STATE
	case 0, SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment
	case 1, SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon
	case 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 1
	msgbox SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon::
	setvar VAR_TEMP_2, 0
	call_if_set FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_eq VAR_TEMP_2, CONTEST_CATEGORIES_COUNT, SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves
	goto_if_eq VAR_SLATEPORT_FAN_CLUB_STATE, 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	msgbox SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_NoMoreScarves::
	msgbox SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon::
	msgbox SlateportCity_PokemonFanClub_Text_HmHmISee, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	call_if_unset FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonTough
	call_if_unset FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonSmart
	call_if_unset FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCute
	call_if_unset FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty
	call_if_unset FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCool
	bufferleadmonspeciesname STR_VAR_1
	switch VAR_TEMP_1
	case 0, SlateportCity_PokemonFanClub_EventScript_NoHighConditions
	case 1, SlateportCity_PokemonFanClub_EventScript_GiveRedScarf
	case 2, SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf
	case 3, SlateportCity_PokemonFanClub_EventScript_GivePinkScarf
	case 4, SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf
	case 5, SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 2
	return

SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf::
	addvar VAR_TEMP_2, 1
	return

SlateportCity_PokemonFanClub_EventScript_NoHighConditions::
	msgbox SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveRedScarf::
	checkitemspace ITEM_RED_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RED_SCARF
	giveitem ITEM_RED_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainRedScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf::
	checkitemspace ITEM_BLUE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BLUE_SCARF
	giveitem ITEM_BLUE_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainBlueScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GivePinkScarf::
	checkitemspace ITEM_PINK_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_PINK_SCARF
	giveitem ITEM_PINK_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainPinkScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf::
	checkitemspace ITEM_GREEN_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_GREEN_SCARF
	giveitem ITEM_GREEN_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainGreenScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf::
	checkitemspace ITEM_YELLOW_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_YELLOW_SCARF
	giveitem ITEM_YELLOW_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainYellowScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf::
	msgbox SlateportCity_PokemonFanClub_Text_NoSpaceForReward, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CheckMonCool::
	specialvar VAR_RESULT, CheckLeadMonCool
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCool
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCool::
	setvar VAR_TEMP_1, 1
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty::
	specialvar VAR_RESULT, CheckLeadMonBeauty
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonBeauty
	return

SlateportCity_PokemonFanClub_EventScript_SetMonBeauty::
	setvar VAR_TEMP_1, 2
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonCute::
	specialvar VAR_RESULT, CheckLeadMonCute
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCute
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCute::
	setvar VAR_TEMP_1, 3
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonSmart::
	specialvar VAR_RESULT, CheckLeadMonSmart
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonSmart
	return

SlateportCity_PokemonFanClub_EventScript_SetMonSmart::
	setvar VAR_TEMP_1, 4
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonTough::
	specialvar VAR_RESULT, CheckLeadMonTough
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonTough
	return

SlateportCity_PokemonFanClub_EventScript_SetMonTough::
	setvar VAR_TEMP_1, 5
	return

SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest::
	goto_if_set FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest::
	msgbox SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_MeetChairman::
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	return

SlateportCity_PokemonFanClub_EventScript_SootheBellWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SOOTHE_BELL, SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell
	msgbox SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, SlateportCity_PokemonFanClub_EventScript_GiveSootheBell
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveSootheBell::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_PokemonFanClub_Text_PokemonAdoresYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SOOTHE_BELL
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell::
	msgbox SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_Man::
	msgbox SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Twin::
	msgbox SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_Text_MeetChairman:
	.string "Ejem, ejem… ¡Soy el PRESIDENTE\ndel CLUB de FANS de POKéMON!\pNaturalmente, el PRESIDENTE\nes la persona más importante…\pNadie me iguala entrenando POKéMON.\n¡Nadie!\pBueno, te voy a explicar qué son\nlos CONCURSOS POKéMON.\p¡Son competiciones donde puedes\nmostrar tus POKéMON al mundo mundial!\pPero siempre tienen lugar en el quinto\npino, así que no puedo participar mucho.\pPor eso nos reunimos aquí, para\nque todo el mundo pueda fardar\lde POKéMON, aunque sea un poco.$"
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

SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon:
	.string "Ya me gustaría ver al POKéMON de algún\nENTRENADOR que haya participado\len algún CONCURSO POKéMON…$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon:
	.string "Ejem, ejem… ¡Ya veo que has\nparticipado en un CONCURSO POKéMON!\pEstoy deseando ver cómo\nhas criado a tu POKéMON.\pEs maravilloso ver cómo los demás\nENTRENADORES cuidan a sus POKéMON.\pMe encantan las caras satisfechas\nde los POKéMON bien entrenados…\pY las cariñosas miradas de sus\norgullosos ENTRENADORES…\pAy, ver tanta felicidad me llena\nde gozo…\p¡Oh, pero discúlpame, empiezo\na hablar y no paro!\pTe lo ruego, permíteme examinar tu\nPOKéMON, a ver cuánto ha crecido.$"
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

SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing:
	.string "¿Qué tal está creciendo tu\nPOKéMON? Déjame examinarlo…$"
	.string ""

SlateportCity_PokemonFanClub_Text_HmHmISee:
	.string "Ajá… Muy bien…\nYa veo…$"
	.string ""

SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks:
	.string "Mmmm… No está mal, pero\ntampoco está bien…\p¡Tú, que entrenas POKéMON,\ndeberías esforzarte más con éste!\pUna sugerencia… ¿Por qué no\nle das más {POKEBLOCK}S?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_NoSpaceForReward:
	.string "Vaya, vaya…\pTu POKéMON está creciendo\nmuy bien. ¡Te mereces un premio!\pLástima que no tengas sitio\nen la MOCHILA…$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis:
	.string "¡Tu {STR_VAR_1} está creciendo\na un ritmo impresionante!\l¡Qué magnífico ejemplar!\pPero, si le das esto, crecerá\naún mejor. ¡Te lo digo yo!$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ExplainRedScarf:
	.string "Dale el PAÑUELO ROJO a un POKéMON.\p¡Así todo el mundo podrá ver\nlo carismático que es!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ExplainBlueScarf:
	.string "Dale el PAÑUELO AZUL a un POKéMON.\p¡De esta manera conseguirás realzar\nsu belleza aún más!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ExplainPinkScarf:
	.string "Dale el PAÑUELO ROSA a un POKéMON.\p¡Con él lograrás que parezca aún\nmás dulce de lo que ya es!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ExplainGreenScarf:
	.string "Dale el PAÑUELO VERDE a un POKéMON.\p¡Potenciará su ingenio!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ExplainYellowScarf:
	.string "Dale el PAÑUELO AMARILLO a un POKéMON.\p¡Le hará ser mucho más duro\nde lo que es ahora!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou:
	.string "Lo siento, pero no me queda nada\nmás que darte… ¡Nada de nada!\pDespués de todo, tienes el don de\nsaber entrenar POKéMON sin recurrir\lcontinuamente a objetos, ¿no?$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou:
	.string "Me encanta ver POKéMON que\nquieren a sus ENTRENADORES.\pLos POKéMON son muy sensibles a los\nsentimientos de sus ENTRENADORES.\pSi tratas a tus POKéMON con amor\ny cariño, te corresponderán.\pCuando tus POKéMON te quieran\nun poco más, vuelve a verme.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_PokemonAdoresYou:
	.string "Tu POKéMON te adora.\p¡Como has demostrado tener un gran\ncorazón, el CLUB de FANS te regala esto!$"
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove:
	.string "Los POKéMON son muy sensibles a los\nsentimientos de los ENTRENADORES.\pSi tratas a tus POKéMON con amor\ny cariño, te corresponderán.$"
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting:
	.string "Si continuamente dejas que tus POKéMON\ncaigan debilitados durante un combate,\lacabarán por resentirse de esto.\pMuy pronto empezarán a perder\nconfianza en su ENTRENADOR.\pEn otras palabras, terminarás\npor no gustarles ni un pelo.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein:
	.string "¿A los POKéMON les gusta\nque se les dé objetos?\pNo sé, los míos se pusieron muy\ncontentos cuando les di PROTEÍNA.$"
	.string ""
	.string ""
	.string ""

SlateportCity_PokemonFanClub_Text_Skitty:
	.string "SKITTY: Skitiiiiii…$"

SlateportCity_PokemonFanClub_Text_Zigzagoon:
	.string "ZIGZAGOON: Zigzaaaa…$"

SlateportCity_PokemonFanClub_Text_Azumarill:
	.string "AZUMARILL: ¿Marimari?$"

