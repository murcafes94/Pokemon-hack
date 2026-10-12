MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pTu TARJETA de RECUENTO de\nCOMBATES te muestra los récords\pde los combates mantenidos con\nENTRENADORES que tienen la\lmisma TARJETA.\pBusca ENTRENADORES que\ntengan la misma TARJETA que tú.\pCuando leas las NOTICIAS,\npodrás ver las clasificaciones.\p¡No te lo pierdas!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\p¡Enhorabuena!\p¡Has ganado un premio por vencer\na tu rival en tres combates!\p¡Esperamos que sigas luchando!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
