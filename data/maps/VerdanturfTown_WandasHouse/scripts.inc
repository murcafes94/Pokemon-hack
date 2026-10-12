VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "BLASCO: Me has vencido, {PLAYER}, pero\nahora eso me importa un comino…\pPorque tengo un nuevo objetivo\nen la vida. Junto a mi RALTS,\lvoy a desafiar a los GIMNASIOS POKéMON\ly convertirme en un gran ENTRENADOR.\pNo me pierdas de vista, {PLAYER}.\nVoy a ser más fuerte que tú.\pY, cuando lo sea, te voy a desafiar\na otro combate…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "BLASCO: Obsérvame bien, {PLAYER}.\nVoy a ser más fuerte que tú.\pY, cuando lo sea, te voy a desafiar\na otro combate…$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "TÍO: ¡Ey, {PLAYER}{KUN}!\nBLASCO está al lado.\pPero primero quiero contarte\nuna cosa…\pEste entorno natural está sentando\na BLASCO de maravilla.\pQuizás no sea sólo el entorno.\nLos POKéMON también tendrán que ver…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "BLASCO se ha ido…\nSe ha marchado sin decir ni mu…$"
	.string ""

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "TÍO: ¿Es cierto que BLASCO\nse ha ido tan lejos él solito?\pBueno, no debería extrañarme:\n¡es el hijo de mi hermano!$"
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "CLARA: ¿Tú eras…?\nAh, sí, ya sé.\pEres {PLAYER}. BLASCO siempre está\nhablando de ti.\pSoy la prima de BLASCO.\n¡Es un placer!\pCreo que a BLASCO se le ve mucho\nmás sano y animado desde que está aquí.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "CLARA: No te preocupes por BLASCO.\nSabe cuidarse él solo.\pConozco a mi primo y además\nno está solo: tiene a sus POKéMON.$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Gracias a ti, puedo ver a mi novia\ncada día. ¿Que si estoy contento?\l¿Acaso no se ve? Je, je, je…$"
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "El novio de mi hija es de lo más\nlanzado y apasionado.\pHa estado cavando el túnel\nsin parar sólo para poder verla.\pMi hija está un poco preocupada,\npor eso va al túnel cada dos por tres.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "Es asombroso. ¡El novio de mi hija\nha estado cavando el túnel a mano!\p¡No me lo puedo creer!$"
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "Si algo le pasara a BLASCO, nunca\npodría volver a mirar a sus padres\la la cara, cuando volviera a PETALIA…$"
	.string ""
	.string ""

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "¿BLASCO ha estado en COLOSALIA?\p¡Sus padres, que viven en PETALIA,\nestarían atónitos si lo supieran!$"
	.string ""
	.string ""

