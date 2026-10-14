@ First Legacy story segment. Persistent decisions use previously unused flags.

Legacy_EventScript_PrologueBriefing::
	msgbox Legacy_Text_BirchResearchBriefing, MSGBOX_DEFAULT
	setflag FLAG_LEGACY_PROLOGUE_BRIEFED
	return

Legacy_EventScript_AnnexGuide::
	lock
	faceplayer
	goto_if_lt VAR_BIRCH_LAB_STATE, 5, Legacy_EventScript_NotReady
	msgbox Legacy_Text_VisitAnnex, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Legacy_EventScript_DeclineVisit
	closemessage
	warp MAP_LITTLEROOT_TOWN_LEGACY_RESEARCH_ANNEX, 6, 8
	waitstate
	releaseall
	end

Legacy_EventScript_DeclineVisit::
	msgbox Legacy_Text_ReturnWhenReady, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_NotReady::
	msgbox Legacy_Text_FinishBirchsTask, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_Researcher::
	lock
	faceplayer
	goto_if_lt VAR_BIRCH_LAB_STATE, 5, Legacy_EventScript_NotReady
	call_if_unset FLAG_LEGACY_PROLOGUE_BRIEFED, Legacy_EventScript_PrologueBriefing
	goto_if_set FLAG_LEGACY_FIELD_ASSIGNED, LegacyField_EventScript_MissionDesk
	goto_if_set FLAG_LEGACY_FIRST_OBSERVATION, Legacy_EventScript_ObservationDebrief
	goto_if_set FLAG_LEGACY_RESEARCH_REGISTERED, Legacy_EventScript_ObservationInstructions
	msgbox Legacy_Text_JoinResearch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Legacy_EventScript_DeclineVisit
	setflag FLAG_LEGACY_RESEARCH_REGISTERED
	goto Legacy_EventScript_ObservationInstructions

Legacy_EventScript_ObservationInstructions::
	msgbox Legacy_Text_ObservePoochyena, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_ObservationDebrief::
	msgbox Legacy_Text_Debrief, MSGBOX_DEFAULT
	goto_if_set FLAG_LEGACY_APPROACH_PATIENTLY, Legacy_EventScript_TrustDebrief
	msgbox Legacy_Text_DistanceDebrief, MSGBOX_DEFAULT
	goto LegacyField_EventScript_MissionDesk

Legacy_EventScript_TrustDebrief::
	msgbox Legacy_Text_TrustDebrief, MSGBOX_DEFAULT
	goto LegacyField_EventScript_MissionDesk

Legacy_EventScript_FirstObservation::
	lock
	faceplayer
	playmoncry SPECIES_POOCHYENA, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_LEGACY_RESEARCH_REGISTERED, Legacy_EventScript_RegisterFirst
	goto_if_set FLAG_LEGACY_FIRST_OBSERVATION, Legacy_EventScript_AlreadyObserved
	msgbox Legacy_Text_PoochyenaHesitates, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Legacy_EventScript_PatientApproach
	clearflag FLAG_LEGACY_APPROACH_PATIENTLY
	msgbox Legacy_Text_ObserveFromDistance, MSGBOX_DEFAULT
	goto Legacy_EventScript_RecordObservation

Legacy_EventScript_PatientApproach::
	setflag FLAG_LEGACY_APPROACH_PATIENTLY
	msgbox Legacy_Text_WaitForPoochyena, MSGBOX_DEFAULT
	goto Legacy_EventScript_RecordObservation

Legacy_EventScript_RecordObservation::
	setflag FLAG_LEGACY_FIRST_OBSERVATION
	msgbox Legacy_Text_ObservationRecorded, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_RegisterFirst::
	msgbox Legacy_Text_RegisterFirst, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_AlreadyObserved::
	msgbox Legacy_Text_PoochyenaRecognizesYou, MSGBOX_DEFAULT
	release
	end

Legacy_EventScript_ResearchJournal::
	lockall
	goto_if_unset FLAG_LEGACY_RESEARCH_REGISTERED, Legacy_EventScript_EmptyJournal
	goto_if_unset FLAG_LEGACY_FIRST_OBSERVATION, Legacy_EventScript_PendingJournal
	goto_if_set FLAG_LEGACY_APPROACH_PATIENTLY, Legacy_EventScript_PatientJournal
	msgbox Legacy_Text_DistanceJournal, MSGBOX_DEFAULT
	goto LegacyField_EventScript_FieldJournal

Legacy_EventScript_EmptyJournal::
	msgbox Legacy_Text_EmptyJournal, MSGBOX_DEFAULT
	releaseall
	end

Legacy_EventScript_PendingJournal::
	msgbox Legacy_Text_PendingJournal, MSGBOX_DEFAULT
	releaseall
	end

Legacy_EventScript_PatientJournal::
	msgbox Legacy_Text_PatientJournal, MSGBOX_DEFAULT
	goto LegacyField_EventScript_FieldJournal

Legacy_EventScript_RegionalNotes::
	msgbox Legacy_Text_RegionalNotes, MSGBOX_SIGN
	end

Legacy_Text_BirchResearchBriefing::
	.string "ABEDUL: Antes de partir, quiero\ncontarte algo sobre mi investigación.\pEn HOENN se han visto cambios\nextraños en algunos POKéMON.\pQuiero estudiar cómo reaccionan\ny qué lazos forman con las personas.\pEn el anexo hay un ayudante.\nPuedes hablar con él si te interesa.\pRecuerda: observar también significa\nsaber cuándo darles espacio.$"

Legacy_Text_VisitAnnex::
	.string "Soy el guía del anexo de ABEDUL.\pAllí estudiamos la confianza\nentre personas y POKéMON.\p¿Quieres que te lleve al anexo?$"

Legacy_Text_ReturnWhenReady::
	.string "Está bien. Puedes volver\ncuando quieras.$"

Legacy_Text_FinishBirchsTask::
	.string "Primero termina el encargo\ndel PROF. ABEDUL.\pCuando tengas tu POKéDEX,\npodrás participar en el estudio.$"

Legacy_Text_JoinResearch::
	.string "¡Bienvenido al anexo!\pABEDUL nos pidió observar cómo\nnace la confianza de los POKéMON.\pNo buscamos obligarlos ni atraparlos.\nQueremos comprenderlos.\p¿Quieres participar en el estudio?$"

Legacy_Text_ObservePoochyena::
	.string "Acércate al POOCHYENA de la sala\ny observa su reacción.\pEstá aprendiendo a confiar\nen personas que no conoce.\pTú decides cómo responder.\nDespués anotaremos lo ocurrido.$"

Legacy_Text_PoochyenaHesitates::
	.string "POOCHYENA te mira con atención,\npero mantiene cierta distancia.\p¿Quieres esperar con calma\na que decida acercarse?$"

Legacy_Text_WaitForPoochyena::
	.string "Te quedas quieto y le das espacio.\pPOOCHYENA olfatea el aire.\nPoco a poco, deja de tensarse.\pTodavía no se acerca, pero\nya parece más tranquilo.$"

Legacy_Text_ObserveFromDistance::
	.string "Decides observar desde lejos.\pPOOCHYENA observa la sala\nsin perderte de vista.\pAnotas cómo busca un lugar\ndonde sentirse seguro.$"

Legacy_Text_ObservationRecorded::
	.string "La primera observación\nquedó anotada en el registro.\pHabla con el investigador\npara comentar lo que viste.$"

Legacy_Text_RegisterFirst::
	.string "POOCHYENA te observa en silencio.\pHabla primero con el investigador\npara participar en el estudio.$"

Legacy_Text_PoochyenaRecognizesYou::
	.string "POOCHYENA reconoce tu presencia.\nContinúa observando la sala.$"

Legacy_Text_Debrief::
	.string "Cada POKéMON expresa sus emociones\nde una manera distinta.\pNuestro trabajo es escuchar\ny comprender esas señales.$"

Legacy_Text_TrustDebrief::
	.string "Elegiste esperar a que se sintiera\nseguro antes de acercarse.\pLa confianza necesita tiempo.\nTu decisión quedó en el registro.$"

Legacy_Text_DistanceDebrief::
	.string "Elegiste observar desde lejos\ny respetaste su espacio.\pConocer su comportamiento también\nnos ayuda a cuidarlo mejor.$"

Legacy_Text_EmptyJournal::
	.string "REGISTRO DE INVESTIGACIÓN\pTodavía no te has inscrito\nen el estudio del anexo.$"

Legacy_Text_PendingJournal::
	.string "REGISTRO DE INVESTIGACIÓN\pPrimera observación: pendiente.\pHabla con el POOCHYENA de la sala\ny después con el investigador.$"

Legacy_Text_PatientJournal::
	.string "REGISTRO DE INVESTIGACIÓN\pPrimera observación: completada.\pRespuesta: esperar con calma.\nPOOCHYENA se mostró más tranquilo.$"

Legacy_Text_DistanceJournal::
	.string "REGISTRO DE INVESTIGACIÓN\pPrimera observación: completada.\pRespuesta: observar a distancia.\nPOOCHYENA conservó su espacio.$"

Legacy_Text_RegionalNotes::
	.string "PLAN DE INVESTIGACIÓN\pHOENN: observar a los POKéMON\ny aprender a reconocer sus señales.\pKANTO y JOHTO: futuros destinos\npara comparar nuestros hallazgos.\pAntes de buscar respuestas lejanas,\ndebemos conocer a quienes nos rodean.$"
