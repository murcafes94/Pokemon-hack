FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_PLUSLE, FortreeCity_House1_Text_YouWillTradeWontYou, FortreeCity_House1_EventScript_DeclineTrade, FortreeCity_House1_EventScript_NotRequestedMon, FortreeCity_House1_Text_MonYouTakeCare
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "¡Grrrrrr! ¡Quiero uno!\n¡Necesito un {STR_VAR_1}!\l¡Daría lo que fuera!\pEh… ¿Has oído el grito desgarrado\nque sale del fondo de mi corazón?\pPues si lo has oído, no dudarás\nen cambiarme tu {STR_VAR_1}\lpor mi {STR_VAR_2}, ¿verdad?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FortreeCity_House1_Text_MonYouTakeCare:
	.string "¡Sí, sí, cómo mola!\p¡Bienvenido, {STR_VAR_1}!\n¡Y tú cuida de {STR_VAR_2}!$"
	.string ""
	.string ""

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Vaya, pues va a ser que no.\nEso no es un {STR_VAR_1}.$"
	.string ""

FortreeCity_House1_Text_YouWontTradeMe:
	.string "¿Que no? ¿No me lo vas a cambiar?\n¿No tienes corazón o qué?$"
	.string ""

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "¡A partir de ahora haré todo lo que sea\nnecesario para fortalecer a VOLBEAT!\p¡Espero que tú hagas lo mismo\npor PLUSLE!$"
	.string ""
	.string ""

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "Cambiar POKéMON…\pPara mí es como dar parte de ti\na otra persona…$"
	.string ""
	.string ""

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: ¿Gungún?$"

