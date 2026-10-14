@ Native forest clearing. Observations never capture or remove its Pokemon.

LegacyForest_EventScript_Guide::
	lock
	faceplayer
	goto_if_unset FLAG_LEGACY_FIELD_REPORTED, LegacyForest_EventScript_NeedReport
	goto_if_lt VAR_PETALBURG_WOODS_STATE, 1, LegacyForest_EventScript_NeedDevon
	goto_if_set FLAG_LEGACY_FOREST_ASSIGNED, LegacyForest_EventScript_Visit
	msgbox LegacyForest_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyForest_EventScript_Decline
	setflag FLAG_LEGACY_FOREST_ASSIGNED
LegacyForest_EventScript_Travel::
	closemessage
	warp MAP_PETALBURG_WOODS_LEGACY_CLEARING, 11, 16
	waitstate
	releaseall
	end

LegacyForest_EventScript_Visit::
	msgbox LegacyForest_Text_Visit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegacyForest_EventScript_Travel
LegacyForest_EventScript_Decline::
	msgbox LegacyForest_Text_Decline, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_NeedReport::
	msgbox LegacyForest_Text_NeedReport, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_NeedDevon::
	msgbox LegacyForest_Text_NeedDevon, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Researcher::
	lock
	faceplayer
LegacyForest_EventScript_Desk::
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyForest_EventScript_NeedReport
	goto_if_set FLAG_LEGACY_FOREST_REPORTED, LegacyForest_EventScript_Done
	goto_if_unset FLAG_LEGACY_FOREST_SHROOMISH, LegacyForest_EventScript_Instructions
	goto_if_unset FLAG_LEGACY_FOREST_WURMPLE, LegacyForest_EventScript_Instructions
	msgbox LegacyForest_Text_Compare, MSGBOX_DEFAULT
	setflag FLAG_LEGACY_FOREST_REPORTED
	msgbox LegacyForest_Text_Report, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Instructions::
	msgbox LegacyForest_Text_Instructions, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Done::
	msgbox LegacyForest_Text_Done, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Shroomish::
	lock
	faceplayer
	playmoncry SPECIES_SHROOMISH, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyForest_EventScript_NeedReport
	goto_if_set FLAG_LEGACY_FOREST_SHROOMISH, LegacyForest_EventScript_ShroomishAgain
	msgbox LegacyForest_Text_Shroomish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyForest_EventScript_ShroomishWait
	setflag FLAG_LEGACY_FOREST_DISTANCE
	msgbox LegacyForest_Text_ShroomishDistance, MSGBOX_DEFAULT
	goto LegacyForest_EventScript_SaveShroomish
LegacyForest_EventScript_ShroomishWait::
	clearflag FLAG_LEGACY_FOREST_DISTANCE
	msgbox LegacyForest_Text_ShroomishWait, MSGBOX_DEFAULT
LegacyForest_EventScript_SaveShroomish::
	setflag FLAG_LEGACY_FOREST_SHROOMISH
	msgbox LegacyForest_Text_Notes, MSGBOX_DEFAULT
	release
	end
LegacyForest_EventScript_ShroomishAgain::
	goto_if_set FLAG_LEGACY_FOREST_DISTANCE, LegacyForest_EventScript_ShroomishDistanceAgain
	msgbox LegacyForest_Text_ShroomishWait, MSGBOX_DEFAULT
	release
	end
LegacyForest_EventScript_ShroomishDistanceAgain::
	msgbox LegacyForest_Text_ShroomishDistance, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Wurmple::
	lock
	faceplayer
	playmoncry SPECIES_WURMPLE, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyForest_EventScript_NeedReport
	goto_if_set FLAG_LEGACY_FOREST_WURMPLE, LegacyForest_EventScript_WurmpleAgain
	msgbox LegacyForest_Text_Wurmple, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyForest_EventScript_WurmplePass
	setflag FLAG_LEGACY_FOREST_QUIET
	msgbox LegacyForest_Text_WurmpleQuiet, MSGBOX_DEFAULT
	goto LegacyForest_EventScript_SaveWurmple
LegacyForest_EventScript_WurmplePass::
	clearflag FLAG_LEGACY_FOREST_QUIET
	msgbox LegacyForest_Text_WurmplePass, MSGBOX_DEFAULT
LegacyForest_EventScript_SaveWurmple::
	setflag FLAG_LEGACY_FOREST_WURMPLE
	msgbox LegacyForest_Text_Notes, MSGBOX_DEFAULT
	release
	end
LegacyForest_EventScript_WurmpleAgain::
	goto_if_set FLAG_LEGACY_FOREST_QUIET, LegacyForest_EventScript_WurmpleQuietAgain
	msgbox LegacyForest_Text_WurmplePass, MSGBOX_DEFAULT
	release
	end
LegacyForest_EventScript_WurmpleQuietAgain::
	msgbox LegacyForest_Text_WurmpleQuiet, MSGBOX_DEFAULT
	release
	end

LegacyForest_EventScript_Sign::
	lockall
	msgbox LegacyForest_Text_Sign, MSGBOX_DEFAULT
	releaseall
	end

LegacyForest_EventScript_Journal::
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyForest_EventScript_EndJournal
	msgbox LegacyForest_Text_JournalOpen, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEGACY_FOREST_SHROOMISH, LegacyForest_EventScript_CheckWurmple
	goto_if_set FLAG_LEGACY_FOREST_DISTANCE, LegacyForest_EventScript_JournalDistance
	msgbox LegacyForest_Text_JournalWait, MSGBOX_DEFAULT
	goto LegacyForest_EventScript_CheckWurmple
LegacyForest_EventScript_JournalDistance::
	msgbox LegacyForest_Text_JournalDistance, MSGBOX_DEFAULT
LegacyForest_EventScript_CheckWurmple::
	goto_if_unset FLAG_LEGACY_FOREST_WURMPLE, LegacyForest_EventScript_CheckReport
	goto_if_set FLAG_LEGACY_FOREST_QUIET, LegacyForest_EventScript_JournalQuiet
	msgbox LegacyForest_Text_JournalPass, MSGBOX_DEFAULT
	goto LegacyForest_EventScript_CheckReport
LegacyForest_EventScript_JournalQuiet::
	msgbox LegacyForest_Text_JournalQuiet, MSGBOX_DEFAULT
LegacyForest_EventScript_CheckReport::
	goto_if_unset FLAG_LEGACY_FOREST_REPORTED, LegacyForest_EventScript_EndJournal
	msgbox LegacyForest_Text_JournalReport, MSGBOX_DEFAULT
LegacyForest_EventScript_EndJournal::
	releaseall
	end

LegacyForest_Text_Offer::
	.string "¡Recibimos tu informe de la RUTA 102!\pMás adelante hubo un altercado\ncon un empleado de DEVON.\pAhora que el sendero está tranquilo,\npodemos continuar el estudio.\pObservaremos a SHROOMISH y WURMPLE\nen un claro apartado del bosque.\p¿Quieres acompañarme al claro?$"
LegacyForest_Text_Visit::
	.string "El camino al claro está despejado.\n¿Quieres que te acompañe?$"
LegacyForest_Text_Decline::
	.string "Te esperaré aquí. Puedes seguir\nexplorando el bosque y volver luego.$"
LegacyForest_Text_NeedReport::
	.string "Preparamos un estudio del bosque.\pEntrega primero el informe de la\nRUTA 102 en el anexo de VILLA RAÍZ.$"
LegacyForest_Text_NeedDevon::
	.string "Se oyen voces más adelante.\pHay un empleado de DEVON\nque podría necesitar ayuda.\pAntes de entrar al claro,\ncomprueba qué está ocurriendo.$"
LegacyForest_Text_Instructions::
	.string "SHROOMISH busca suelo húmedo.\nWURMPLE se acerca a los árboles.\pObserva a los dos sin capturarlos.\nSus señales pueden ser distintas.\pCuando tengas ambas notas, habla\nconmigo o vuelve al anexo de ABEDUL.$"
LegacyForest_Text_Shroomish::
	.string "SHROOMISH se detiene junto\na la hierba húmeda y te mira.\p¿Quieres observar desde lejos\npara no invadir su espacio?$"
LegacyForest_Text_ShroomishDistance::
	.string "Mantienes la distancia.\pSHROOMISH vuelve a buscar alimento\nsin perder de vista el sendero.$"
LegacyForest_Text_ShroomishWait::
	.string "Permaneces quieto y esperas.\pSHROOMISH te observa un momento\nantes de volver al suelo húmedo.$"
LegacyForest_Text_Wurmple::
	.string "WURMPLE se detiene al notar\nlas pisadas cerca del árbol.\p¿Quieres esperar en silencio\npara observar su reacción?$"
LegacyForest_Text_WurmpleQuiet::
	.string "Esperas sin hacer ruido.\pWURMPLE deja de encogerse\ny vuelve a mirar hacia el árbol.$"
LegacyForest_Text_WurmplePass::
	.string "Le dejas libre el paso.\pWURMPLE vuelve a estirarse\nmientras vigila el sendero.$"
LegacyForest_Text_Notes::
	.string "Anotaste la reacción del POKéMON.\pObserva a las dos especies\ny entrega el informe al investigador.$"
LegacyForest_Text_Compare::
	.string "¡Ya tenemos las dos observaciones!\pEl espacio, el ruido y la paciencia\npueden cambiar una misma situación.\pNo basta con repetir una respuesta:\nhay que atender a cada POKéMON.$"
LegacyForest_Text_Report::
	.string "Informe del claro registrado.\pConservamos tus decisiones anteriores\ny las notas de las dos especies.\pPuedes consultarlas en el libro\ndel anexo de VILLA RAÍZ.$"
LegacyForest_Text_Done::
	.string "El informe del claro ya está guardado.\pPuedes volver a ver a los POKéMON\ny continuar tu recorrido por HOENN.$"
LegacyForest_Text_Sign::
	.string "CLARO DE INVESTIGACIÓN\pRespeta el espacio de los POKéMON.\nLa salida está al sur.\pEl camino regresa al BOSQUE PETALIA,\njunto al guía del estudio.$"
LegacyForest_Text_JournalOpen::
	.string "BOSQUE PETALIA: estudio del claro.\nEspecies: SHROOMISH y WURMPLE.$"
LegacyForest_Text_JournalDistance::
	.string "SHROOMISH: observaste desde lejos\ny respetaste su espacio.$"
LegacyForest_Text_JournalWait::
	.string "SHROOMISH: permaneciste quieto\ny esperaste su reacción.$"
LegacyForest_Text_JournalQuiet::
	.string "WURMPLE: esperaste en silencio\njunto al árbol.$"
LegacyForest_Text_JournalPass::
	.string "WURMPLE: dejaste libre el paso\ny observaste desde el sendero.$"
LegacyForest_Text_JournalReport::
	.string "Informe del claro entregado.\nLas dos observaciones se conservan.$"
