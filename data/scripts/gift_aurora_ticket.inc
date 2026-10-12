MysteryGiftScript_AuroraTicket::
	setvaddress MysteryGiftScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pDebes de ser {PLAYER}, ¿no?\pPues tenemos un ticket para ti.$"
	.string ""
	.string ""
	.string ""

sText_AuroraTicketUseAtPort:
	.string "Parece que puedes usarlo en el\npuerto de CIUDAD CALAGUA.\p¿Por qué no curioseas un poco\npara ver de qué va la cosa?$"
	.string ""
	.string ""
	.string ""

sText_AuroraTicketThankYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.$"
	.string ""

sText_AuroraTicketBagFull:
	.string "Lo siento, {PLAYER}. El BOLSILLO\nde los OBJETOS CLAVE está lleno.\pGuarda algo en el PC y vuelve\nmás tarde.$"
	.string ""
	.string ""
	.string ""
