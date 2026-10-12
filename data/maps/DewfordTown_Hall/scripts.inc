DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "¿Qué es lo que está de moda? ¡Pues\n“{STR_VAR_1}”, claro!\p¡No puedo imaginarme lo que sería la\nvida sin “{STR_VAR_1}”!$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_GettingBoredOfTrend:
	.string "¿Qué es lo que está de moda? ¡Pues\n“{STR_VAR_1}”, claro!\pPero ya empiezo a hartarme un poco…\pDebería enterarme de lo que está\na la última de verdad…$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "Estoy enseñando a mi POKéMON todo\nsobre “{STR_VAR_1}”,\lpero no acaba de funcionar…\pCreo que el pobre no da más de sí…$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "Estoy estudiando algo supermolón:\n¡“{STR_VAR_1}”!\p¿Crees que de veras existe un vínculo\nentre “{STR_VAR_1}”\ly “{STR_VAR_2}”?$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "¡Oh!\n¡Entonces mi corazonada era cierta!\p¡Cada vez estoy más cerca de ser\nsuperguay y supermoderno! ¡Yupi!$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "¡¿Cómo?!\n¡¿En serio?!\pYa estoy muy mayor para estar al\ntanto de las últimas tendencias…$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "Toda esta historia de\n“{STR_VAR_1}”…\l¿Ha salido en la tele o algo?$"
	.string ""
	.string ""

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "¿Y al otro lado del mar…\ptodo el mundo dice también\n“{STR_VAR_1}”?$"
	.string ""
	.string ""

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "Colecciono artículos oficiales\n“{STR_VAR_1}”.\pTengo muñecos oficiales\n“{STR_VAR_1}”…,\propa de marca\n“{STR_VAR_1}”…\py libros ilustrados oficiales\n“{STR_VAR_1}”.\p¡Y es todo mío!\n¡Se mira, pero no se toca!$"
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

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "“DIFERENCIANDO UN BUEN\n“{STR_VAR_1}” DE UN\l“{STR_VAR_1}” MALO”…\p“LA CONEXIÓN ENTRE\n“{STR_VAR_1}” Y\lLOS POKéMON”…\p“EL “{STR_VAR_1}”\nÚTIL”…\pHay un montón de libros que tratan de\n“{STR_VAR_1}”.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_TrendsScream:
	.string "El título es “EL GRITO DE\n{STR_VAR_1}”.$"
	.string ""

DewfordTown_Hall_Text_TrendsSmile:
	.string "El título es “LA SONRISA DE\n{STR_VAR_1}”.$"
	.string ""

DewfordTown_Hall_Text_LastTrend:
	.string "El título es “EL ÚLTIMO\n{STR_VAR_1}”.$"
	.string ""

DewfordTown_Hall_Text_BirthOfTrend:
	.string "El título es “EL NACIMIENTO DE\n{STR_VAR_1}”.$"
	.string ""

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "He visto “{STR_VAR_1}”\ny mola cantidubi.\pMe ha hecho flipar en colores.\p¡Era asombroso!\n¡Lo más de lo más!$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "Oh, no, no y no.\pCrees haber visto\n“{STR_VAR_1}”…\lPero es de mentira…\pPara ser auténtico, debería tener…,\n¿cómo lo diría yo?…, fuerza y\ldelicadeza al mismo tiempo…\pBah, qué más da… ¡Es chulísimo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "Óyeme. He compuesto una canción\nsobre “{STR_VAR_1}”.\p“{STR_VAR_1}”\nes muy popular actualmente.\p¡Vale, escúchala!\p¡Oh, oh, {STR_VAR_1}!\n¡La, la, la!\p¡Sólo {STR_VAR_1}!\n¡La, la, la!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "Jo, colega…\pAntes de chafar del todo\n“{STR_VAR_1}”,\ldeberías aprender a cantar…$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "Pero como decía yo antes, habría\nque juntarse y organizar una fiesta\l“{STR_VAR_1}”\len la isla.$"
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "¡Qué idea tan buena!\pPor fin sabremos quién es el as de\n“{STR_VAR_1}”.\l¡Una idea buenísima!\p¡A partir de hoy, todo girará alrededor\nde “{STR_VAR_1}”!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "Estaba pensando una cosa…\p¿No opinas también que\n“{STR_VAR_1}” ha\lpasado de ser una moda a ser\lparte de nuestras vidas?$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "¿Perdón?\n¿Tanto como eso?\pSin embargo, es verdad que tenemos\na “{STR_VAR_1}”\len la cabeza a todas horas.\p¡Pero, en lo que respecta a pensar\nen “{STR_VAR_1}”,\lnadie te gana, coleguita!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "Si tú y yo unimos fuerzas, seremos\ninvencibles en todo lo que concierne\la “{STR_VAR_1}”.$"
	.string ""
	.string ""

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "¡Escucha, colega!\p¡Seremos el DÚO\n“{STR_VAR_1}”!\p¿No te parece buena idea?\n¡Ja, ja, ja, ja!$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "En mi opinión, BOMBA LODO está\nen su mejor momento. Es lo mejor.\p¿Eh? ¿Me estás diciendo que no\nsabes lo que es BOMBA LODO?\pQué pena, penita, pena.\nPues te voy a dar una, fíjate tú.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "Me encanta BOMBA LODO.\pPero también me gustan los POKéMON\nque saben el movimiento\l“{STR_VAR_1}”.$"
	.string ""
	.string ""
	.string ""

