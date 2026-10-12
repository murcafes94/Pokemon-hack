JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
	.string "El DESFILADERO del MONTE CENIZO…\pSiempre he querido encontrar\nuna montaña como ésta.\pEsta superficie irregular…\n¡Me hace dar botes de alegría!$"
	.string ""
	.string ""
	.string ""
	.string ""

JaggedPass_Text_EricDefeat:
	.string "Perder me deja hecho polvo…$"

JaggedPass_Text_EricPostBattle:
	.string "Sí, he perdido en el combate POKéMON…\p¡Pero seguro que llego a cualquier\ncima antes que tú!$"
	.string ""
	.string ""

JaggedPass_Text_DianaIntro:
	.string "Este lugar no es el típico al que viene\nla gente a hacer picnics.$"
	.string ""

JaggedPass_Text_DianaDefeat:
	.string "¡Ooooh, no!\n¡El terreno es demasiado irregular!$"
	.string ""

JaggedPass_Text_DianaPostBattle:
	.string "¿Sabes una cosa?\pHay gente muy habilidosa que sube\nen bici por este horrible camino\llleno de baches.$"
	.string ""
	.string ""

JaggedPass_Text_DianaRegister:
	.string "¿Piensas volver por aquí?\nEn ese caso, quiero mi revancha.$"
	.string ""

JaggedPass_Text_DianaRematchIntro:
	.string "Los picnics son siempre divertidos,\n¡pero los POKéMON lo son aún más!$"
	.string ""

JaggedPass_Text_DianaRematchDefeat:
	.string "¡He perdido, pero sólo porque\nhe metido el pie en un bache!$"
	.string ""

JaggedPass_Text_DianaPostRematch:
	.string "Mejor no pienso en la derrota y disfruto\nde este paseo accidentado, ja, ja, ja.$"
	.string ""

JaggedPass_Text_EthanIntro:
	.string "Es difícil caminar por el DESFILADERO,\npero es lo mejor para entrenarse.$"
	.string ""

JaggedPass_Text_EthanDefeat:
	.string "¡Oye, no es justo, que todavía estaba\nintentando mantener el equilibrio!$"
	.string ""

JaggedPass_Text_EthanPostBattle:
	.string "Si tuviera una BICI ACROBÁTICA, podría\nsaltar sobre cualquier desnivel…$"
	.string ""

JaggedPass_Text_EthanRegister:
	.string "Este terreno está lleno de baches,\npero en cuanto me acostumbre ganaré.\p¿Quieres registrarme en tu POKéNAV?$"
	.string ""
	.string ""

JaggedPass_Text_EthanRematchIntro:
	.string "Me he acostumbrado a estos\nbaches y ahora son pan comido.$"
	.string ""

JaggedPass_Text_EthanRematchDefeat:
	.string "Sigue sin ser fácil luchar en este\nterreno tan irregular…$"
	.string ""

JaggedPass_Text_EthanPostRematch:
	.string "Debería comprar a ANACLETO una BICI\nACROBÁTICA en CIUDAD MALVALONA…$"
	.string ""

JaggedPass_Text_GruntIntro:
	.string "¡Oye!\n¿Qué haces tú aquí?\pYa puestos, ¿qué hago yo aquí?\pPero, sobre todo, ¿qué haces tú?$"
	.string ""
	.string ""
	.string ""

JaggedPass_Text_GruntDefeat:
	.string "Aaargh…\pDebería haberme ocultado en la\nGUARIDA nada más verte…$"
	.string ""
	.string ""

JaggedPass_Text_GoWhereverYouWant:
	.string "¡Vale, vale, que sí!\nLo reconozco: ¡eres fuerte!\pY, desde luego, pienso dejarte\nir a donde te plazca…$"
	.string ""
	.string ""
	.string ""

JaggedPass_Text_BoulderShakingInResponseToEmblem:
	.string "¡Oh! ¡Se diría que esta roca está\ntemblando ante el SIGNO MAGMA!$"
	.string ""

JaggedPass_Text_JulioIntro:
	.string "¡Aaaah, qué susto! ¡No se puede\naparecer de repente, sin avisar!$"
	.string ""

JaggedPass_Text_JulioDefeat:
	.string "Me has desinflado…$"

JaggedPass_Text_JulioPostBattle:
	.string "Tengo el trasero hecho polvo por culpa\nde todos los baches que he pillado.$"
	.string ""

JaggedPass_Text_AutumnIntro:
	.string "Subo esta cuesta cada día.\n¡Estoy en forma!$"
	.string ""

JaggedPass_Text_AutumnDefeat:
	.string "Estoy sin aliento…\n¿Cómo ha podido ocurrir?$"
	.string ""

JaggedPass_Text_AutumnPostBattle:
	.string "¿Qué será esa extraña protuberancia\nrocosa que hay arriba de la colina?$"
	.string ""

