SafariZone_EventScript_OutOfBallsMidBattle::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 3
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#else
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	end

SafariZone_EventScript_Exit::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#else
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "¿Quieres salir de la ZONA SAFARI\nahora mismo?$"
	.string ""

SafariZone_Text_TimesUp:
	.string "¡Ding, dong! ¡Se acabó el tiempo!\nTu partida SAFARI ha terminado.$"
	.string ""

SafariZone_Text_OutOfBalls:
	.string "Te has quedado sin SAFARI BALLS.\nTu partida SAFARI ha terminado.$"
	.string ""

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "¿Quieres colocar un {POKEBLOCK}\nen el COMEDERO de {POKEBLOCK}S?$"
	.string ""

SafariZone_Text_PokeblockStillHere:
	.string "El {STR_VAR_1} que colocaste\nantes sigue aquí.$"
	.string ""

SafariZone_Text_PokeblockWasPlaced:
	.string "Has colocado un {STR_VAR_1}\nen el COMEDERO de {POKEBLOCK}S.$"
	.string ""

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "¡Hola! ¡Ésta es la ZONA SAFARI!\pAquí puedes ver muchos tipos\nde POKéMON poco comunes en HOENN.\pY además los verás en estado\nsalvaje, en su hábitat natural.\pLo que es más, hemos abierto nuestras\npuertas a los ENTRENADORES POKéMON.\p¡Puedes atrapar los POKéMON\nque quieras y quedártelos para siempre!\p¡Pasa y disfruta de la ZONA SAFARI!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "¡Hola! ¡Ésta es la ZONA SAFARI!\n¿Es la primera vez que vienes?$"
	.string ""

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "¡Pasa y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Cuando entras en la ZONA SAFARI,\nte dan 30 SAFARI BALLS para\latrapar POKéMON.\pLa partida SAFARI se acaba cuando\nte quedas sin SAFARI BALLS\lo has dado 500 pasos.\p¡Pasa y disfruta de la ZONA SAFARI!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "¡Hola! ¡Ésta es la ZONA SAFARI!\p¡Atrapa todo lo que puedas por sólo\n500¥! ¿Quieres jugar una partida\lSAFARI?$"
	.string ""
	.string ""

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "No hay problema.\nVen cuando quieras.$"
	.string ""

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "Lo siento, no tienes bastante dinero.$"
	.string ""

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Son 500¥, por favor.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Aquí tienes tus SAFARI BALLS.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} recibió 30 SAFARI BALLS.$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Te avisaremos cuando se termine\nla partida.\pHasta entonces, pásatelo bien.\n¡La aventura ha comenzado!$"
	.string ""
	.string ""
	.string ""

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "Lo siento, pero todas las CAJAS\nde tu PC están llenas.$"
	.string ""

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "Excuse me!\n"
	.string "You seem to be without a {POKEBLOCK} CASE.\p"
	.string "Your SAFARI Game will be much more\n"
	.string "fruitful if you use {POKEBLOCK}S.\p"
	.string "Please come back with a {POKEBLOCK} CASE.\p"
	.string "You may obtain a {POKEBLOCK} CASE from\n"
	.string "the LILYCOVE CONTEST HALL.$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "Todavía te queda tiempo. ¿Quieres\nsalir de la ZONA SAFARI ahora mismo?$"
	.string ""

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "¡Sigue disfrutando de tu aventura!$"
	.string ""

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Muy bien.\pMe quedaré con las SAFARI BALLS\nque te sobran.\pGracias por jugar con nosotros.\nVuelve siempre que quieras.$"
	.string ""
	.string ""
	.string ""
	.string ""

SafariZone_South_Text_GoodLuck:
	.string "¡Buena suerte!\pSi necesitas algo, lo que sea,\navísame, ¿de acuerdo?$"
	.string ""
	.string ""

SafariZone_South_Text_Boy:
	.string "¿No lo sabías?\pSi pones un {POKEBLOCK} en ese cajón,\natraerás a muchos POKéMON.$"
	.string ""
	.string ""

SafariZone_South_Text_Man:
	.string "Quiero seguir adentrándome,\npero he olvidado mi BICI.\pTengo la corazonada de que en\nlas zonas más distantes viven\lPOKéMON raros.$"
	.string ""
	.string ""
	.string ""

SafariZone_Southwest_Text_Woman:
	.string "A veces, cuando lanzo un {POKEBLOCK}\na un POKéMON, no le hace ni caso.\p¿Los POKéMON también son\ntiquismiquis con la comida?$"
	.string ""
	.string ""
	.string ""

SafariZone_Northwest_Text_Man:
	.string "Uf… Uf…\nHe… llegado hasta… aquí…\pEstoy agotado… No me quedan\nfuerzas para atrapar POKéMON…$"
	.string ""
	.string ""
	.string ""

SafariZone_North_Text_Fisherman:
	.string "Estoy en una misión de búsqueda\nde POKéMON raros de tipo AGUA.\p¿Sabes por dónde queda el lago?$"
	.string ""
	.string ""

SafariZone_North_Text_Man:
	.string "Voy a atrapar un montón de POKéMON\nraros para cambiarlos con mis amigos.$"
	.string ""

SafariZone_South_Text_Youngster:
	.string "He puesto un {POKEBLOCK} en el COMEDERO\nde {POKEBLOCK}S, pero ha desaparecido.\pCreo que algún POKéMON se lo habrá\ncomido cuando no miraba.$"
	.string ""
	.string ""
	.string ""

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "PISTA para ENTRENADORES\nde la ZONA SAFARI\pLanza {POKEBLOCK}S a los POKéMON salvajes\npara que no se escapen corriendo.$"
	.string ""
	.string ""

SafariZone_Southwest_Text_RestHouseSign:
	.string "POSADA\n“Alivia tus cansados pies.”$"
	.string ""

SafariZone_RestHouse_Text_Youngster:
	.string "No tengo ningún {POKEBLOCK}, pero\nhe atrapado bastantes POKéMON.\pPuedes mejorar tus posibilidades\nde atrapar POKéMON acercándote a ellos\lantes de lanzar una SAFARI BALL.$"
	.string ""
	.string ""
	.string ""
	.string ""

SafariZone_RestHouse_Text_PsychicM:
	.string "Si usas {POKEBLOCK}S, los POKéMON\nsalvajes no escaparán tan rápido.\pPero no vale la pena dar {POKEBLOCK}S a los\nPOKéMON que son más mansos…$"
	.string ""
	.string ""
	.string ""

SafariZone_RestHouse_Text_FatMan:
	.string "If you put a {POKEBLOCK} on the FEEDER,\n"
	.string "POKéMON are attracted to it.\p"
	.string "I think POKéMON with the same sort of\n"
	.string "nature are drawn by a certain {POKEBLOCK}.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Aún se está construyendo esta zona.\n¡No te acerques, por favor!$"
	.string ""

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "Ya ha concluido el proyecto\nde ampliación de la ZONA SAFARI.\pEspero que disfrutes de las nuevas\ninstalaciones.$"
	.string ""
	.string ""

SafariZone_South_Text_AreaOffLimits2:
	.string "Aún se está construyendo esta zona.\n¡No te acerques, por favor!$"
	.string ""

SafariZone_Southeast_Text_LittleGirl:
	.string "¡Guau! ¡Eh! ¡Nunca había visto\nestos POKéMON antes!$"
	.string ""

SafariZone_Southeast_Text_FatMan:
	.string "Todos los POKéMON de esta zona\nson nuevos para mí.\p¡Y tengo permiso para atraparlos!\n¡Qué suerte!$"
	.string ""
	.string ""
	.string ""

SafariZone_Southeast_Text_RichBoy:
	.string "Los POKéMON que hay por aquí\nno parece que sean de HOENN.$"
	.string ""

SafariZone_Northeast_Text_Boy:
	.string "Ya sólo me quedan dos SAFARI BALLS.\pLo estoy pasando mal teniendo que\ndecidir cuáles atrapo y cuáles no.$"
	.string ""
	.string ""

SafariZone_Northeast_Text_Woman:
	.string "He oído que hay PIKACHU por aquí.\n¿Por dónde andarán?$"
	.string ""

SafariZone_Northeast_Text_Girl:
	.string "¡Bah!\n¡Oye, no pillo nada!\p¡Con lo que cuesta la entrada\ny yo no voy a atrapar ni uno!$"
	.string ""
	.string ""
	.string ""
