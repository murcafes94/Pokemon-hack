@ East Kanto: a returnable field stop; the circuit is never a travel gate.
LegacyEast_EventScript_Camp::
	lock
	faceplayer
	msgbox LegacyEast_Text_Camp, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEGACY_BADGE_BOULDER, LegacyEast_EventScript_CampBeforeBadge
	msgbox LegacyEast_Text_CampAfterBadge, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_CampBeforeBadge::
	msgbox LegacyEast_Text_CampBeforeBadge, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_Ranger::
	lock
	faceplayer
	checktrainerflag TRAINER_LEGACY_ROUTE3_RANGER
	goto_if_eq VAR_RESULT, TRUE, LegacyEast_EventScript_RangerDone
	msgbox LegacyEast_Text_RangerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyEast_EventScript_Cancel
	trainerbattle_single TRAINER_LEGACY_ROUTE3_RANGER, LegacyEast_Text_RangerIntro, LegacyEast_Text_RangerDefeat, LegacyEast_EventScript_RangerDone
	release
	end
LegacyEast_EventScript_RangerDone::
	msgbox LegacyEast_Text_RangerDone, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_Cancel::
	msgbox LegacyEast_Text_Cancel, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_Clefairy::
	lock
	faceplayer
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	msgbox LegacyEast_Text_Clefairy, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_MoonNotes::
	lock
	faceplayer
	msgbox LegacyEast_Text_MoonNotes, MSGBOX_DEFAULT
	checktrainerflag TRAINER_LEGACY_BROCK_CIRCUIT
	goto_if_eq VAR_RESULT, TRUE, LegacyEast_EventScript_CircuitNotes
	msgbox LegacyEast_Text_ResearchNotes, MSGBOX_DEFAULT
	release
	end
LegacyEast_EventScript_CircuitNotes::
	msgbox LegacyEast_Text_CircuitNotes, MSGBOX_DEFAULT
	release
	end

LegacyEast_Text_Camp::
	.string "La RUTA 3 bordea MONTE LUNA.\pEn la cámara de la colina estudiamos\ncómo reaccionan los POKéMON\pa los pasos y al ruido.\pPuedes entrar y volver por aquí.\nPara curarte, regresa al puesto\pde CIUDAD PLATEADA.$"
LegacyEast_Text_CampBeforeBadge::
	.string "BROCK también ayuda al estudio.\pSu gimnasio queda al oeste,\nen CIUDAD PLATEADA. Este sendero\pno exige participar en el circuito.$"
LegacyEast_Text_CampAfterBadge::
	.string "BROCK nos envió notas sobre los\nequipos que llegan desde HOENN.\pQueremos compartirlas con MISTY\ncuando se abra la ruta a CELESTE.\pPor ahora, el recorrido termina\nen esta cámara de MONTE LUNA.$"
LegacyEast_Text_RangerOffer::
	.string "Soy ELÍAS, guía de MONTE LUNA.\pConocer el terreno ayuda tanto\ncomo conocer a tu equipo.\pMis dos POKéMON son de nivel 58\ny 59. ¿Hacemos un combate amistoso?$"
LegacyEast_Text_RangerIntro::
	.string "¡Busquemos nuestro propio ritmo!$"
LegacyEast_Text_RangerDefeat::
	.string "¡Has leído bien el terreno!$"
LegacyEast_Text_RangerDone::
	.string "Para cruzar una región no basta\ncon entrenar para un solo gimnasio.\pLa hierba queda al sur. Si quieres\nevitar encuentros, usa el sendero.\pLa cámara de MONTE LUNA no necesita\nDESTELLO. Guarda antes de entrar.$"
LegacyEast_Text_Cancel::
	.string "Sin prisa. El sendero está libre\ny podemos combatir cuando quieras.$"
LegacyEast_Text_Clefairy::
	.string "CLEFAIRY se detiene a escuchar.\pAl bajar la voz, vuelve a moverse\nentre las piedras. Este POKéMON\pacompaña al equipo de observación.\pPuedes encontrar otros CLEFAIRY\nsalvajes en el suelo de la cueva.$"
LegacyEast_Text_MoonNotes::
	.string "ABEDUL observó cambios de conducta\nen los bosques de HOENN.\pAquí comparamos esas notas con\nla respuesta de los POKéMON\pal eco de MONTE LUNA.\pNo queremos sacar conclusiones\nsin observar antes.$"
LegacyEast_Text_ResearchNotes::
	.string "BROCK participa en el CIRCUITO\nDE LOS LAZOS, en CIUDAD PLATEADA.\pSus exhibiciones nos ayudan a\ncomparar equipos de otras regiones.\pEs una investigación opcional.\nPuedes explorar a tu ritmo.$"
LegacyEast_Text_CircuitNotes::
	.string "BROCK ya nos habló de tu exhibición.\pTu equipo supo cambiar de estrategia\nsin perder la coordinación.\pAnotaremos ese resultado junto a\nlas observaciones de MONTE LUNA.\pCuando lleguemos a CELESTE, MISTY\npodrá aportar otra perspectiva.$"
