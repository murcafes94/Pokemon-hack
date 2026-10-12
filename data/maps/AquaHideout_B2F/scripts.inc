AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	setvar VAR_0x8009, LOCALID_AQUA_HIDEOUT_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "Jo, jo, jo…\p¿Has llegado hasta aquí?\nCreo que te hemos subestimado.\p¡Pero ya está bien de tonterías!\pYo soy más fuerte que los SOLDADOS\ncon los que has luchado hasta ahora.\pNo voy a limitarme a hacerte perder\ntiempo… ¡Te voy a pulverizar!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_B2F_Text_MattDefeat:
	.string "Jo, jo, jo…\nYo tampoco lo he logrado…$"
	.string ""

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "¡Jo, jo, jo!\p¡Mientras me divertía contigo,\nnuestro JEFE terminó los preparativos!$"
	.string ""
	.string ""

AquaHideout_B2F_Text_MattPostBattle:
	.string "¡Jo, jo, jo!\pNuestro JEFE ya ha ido a ocultarse\na una cueva submarina.\pSi quieres encontrarlo, tendrás que\nbuscarlo en el gran mar que hay\lmás allá de CALAGUA.\p¿Pero acaso podrás encontrar\nsiquiera el mar? ¡Jo, jo, jo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_B2F_Text_Grunt4Intro:
	.string "¡Jua, jua, jua! ¡Estoy harto de esperar!\n¡Me debes un combate!$"
	.string ""

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "Total, podía haberme quedado\nesperando…$"
	.string ""

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "El JEFE no va a estar satisfecho…$"
	.string ""

AquaHideout_B2F_Text_Grunt6Intro:
	.string "Baldosas teletransportadoras:\n¡el orgullo de la GUARIDA!\pNo tienes ni idea de dónde estás,\n¿verdad?\pAturullar al enemigo para luego caer\nsobre ellos. ¡Ése es nuestro plan!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "¿Y tú qué desayunas?\n¿Cómo es que no te cansas?$"
	.string ""

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "Esto me recuerda… que no me acuerdo\nde dónde puse la MASTER BALL.\pSi no la protejo bien, el JEFE me va\na machacar…$"
	.string ""
	.string ""
	.string ""

AquaHideout_B2F_Text_Grunt8Intro:
	.string "Lo primero que aprendí al entrar en el\nEQUIPO AQUA fue cómo están conectadas\lestas baldosas teletransportadoras.$"
	.string ""
	.string ""

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "Debería pensar en algo más que en las\nbaldosas teletransportadoras…$"
	.string ""

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "Tengo que encontrar la manera\nde luchar de forma más eficaz…$"
	.string ""
