@ Hoenn field assignment. No terrain, encounter tables, or original rewards changed.

LegacyField_EventScript_MissionDesk::
	goto_if_unset FLAG_LEGACY_FIRST_OBSERVATION, LegacyField_EventScript_NotReady
	goto_if_set FLAG_LEGACY_FIELD_REPORTED, LegacyField_EventScript_ReportAlreadyFiled
	goto_if_set FLAG_LEGACY_FIELD_OBSERVED, LegacyField_EventScript_FileReport
	goto_if_set FLAG_LEGACY_FIELD_ASSIGNED, LegacyField_EventScript_AssignmentReminder
	msgbox LegacyField_Text_OfferAssignment, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyField_EventScript_DeclineAssignment
	setflag FLAG_LEGACY_FIELD_ASSIGNED
	msgbox LegacyField_Text_Directions, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_DeclineAssignment::
	msgbox LegacyField_Text_DeclineAssignment, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_NotReady::
	msgbox LegacyField_Text_FinishFirstObservation, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_AssignmentReminder::
	msgbox LegacyField_Text_Directions, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_FieldResearcher::
	lock
	faceplayer
	goto_if_unset FLAG_LEGACY_FIELD_ASSIGNED, LegacyField_EventScript_CampNotReady
	goto_if_set FLAG_LEGACY_FIELD_REPORTED, LegacyField_EventScript_CampAfterReport
	goto_if_set FLAG_LEGACY_FIELD_OBSERVED, LegacyField_EventScript_ReturnToAnnex
	msgbox LegacyField_Text_CampIntroduction, MSGBOX_DEFAULT
	goto_if_set FLAG_LEGACY_APPROACH_PATIENTLY, LegacyField_EventScript_PatienceAdvice
	msgbox LegacyField_Text_DistanceAdvice, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_CampNotReady::
	msgbox LegacyField_Text_CampNotReady, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_PatienceAdvice::
	msgbox LegacyField_Text_PatienceAdvice, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_ReturnToAnnex::
	msgbox LegacyField_Text_ReturnToAnnex, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_CampAfterReport::
	msgbox LegacyField_Text_CampAfterReport, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_ObserveZigzagoon::
	lock
	faceplayer
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_LEGACY_FIELD_ASSIGNED, LegacyField_EventScript_ZigzagoonBeforeAssignment
	goto_if_set FLAG_LEGACY_FIELD_OBSERVED, LegacyField_EventScript_RepeatObservation
	msgbox LegacyField_Text_ZigzagoonAtPath, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegacyField_EventScript_WaitForZigzagoon
	clearflag FLAG_LEGACY_FIELD_WAITED
	msgbox LegacyField_Text_LeavePassage, MSGBOX_DEFAULT
	goto LegacyField_EventScript_RecordFieldObservation

LegacyField_EventScript_WaitForZigzagoon::
	setflag FLAG_LEGACY_FIELD_WAITED
	msgbox LegacyField_Text_WaitForZigzagoon, MSGBOX_DEFAULT
	goto LegacyField_EventScript_RecordFieldObservation

LegacyField_EventScript_RecordFieldObservation::
	setflag FLAG_LEGACY_FIELD_OBSERVED
	msgbox LegacyField_Text_FieldObservationRecorded, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_ZigzagoonBeforeAssignment::
	msgbox LegacyField_Text_ZigzagoonBeforeAssignment, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_RepeatObservation::
	goto_if_set FLAG_LEGACY_FIELD_WAITED, LegacyField_EventScript_ZigzagoonCalmer
	msgbox LegacyField_Text_ZigzagoonKeepingDistance, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_ZigzagoonCalmer::
	msgbox LegacyField_Text_ZigzagoonCalmer, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_FileReport::
	msgbox LegacyField_Text_ReportIntroduction, MSGBOX_DEFAULT
	goto_if_set FLAG_LEGACY_FIELD_WAITED, LegacyField_EventScript_FilePatientReport
	msgbox LegacyField_Text_PassageReport, MSGBOX_DEFAULT
	goto LegacyField_EventScript_CloseReport

LegacyField_EventScript_FilePatientReport::
	msgbox LegacyField_Text_PatientReport, MSGBOX_DEFAULT
	goto LegacyField_EventScript_CloseReport

LegacyField_EventScript_CloseReport::
	setflag FLAG_LEGACY_FIELD_REPORTED
	msgbox LegacyField_Text_ReportFiled, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_ReportAlreadyFiled::
	msgbox LegacyField_Text_ReportAlreadyFiled, MSGBOX_DEFAULT
	release
	end

LegacyField_EventScript_FieldJournal::
	goto_if_unset FLAG_LEGACY_FIELD_ASSIGNED, LegacyField_EventScript_EndJournal
	goto_if_set FLAG_LEGACY_FIELD_REPORTED, LegacyField_EventScript_JournalReport
	goto_if_set FLAG_LEGACY_FIELD_OBSERVED, LegacyField_EventScript_JournalReturn
	msgbox LegacyField_Text_JournalAssigned, MSGBOX_DEFAULT
	releaseall
	end

LegacyField_EventScript_JournalReturn::
	msgbox LegacyField_Text_JournalReturn, MSGBOX_DEFAULT
	releaseall
	end

LegacyField_EventScript_JournalReport::
	goto_if_set FLAG_LEGACY_FIELD_WAITED, LegacyField_EventScript_JournalPatientReport
	msgbox LegacyField_Text_JournalPassageReport, MSGBOX_DEFAULT
	releaseall
	end

LegacyField_EventScript_JournalPatientReport::
	msgbox LegacyField_Text_JournalPatientReport, MSGBOX_DEFAULT
	releaseall
	end

LegacyField_EventScript_EndJournal::
	releaseall
	end

LegacyField_EventScript_Route102Transition::
	goto_if_unset FLAG_LEGACY_FIELD_OBSERVED, LegacyField_EventScript_EndTransition
	goto_if_unset FLAG_LEGACY_FIELD_WAITED, LegacyField_EventScript_EndTransition
	setobjectmovementtype LOCALID_LEGACY_FIELD_ZIGZAGOON, MOVEMENT_TYPE_LOOK_AROUND
LegacyField_EventScript_EndTransition::
	end

LegacyField_Text_OfferAssignment::
	.string "Ya viste cómo reacciona un POKéMON\nen un lugar donde se siente protegido.\pAhora queremos comparar esa señal\ncon lo que ocurre en su entorno.\pHay un ZIGZAGOON en la RUTA 102,\ncerca de los árboles de bayas.\p¿Quieres realizar una observación\nde campo y traer tus notas?$"

LegacyField_Text_DeclineAssignment::
	.string "De acuerdo. El encargo seguirá\ndisponible cuando quieras volver.$"

LegacyField_Text_FinishFirstObservation::
	.string "Primero completa la observación\nde POOCHYENA en el anexo.\pDespués podrás participar\nen el trabajo de campo.$"

LegacyField_Text_Directions::
	.string "Ve a la RUTA 102, al oeste\nde PUEBLO ESCASO.\pEncontrarás a nuestro investigador\nal norte, cerca de los árboles de bayas.\pObserva al ZIGZAGOON de esa zona\ny vuelve al anexo con tus notas.\pNo necesitas atraparlo ni combatir.\nNos interesa conocer su reacción.$"

LegacyField_Text_CampIntroduction::
	.string "¡Vienes del anexo de ABEDUL!\pEse ZIGZAGOON se detiene\ncuando alguien pasa por el sendero.\pQueremos entender si se siente\nseguro con nuestra presencia.$"

LegacyField_Text_PatienceAdvice::
	.string "Me contaron que esperaste\ncon calma junto a POOCHYENA.\pPuedes partir de esa experiencia,\npero observa las señales de ZIGZAGOON.\pCada POKéMON puede necesitar\nuna respuesta diferente.$"

LegacyField_Text_DistanceAdvice::
	.string "Me contaron que observaste\na POOCHYENA desde lejos.\pAquí también es importante\nrespetar el espacio del POKéMON.\pFíjate en cómo responde ZIGZAGOON\nantes de decidir qué hacer.$"

LegacyField_Text_CampNotReady::
	.string "Soy parte del estudio de ABEDUL.\pNuestro equipo trabaja desde\nel anexo del laboratorio de VILLA RAÍZ.\pHabla allí con el investigador\nsi quieres participar.$"

LegacyField_Text_ZigzagoonAtPath::
	.string "ZIGZAGOON deja de olfatear\nlas bayas y te observa.\pParece atento al espacio\nque queda junto al sendero.\p¿Quieres esperar sin moverte\npara que se acostumbre a tu presencia?$"

LegacyField_Text_WaitForZigzagoon::
	.string "Esperas en silencio.\pZIGZAGOON vuelve a olfatear el aire.\nYa no te mira con tanta tensión.\pAnotas cómo cambia su reacción\ncuando dejas de moverte.$"

LegacyField_Text_LeavePassage::
	.string "Decides darle espacio para pasar.\pZIGZAGOON sigue atento al sendero,\npero ya no necesita vigilarte tanto.\pAnotas la importancia de mantener\nuna distancia que le resulte segura.$"

LegacyField_Text_FieldObservationRecorded::
	.string "Guardaste tus notas de campo.\pVuelve con el investigador del anexo\npara entregar el informe.$"

LegacyField_Text_ZigzagoonBeforeAssignment::
	.string "ZIGZAGOON te observa desde\nel borde del sendero.\pParece interesado en las bayas.$"

LegacyField_Text_ZigzagoonCalmer::
	.string "ZIGZAGOON te reconoce.\pMira alrededor con más calma\ny vuelve a olfatear el aire.$"

LegacyField_Text_ZigzagoonKeepingDistance::
	.string "ZIGZAGOON conserva su espacio.\pContinúa atento al sendero\nmientras te observa.$"

LegacyField_Text_ReturnToAnnex::
	.string "Tus notas ya están listas.\pVuelve al anexo de VILLA RAÍZ\ny habla con el investigador.\pAllí compararemos ambos registros.$"

LegacyField_Text_CampAfterReport::
	.string "¡ABEDUL ya recibió tu informe!\pLa observación del sendero ayudará\na preparar la siguiente investigación.$"

LegacyField_Text_ReportIntroduction::
	.string "¡Trajiste las notas de la RUTA 102!\pEn el anexo y en el campo observaste\nseñales de confianza y de cautela.\pVeamos qué ocurrió en el sendero.$"

LegacyField_Text_PatientReport::
	.string "Al quedarte quieto, ZIGZAGOON\npareció aceptar mejor tu presencia.\pEso no significa que todos los\nPOKéMON reaccionen igual.\pEscuchar sus señales será importante\nen las próximas investigaciones.$"

LegacyField_Text_PassageReport::
	.string "Elegiste darle espacio para pasar.\pRespetar sus movimientos también\nes una forma de cuidarlo.\pLo importante es comprender\nlo que el POKéMON intenta expresar.$"

LegacyField_Text_ReportFiled::
	.string "Informe de campo entregado.\pEnviaré estas notas al PROF. ABEDUL.\nPuedes consultarlas en el registro.\pEl próximo informe viene del\nBOSQUE PETALIA. Aún debemos revisarlo.\pPor ahora, sigue explorando HOENN.\nTe avisaremos cuando haya novedades.$"

LegacyField_Text_ReportAlreadyFiled::
	.string "Tu informe de la RUTA 102\nya está registrado.\pGracias por ayudar a comprender\nmejor a los POKéMON de HOENN.$"

LegacyField_Text_JournalAssigned::
	.string "TRABAJO DE CAMPO: RUTA 102\pEncargo: observar a ZIGZAGOON\ncerca de los árboles de bayas.\pEstado: observación pendiente.$"

LegacyField_Text_JournalReturn::
	.string "TRABAJO DE CAMPO: RUTA 102\pObservación: completada.\nInforme: pendiente de entregar.\pVuelve con el investigador del anexo.$"

LegacyField_Text_JournalPatientReport::
	.string "TRABAJO DE CAMPO: RUTA 102\pInforme: entregado.\pRespuesta: esperar en silencio.\nZIGZAGOON se mostró más tranquilo.$"

LegacyField_Text_JournalPassageReport::
	.string "TRABAJO DE CAMPO: RUTA 102\pInforme: entregado.\pRespuesta: darle espacio para pasar.\nZIGZAGOON mantuvo su espacio.$"
