BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MEOWTH, BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, BattleFrontier_Lounge6_EventScript_DeclineTrade, BattleFrontier_Lounge6_EventScript_NotRequestedMon, BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "Mi POKéMON es un {STR_VAR_2}.\n¿Lo conoces?\l¿A que es una monada?\pSi quieres, te lo cambio por uno tuyo.\p¿Qué tal cambiar tu {STR_VAR_1}\npor mi {STR_VAR_2}?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "¡Oh, es adorable!\n¡Gracias!\l¡Te prometo que me portaré bien con él!\p¡Y espero que tú también\nte portes bien con mi {STR_VAR_2}!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "¡Oh, lo siento!\nSólo lo cambio por un {STR_VAR_1}.$"
	.string ""
	.string ""

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "Ah, ¿que no?\nBueno, a mí, plin.\lEn fin, ya sabes dónde me tienes.$"
	.string ""
	.string ""

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "¡Ji, ji, ji!\nSKITTY es mucho más mono de lo\lque pensaba. ¡Estoy encantadísima!$"
	.string ""
	.string ""
