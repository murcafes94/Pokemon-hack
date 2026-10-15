@ Northern Kanto: native routes and an independent ninth badge.
LegacyNorth_EventScript_PewterTransition::
	setflag FLAG_LEGACY_KANTO_PEWTER_VISITED
	setrespawn HEAL_LOCATION_LEGACY_KANTO_PEWTER
	end
LegacyNorth_EventScript_Heal::
	lock
	faceplayer
	special HealPlayerParty
	setrespawn HEAL_LOCATION_LEGACY_KANTO_PEWTER
	msgbox LegacyNorth_Text_Healed, MSGBOX_DEFAULT
	release
	end
LegacyNorth_EventScript_RouteAdvice::
	msgbox LegacyNorth_Text_Route, MSGBOX_NPC
	end
LegacyNorth_EventScript_ForestAdvice::
	msgbox LegacyNorth_Text_Forest, MSGBOX_NPC
	end
LegacyNorth_EventScript_PewterAdvice::
	msgbox LegacyNorth_Text_Pewter, MSGBOX_NPC
	end
LegacyNorth_EventScript_Pikachu::
	lock
	faceplayer
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	waitmoncry
	msgbox LegacyNorth_Text_Pikachu, MSGBOX_DEFAULT
	release
	end
LegacyNorth_EventScript_Brock::
	lock
	faceplayer
	goto_if_set FLAG_LEGACY_BADGE_BOULDER, LegacyNorth_EventScript_BrockDone
	goto_if_unset FLAG_SYS_GAME_CLEAR, LegacyNorth_EventScript_NotChampion
	checktrainerflag TRAINER_LEGACY_BROCK
	goto_if_eq VAR_RESULT, TRUE, LegacyNorth_EventScript_AwardBoulder
	msgbox LegacyNorth_Text_BrockOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyNorth_EventScript_Cancel
	trainerbattle_single TRAINER_LEGACY_BROCK, LegacyNorth_Text_BrockIntro, LegacyNorth_Text_BrockDefeat, LegacyNorth_EventScript_AwardBoulder
	release
	end
LegacyNorth_EventScript_AwardBoulder::
	setflag FLAG_LEGACY_BADGE_BOULDER
	playfanfare MUS_OBTAIN_BADGE
	msgbox LegacyNorth_Text_Boulder, MSGBOX_DEFAULT
	waitfanfare
	release
	end
LegacyNorth_EventScript_BrockDone::
	msgbox LegacyNorth_Text_BrockDone, MSGBOX_DEFAULT
	release
	end
LegacyNorth_EventScript_NotChampion::
	msgbox LegacyNorth_Text_NotChampion, MSGBOX_DEFAULT
	release
	end
LegacyNorth_EventScript_Cancel::
	msgbox LegacyNorth_Text_Cancel, MSGBOX_DEFAULT
	release
	end
LegacyNorth_EventScript_BadgeJournal::
	msgbox LegacyNorth_Text_BadgeJournal, MSGBOX_DEFAULT
	goto_if_set FLAG_LEGACY_BADGE_BOULDER, LegacyNorth_EventScript_BadgeRecorded
	msgbox LegacyNorth_Text_BadgePending, MSGBOX_DEFAULT
	return
LegacyNorth_EventScript_BadgeRecorded::
	msgbox LegacyNorth_Text_BadgeRecorded, MSGBOX_DEFAULT
	return

LegacyNorth_Text_Route::
	.string "Esta es la RUTA 2. Hacia el norte\nestá el BOSQUE VERDE.\pEl sendero cruza el bosque hasta\nCIUDAD PLATEADA. Puedes regresar\ppor el mismo camino.$"
LegacyNorth_Text_Forest::
	.string "En este bosque viven CATERPIE,\nWEEDLE y sus evoluciones.\pTambién se ven PIKACHU entre los\nárboles. Los POKéMON salvajes\pestán entre los niveles 51 y 55.\nPrepara a tu equipo antes de cruzar.$"
LegacyNorth_Text_Pikachu::
	.string "PIKACHU escucha el movimiento de\nlas hojas y levanta sus orejas.\pEste POKéMON acompaña al equipo de\ncampo. Puedes encontrar otros\pPIKACHU salvajes entre la hierba.$"
LegacyNorth_Text_Pewter::
	.string "¡Llegaste a CIUDAD PLATEADA!\pLa enfermera del puesto puede\nrecuperar a tus POKéMON.\pBROCK te espera en el gimnasio.\nSu equipo está entre los niveles\p56 y 58. El resto de KANTO sigue\nen preparación.$"
LegacyNorth_Text_Healed::
	.string "Tu equipo está recuperado.\pSi pierdes, regresarás al puesto\nde CIUDAD PLATEADA.\pPara volver a HOENN, sigue al sur\nhasta el barco de PUEBLO PALETA.$"
LegacyNorth_Text_BrockOffer::
	.string "Soy BROCK. Has llegado desde HOENN\npara conocer nuestra región.\pMis POKéMON de tipo ROCA están\nentre los niveles 56 y 58.\p¿Quieres disputar la primera\nmedalla de KANTO?$"
LegacyNorth_Text_BrockIntro::
	.string "¡La firmeza también nace de\nla confianza en tu equipo!$"
LegacyNorth_Text_BrockDefeat::
	.string "¡Has superado nuestra defensa!$"
LegacyNorth_Text_Boulder::
	.string "¡Recibiste la MEDALLA ROCA!\pEs tu primera medalla de KANTO.\nTus ocho medallas de HOENN\ppermanecen en tu tarjeta.\pEl registro de KANTO guardará\nesta nueva victoria.$"
LegacyNorth_Text_BrockDone::
	.string "La MEDALLA ROCA ya es tuya.\pCada región te enseñará una forma\ndistinta de cuidar y entrenar\pa tus POKéMON.$"
LegacyNorth_Text_NotChampion::
	.string "Este desafío continúa tu aventura\ndespués de la LIGA de HOENN.$"
LegacyNorth_Text_Cancel::
	.string "Prepara a tu equipo. Podemos\ncombatir cuando estés listo.$"
LegacyNorth_Text_BadgeJournal::
	.string "REGISTRO DE MEDALLAS DE KANTO\pLas medallas de esta región se\nguardan aparte de la tarjeta\pde HOENN.$"
LegacyNorth_Text_BadgePending::
	.string "MEDALLA ROCA: pendiente.\pVisita a BROCK en el gimnasio\nde CIUDAD PLATEADA.$"
LegacyNorth_Text_BadgeRecorded::
	.string "MEDALLA ROCA: conseguida.\pKANTO: 1 de 8 medallas.\nCon las ocho de HOENN, tienes\p9 de las 24 medallas previstas.\pLos demás gimnasios de KANTO y\nla región de JOHTO siguen\pen preparación.$"
