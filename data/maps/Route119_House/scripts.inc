Route119_House_MapScripts::
	.byte 0

Route119_House_EventScript_Woman::
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RumorAboutCaveOfOrigin:
	.string "He oído hablar de una cueva llamada\nCUEVA ANCESTRAL.\pSe rumorea que allí resucitan los\nespíritus de los POKéMON que han\lpartido. ¿Será verdad…?$"
	.string ""
	.string ""
	.string ""
	.string ""

Route119_House_Text_Wingull:
	.string "WINGULL: ¿Wingulu?$"

