RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "En la pizarra hay notas sobre los\ncambios de estado que pueden afectar\la los POKéMON durante un combate.$"
	.string ""

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "¿Sobre qué tema te gustaría leer?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "Si un POKéMON está envenenado,\nirá perdiendo PS continuamente.\pLos efectos del veneno se dejan sentir\nincluso después del combate.\pLos PS de un POKéMON envenenado\ndisminuirán mientras viaja.\pPara curar un caso de envenenamiento,\nusa un ANTÍDOTO.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "Si un POKéMON está paralizado,\nsu VELOCIDAD cae en picado.\pEs posible que incluso quede\ninmovilizado durante el combate.\pLa parálisis permanece después del\ncombate. Usa ANTIPARALIZACIÓN.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "Si un POKéMON se duerme, no podrá\natacar a su rival.\pUn POKéMON puede despertarse por\nsí solo, pero, si el combate finaliza\lmientras está dormido, seguirá así.\pDespiértalo usando DESPERTAR.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "Una quemadura reduce el poder\nde ATAQUE y los PS de la víctima.\pSus efectos continúan tras el\ncombate. Usa ANTIQUEMAR.$"
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "Si un POKéMON está congelado,\nqueda completamente indefenso.\pContinuará congelado tras el combate.\nDescongélalo usando ANTIHIELO.$"
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "Cuando un alumno no estudia nada,\nle doy jarabe de GARRA RÁPIDA.\pTu aplicación en el estudio se verá por\nla manera en que uses este objeto.$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
	.string "Un POKéMON que tiene GARRA RÁPIDA\na veces ganará velocidad y se moverá\lantes que su rival.\pHay muchos otros objetos que\nse pueden dar a los POKéMON.\pSólo eso da para estudiar un montón.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_TradingRightNow:
	.string "Voy a intercambiar un POKéMON\ncon mi amigo ahora mismo.$"
	.string ""

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
	.string "Siempre he querido un SEEDOT\ny por fin voy a conseguir uno.$"
	.string ""

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
	.string "Los POKéMON pueden llevar objetos,\npero no saben qué hacer con las\lPOCIONES y los ANTÍDOTOS, por ejemplo.$"
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
	.string "¿Sabes que algunos movimientos\npueden confundir a un POKéMON?\pUn POKéMON confuso puede hacerse\ndaño a sí mismo sin querer.\pPero cuando acaba el combate,\nse pasa el efecto.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
	.string "Un POKéMON que tiene una BAYA\npuede curarse a sí mismo.\pHay muchos tipos de objeto que\nse pueden dar a los POKéMON.\pUf, qué cansado es coger apuntes…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "Es un cuaderno de un alumno…\pSe atrapa a los POKéMON usando\nlas POKé BALLS.\pUn ENTRENADOR puede llevar hasta\nseis POKéMON consigo.\pUn ENTRENADOR es alguien que atrapa\na los POKéMON, los entrena y lucha\lcon ellos.\pLa misión de un ENTRENADOR es derrotar\na los ENTRENADORES fuertes que están\len los GIMNASIOS POKéMON.$"
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

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "Hola, ¿nos conocemos?\nQuizás de CIUDAD PETALIA…\pPermíteme presentarme:\nme llamo TRETO.\pHe estado viajando por el mundo en\nbusca de grandes ENTRENADORES.\pO más bien estoy buscando expertos\nen los combates POKéMON.\pAsí que, ¿qué te trae por esta ESCUELA?\n¿Tú también entrenas POKéMON?\pLo primero que tendrías que enseñar\na un POKéMON es el movimiento CORTE.\pSi no recuerdo mal, alguien de por\naquí tiene el movimiento CORTE.$"
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

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "TRETO: Mmm…\pDesconocemos el talento real de\nnuestros estudiantes, pero lo que\lestá claro es que tienen potencial.$"
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "TRETO: Eh, ¿qué es eso?\pUna MEDALLA PIEDRA, ¿verdad?\nEstoy impresionado, la verdad.\pPero de todas formas me hubiera\ngustado verte en acción.\pLas MEDALLAS no bastan para saber\nqué tipo de ENTRENADOR se es.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "Hola, ¿nos conocemos?\nQuizás de CIUDAD PETALIA…\pPermíteme presentarme:\nme llamo TRETO.\pHe estado viajando por el mundo en\nbusca de grandes ENTRENADORES.\pO más bien estoy buscando expertos\nen los combates con POKéMON.\pAnda, ¿eso qué es?\nUna MEDALLA PIEDRA, ¿verdad?\pY eso que no tienes mucha experiencia.\nEstoy impresionado, la verdad.\pPero de todas formas me hubiera\ngustado verte en acción.\pLas MEDALLAS no bastan para saber\nqué tipo de ENTRENADOR se es.$"
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

