@ Second Kanto leg. Badge uses a new save flag, without resizing save blocks.
LegacyPewter_EventScript_Transition::
	setflag FLAG_LEGACY_KANTO_PEWTER_VISITED
	setrespawn HEAL_LOCATION_LEGACY_KANTO_PEWTER
	end

LegacyPewter_EventScript_RouteAdvice::
	msgbox LegacyPewter_Text_Route, MSGBOX_NPC
	end
LegacyPewter_EventScript_ForestAdvice::
	msgbox LegacyPewter_Text_Forest, MSGBOX_NPC
	end
LegacyPewter_EventScript_Pikachu::
	lock
	faceplayer
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	waitmoncry
	msgbox LegacyPewter_Text_Pikachu, MSGBOX_DEFAULT
	release
	end
LegacyPewter_EventScript_Heal::
	lock
	faceplayer
	special HealPlayerParty
	setrespawn HEAL_LOCATION_LEGACY_KANTO_PEWTER
	msgbox LegacyPewter_Text_Healed, MSGBOX_DEFAULT
	release
	end
LegacyPewter_EventScript_EnterGym::
	lock
	faceplayer
	msgbox LegacyPewter_Text_EnterGym, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyPewter_EventScript_End
	closemessage
	warp MAP_LEGACY_KANTO_PEWTER_GYM, 5, 18
	waitstate
LegacyPewter_EventScript_End::
	releaseall
	end
LegacyPewter_EventScript_GymAdvice::
	msgbox LegacyPewter_Text_GymAdvice, MSGBOX_NPC
	end

LegacyPewter_EventScript_Brock::
	lock
	faceplayer
	goto_if_set FLAG_LEGACY_BADGE_BOULDER, LegacyPewter_EventScript_Done
	goto_if_unset FLAG_SYS_GAME_CLEAR, LegacyPewter_EventScript_NotReady
	goto_if_unset FLAG_LEGACY_KANTO_REPORTED, LegacyPewter_EventScript_NotReady
	checktrainerflag TRAINER_LEGACY_BROCK
	goto_if_eq VAR_RESULT, TRUE, LegacyPewter_EventScript_Award
	msgbox LegacyPewter_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyPewter_EventScript_End
	trainerbattle_single TRAINER_LEGACY_BROCK, LegacyPewter_Text_Intro, LegacyPewter_Text_Defeat, LegacyPewter_EventScript_Award
	goto LegacyPewter_EventScript_Award
LegacyPewter_EventScript_Award::
	setflag FLAG_LEGACY_BADGE_BOULDER
	msgbox LegacyPewter_Text_Award, MSGBOX_DEFAULT
	release
	end
LegacyPewter_EventScript_NotReady::
	msgbox LegacyPewter_Text_NotReady, MSGBOX_DEFAULT
	release
	end
LegacyPewter_EventScript_Done::
	msgbox LegacyPewter_Text_Done, MSGBOX_DEFAULT
	release
	end

LegacyPewter_EventScript_Journal::
	lockall
	msgbox LegacyPewter_Text_Journal, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEGACY_BADGE_BOULDER, LegacyPewter_EventScript_Pending
	msgbox LegacyPewter_Text_Done, MSGBOX_DEFAULT
	releaseall
	end
LegacyPewter_EventScript_Pending::
	msgbox LegacyPewter_Text_Pending, MSGBOX_DEFAULT
	releaseall
	end

LegacyPewter_Text_Route::
	.string "RUTA 2\pAl norte está el BOSQUE VERDE.\nCruza su sendero para llegar al\ppuesto de CIUDAD PLATEADA.\pPodrás regresar a CIUDAD VERDE\npor este mismo camino.$"
LegacyPewter_Text_Forest::
	.string "Los POKéMON del bosque viven\nentre los árboles y la hierba.\pEl sendero central permite cruzar\nsin tener que usar CORTE.\pRespeta el espacio de los POKéMON\ny lleva medicinas para tu equipo.$"
LegacyPewter_Text_Pikachu::
	.string "PIKACHU está atento a los sonidos\ndel bosque.\pLo observas desde el sendero\nsin interrumpir su descanso.$"
LegacyPewter_Text_Healed::
	.string "Tu equipo está recuperado.\pEste puesto será tu punto de\nregreso si pierdes un combate.$"
LegacyPewter_Text_EnterGym::
	.string "BROCK dirige el desafío de\nCIUDAD PLATEADA.\pSu equipo está entre los niveles\n58 y 60.\p¿Quieres entrar al gimnasio?$"
LegacyPewter_Text_GymAdvice::
	.string "BROCK usa POKéMON de tipo ROCA.\pAntes de desafiarlo, entrega el\ninforme de PIDGEY y RATTATA en\pla estación de CIUDAD VERDE.\pLa enfermera del puesto puede\nrecuperar a tu equipo.$"
LegacyPewter_Text_Offer::
	.string "Soy BROCK. He leído tu informe\nsobre los POKéMON de KANTO.\pConocer a tu equipo también\nsignifica aprender a combatir\pjunto a él.\p¿Aceptas el desafío por la\nMEDALLA ROCA?$"
LegacyPewter_Text_Intro::
	.string "¡Muéstrame la fuerza y la\nconfianza de tu equipo!$"
LegacyPewter_Text_Defeat::
	.string "Tu equipo ha demostrado\nuna gran determinación.$"
LegacyPewter_Text_Award::
	.string "¡Has ganado la MEDALLA ROCA!\pEs tu primera medalla de KANTO\ny la novena de tu aventura.\pQueda guardada en el REGISTRO\nDE KANTO de este puesto.\pLas ocho medallas de HOENN\nconservan su propio registro.$"
LegacyPewter_Text_NotReady::
	.string "Este desafío está reservado a\nquienes superaron la LIGA de\pHOENN y entregaron su primer\ninforme de KANTO.\pHabla con el investigador de\nla estación de CIUDAD VERDE.$"
LegacyPewter_Text_Done::
	.string "MEDALLA ROCA: obtenida.\pBROCK reconoce el esfuerzo de\ntu equipo.\pEl siguiente tramo de KANTO\ntodavía está en preparación.$"
LegacyPewter_Text_Journal::
	.string "REGISTRO DE KANTO\pCIUDAD PLATEADA: desafío de\nBROCK por la MEDALLA ROCA.\pEste registro complementa las\nocho medallas de HOENN.$"
LegacyPewter_Text_Pending::
	.string "MEDALLA ROCA: pendiente.\pPuedes prepararte, curar a tu\nequipo y hablar con BROCK.$"
