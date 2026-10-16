@ Native Cerulean: checkpoint, independent badge and optional circuit.
LegacyCerulean_EventScript_Transition::
	setflag FLAG_LEGACY_KANTO_CERULEAN_VISITED
	setrespawn HEAL_LOCATION_LEGACY_KANTO_CERULEAN
	end
LegacyCerulean_EventScript_Heal::
	lock
	faceplayer
	special HealPlayerParty
	setrespawn HEAL_LOCATION_LEGACY_KANTO_CERULEAN
	msgbox LegacyCerulean_Text_Healed, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_RouteAdvice::
	msgbox LegacyCerulean_Text_Route, MSGBOX_NPC
	end
LegacyCerulean_EventScript_Research::
	lock
	faceplayer
	msgbox LegacyCerulean_Text_Research, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEGACY_BADGE_CASCADE, LegacyCerulean_EventScript_ResearchPending
	msgbox LegacyCerulean_Text_ResearchBadge, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_ResearchPending::
	msgbox LegacyCerulean_Text_ResearchPending, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_Misty::
	lock
	faceplayer
	goto_if_set FLAG_LEGACY_BADGE_CASCADE, LegacyCerulean_EventScript_Circuit
	goto_if_unset FLAG_LEGACY_BADGE_BOULDER, LegacyCerulean_EventScript_BrockFirst
	checktrainerflag TRAINER_LEGACY_MISTY
	goto_if_eq VAR_RESULT, TRUE, LegacyCerulean_EventScript_AwardCascade
	msgbox LegacyCerulean_Text_MistyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyCerulean_EventScript_Cancel
	trainerbattle_single TRAINER_LEGACY_MISTY, LegacyCerulean_Text_MistyIntro, LegacyCerulean_Text_MistyDefeat, LegacyCerulean_EventScript_AwardCascade
	release
	end
LegacyCerulean_EventScript_AwardCascade::
	setflag FLAG_LEGACY_BADGE_CASCADE
	playfanfare MUS_OBTAIN_BADGE
	msgbox LegacyCerulean_Text_Cascade, MSGBOX_DEFAULT
	waitfanfare
	release
	end
LegacyCerulean_EventScript_BrockFirst::
	msgbox LegacyCerulean_Text_BrockFirst, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_Cancel::
	msgbox LegacyCerulean_Text_Cancel, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_Circuit::
	checktrainerflag TRAINER_LEGACY_MISTY_CIRCUIT
	goto_if_eq VAR_RESULT, TRUE, LegacyCerulean_EventScript_CircuitDone
	checktrainerflag TRAINER_LEGACY_BROCK_CIRCUIT
	goto_if_eq VAR_RESULT, FALSE, LegacyCerulean_EventScript_CircuitBrockFirst
	msgbox LegacyCerulean_Text_CircuitOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyCerulean_EventScript_Cancel
	trainerbattle_single TRAINER_LEGACY_MISTY_CIRCUIT, LegacyCerulean_Text_CircuitIntro, LegacyCerulean_Text_CircuitDefeat, LegacyCerulean_EventScript_CircuitDone
	release
	end
LegacyCerulean_EventScript_CircuitBrockFirst::
	msgbox LegacyCerulean_Text_CircuitBrockFirst, MSGBOX_DEFAULT
	release
	end
LegacyCerulean_EventScript_CircuitDone::
	msgbox LegacyCerulean_Text_CircuitDone, MSGBOX_DEFAULT
	release
	end

LegacyCerulean_Text_Route::
	.string "Esta es la RUTA 4. Hacia el este\nllegarás a CIUDAD CELESTE.\pEl sendero evita la hierba alta.\nPuedes volver a MONTE LUNA\ppor la entrada del oeste.$"
LegacyCerulean_Text_Healed::
	.string "Tu equipo está recuperado.\pSi pierdes un combate, regresarás\na este puesto de CIUDAD CELESTE.\pPara volver a HOENN puedes regresar\na PUEBLO PALETA y tomar el barco.$"
LegacyCerulean_Text_Research::
	.string "¡Bienvenido a CIUDAD CELESTE!\pAquí comparamos las observaciones\nde MONTE LUNA con las respuestas\pde los POKéMON de tipo AGUA.\pMISTY dirige los combates en el\npatio junto al estanque.$"
LegacyCerulean_Text_ResearchPending::
	.string "La enfermera y el vendedor están\nen el puesto de la plaza.\pMISTY te espera al nordeste.\nPrimero consigue la MEDALLA ROCA\pde BROCK para disputar la suya.$"
LegacyCerulean_Text_ResearchBadge::
	.string "MEDALLA CASCADA: conseguida.\pKANTO: 2 de 8 medallas.\nCon las ocho de HOENN, tienes\p10 de las 24 medallas previstas.\pEl CIRCUITO DE LOS LAZOS ofrece\nun desafío aparte de los gimnasios.$"
LegacyCerulean_Text_MistyOffer::
	.string "Soy MISTY. BROCK me avisó de tu\nrecorrido desde HOENN.\pEste patio es nuestro escenario\npara el desafío de CELESTE.\pUsaré tres POKéMON de tipo AGUA,\nentre los niveles 60 y 62.\p¿Quieres disputar la\nMEDALLA CASCADA?$"
LegacyCerulean_Text_MistyIntro::
	.string "¡Un equipo debe saber cambiar\nde corriente sin separarse!$"
LegacyCerulean_Text_MistyDefeat::
	.string "¡Has encontrado nuestro ritmo!$"
LegacyCerulean_Text_Cascade::
	.string "¡Recibiste la MEDALLA CASCADA!\pEs tu segunda medalla de KANTO.\nEl registro conserva también\pla MEDALLA ROCA de BROCK.\pTus ocho medallas de HOENN\npermanecen en tu tarjeta.$"
LegacyCerulean_Text_BrockFirst::
	.string "Puedes explorar CELESTE libremente.\pPara disputar mi medalla, consigue\nantes la MEDALLA ROCA de BROCK,\pen CIUDAD PLATEADA.$"
LegacyCerulean_Text_Cancel::
	.string "Prepara a tu equipo con calma.\nPodemos combatir cuando quieras.$"
LegacyCerulean_Text_CircuitOffer::
	.string "BROCK compartió tus resultados\ndel CIRCUITO DE LOS LAZOS.\pEn HOENN estudiaste la confianza.\nAhora observaremos la adaptación\pde un equipo que cambia de ritmo.\pMi exhibición usa tres POKéMON\nde nivel 64, 65 y 66.\pNo está en juego otra medalla.\n¿Quieres participar?$"
LegacyCerulean_Text_CircuitIntro::
	.string "¡La confianza también nos permite\nprobar una estrategia diferente!$"
LegacyCerulean_Text_CircuitDefeat::
	.string "¡Tu equipo sabe adaptarse!$"
LegacyCerulean_Text_CircuitBrockFirst::
	.string "La MEDALLA CASCADA ya es tuya.\pTambién participo en el CIRCUITO\nDE LOS LAZOS, junto a BROCK.\pEmpieza su exhibición en PLATEADA.\nDespués podremos comparar aquí\plo aprendido por ambos equipos.$"
LegacyCerulean_Text_CircuitDone::
	.string "Tu exhibición de CELESTE queda\nregistrada en el circuito.\pCompartiremos las notas con ABEDUL:\nconfiar también significa permitir\pque un compañero cambie de ritmo.\pBROCK y yo seguimos preparando\nnuevos encuentros entre regiones.$"

LegacyCerulean_EventScript_BothBadges::
	msgbox LegacyCerulean_Text_ResearchBadge, MSGBOX_DEFAULT
	return
