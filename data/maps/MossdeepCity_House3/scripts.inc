MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "¡Oye, tú, una SUPERCAÑA es lo mejor\npara cualquier ENTRENADOR!\p¿Que no? Pues es lo mejor para\npescar POKéMON marinos.\p¿Qué te parece?\n¿A que quieres una?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "¡Si ya lo sabía yo!\p¡Al fin y al cabo una SUPERCAÑA\nes la caña!$"
	.string ""

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "Si ves algo de agua, lanza la CAÑA\ny espera a ver qué pica.$"
	.string ""

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "¿Y eso?\n¿No te gusta pescar?$"
	.string ""

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "¡Hazte con los POKéMON marinos\ncon la ayuda de tu SUPERCAÑA!$"
	.string ""

