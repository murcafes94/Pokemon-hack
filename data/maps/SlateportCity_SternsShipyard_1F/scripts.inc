SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "A ver… Si esto va aquí\ny aquello va allá…\p¿Dónde va esto entonces?\n¿Y qué es esta cosa?\p¡Aaaaah!\n¡No entiendo nada de nada!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "¿Eh?\nAh, hola, soy MUÉLLEZ.\pEl CAP. BABOR me ha encargado\nque diseñe un ferry.\pOh, eso de ahí…\n¿Son las PIEZAS DEVON?\pPero… No puede ser…\pEl CAP. BABOR se fue a no sé\ndónde. Tenía algo que hacer.\p¿Podrías ir a buscarlo\ny entregárselas?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "MUÉLLEZ: ¿Adónde puede haber\nido el CAP. BABOR?\p¿Podrías ir a buscarlo\ny entregarle ese paquete?$"
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "MUÉLLEZ: Construir barcos es todo\nun arte.\pHay muchas cosas que no\nse pueden calcular sin más.\pCómo me gustaría que algún\nlobo de mar me aconsejase…$"
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "MUÉLLEZ: ¡Hola! El SR. ARENQUE\nse ha unido a nosotros.\pGracias a su valiosísima ayuda,\nnuestro proyecto de ferry\lempieza a tomar forma.$"
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "MUÉLLEZ: ¡El ferry está listo!\p¡El nuevo S.S. MAREA es toda\nuna maravilla tecnológica!\pSin embargo, creo que aún\npodemos mejorar el diseño.\p¡Ya sabes que el avance\nde la ciencia es imparable!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "SR. ARENQUE: ¡Anda, {PLAYER}{KUN}!\n¡Cuánto tiempo!\pDesde que te conocí, me he\nsentido la mar de inquieto.\pAsí que he decidido ayudar a\nMUÉLLEZ a construir el ferry.\p¡Imagina cuánta gente podría\ntransportar en cada viaje!\p¿Sabes? Este MUÉLLEZ es\nun tipo especial de verdad.\pUniendo sus conocimientos\ny mi experiencia, haremos\lun gran barco, ¡ya lo creo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Las estaciones, el tiempo,\nla posición de la Luna…\pEl estado del mar se ve afectado\npor todo esto y mucho más.\p¡Exactamente!\n¡El mar tiene vida!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Me entra mareo con nada…, así que\nme han destinado a este puesto.$"
	.string ""

