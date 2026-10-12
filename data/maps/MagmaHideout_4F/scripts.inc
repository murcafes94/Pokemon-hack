MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON_SLEEPING
	addobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAGMA_HIDEOUT_4F_MAXIE
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_1
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_2
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_3
	removeobject LOCALID_MAGMA_HIDEOUT_4F_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "Yo también quiero ver a GROUDON, pero\nno me dejan ni acercarme a la cola…\pQué frustración más grande…\p¡Oh, no!\n¡Se me ha escapado lo de GROUDON!$"
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "Supongo que no se puede ganar cuando\nno se está tranquilo y concentrado…$"
	.string ""

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "¿Tendrá cola GROUDON?…$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "¡Jua, jua, jua!\n¡Queda poco! ¡Muy poco!\l¡Se va a cumplir nuestro objetivo!$"
	.string ""
	.string ""

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "Grrr…\n¿He venido tan lejos para esto?$"
	.string ""

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "¡Tengo que avisar a MAGNO de que\nse nos ha colado alguien!$"
	.string ""

MagmaHideout_4F_Text_Grunt13Intro:
	.string "¡Todavía no hemos acabado contigo!\n¡No te voy a dejar pasar porque sí!$"
	.string ""

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "¿Tan fácil es derrotarme?$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "Anda, dame la revancha…$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "¡Je, je, je!\n¡Has llegado lejos, lo reconozco!\p¡Y sí, tienes razón!\n¡GROUDON duerme algo más arriba!\p¡MAGNO acaba de ir ahora mismo\nhacia donde está GROUDON!\p¡Le falta poco para despertarse!\n¡Je, je! ¡Je, je, je!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_4F_Text_TabithaDefeat:
	.string "Otra vez vencido…\nJe, je…$"
	.string ""

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "Mientras perdías el tiempo conmigo,\nMAGNO ha despertado a GROUDON…$"
	.string ""

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "MAGNO: GROUDON…\pNada ha logrado despertarte y liberarte\nde tu prisión de magma…\pLo que buscabas era esta\nESFERA AZUL, ¿a que sí?\pPues aquí la tienes.\n¡Que su brillo te despierte!\p¡Muéstrame tu gran poder\nen toda su plenitud!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "MAGNO: ¡GROUDON!\n¿Qué ocurre?\p¿La ESFERA AZUL no es la llave?\p¡GROUDON!\n¿Adónde te has ido?$"
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "MAGNO: Ah, ¿así que has sido tú?\pYa me había fijado en cómo metías\nlas narices donde no te llamaban…\p¡Ya está!\n¡Seguro que todo es culpa tuya!$"
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_4F_Text_MaxieDefeat:
	.string "¿Por qué te gusta tanto andar\ncon los POKéMON?$"
	.string ""

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "MAGNO: Debe de haber algún motivo\npor el que GROUDON se ha ido…\pEso es lo que estás intentando\ndecirme, ¿verdad?\pYa…\nClaro…\pMmmm…\n¿Crees que no me había dado cuenta?\pComo GROUDON se ha ido, ya no\nnecesitamos este estúpido volcán.\p¡Me voy en busca de GROUDON,\nasí que hasta nunca!$"
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
