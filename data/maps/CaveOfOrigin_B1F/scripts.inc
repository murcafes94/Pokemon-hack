CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_CAVE_OF_ORIGIN_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ah, así que eres {PLAYER}{KUN}.\nHe oído hablar mucho de ti.\pMe llamo PLUBIO.\pEra el LÍDER del GIMNASIO\nde ARRECÍPOLIS, pero ocurrió algo.\pAsí que pedí a mi mentor, GALANO,\nque se ocupara del GIMNASIO.\pVerás…\nResulta que…\pGROUDON y KYOGRE, los dos POKéMON\nque están haciendo estragos aquí,\lson dos POKéMON muy antiguos.\pPero no son los únicos…\pHay alguno más en algún lugar.\pExiste un tercer POKéMON\nantiquísimo llamado RAYQUAZA.\pSe cuenta que fue RAYQUAZA\nquien calmó a estos combatientes\len un pasado ya muy lejano.\pPero ni siquiera yo sé dónde\npodemos encontrar a RAYQUAZA…$"
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
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "PLUBIO: {PLAYER}{KUN}, ¿es posible que tú\nsepas dónde encontrar a RAYQUAZA?\pSi es así, dímelo, por favor.$"
	.string ""
	.string ""

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "PLUBIO: ¿En la CUEVA ANCESTRAL?\p¡Pero si eso está aquí mismo!\n¡No me basta con eso!\pLo que necesito es que me digas dónde\nestá RAYQUAZA ahora mismo.$"
	.string ""
	.string ""
	.string ""
	.string ""

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "PLUBIO: ¿En el MONTE PÍRICO?\pPero, cuando me encontré con la\nanciana allí, no hizo mención a eso.\pDudo mucho que la anciana\nintentara ocultarme algo así…\p{PLAYER}{KUN}, ¿podrías pensarlo\ncon más detenimiento?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "PLUBIO: ¿Qué? ¿No te acuerdas?\nPues eso es un problema…\p¿No te acuerdas ni un poquito?$"
	.string ""
	.string ""

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "PLUBIO: ¿En el PILAR CELESTE?\p¡Sí, eso es!\n¡Tiene que estar allí!\p{PLAYER}{KUN}, no hay tiempo que perder.\n¡Vamos al PILAR CELESTE enseguida!$"
	.string ""
	.string ""
	.string ""
	.string ""

