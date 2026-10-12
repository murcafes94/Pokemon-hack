MysteryGiftScript_OldSeaMap::
	setvaddress MysteryGiftScript_OldSeaMap
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_OLD_SEA_MAP, OldSeaMap_Obtained
	vgoto_if_set FLAG_CAUGHT_MEW, OldSeaMap_Obtained
	checkitem ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, TRUE, OldSeaMap_Obtained
	vmessage sText_MysteryGiftOldSeaMapForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, OldSeaMap_NoBagSpace
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	vmessage sText_MysteryGiftOldSeaMapUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_NoBagSpace:
	vmessage sText_MysteryGiftOldSeaMapBagFull
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_Obtained:
	vmessage sText_MysteryGiftOldSeaMapThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftOldSeaMapForYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pDebes de ser {PLAYER}, ¿no?\pPues tenemos una CARTA MARINA para ti.$"
	.string ""
	.string ""
	.string ""
	.string ""

sText_MysteryGiftOldSeaMapUseAtPort:
	.string "Parece que puedes usarlo en el\npuerto de CIUDAD CALAGUA.\p¿Por qué no curioseas un poco\npara ver de qué va la cosa?$"
	.string ""
	.string ""
	.string ""

sText_MysteryGiftOldSeaMapThankYou:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.$"
	.string ""

sText_MysteryGiftOldSeaMapBagFull:
	.string "Lo siento, {PLAYER}. El BOLSILLO\nde los OBJETOS CLAVE está lleno.\pGuarda algo en el PC y vuelve más\ntarde.$"
	.string ""
	.string ""
	.string ""
