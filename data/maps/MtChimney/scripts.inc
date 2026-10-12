MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_CHIMNEY_MAXIE
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
	removeobject LOCALID_MT_CHIMNEY_TABITHA
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreenswapbuffers FADE_FROM_BLACK
	setobjectxyperm LOCALID_MT_CHIMNEY_ARCHIE, 10, 12
	addobject LOCALID_MT_CHIMNEY_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_MT_CHIMNEY_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
.if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_OFF
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end
.else
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end
.endif @ OW_SHOW_ITEM_DESCRIPTIONS


MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MeteoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "Ese METEORITO posee un gran poder…\pSi lo amplificamos con esta máquina,\nla actividad volcánica del MONTE CENIZO\laumentará al instante…\pSu energía inundará el cráter\ny entonces…\lJua, jua, jua…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_MaxieIntro:
	.string "MAGNO: ¿Eh?\n¿Quién eres tú?\pAjá…\nYa veo…\pHe oído a AQUILES quejarse de alguien\nque intentaba tirar por la borda los\lterribles designios del EQUIPO AQUA.\pSeguro que hablaba de ti.\p¡Ja! ¿Y también buscas problemas\ncon nosotros, el EQUIPO MAGMA?\pEscúchame bien. Desde siempre,\nlos seres vivos han necesitado\lla tierra para vivir. \p¡La tierra lo es todo!\n¡Su importancia es vital!\pPor eso el EQUIPO MAGMA se está\ndedicando a expandir la tierra firme.\p¡Es por el bien de la humanidad\ny de los POKéMON!\pY por eso necesitamos el poder\nque duerme en esa montaña.\p¡Oh! No debería haberte dicho eso.\nTotal, no es asunto tuyo.\p¡Pero no importa! ¡Ahora sufrirás\nlas consecuencias de haberte\lentrometido en nuestros planes!$"
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
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_MaxieDefeat:
	.string "¡¿Qué?!\p¡¿A mí, al gran MAGNO,\nme han dado una lección?!$"
	.string ""

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "MAGNO: Ya basta.\nEsta vez has ganado.\pPero no pienses que es la última vez\nque oirás hablar del EQUIPO MAGMA.\pJua, jua, jua…\pEl METEORITO no importa. Si logramos\nhacernos con la ESFERA… Jua, jua…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_TabithaIntro:
	.string "¡Je, je, je!\p¡Así que has llegado hasta aquí!\p¡Pero ya es demasiado tarde!\n¡He entregado el METEORITO\lde la CASCADA METEORO al JEFE!$"
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_TabithaDefeat:
	.string "Ji, ji, ji…\pMi derrota es irrelevante. Si el JEFE\nlogra despertar a esa cosa…$"
	.string ""
	.string ""

MtChimney_Text_TabithaPostBattle:
	.string "¡JEFE, date prisa!\n¡Transmítele la energía del METEORITO!\pJi, ji, ji…$"
	.string ""
	.string ""

MtChimney_Text_Grunt2Intro:
	.string "Nosotros, los del EQUIPO MAGMA,\nestamos trabajando mucho en beneficio\lde todos.\pPorque, si hay más tierra,\nhabrá más sitios donde vivir.\l¡Todo el mundo será más feliz!$"
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_Grunt2Defeat:
	.string "¿Eh?\n¿Qué quieres decir con que he perdido?$"
	.string ""

MtChimney_Text_Grunt2PostBattle:
	.string "Nuestro JEFE dice que todo el mundo\nserá más feliz…\p¿Pero por qué todo el mundo parece\nllevarnos la contraria?$"
	.string ""
	.string ""
	.string ""

MtChimney_Text_Grunt1Intro:
	.string "¡Si la tierra fuera más vasta, podría\ntener una casona sólo para mí!\p¡La construiré sobre terreno volcánico!$"
	.string ""
	.string ""

MtChimney_Text_Grunt1Defeat:
	.string "Ya me he quedado sin casona…$"

MtChimney_Text_Grunt1PostBattle:
	.string "¡Alguien tan joven como tú\nno tendría que estar aquí!$"
	.string ""

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "Esos plastas del EQUIPO AQUA…\n¡Siempre se meten en todo!$"
	.string ""

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "¡Los METEORITOS contienen\nun poder inmenso!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "¡Será mejor que no nos\nbusques las cosquillas!\p¡Queremos despertar a esa\ncosa en beneficio de todos!$"
	.string ""
	.string ""

MtChimney_Text_AquasNameSimilar:
	.string "¡Somos el EQUIPO MAGMA!\p¡Ellos son el EQUIPO AQUA!\p¡Me fastidia mogollón que\ncasi nos copien el nombre!$"
	.string ""
	.string ""
	.string ""

MtChimney_Text_DouseThemInFire:
	.string "¡Eso, eso!\n¡Abrasémoslos!$"
	.string ""

MtChimney_Text_KeepMakingMoreLand:
	.string "¡Seguiremos luchando por expandir\nla tierra firme!$"

MtChimney_Text_Bufoh:
	.string "¡Guaguaguauuuu!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "AQUILES: ¡{PLAYER}, grrrr!\n¡Tendría que haberlo supuesto!\p¡Ya puedes ver hasta dónde llega\nla locura del EQUIPO MAGMA!\p¡Están intentando transmitir el poder\ndel METEORITO robado al volcán!\p¡Eso provocará que el volcán\nentre en erupción!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "AQUILES: Grrr…\p¡Quiero pararle los pies a ese MAGNO,\npero no puedo!\p¡No si tengo que enfrentarme\na tres adversarios a la vez!$"
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_ArchieThankYou:
	.string "AQUILES: ¡{PLAYER}, gracias!\p¡Con tu ayuda hemos echado por tierra\nel destructivo plan del EQUIPO MAGMA!\pPero tú…\n¿de qué lado estás?\pBah, no importa.\pNo bajaremos la guardia en lo que\nconcierne al malvado EQUIPO MAGMA.\p¡Hasta la próxima, {PLAYER}!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_MagmaOutnumbersUs:
	.string "Vaya… El EQUIPO MAGMA nos supera\nen número. ¡No podemos con ellos!$"
	.string ""

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "Si expanden la tierra, el hábitat de los\nPOKéMON de tipo AGUA se reducirá.$"
	.string ""

MtChimney_Text_MagmasNameSimilar:
	.string "¡Somos el EQUIPO AQUA!\p¡Ellos son el EQUIPO MAGMA!\p¡Me fastidia mogollón que\ncasi nos copien el nombre!$"
	.string ""
	.string ""
	.string ""

MtChimney_Text_Bushaa:
	.string "¡Guau, guau, guau!$"

MtChimney_Text_LavaCookiesJust200:
	.string "Las GALLETAS LAVA son la especialidad\ndel MONTE CENIZO.\pPrueba una. Son sólo 200¥.$"
	.string ""
	.string ""

MtChimney_Text_ThankYouDear:
	.string "¡Muchas gracias!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Pero vamos a ver: si no tienes dinero,\nno puedes comprar nada de nada.$"
	.string ""

MtChimney_Text_OhFineThen:
	.string "Bueno. Tú te lo pierdes…$"

MtChimney_Text_MeteoriteFittedOnMachine:
	.string "A METEORITE is fitted on a mysterious\n"
	.string "machine…\p"
	.string "The machine seems to be storing\n"
	.string "energy in the METEORITE.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Hay un METEORITO dentro de\nuna extraña máquina…\p¿Quieres sacar el METEORITO?$"
	.string ""
	.string ""

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} sacó el METEORITO\nde la extraña máquina.$"
	.string ""

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} dejó el METEORITO\ndonde estaba.$"
	.string ""

MtChimney_Text_MachineMakesNoResponse:
	.string "Esta extraña máquina…\nNo responde…$"
	.string ""

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} DESFILADERO\nPUEBLO LAVACALDA MÁS ADELANTE$"
	.string ""

MtChimney_Text_ShelbyIntro:
	.string "He estado en las fuentes termales\ny he descansado mis pobres huesos.\l¡Ahora me siento fuerte como un roble!$"
	.string ""
	.string ""

MtChimney_Text_ShelbyDefeat:
	.string "Vaya, vaya, vaya…\nTienes un estilo increíble luchando.$"
	.string ""

MtChimney_Text_ShelbyPostBattle:
	.string "Soy una POKéABU con mucha experiencia,\npero aún me pueden dar una lección…$"
	.string ""

MtChimney_Text_ShelbyRegister:
	.string "Gracias, joven. Me ha hecho ilusión\nenfrentarme a las nuevas generaciones.\pNo dudes en venir a verme en alguna\notra ocasión para combatir de nuevo.$"
	.string ""
	.string ""
	.string ""

MtChimney_Text_ShelbyRematchIntro:
	.string "Si eres capaz de fundir tu corazón\ncon los de tus POKéMON, sin duda\llograrás todo lo que te propongas.$"
	.string ""
	.string ""

MtChimney_Text_ShelbyRematchDefeat:
	.string "Vaya, vaya, vaya…\nTienes un estilo increíble luchando.$"
	.string ""

MtChimney_Text_ShelbyPostRematch:
	.string "Es posible que tu corazón y los de tus\nPOKéMON sean sólo uno.$"
	.string ""

MtChimney_Text_MelissaIntro:
	.string "Estoy la mar de nerviosa. Tengo que\ndescargar adrenalina. ¡Vamos a luchar!$"
	.string ""

MtChimney_Text_MelissaDefeat:
	.string "Me he quedado la mar de tranquila…$"

MtChimney_Text_MelissaPostBattle:
	.string "No hay nada como un poco de ejercicio\npara recuperar el buen humor.$"
	.string ""

MtChimney_Text_SheilaIntro:
	.string "Por fin he llegado al MONTE CENIZO.\n¡Y ahora quiero un combate POKéMON!$"
	.string ""

MtChimney_Text_SheilaDefeat:
	.string "Tu manera de luchar…\n¡es como una erupción volcánica!$"
	.string ""

MtChimney_Text_SheilaPostBattle:
	.string "Pues sí, por fin he llegado al MONTE\nCENIZO y no me voy a dedicar\lsólo a hacer visitas…\pTambién quiero luchar un poquito\ny comprar GALLETAS de recuerdo.$"
	.string ""
	.string ""
	.string ""
	.string ""

MtChimney_Text_ShirleyIntro:
	.string "Desde que fui a los baños termales,\nme siento como nueva.\l¡Seguro que te gano!$"
	.string ""
	.string ""

MtChimney_Text_ShirleyDefeat:
	.string "¡Achís!\n¡Creo que he pillado frío!$"
	.string ""

MtChimney_Text_ShirleyPostBattle:
	.string "Mejor me vuelvo a los baños…\n¿Te apuntas?\pYa, ya sé que tienes cosas más\nimportantes que hacer…$"
	.string ""
	.string ""

MtChimney_Text_SawyerIntro:
	.string "¡Esta montaña está que arde! ¡Está\nllena de gente impetuosa y apasionada!$"
	.string ""

MtChimney_Text_SawyerDefeat:
	.string "¡Me has dejado echando humo!$"

MtChimney_Text_SawyerPostBattle:
	.string "¡Debería ir a los BAÑOS TERMALES\nde LAVACALDA, como hacen todos!$"
	.string ""

MtChimney_Text_SawyerRegister:
	.string "Me gusta la gente entusiasta como tú.\nTe voy a registrar en mi POKéNAV.$"
	.string ""

MtChimney_Text_SawyerRematchIntro:
	.string "¡Hay tanta gente que rebosa energía\na mi alrededor que no puedo perder!$"
	.string ""

MtChimney_Text_SawyerRematchDefeat:
	.string "¡Se ve que a ti te gusta\nescaldar a la gente!$"
	.string ""

MtChimney_Text_SawyerPostRematch:
	.string "Va a ser que me he abrigado demasiado\npara el calor que hace por aquí.$"
	.string ""
