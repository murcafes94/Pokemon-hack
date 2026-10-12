Route119_WeatherInstitute_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_2F_OnTransition
	.byte 0

Route119_WeatherInstitute_2F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 1, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone
	call_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear
	end

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 1, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 4, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 2, 2
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_UP
	return

Route119_WeatherInstitute_2F_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_5, Route119_WeatherInstitute_2F_Text_Grunt5Intro, Route119_WeatherInstitute_2F_Text_Grunt5Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_2, Route119_WeatherInstitute_2F_Text_Grunt2Intro, Route119_WeatherInstitute_2F_Text_Grunt2Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_3, Route119_WeatherInstitute_2F_Text_Grunt3Intro, Route119_WeatherInstitute_2F_Text_Grunt3Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_WEATHER_INSTITUTE, Route119_WeatherInstitute_2F_Text_ShellyIntro, Route119_WeatherInstitute_2F_Text_ShellyDefeat, Route119_WeatherInstitute_2F_EventScript_ShellyDefeated
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_ShellyDefeated::
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3, Route119_WeatherInstitute_2F_Movement_GruntApproachShelly
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_Delay48
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre, MSGBOX_DEFAULT
	closemessage
	setvar VAR_WEATHER_INSTITUTE_STATE, 1
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_1
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_2
	removeobject LOCALID_WEATHER_INSTITUTE_2F_SHELLY
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_4
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition
	waitmovement 0
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastform::
	msgbox Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CASTFORM_NORMAL
	givemon SPECIES_CASTFORM_NORMAL, 25, ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	end

Route119_WeatherInstitute_2F_EventScript_SendCastformToPC::
	call Common_EventScript_TransferredToPC
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_CASTFORM_NORMAL
	return

Route119_WeatherInstitute_2F_EventScript_ExplainCastform::
	msgbox Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_CASTFORM
	release
	end

Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather::
	goto_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather
	msgbox Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather::
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather  @ Both defeated
	call_if_unset FLAG_TEMP_2, Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather
	specialvar VAR_RESULT, GetAbnormalWeatherMapNameAndType
	goto_if_eq VAR_RESULT, 1, Route119_WeatherInstitute_2F_EventScript_KyogreWeather
	msgbox Route119_WeatherInstitute_2F_Text_GroudonWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_KyogreWeather::
	msgbox Route119_WeatherInstitute_2F_Text_KyogreWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather::
	special CreateAbnormalWeatherEvent
	setflag FLAG_TEMP_2
	return

Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather::
	msgbox Route119_WeatherInstitute_2F_Text_NoAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_Movement_GruntApproachShelly:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	ride_water_current_up
	walk_in_place_faster_down
	step_end

Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition:
	slide_down
	walk_in_place_faster_left
	step_end

Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer:
	walk_right
	walk_right
	walk_right
	step_end

Route119_WeatherInstitute_2F_EventScript_WeatherScientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CASTFORM, Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_Text_Grunt2Intro:
	.string "El INSTITUTO ha creado un tipo\nde POKéMON que tiene algo que ver con\lel tiempo. ¡Venimos a por unos cuantos!$"
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_Grunt2Defeat:
	.string "¡¿Semejante mequetrefe\nnos está chafando el plan?!$"

Route119_WeatherInstitute_2F_Text_Grunt2PostBattle:
	.string "¡Si los POKéMON creados aquí pueden\ncontrolar el tiempo a voluntad,\llos del EQUIPO AQUA los necesitamos!$"
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_Grunt3Intro:
	.string "¡Somos el EQUIPO AQUA! ¡Aparecemos\nallí donde hay algo extraordinario!$"
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_Grunt3Defeat:
	.string "¡Me has parado los pies!$"

Route119_WeatherInstitute_2F_Text_Grunt3PostBattle:
	.string "¡No tienes ni idea de lo que los del\nEQUIPO AQUA estamos planeando!\l¡Fuera de mi camino!$"
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_Grunt5Intro:
	.string "¡No me digas que tú también estás\nbuscando ese POKéMON del tiempo!\p¡Ah, pues no, no y no!\n¡Nosotros llegamos aquí primero!$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_Grunt5Defeat:
	.string "Oh, ¿ves cómo están mis POKéMON?$"

Route119_WeatherInstitute_2F_Text_Grunt5PostBattle:
	.string "Bah, ¿y qué?\nLo que nosotros buscamos de verdad…\pLo que nosotros buscamos no está aquí.\n¡Ji, ji, ji, ji!…$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_ShellyIntro:
	.string "¡Ja, ja, ja, ja!\p¿Vas a mezclarte en los asuntos\ndel EQUIPO AQUA?\p¡Entonces, o no tienes miedo o no\ntienes ni idea!\p¡Eres tan dulce que empalagas!\n¡Voy a darte una buena tunda!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_ShellyDefeat:
	.string "¡Ja, ja, ja, ja!\p¡Eres tan fuerte que agobias!$"
	.string ""

Route119_WeatherInstitute_2F_Text_ShellyPostBattle:
	.string "¡Ya es un fastidio tener todo el día\ndetrás al EQUIPO MAGMA\lpara que ahora encima vengas tú!\p¿Se puede saber por qué metes\nlas narices donde no te llaman?$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy:
	.string "¡Tenemos un problema!\pUna banda del EQUIPO MAGMA acaba de\npasar por el INSTITUTO METEOROLÓGICO.\p¡Parece que se dirigen al MONTE PÍRICO!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre:
	.string "¡¿Qué?! ¡¿Cómo?!\p¡No perdamos más tiempo aquí!\nDeprisa, ¡al MONTE PÍRICO!\p¡Ja, ja, ja, ja!\n¡Prepárate, EQUIPO MAGMA! ¡Allá vamos!$"
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon:
	.string "¡Gracias, gracias!\n¡Nos has salvado!\pQuiero agradecértelo de algún modo,\nasí que voy a darte este POKéMON.$"
	.string ""
	.string ""
	.string ""

@ Unused
Route119_WeatherInstitute_2F_Text_NoRoomForPokemon:
	.string "Hm? You don’t seem to have any room\nfor this POKéMON.$"
	.string ""

Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform:
	.string "¡{PLAYER} recibió a CASTFORM!$"

Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather:
	.string "Este POKéMON cambia de forma según\nlas condiciones meteorológicas.\pHay un montón de ellos\nen el INSTITUTO: éste es para ti.$"
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous:
	.string "He investigado la lluvia durante años,\npero es ridículo creer que el hombre\lpuede cambiar el tiempo a su antojo.$"
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_GroudonWeather:
	.string "Me dedico a estudiar los fenómenos\natmosféricos de la región de HOENN.\pAhora mismo, se ha detectado\nque hay sequía en {STR_VAR_1}.\pPodría ser en algún punto cercano\na {STR_VAR_1}…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_KyogreWeather:
	.string "Me dedico a estudiar los fenómenos\natmosféricos de la región de HOENN.\pAhora mismo, se ha detectado que\nhay inundaciones en {STR_VAR_1}.\pPodría ser en algún punto cercano\na {STR_VAR_1}…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route119_WeatherInstitute_2F_Text_NoAbnormalWeather:
	.string "Actualmente no se detecta ninguna\nanomalía en lo que al tiempo se refiere.\pLa verdad es que la lluvia a veces\nviene como agua de mayo.$"
	.string ""
	.string ""
	.string ""

