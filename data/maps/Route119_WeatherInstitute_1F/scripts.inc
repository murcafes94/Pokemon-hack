Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  @ Both defeated
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
	.string "El JEFE está interesado en la\ninvestigación que están realizando\laquí, por eso nos ha enviado.\p¡Quítate de en medio!$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
	.string "No me lo creo…\nMe has vencido, mequetrefe…$"
	.string ""

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
	.string "No hay nada que nuestro\nJEFE no sepa…\pPero yo sólo soy un SOLDADO. ¿Cómo\nvoy a saber lo que tiene en mente?$"
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
	.string "¿Eh?\n¿Qué haces tú aquí?$"
	.string ""

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
	.string "¿Yo?\n¿He perdido? ¡¿Yo?!$"
	.string ""

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
	.string "Oh, no…\nQué bronca me va a caer…\pCreo que voy a echarme una siesta\npara olvidar todo esto…$"
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
	.string "¡Mientras dormía, alguien se coló\narriba!$"
	.string ""

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
	.string "¡Guau, qué fuerte eres!\p¡Ojalá pudiera ser un ENTRENADOR\nPOKéMON tan bueno como tú!$"
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
	.string "Al PROFESOR le encanta la lluvia.\nEso es un hecho.\pPero si sigue lloviendo así, tendremos\nproblemas. Eso también es un hecho.\pPor eso el PROFESOR está estudiando\ncómo hacer buen uso de esta lluvia.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
	.string "En el primer piso del INSTITUTO\nestudiamos los fenómenos atmosféricos\lde la región de HOENN.\pÚltimamente, estamos detectando casos\naislados de sequía e inundaciones…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
	.string "¡Hola!\n¡Nos has salvado!\pLo que no logro entender es lo que\npretenden los del EQUIPO AQUA…$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
	.string "Mira, una cama…\n¡A descansar!$"
	.string ""

