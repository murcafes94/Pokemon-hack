MysteryGiftScript_MysticTicket::
	setvaddress MysteryGiftScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pDebes de ser {PLAYER}, ¿no?\pPues tenemos un ticket para ti.$"
	.string ""
	.string ""
	.string ""

sText_MysticTicketUseAtPort:
	.string "Parece que puedes usarlo en el\npuerto de CIUDAD CALAGUA.\p¿Por qué no curioseas un poco\npara ver de qué va la cosa?$"
	.string ""
	.string ""
	.string ""

sText_MysticTicketThankYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.$"
	.string ""

sText_MysticTicketBagFull:
	.string "Lo siento, {PLAYER}. El BOLSILLO\nde los OBJETOS CLAVE está lleno.\pGuarda algo en el PC y vuelve\nmás tarde.$"
	.string ""
	.string ""
	.string ""
