BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "¡Eh, qué tal! Si quieres saber algo sobre\nel FRENTE de BATALLA, yo soy tu hombre.\pSe puede decir que soy\nel FOROFO del FRENTE.\pSólo para asegurarme,\ntú entrenas POKéMON, ¿verdad?\pPues estaré encantado de contarte las\núltimas noticias del FRENTE de BATALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "¿Qué tal? ¿Has venido a preguntarme\nqué es lo que más está de moda?$"
	.string ""

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "Well? Well? Well?\pI’m sure my information’s been\nseriously useful to you, right?$"
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "Déjame pensar…\pYo diría que…, sí,\n{STR_VAR_1}, sin duda.$"
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "Déjame pensar…\pCreo que {STR_VAR_1},\nde TORRE BATALLA, es lo que más mola.$"
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "¡Seguro que no lo sabías!\pAllí hay una ENTRENADORA\nde esas a las que TRETO denomina\lAS del FRENTE.\pEs la misteriosa DAMA de la TORRE,\ny es la que hace y deshace por allí.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "¿Te has enfrentado alguna vez\na la DAMA de la TORRE?\pPara medir las fuerzas de su adversario,\nsuele usar estos POKéMON:\pUn POKéMON PSI de tipo PSÍQUICO,\nun POKéMON VOLCÁN de tipo FUEGO\ly un POKéMON DORMIR de tipo NORMAL.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "¿Te has enfrentado alguna vez\na la DAMA de la TORRE en serio?\pCuando pone toda la carne en el asador,\nparece que usa estos POKéMON:\pUn POKéMON EÓN de tipo PSÍQUICO y\nDRAGÓN, un POKéMON TRUENO de tipo\lELÉCTRICO y un POKéMON DORMIR\lde tipo NORMAL.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "¡Seguro que no lo sabías!\pAllí hay un ENTRENADOR de esos\nque TRETO denomina AS del FRENTE.\pEs el extravagante ASTRO de la CÚPULA\ny es el jefe de allí, vaya.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "¿Te has enfrentado alguna vez\nal ASTRO de la CÚPULA?\pCuando no quiere cebarse con el rival,\nsuele usar estos tres POKéMON:\pUn POKéMON DRAGÓN de tipo DRAGÓN\ny VOLADOR, un POKéMON PEZ LODO\lde tipo AGUA y TIERRA, y un POKéMON\lLLAMA de tipo FUEGO y VOLADOR.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "¿Te has enfrentado alguna vez\nal ASTRO de la CÚPULA en serio?\pCuando quiere demostrar lo que sabe,\nsuele usar estos tres POKéMON:\pUn POKéMON EÓN de tipo DRAGÓN y\nPSÍQUICO, un POKéMON PEZ LODO de tipo\lAGUA y TIERRA, y un POKéMON PATA\lHIERRO de tipo ACERO y PSÍQUICO.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "¡Apuesto a que no lo sabías!\pAllí hay un ENTRENADOR de esos\nque TRETO denomina AS del FRENTE.\pEs un tipo un poco raro, pero la cosa\nes que es el JEFE de la FÁBRICA.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "¿Te has enfrentado alguna vez\nal JEFE de la FÁBRICA?\pSi mal no recuerdo, en combate\nsuele alquilar sólo tres POKéMON:\pSuele luchar en igualdad\nde condiciones contra su rival.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "¿Te has enfrentado alguna vez\nal JEFE de la FÁBRICA en serio?\pAunque el combate vaya en serio,\nsigue alquilando sólo tres POKéMON:\pSiempre lucha en igualdad\nde condiciones contra su rival.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "¡Apuesto a que no lo sabías!\pAllí hay una ENTRENADORA\nde esas a las que TRETO denomina\lAS del FRENTE.\pDa un miedo terrible,\n¡es la REINA de la SIERPE!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "¿Te has enfrentado alguna vez\na la REINA de la SIERPE?\pCuando está de buenas, suele\nusar estos tres POKéMON:\pUn POKéMON COLMILLOS de tipo VENENO,\nun POKéMON MOHO de tipo BICHO y ROCA,\ly un POKéMON TIERNO de tipo AGUA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "¿Te has enfrentado alguna vez\na la REINA de la SIERPE en serio?\pCuando está furiosa de verdad,\nsuele usar estos tres POKéMON:\pUn POKéMON COLMILLOS de tipo VENENO,\nun POKéMON SERPFÉRREA de tipo ACERO\ly TIERRA, y un POKéMON ATROCIDAD\lde tipo AGUA y VOLADOR.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "¡Apuesto a que no lo sabías!\pAllí hay una ENTRENADORA\nde esas a las que TRETO denomina\lAS del FRENTE.\pEs una belleza, es la MAESTRA del DOJO.\nParece que es quien manda allí.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "¿Te has enfrentado alguna vez\na la MAESTRA del DOJO?\pCuando está calibrando las fuerzas del\nenemigo, suele usar estos tres POKéMON:\pUn POKéMON UNICORNIO de tipo BICHO\ny LUCHA, un POKéMON LUZ LUNAR\lde tipo SINIESTRO y un POKéMON MUDA\lde tipo BICHO y FANTASMA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "¿Te has enfrentado alguna vez\na la MAESTRA del DOJO en serio?\pCuando da el todo por el todo,\nsuele usar estos tres POKéMON:\pUn POKéMON LUZ LUNAR de tipo\nSINIESTRO, un POKéMON SOMBRA de tipo\lFANTASMA y VENENO, y un POKéMON\lHONGO de tipo PLANTA y LUCHA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "¡Apuesto a que no lo sabías!\pAllí hay un ENTRENADOR de esos\nque TRETO denomina AS del FRENTE.\pEs un ENTRENADOR siniestro llamado\nAMO del PALACIO, y es el que manda allí.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "¿Te has enfrentado alguna vez\nal AMO del PALACIO?\pCuando quiere poner a prueba al rival,\ndicen que suele usar estos POKéMON:\pUn POKéMON MURCIÉLAGO de tipo VENENO\ny VOLADOR, un POKéMON HOLGAZÁN de\ltipo NORMAL y un POKéMON TRANSPORTE\lde tipo AGUA y HIELO.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "¿Te has enfrentado alguna vez\nal AMO del PALACIO en serio?\pCuando se la juega de verdad,\ndicen que usa estos POKéMON:\pUn POKéMON LEGENDARIO de tipo FUEGO,\nun POKéMON HOLGAZÁN de tipo NORMAL\ly un POKéMON AURORA de tipo AGUA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "¡Apuesto a que no lo sabías!\pAllí hay un ENTRENADOR de esos\nque TRETO denomina AS del FRENTE.\pEs el feroz ENTRENADOR al que llaman\nREY de la PIRÁMIDE,\ly allí es como el dueño.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "¿Te has enfrentado alguna vez\nal REY de la PIRÁMIDE?\pCuando quiere probar al enemigo,\nusa siempre estos POKéMON:\pUn POKéMON PICO ROCA de tipo ROCA,\nun POKéMON ICEBERG de tipo HIELO\ly un POKéMON HIERRO de tipo ACERO.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "¿Te has enfrentado alguna vez\nal REY de la PIRÁMIDE en serio?\pCuando no se anda con chiquitas,\nusa siempre estos POKéMON:\pUn POKéMON CONGELAR de tipo HIELO\ny VOLADOR, un POKéMON ELÉCTRICO\lde tipo ELÉCTRICO y VOLADOR, y un\lPOKéMON LLAMA de tipo FUEGO y VOLADOR.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "Claro, hay varios sitios donde puedes\nenfrentarte en COMBATES DOBLES.\pPero digamos que lo básico son las\nSALAS BATALLA de COMBATES DOBLES\lde la TORRE BATALLA.\pEs donde se aprende de verdad\na entablar COMBATES DOBLES\len el FRENTE de BATALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "Ten cuidado en los combates de aquí.\pHe oído que hay ENTRENADORES\nque han creado estrategias sólo\lpara los COMBATES DOBLES.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "Cuando creas que dominas los COMBATES\nDOBLES de aquí, podrás pensar en ir\la otros lugares donde también haya.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "En el SALÓN BATALLA se juntan\ntodo tipo de ENTRENADORES.\p¡Piénsalo, igual hasta te encuentras\ncon tus amigos o con tus seguidores!\l¡Busca y seguro que encuentras!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "Si estás con un amigo, ve a la\nSALA BATALLA de COMBATES\lMULTIJUGADOR con CONEXIÓN.\p¡Si tu amigo es muy fuerte, prepárate\npara enfrentarte a enemigos muy duros!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "¡Qué extraordinario poder adivinatorio!\n¡Nadie puede compararse a mi mentor!$"
	.string ""

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "¡Qué magnífico poder de observación!\n¡Nadie puede compararse a mi mentor!$"
	.string ""

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "¡Qué increíble poder de persuasión!\n¡Nadie puede compararse a mi mentor!$"
	.string ""

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "¡Qué sitio más raro!…\nMe da hasta miedo…$"
	.string ""

