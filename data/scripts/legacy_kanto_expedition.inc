@ Legacy Kanto expedition: curated native maps, independent save flags.
LegacyKanto_EventScript_Depart::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, LegacyKanto_EventScript_NotChampion
	msgbox LegacyKanto_Text_Depart, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	setflag FLAG_LEGACY_KANTO_VISITED
	closemessage
	warp MAP_LEGACY_KANTO_ARRIVAL_PORT, 11, 12
	waitstate
	releaseall
	end
LegacyKanto_EventScript_NotChampion::
	msgbox LegacyKanto_Text_NotChampion, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Cancel::
	msgbox LegacyKanto_Text_Cancel, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Return::
	lock
	faceplayer
	msgbox LegacyKanto_Text_Return, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	closemessage
	setrespawn HEAL_LOCATION_LILYCOVE_CITY
	warp MAP_LILYCOVE_CITY_HARBOR, 5, 13
	waitstate
	releaseall
	end
LegacyKanto_EventScript_Welcome::
	msgbox LegacyKanto_Text_Welcome, MSGBOX_NPC
	end
LegacyKanto_EventScript_RouteAdvice::
	msgbox LegacyKanto_Text_RouteAdvice, MSGBOX_NPC
	end
LegacyKanto_EventScript_StationGuide::
	lock
	faceplayer
	msgbox LegacyKanto_Text_StationGuide, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	closemessage
	warp MAP_LEGACY_KANTO_RESEARCH_STATION, 6, 8
	waitstate
	releaseall
	end
LegacyKanto_EventScript_StationTransition::
	setrespawn HEAL_LOCATION_LEGACY_KANTO_STATION
	end
LegacyKanto_EventScript_Heal::
	lock
	faceplayer
	special HealPlayerParty
	setrespawn HEAL_LOCATION_LEGACY_KANTO_STATION
	msgbox LegacyKanto_Text_Healed, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Shop::
	lock
	faceplayer
	msgbox LegacyKanto_Text_Shop, MSGBOX_DEFAULT
	pokemart LegacyKanto_Items
	release
	end
LegacyKanto_Items:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_REVIVE
	.2byte ITEM_NONE
LegacyKanto_EventScript_Pidgey::
	lock
	faceplayer
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	waitmoncry
	goto_if_set FLAG_LEGACY_KANTO_PIDGEY, LegacyKanto_EventScript_PidgeyAgain
	msgbox LegacyKanto_Text_Pidgey, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	setflag FLAG_LEGACY_KANTO_PIDGEY
	msgbox LegacyKanto_Text_PidgeyNotes, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_PidgeyAgain::
	msgbox LegacyKanto_Text_PidgeyNotes, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Rattata::
	lock
	faceplayer
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	waitmoncry
	goto_if_set FLAG_LEGACY_KANTO_RATTATA, LegacyKanto_EventScript_RattataAgain
	msgbox LegacyKanto_Text_Rattata, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	setflag FLAG_LEGACY_KANTO_RATTATA
	msgbox LegacyKanto_Text_RattataNotes, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_RattataAgain::
	msgbox LegacyKanto_Text_RattataNotes, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Report::
	lock
	faceplayer
	goto_if_set FLAG_LEGACY_KANTO_REPORTED, LegacyKanto_EventScript_Done
	goto_if_unset FLAG_LEGACY_KANTO_PIDGEY, LegacyKanto_EventScript_Pending
	goto_if_unset FLAG_LEGACY_KANTO_RATTATA, LegacyKanto_EventScript_Pending
	setflag FLAG_LEGACY_KANTO_REPORTED
	msgbox LegacyKanto_Text_Report, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Pending::
	msgbox LegacyKanto_Text_Pending, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Done::
	msgbox LegacyKanto_Text_Done, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_Journal::
	lockall
	msgbox LegacyKanto_Text_Journal, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEGACY_KANTO_PIDGEY, LegacyKanto_EventScript_CheckRattata
	msgbox LegacyKanto_Text_PidgeyNotes, MSGBOX_DEFAULT
LegacyKanto_EventScript_CheckRattata::
	goto_if_unset FLAG_LEGACY_KANTO_RATTATA, LegacyKanto_EventScript_CheckReport
	msgbox LegacyKanto_Text_RattataNotes, MSGBOX_DEFAULT
LegacyKanto_EventScript_CheckReport::
	goto_if_unset FLAG_LEGACY_KANTO_REPORTED, LegacyKanto_EventScript_EndJournal
	msgbox LegacyKanto_Text_Done, MSGBOX_DEFAULT
LegacyKanto_EventScript_EndJournal::
	releaseall
	end
LegacyKanto_EventScript_Eevee::
	lock
	faceplayer
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	waitmoncry
	msgbox LegacyKanto_Text_Eevee, MSGBOX_DEFAULT
	release
	end
LegacyKanto_EventScript_OutpostSign::
	msgbox LegacyKanto_Text_Outpost, MSGBOX_SIGN
	end
LegacyKanto_EventScript_Trainer::
	lock
	faceplayer
	checktrainerflag TRAINER_LEGACY_KANTO_SCOUT
	goto_if_eq VAR_RESULT, TRUE, LegacyKanto_EventScript_TrainerDone
	msgbox LegacyKanto_Text_TrainerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyKanto_EventScript_Cancel
	trainerbattle_single TRAINER_LEGACY_KANTO_SCOUT, LegacyKanto_Text_TrainerIntro, LegacyKanto_Text_TrainerDefeat
LegacyKanto_EventScript_TrainerDone::
	msgbox LegacyKanto_Text_TrainerDone, MSGBOX_DEFAULT
	release
	end

LegacyKanto_Text_Depart::
	.string "La expedición de ABEDUL está lista\npara visitar KANTO.\pAtracaremos en el puesto costero de\nPUEBLO PALETA.\pTu equipo y tu equipaje viajarán\ncontigo. Puedes volver cuando\pquieras.\p¿Quieres embarcar hacia KANTO?$"

LegacyKanto_Text_NotChampion::
	.string "Este viaje se prepara para después de\nsuperar la LIGA de HOENN.\pPrimero continúa tu aventura. El barco\nte esperará en este puerto.$"

LegacyKanto_Text_Cancel::
	.string "De acuerdo. Puedes volver cuando\nestés listo.$"

LegacyKanto_Text_Return::
	.string "El barco puede llevarte de vuelta a\nCIUDAD CALAGUA, en HOENN.\p¿Quieres regresar ahora?$"

LegacyKanto_Text_Welcome::
	.string "¡Bienvenido a KANTO! Este es nuestro\npuesto junto a PUEBLO PALETA.\pLa salida del edificio lleva a la RUTA\n1. Sigue al norte hasta el puesto de\pCIUDAD VERDE.\pAllí podrás curar a tu equipo y\nentregar tus notas.\pEsta expedición abre el primer tramo.\nLos demás destinos siguen en\ppreparación.$"

LegacyKanto_Text_RouteAdvice::
	.string "En HOENN observaste a ZIGZAGOON.\nAquí compararemos a PIDGEY y\pRATTATA.\pHabla con los dos POKéMON del sendero.\nSus notas van al puesto del norte.\pEn la hierba hay POKéMON salvajes que\nsí puedes combatir y capturar.$"

LegacyKanto_Text_StationGuide::
	.string "Aquí comienza el puesto de estudio de\nCIUDAD VERDE.\pEn la estación encontrarás una\nenfermera y al investigador.\p¿Quieres entrar?$"

LegacyKanto_Text_Healed::
	.string "Tu equipo está recuperado.\pSi pierdes un combate, regresarás a\nesta estación.\pEl barco del sur sigue disponible para\nvolver a HOENN.$"

LegacyKanto_Text_Shop::
	.string "Tenemos provisiones para la\nexpedición. ¿Qué necesitas?$"

LegacyKanto_Text_Pidgey::
	.string "PIDGEY vigila el sendero desde el\nborde de la hierba.\p¿Quieres observar cómo cambia su\natención cuando te quedas quieto?$"

LegacyKanto_Text_PidgeyNotes::
	.string "PIDGEY: al detenerte, el POKéMON\nvolvió a mirar hacia la hierba.\pLa nota quedó guardada para\ncompararla con los registros de HOENN.$"

LegacyKanto_Text_Rattata::
	.string "RATTATA busca alimento junto al\ncamino y se detiene al verte.\p¿Quieres observarlo dejando libre su\nrecorrido?$"

LegacyKanto_Text_RattataNotes::
	.string "RATTATA: mantuviste libre el camino y\ncontinuó buscando alimento.\pLa nota quedó guardada para el\ninforme de KANTO.$"

LegacyKanto_Text_Pending::
	.string "Necesitamos las notas de PIDGEY y\nRATTATA de la RUTA 1.\pPuedes observarlos en cualquier\norden. Regresa cuando tengas ambas.$"

LegacyKanto_Text_Report::
	.string "¡Primer informe de KANTO registrado!\pPIDGEY vigila desde la hierba. RATTATA\nbusca un paso seguro.\pCompararemos estas señales con\nPOOCHYENA y ZIGZAGOON de HOENN.\pEl estudio continúa hacia CIUDAD\nPLATEADA. Estamos preparando el\psiguiente tramo.$"

LegacyKanto_Text_Done::
	.string "El informe de KANTO ya está guardado.\nPuedes consultarlo en este libro.\pTus observaciones anteriores\npermanecen en el anexo de ABEDUL.$"

LegacyKanto_Text_Journal::
	.string "REGISTRO DE KANTO\pEstudio: PIDGEY y RATTATA de la RUTA\n1. Las notas aparecen a continuación.$"

LegacyKanto_Text_Eevee::
	.string "EEVEE observa a los visitantes del\npuesto de investigación.\pParece adaptarse con facilidad a un\nentorno nuevo.$"

LegacyKanto_Text_Outpost::
	.string "PUESTO DE CIUDAD VERDE\pEstación de investigación: habla con\nel guía del norte.\pRegreso a PUEBLO PALETA: sigue el\nsendero hacia el sur.$"

LegacyKanto_Text_TrainerOffer::
	.string "Soy MARCOS, del equipo de campo. Mis\nPOKéMON están entre los niveles 55 y\p56.\pPodemos comprobar cómo se adapta tu\nequipo a KANTO.\p¿Quieres un combate de práctica?$"

LegacyKanto_Text_TrainerIntro::
	.string "¡Veamos lo que aprendiste en HOENN!$"

LegacyKanto_Text_TrainerDefeat::
	.string "¡Tu equipo sabe trabajar unido!$"

LegacyKanto_Text_TrainerDone::
	.string "Buen combate. El estudio del\ncomportamiento también nos enseña a\pentrenar.\pPuedes continuar por el sendero o\ndescansar en la estación.$"
