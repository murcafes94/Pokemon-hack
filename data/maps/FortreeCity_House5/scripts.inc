FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "Las casas de ARBORADA son geniales.\pÉste es el mejor pueblo para vivir con\nlos POKéMON…, ¡encima de un árbol!$"
	.string ""
	.string ""

FortreeCity_House5_Text_AdaptedToNature:
	.string "Los POKéMON y la gente han tenido\nque adaptarse para sobrevivir.\pEs normal, ¡la naturaleza\nno va a adaptarse a nosotros!$"
	.string ""
	.string ""
	.string ""

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Gungún!$"

