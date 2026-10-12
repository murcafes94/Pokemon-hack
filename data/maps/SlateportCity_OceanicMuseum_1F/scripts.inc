SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "Hola. Éste es el MUSEO OCEÁNICO.\pLa entrada cuesta 50¥.\n¿Quieres entrar?$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "Disfruta de la visita.$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "Vaya, lo siento, pero parece que\nno tienes bastante dinero…$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "¿Ah, sí? ¿Vienes con el grupo\nque entró justo antes?\p¡Pues llegas tarde!\n¡Date prisa para alcanzarles!$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "¡Nosotros, el EQUIPO AQUA, existimos\npor el bien de la humanidad!$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "Nos dijeron que viniéramos aquí\ny eso hemos hecho, pero…\pNuestro JEFE no está y sin él\nno somos nada.$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "Si birlara todas las cosas\nque hay aquí, ¿me haría rico?$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "Todo lo que aprenda aquí puedo\naplicarlo con fines malvados…$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "¡Si nuestro matón no la hubiera\npifiado en CIUDAD FÉRRICA,\lno tendríamos que estar aquí!$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "Yo no tenía 50¥, así que tuve que\nburlar a la recepcionista para entrar.\l¡No fue nada fácil!$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "Quiero aprender todo lo que pueda\nsobre el mar y aplicarlo al combate.$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "Me entra un mareo horrible\ncada vez que veo el mar…\p¡Ojalá pudiera ser tan valiente\ncomo el CAP. BABOR!$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "El mar es tan, tan grande y tan,\ntan profundo…\pSeguro que hay muchos POKéMON\nde los que nunca hemos oído hablar.$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "Quiero un POKéMON marino.\pAbrazarlo resultaría tan\nfresquito y agradable…$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "¡Aaaaah!\n¿Qué haces aquí?\p¿Yo? Soy el miembro del EQUIPO\nAQUA al que diste una paliza en el\lTÚNEL FERVERGAL, ¿recuerdas?\p¡Hala, toma!\n¡Y espero que me perdones!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "Esa MT va más contigo que\nconmigo.\p¡Hasta nunca, espero!\n¡Jua, ja, ja, ja!$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "¡Encima esto!\n¡Toma esto y deja que me largue!$"
	.string ""

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "Un líquido azul fluye en espiral dentro\nde un recipiente de cristal.\p“Éste es un experimento que se sirve\nde la fuerza del viento para recrear\lun TORBELLINO.”$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "Una bola roja sube y baja dentro\nde un recipiente de cristal.\p“Éste es un experimento que se sirve\ndel principio de la flotabilidad para\lsimular una CASCADA.”$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "Se trata de una muestra de tierra\ndel fondo oceánico.\p“A lo largo de miles de años, los\nrestos orgánicos se van depositando\len el fondo del mar y crean capas.\pMediante el análisis de estas capas\nsedimentarias, se puede aprender mucho\lsobre el pasado más remoto.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "Se trata de una muestra de arena\nde playa.\p“El agua de los ríos erosiona las rocas\nde las montañas, las fragmenta y las\lentierra en el lecho de los mismos.\pSon reducidas a gravilla por la fricción\ndel agua y acaban depositándose\len las playas.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "MINI-INFO OCEÁNICA 1\n¿Por qué el agua del mar es azul?\p“La luz se compone de muchos colores.\pCuando la luz atraviesa el agua,\nla mayoría de estos colores son\labsorbidos, sobre todo los rojos.\pLa luz azul se dispersa más fácilmente,\npor eso el mar tiene ese color.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "MINI-INFO OCEÁNICA 2\n¿Por qué el mar es salado?\p“El agua del mar contiene sal disuelta\nbajo forma de iones de sodio y cloruro.\pEstos iones se separan de las rocas y\nllegan al mar por la acción de la lluvia.\pLa alta concentración de sal disuelta\nhace que el mar sea salado.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "MINI-INFO OCEÁNICA 3\n¿Qué es mayor? ¿La tierra o el mar?\p“El mar cubre alrededor de un 70% del\nplaneta, y el resto es tierra firme.\pPor lo tanto, el mar es más del doble\nde grande que la tierra.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "Se trata de un fósil con crestas\nonduladas.\p“La marea erosiona el suelo\ndel fondo oceánico.\pLas corrientes marcan el suelo\ncon pequeñas crestas y valles.\pSi este suelo termina fosilizándose,\nrecibe el nombre de marca fósil.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "Una extraña máquina está rotando\nbajo una cúpula de cristal.\pQuizás sirva para medir la\nprofundidad de algo…$"
	.string ""
	.string ""
	.string ""

