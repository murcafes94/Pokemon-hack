PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_HORSEA, PacifidlogTown_House3_Text_WillingToTradeIt, PacifidlogTown_House3_EventScript_DeclineTrade, PacifidlogTown_House3_EventScript_NotRequestedMon, PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "¿Qué te parece este {STR_VAR_2}?\p¡Es el {STR_VAR_2} que atrapé ayer\npara celebrar mi cumpleaños!\p¡Se te ve en la mirada que lo quieres!\nNo me extraña, ¡no tiene precio!\pTe diré algo. Si quieres,\nte lo cambio por tu {STR_VAR_1}.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "Oh, ¿esto es un {STR_VAR_1}?\pEn cierto modo es como un {STR_VAR_2},\npero, a la vez, sutilmente distinto.\p¡Gracias!$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "¡No, no, no! ¡No aceptaré nada\nque no sea un auténtico {STR_VAR_1}!$"
	.string ""

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "Oh, así que te echas atrás, ¿eh?\pPor mí, perfecto. Yo no es que necesite\ndesesperadamente el cambio, ¿sabes?$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "Ya sé que podía haber ido yo\na buscarlo…\pPero es que quería un BAGON\nque hubiera atrapado otro ENTRENADOR…$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "¿Eso es una POKéDEX?\p¿Has encontrado muchos tipos\ndiferentes de POKéMON?\pOjalá fuera como tú…$"
	.string ""
	.string ""
	.string ""

