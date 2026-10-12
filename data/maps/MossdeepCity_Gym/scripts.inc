MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

MossdeepCity_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower since it can collide with moving statues
	end

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "Eh, ¿cómo lo llevas, {PLAYER}?\n¿Camino del CAMPEONATO?\pLos LÍDERES de este GIMNASIO usan\nPOKéMON de tipo PSÍQUICO.\pSi les atacas con POKéMON de los tipos\nLUCHA o VENENO, te destrozarán.\pAdemás, van a combatirte con ataques\ncombinados realmente increíbles.\pSi quieres ganar, tendrás que mostrar\nque estás muy unido a tus POKéMON.\l¡Adelante!$"
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

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "¡Guau, eres sorprendente!\n¡Tú sabes cómo luchar!$"
	.string ""

MossdeepCity_Gym_Text_PrestonIntro:
	.string "El resultado del combate depende de tu\nfuerza de voluntad. ¡Nunca te rindas!$"
	.string ""

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "¡Mi fuerza de voluntad ha flaqueado!\n¡Y yo he perdido!$"
	.string ""

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Los indecisos siempre pierden.\nTenlo en cuenta.$"
	.string ""

MossdeepCity_Gym_Text_VirgilIntro:
	.string "¡Demuéstrame lo que vales!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "¡Tú sí que vales!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Las maravillas humanas de este mundo\nson los LÍDERES de GIMNASIO.\pPero es posible que puedas demostrar\nque vales incluso más que ellos…$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Ommmmm… Mira cómo hago levitar\nuna POKé BALL por telequinesia.\pHuy, huy, huy…\n¡Aaaaaaaaah!\pEjem… A veces no controlo muy\nbien mis poderes, je, je, je.$"
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "¡Vaya, mi POKéMON tampoco controla\nmuy bien sus habilidades de combate!$"
	.string ""

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "La POKé BALL de antes pesaba mucho,\n¡pero ya verás con esta pelusa!\pOmmmmm… \p¡Que no! ¡Que no he hecho trampa!\n¡No he soplado, de verdad! Je, je, je.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_HannahIntro:
	.string "Cuando pierdas contra mí, no te\ndeprimas demasiado…\pNo es que seas débil, ¡es que YO\nsoy superfuerte!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_HannahDefeat:
	.string "Ejem… TÚ eres superfuerte…$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "Pero no pienso deprimirme por esta\nderrota, voy a entrenarme más.\p¡Hay que pensar de forma positiva! \n¡Y a mí eso se me da requetebién!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Puedo verlo…\nPuedo verlo claro como el agua…\p¿Quién vencerá en este combate?\n¡No pienso decírtelo!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "¡Esto no estaba previsto!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Puedo ver que librarás un terrible\ncombate con nuestros LÍDERES…\pY ganará…\n¡No pienso decírtelo!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_MauraIntro:
	.string "Has viajado mucho y has vivido\ntodo tipo de experiencias…\p¡Enséñame ahora qué es lo que\nhas aprendido!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_MauraDefeat:
	.string "¡Has viajado por el camino\nde los grandes!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "A aquellos que trabajan duro\nles aguarda un futuro brillante.\pA aquellos que gandulean sólo\nles esperan bastantes palos…\p¡Siempre se recoge lo que se siembra!$"
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_SylviaIntro:
	.string "¡Pienso ganar este combate\ncueste lo que cueste!$"
	.string ""

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Tu forma de luchar…\nes aterradora…$"
	.string ""

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "¿Cómo osas derrotarme?\pNo será culpa mía si te ocurre\nalgo malo muy pronto…$"
	.string ""
	.string ""

MossdeepCity_Gym_Text_NateIntro:
	.string "Jo, jo, jo…\pSerá un placer mostrarte lo tenaz\nque puede ser el tipo PSÍQUICO.$"
	.string ""
	.string ""

MossdeepCity_Gym_Text_NateDefeat:
	.string "¡Fantástico! ¡Excepcional!\n¡Qué estilo de lucha tan magnífico!$"
	.string ""

MossdeepCity_Gym_Text_NatePostBattle:
	.string "Yo… nunca me dejo achantar por\nla derrota…, aunque sea apabullante.$"
	.string ""

MossdeepCity_Gym_Text_KathleenIntro:
	.string "¡Prepárate para pasar más miedo\nque en toda tu vida!$"
	.string ""

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "¡Noooo!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "¡Me has dejado temblando!\n¡Aléjate de mí!$"
	.string ""

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Puede que ya no sea un pimpollo,\npero aún tengo cuerda para rato.$"
	.string ""

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "¡Ah, esta juventud!\n¡Siempre avasallando!$"
	.string ""

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Me temo que me he dejado arrollar\npor tu imperiosa juventud.$"
	.string ""

MossdeepCity_Gym_Text_MaceyIntro:
	.string "¡No pasarás!\n¡No, si puedo impedirlo!$"
	.string ""

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "¿A quién quieres impresionar\ncon esa demostración de fuerza?$"
	.string ""

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "¡Bah! ¡Serás fuerte, pero no tienes\ncualidades para el tipo PSÍQUICO!\p¡Tu manera de luchar es brutal!$"
	.string ""
	.string ""

MossdeepCity_Gym_Text_NicholasIntro:
	.string "¡Grrrrr! ¡Vas a probar mi jarabe\nde POKéMON! ¡Prepárate!$"
	.string ""

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "¡Ah!\n¡Se acabó lo que se daba!$"
	.string ""

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "La próxima vez ya verás…\n¡Te daré jarabe de POKéMON del bueno!$"
	.string ""

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "VITO: Je, je, je, ¿no lo esperabas?\pLETI: Ji, ji, ji, ¿no lo esperabas?\pVITO: ¡Somos dos LÍDERES de GIMNASIO!\nLETI: ¡Somos dos LÍDERES de GIMNASIO!\pVITO: ¡Somos mellizos!\nLETI: ¡Somos mellizos!\pVITO: No necesitamos hablar porque…\nLETI: los dos siempre sabemos lo que…\pVITO: el otro piensa.\nLETI: ¡Es telepatía!\pVITO: Los dos juntos…\nLETI: ¡somos invencibles!$"
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

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "VITO: ¡¿Pe-pero…?! Los dos juntos…\nLETI: ¡nos hemos dejado derrotar!\pVITO: La vida es así. Has ganado…\nLETI: Y también te has ganado esto…$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER} recibió la MEDALLA MENTE\nde LETI y VITO.$"
	.string ""

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "VITO: La MEDALLA MENTE mejora el\nAT. ESP. y la DEF. ESP. de los POKéMON.\pLETI: También te permite usar la MO\nBUCEO fuera del combate.\pVITO: Toma esto también…$"
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "VITO: La MT04 contiene…\nLETI: ¡PAZ MENTAL!\pVITO: Mejora el AT. ESP. y…\nLETI: ¡también la DEF. ESP.!\pVITO: Es un movimiento perfecto…\nLETI: ¡para los POKéMON PSÍQUICOS!\p(…)$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "Acabas de registrar a VITO y LETI, los \nLÍDERES de GIMNASIO, en el POKéNAV.$"
	.string ""

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "VITO: Parece que el vínculo que te une\na tus POKéMON es más fuerte\lque el que nos une como mellizos.\pLETI: ¡Y te harás todavía más fuerte!\nEstamos seguros por cómo combates.$"
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "VITO: Je, je, je, ¿no lo esperabas?\pLETI: ¡Somos dos LÍDERES de GIMNASIO!\pVITO: O-oh, sólo tienes un…\nLETI: POKéMON para luchar.\pVITO: ¡Así no se puede!\pLETI: Si quieres desafiarnos,\ntrae algún POKéMON más.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON de CIUDAD ALGARIA$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON de CIUDAD ALGARIA\pNUEVOS ENTRENADORES CERTIFICADOS:\n{PLAYER}$"
	.string ""
	.string ""

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "VITO: POKéMON por aquí…\nLETI: POKéMON por allá…\pVITO: Cambia la composición del equipo…\nLETI: y cambiarás tu estilo de lucha.\pVITO: Pero yo…\nLETI: Pero yo…\pVITO: ¡siempre estaré con LETI!\nLETI: ¡siempre estaré con VITO!\pVITO: Los dos juntos…\nLETI: ¡somos invencibles!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "VITO: Tus POKéMON y tú…\nLETI: ¡estáis muy unidos!$"
	.string ""

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "VITO: ¡Podrás derrotarnos,\npero nunca achantarnos!\pLETI: ¡Porque nos apoyamos\ny animamos mutuamente!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "VITO: Así que has vuelto…\nLETI: Ya sabemos por qué…\pVITO: Quieres luchar con nosotros.\nLETI: No lo niegues.\pVITO: Pero…,\nLETI: si quieres pelea…,\pVITO: ¡no basta con un POKéMON!\nLETI: ¡Y sólo tienes uno!\pVITO: Necesitas…\nLETI: al menos dos POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
