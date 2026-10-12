AbandonedShip_CaptainsOffice_MapScripts::
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide::
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "Estoy investigando este barco\nen nombre del CAP. BABOR.\pTambién me ha pedido que encuentre\nun ESCÁNER, pero no lo he visto aún…$"
	.string ""
	.string ""
	.string ""

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "¡Ahí va! ¡Eso es un ESCÁNER!\pEscucha, ¿puedes llevárselo\ntú al CAP. BABOR?\pTodavía no he terminado\nde investigar el barco…$"
	.string ""
	.string ""
	.string ""
	.string ""

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "Este barco se llama S.S. CACTUS.\nEs más antiguo que andar “palante”…$"
	.string ""

