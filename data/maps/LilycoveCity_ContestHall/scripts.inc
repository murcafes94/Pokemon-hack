@ All the LOCALID constants used in this file are essentially redundant.
@ They're all used to have the NPC the player talked to turn back so they're facing
@ their original direction (because they're watching/participating in the contests).
@ They could all be substituted for VAR_LAST_TALKED.
LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "Este POKéMON ya ha ganado\nel CONCURSO de BELLEZA…\p¿Y sabes qué? ¡Hoy ha ganado\nel CONCURSO de INGENIO!\pSoy tan bueno que no me lo creo…$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "He entrado en un montón de CONCURSOS\npara ver cómo funciona este tinglado.\pSi estás en un CONCURSO de CARISMA,\nusa movimientos carismáticos para\lganar más puntos.\pVamos, que los movimientos ingeniosos\no dulces no servirán de gran cosa…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "Ese jovencito que ganó antes tenía\nun buen montón de {POKEBLOCK}S diferentes.\p¿Crees que usando muchas cosas\nde ésas resulta más fácil ganar?$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "Guau… Este sitio es gigantesco…\pSe respira tanta tensión… No es en\nabsoluto como esas SALAS de CONCURSO\lperdidas en medio de la nada…$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "PRESENTADORA: Muy bien. POKéMON\ningeniosos y ENTRENADORES\lrespectivos, ¿estáis listos?\p¡Dad lo mejor de vosotros!\n¡A exhibirse!$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "JUEZ: ¿Te está gustando el CONCURSO?\pVuelve con tres amigos más y todos\npodréis participar en uno.$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "Ay, ay, ay, ay…\n¡Me he equivocado de CONCURSO!\pHe apuntado a un POKéMON duro\na un CONCURSO de INGENIO…\p¡Venga, déjalos patidifusos\ncon un ingenioso GOLPE ROCA!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "Durante años he aplicado todos\nmis conocimientos para entrenar\lun POKéMON ingenioso como él solo.\pDudo mucho que los POKéMON\nde unos renacuajos puedan superarlo…\pCariño, ¿ves todo bien desde ahí?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "¡Toma ya!\p¡Si mi POKéMON hace alarde\nde un movimiento ingenioso ahora,\lel público se va a volver loco!$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "¡Oh, no!\pEl CHUPAVIDAS de mi querido ZUBAT\nes tan guay que lo he usado varias\lveces seguidas…\p¡Pero estos cabezas de chorlito no\nhan sabido apreciarlo en absoluto!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "¡Adelante! ¡Amorcito, eres el mejor!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "Aun cuando los ENTRENADORES apuntan\nal mismo tipo de POKéMON, cada uno\lse exhibe con un movimiento distinto.\pPorque, claro, ¡todo el mundo\ntiene su propio estilo de lucha!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "Creo que esos POKéMON parecen mucho\nmás ingeniosos que sus ENTRENADORES.$"
	.string ""

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "Por mucho que venga, estos CONCURSOS\nde INGENIO me siguen encantando.\pEse color verde es tan… agudo…\nEs tan, tan… intelectual…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "PRESENTADORA: ¿Tú también participas\nen el CONCURSO de BELLEZA?\l¡Pues suerte!$"
	.string ""

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "JUEZ: Todos los POKéMON que hay aquí\nson un modelo de perfecta belleza.\p¡Huy, en vez de admirarlos tanto,\ndebería darles una puntuación!$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "Este POKéMON es de una BELLEZA\nsin igual… No tiene rival.\pSin duda el público se quedará\nadmirado al verlo.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "¡Aaaaah!\pHe peinado y arreglado a mi POKéMON\nespecialmente para el CONCURSO…\pPero me he pasado…\nY ahora su bonito pelo está todo tieso…\p¡¿Qué puedo hacer?!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "Este RAYO AURORA es deslumbrante.\nEl JUEZ no podrá ni verlo.\pEh, un momento…\n¡Entonces no servirá de nada!$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "Este bonito POKéMON se parece\na mí cuando era joven, clavadito.\pPues, cuando se lo dije a mi marido,\nno pudo aguantarse la risa.\pY, digo yo, ¿dónde está la gracia?$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "Yo creo que a cualquiera le hace\nilusión ganar un CONCURSO\lde BELLEZA, ¿o no?$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "¡Ja, ja, ja!\p¡Mira bien todos esos POKéMON!\n¡Son tan bonitos que deslumbran!$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "La belleza natural no basta.\pHay que potenciarla un poco para\nconseguir una imagen tan estupenda\lcomo la de mi POKéMON.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "PRESENTADORA: ¡Huy, hola!\n¡Estamos en mitad de un CONCURSO!\pVe a registrarte primero si quieres\nparticipar, ¿vale?$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "JUEZ: ¡Nunca había visto exhibiciones\ntan dulces y encantadoras como éstas!\pPor ejemplo, ese HIDROCHORRO tan\nadorable merece una gran puntuación.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "Oh, no, un POKéMON ha distraído\na mi dulce AZURILL…$"
	.string ""

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "Mi POKéMON nunca ha vencido luchando,\n¡pero ya verás como gana el CONCURSO!$"
	.string ""

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "La DANZA PÉTALO de mi POKéMON\nes un prodigio de elegancia.\pNo dejaré que nadie le moleste\ndurante su actuación.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "Todo el mundo piensa que su POKéMON\nes el más dulce de todos.\pPero yo sé que, cuando el mío haga\nuna exhibición de DULZURA…,\p¡se llevará la palma!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "Mi hijo está participando\nen el CONCURSO.$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "¡Adelante, cariño!\n¡Tu POKéMON es el mejor!$"
	.string ""

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "Creo que esa chica de ahí\nes la más dulce de toda la sala.\p¿Cómo? ¿Que compiten los POKéMON,\nno sus ENTRENADORES?$"
	.string ""
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "Oooooh, al ver a esos POKéMON tan\ndulces, me entran ganas de tener uno…\p¡Me voy a atrapar unos cuantos!$"
	.string ""
	.string ""

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "ESCENARIO del CONCURSO de BELLEZA\n¡LOS POKéMON MÁS GUAPOS!$"
	.string ""

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "ESCENARIO del CONCURSO de DULZURA\n¡LOS POKéMON MÁS ACHUCHABLES!$"
	.string ""

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "ESCENARIO del CONCURSO de INGENIO\n¡LOS POKéMON MÁS LISTOS!$"
	.string ""

