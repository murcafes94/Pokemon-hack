MossdeepCity_House1_MapScripts::
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	goto_if_eq VAR_RESULT, 0, MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature::
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman::
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon:
	.string "¡Ajá!\nTu {STR_VAR_1} lo tiene claro…$"
	.string ""

MossdeepCity_House1_Text_ItLikesXPokeblocks:
	.string "Lo que más le gusta en el mundo\nes un {STR_VAR_1}, ¿a que sí?\pSí, sí, no cabe ninguna duda. ¡Haría lo\nque fuera por un {STR_VAR_1}!$"
	.string ""
	.string ""
	.string ""

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks:
	.string "Le da un poco igual qué tipo\nde {POKEBLOCK}S le des, ¿no?$"
	.string ""

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes:
	.string "Mi marido adivina enseguida qué tipo\nde {POKEBLOCK}S prefiere cada POKéMON.$"
	.string ""

