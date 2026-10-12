FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "Eh, ¿cómo lo llevas, {PLAYER}?\n¿Camino del CAMPEONATO?\pALANA, la LÍDER del GIMNASIO\nde ARBORADA, es una maestra\lde los POKéMON de tipo VOLADOR.\pElla está al fondo del GIMNASIO,\ntras las puertas giratorias.\pEstá esperando a los ENTRENADORES\nque quieren volar a lo más alto.\pMuy bien, ¡adelante!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "¡Lo has hecho!\n¡Has conseguido despegar!$"
	.string ""

FortreeCity_Gym_Text_JaredIntro:
	.string "¡Observa con qué elegancia lucha\nmi POKéMON PÁJARO!$"
	.string ""

FortreeCity_Gym_Text_JaredDefeat:
	.string "Tú…\neres muy fuerte…$"
	.string ""

FortreeCity_Gym_Text_JaredPostBattle:
	.string "Un ENTRENADOR ha de ser listo y saber\nreaccionar ante cualquier situación.\p¿Y tú? ¿Tienes el ingenio que hace\nfalta para llegar a nuestra LÍDER?$"
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_EdwardoIntro:
	.string "Los amantes de los POKéMON PÁJARO\ndesean ser miembros de este GIMNASIO.\pY, los que somos miembros ya…,\n¡no podemos permitirnos perder!$"
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "Era una carga demasiado pesada\npara mí…$"
	.string ""

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "El mundo es enorme y hay montones\nde ENTRENADORES muy fuertes.\pPor eso debo seguir entrenando\ny mejorando cada vez más.$"
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_FlintIntro:
	.string "¡ALANA, nuestra LÍDER de GIMNASIO,\nno tiene por qué perder tiempo contigo!\p¡Yo me sobro para vencerte!$"
	.string ""
	.string ""

FortreeCity_Gym_Text_FlintDefeat:
	.string "Qué dirá ALANA…\n¡He perdido!$"
	.string ""

FortreeCity_Gym_Text_FlintPostBattle:
	.string "ALANA es la LÍDER definitiva:\n¡tiene fuerza y carácter!\pElla no va a dejarse ganar…$"
	.string ""
	.string ""

FortreeCity_Gym_Text_AshleyIntro:
	.string "ALANA me enseñó todo lo que sé,\nno te pienses que será tan fácil…$"
	.string ""

FortreeCity_Gym_Text_AshleyDefeat:
	.string "Me han derrotado…$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "La gente de ARBORADA vive mucho\nmás tranquila desde que está ALANA.$"
	.string ""

FortreeCity_Gym_Text_HumbertoIntro:
	.string "Cuando ALANA entra en combate,\nsu rostro brilla con determinación…\p¡Pero no dejaré que lo veas\ncon tus propios ojos!$"
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "¡Argh!\nNo he logrado detenerte.$"
	.string ""

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "¡Será mejor que te andes con cuidado!\n¡No te distraigas frente a ALANA\lo te hará picadillo en un periquete!$"
	.string ""
	.string ""

FortreeCity_Gym_Text_DariusIntro:
	.string "Sabrás que hay muchísimas clases\nde POKéMON de tipo VOLADOR…\p¿O no tenías ni idea?$"
	.string ""
	.string ""

FortreeCity_Gym_Text_DariusDefeat:
	.string "¡Ya veo que te sabes la lección!$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "No hay duda de que has vencido, pero\nve con pies de plomo. Los POKéMON\lde nuestra LÍDER ALANA son cosa seria.$"
	.string ""
	.string ""

FortreeCity_Gym_Text_WinonaIntro:
	.string "Soy ALANA, la LÍDER del GIMNASIO\nde ARBORADA.\pHe unido fuerzas con los POKéMON\nPÁJARO y alzado el vuelo.\pPor duro que fuera el combate, siempre\nhemos vencido con gracia y donaire.\p¡Ahora verás con qué elegancia te\nderrotan mis POKéMON PÁJARO!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_WinonaDefeat:
	.string "Nunca antes había visto a ningún\nENTRENADOR capaz de dirigir a sus\lPOKéMON con más arte que yo…\pDebo reconocer tamaña proeza como\nse merece. Toma esta MEDALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{PLAYER} recibió la MEDALLA PLUMA\nde ALANA.$"
	.string ""

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "Con la MEDALLA PLUMA te obedecerán\ntodos los POKéMON hasta el nivel 70,\lincluso los que has intercambiado.\pTambién podrás usar el movimiento\nde la MO VUELO fuera de los combates.\pAdemás quiero hacerte un regalo…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "La MT40 contiene GOLPE AÉREO.\pEs velocísimo: ningún POKéMON\ndebería ser capaz de evitarlo.\pAbsolutamente ninguno…$"
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_RegisteredWinona:
	.string "Acabas de registrar a ALANA,\nla LÍDER de GIMNASIO, en el POKéNAV.$"
	.string ""

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "Aunque he caído ante ti, seguiré\nsiendo fiel a mis POKéMON PÁJARO.$"
	.string ""

FortreeCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON de CIUDAD ARBORADA$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON de CIUDAD ARBORADA\pNUEVOS ENTRENADORES CERTIFICADOS:\n{PLAYER}$"
	.string ""
	.string ""

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "ALANA: Los humanos no podemos\nescapar a la fuerza de la gravedad.\pPero, con mucho trabajo y esfuerzo,\npodemos llegar a lo más alto.\pHas coronado la cumbre y te has\nhecho con el CAMPEONATO.\p¡Estoy deseando ver cómo\nemprendes el vuelo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "Esta nueva victoria te ha dado alas…$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "ALANA: Aunque he perdido,\nmi espíritu permanece intacto.\pSé que puedo alzar el vuelo\ny tocar las nubes.\p¡Y eso haré!$"
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "ALANA: Los humanos no podemos\nescapar a la fuerza de la gravedad.\pPero, con mucho trabajo y esfuerzo,\npodemos llegar a lo más alto.\pHas coronado la cumbre y te has\nhecho con el CAMPEONATO.\p¡Estoy deseando ver cómo\nemprendes el vuelo!\pOh, no…\n¿Sólo llevas un POKéMON contigo?\pVuelve cuando tengas al menos\ndos POKéMON.$"
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
