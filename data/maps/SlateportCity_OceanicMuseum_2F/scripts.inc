SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_PARTS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "Si estás buscando a un tal BABOR,\nése soy yo.\p¡Anda! Ésas deben de ser las piezas\nque pedí al SR. PEÑAS de DEVON.\p¡Gracias! ¡Qué bien me vienen!\nYa puedo preparar la expedición.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "¡Je, je, je! ¡Alto ahí!\n¡Esas piezas son nuestras!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "CAP. BABOR: ¿Pe-pero…?\n¿Quiénes sois vosotros?$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "¡Somos el EQUIPO AQUA!\p¡Nuestro JEFE quiere esas piezas!\n¡Cierra el pico y suéltalas!$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "¡Aaaah!\n¡Me ha ganado una criatura!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Ay, ay, ay, qué desastre…\nEl JEFE se va a mosquear…$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "¡Apártate, llorica!\n¡Yo me ocupo de todo!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "¡¿Cómo puede ser?!\n¡Yo también he perdido!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "¿Y ahora qué? ¡Si no conseguimos\nlas piezas, estamos listos!\p¡Aaaah, nunca pensé que alguien\nmangonearía nuestros planes\lde mangoneo!$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Vine a ver por qué tardabais tanto\nen robar unas piezas de nada\ly me encuentro con esto.\p¿Ahora os dejáis vencer por párvulos?$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "¡Somos el EQUIPO AQUA\ny nos encanta el mar!\p¡Y yo soy AQUILES, el líder\ndel EQUIPO AQUA!\pA ver, ¿por qué te inmiscuyes\nen nuestros nobles asuntos?\p¡No! ¡No puede ser!\n¿No eres del EQUIPO MAGMA?\pUn momento, hay algo que no va.\nTu ropa no es como debería ser…\pNo sé, no sé…\pEn fin, has de saber que los POKéMON, la\ngente…, toda la vida depende del mar.\pPor esta razón, el EQUIPO AQUA se\nha consagrado a la expansión del mar.\p¿No estás de acuerdo?\n¡Si nuestra labor es encomiable!\pAh, claro, es natural…\nTodavía eres muy joven para\lentender tan loable objetivo.\pPero, si te vuelves a oponer a\nnuestros designios, ¡tendrás que\lsufrir las consecuencias!\p¡No digas que no te lo he\nadvertido! \p¡Que no se te olvide!$"
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

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "CAP. BABOR: Eres…\nAh, sí, eres {PLAYER}{KUN}…\pUf, qué situación tan violenta…\n¡Gracias por salvarnos!\pAh, sí, casi me olvido de que además\nhas traído las piezas de DEVON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "CAP. BABOR: ¡Pues adelante!\n¡No hay tiempo que perder!\pTenemos que zarpar lo antes posible\npara llevar a cabo nuestra expedición\lal fondo oceánico.\pGracias y discúlpame, pero es que\ntengo cosas que hacer…\p¡Ahora bien, tú puedes darte todas\nlas vueltas que quieras por aquí\ly curiosear cuanto te apetezca!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "He visto un modelo de barco aquí.\pMe ha recordado a la NAO ABANDONADA\nque hay cerca de PUEBLO AZULIZA.$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "¡Ni se te ocurra correr\npor el MUSEO!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "¡Guau, este submarino es impresionante!\n¡Yo me quiero montar!$"
	.string ""

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "La etiqueta dice: “MUESTRA de CALIDAD\nde AGUA 1”.\pTodos los mares se comunican, pero\nel agua parece diferente en cada zona.$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "La etiqueta dice: “MUESTRA de CALIDAD\nde AGUA 2”.\pEs posible que la salinidad del agua sea\ndiferente de un mar a otro…$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Una bola de goma se hincha y deshincha.\p“En el mar, el mismo peso del agua\nejerce presión.\pEn aguas poco profundas, la presión\nno es tan fuerte.\pPero en aguas profundas, la presión\npuede llegar a ser de decenas de miles\lde toneladas en una pequeña zona.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MODELO de la REGIÓN de HOENN”\pEs un diorama en miniatura\nde la región de HOENN.\p¿Dónde está VILLA RAÍZ aquí?$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Es una exposición sobre las corrientes\nmarinas.\p“Cerca del fondo del mar, el agua\nfluye porque hay diferencias de\ltemperatura y salinidad.”$"
	.string ""
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Es una exposición sobre las corrientes\nmarinas.\p“Cerca de la superficie, el agua\nfluye debido a las corrientes que\lprovoca el viento.”$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "EL FERRY S.S. MAREA\p“Una réplica a escala de la nave que se\nestá construyendo en los ASTILLEROS\lBABOR.”$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "SUBMARINO EXPLORADOR 1\p“Una réplica del modernísimo submarino\nde exploración del fondo oceánico.”$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "VEHÍCULO SUMERGIBLE\p“Una réplica de un vehículo de\nexploración del fondo oceánico\lcompacto y no tripulado.”$"
	.string ""
	.string ""

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "S.S. ANNE\p“Una réplica de un transatlántico de\nlujo que navega por todo el mundo.”$"
	.string ""
	.string ""
