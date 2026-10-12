SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
	.string "¡Aaaaargh! ¡Estoy hasta las narices\nde no acabar nunca de limpiar esto!\p¡Vamos a luchar para desfogarme!$"
	.string ""
	.string ""

SSTidalLowerDeck_Text_PhillipDefeat:
	.string "Je, je… Pues he perdido…$"

SSTidalLowerDeck_Text_PhillipPostBattle:
	.string "¡Somos los HERMANOS FREGONA!\pEl mayor echa jabón en el suelo\ny el joven fregotea por todas partes.$"
	.string ""
	.string ""

SSTidalLowerDeck_Text_LeonardIntro:
	.string "Éste es el nivel inferior del casco.\nAquí hay un montón de sitio.\lSe puede luchar sin agobios…$"
	.string ""
	.string ""

SSTidalLowerDeck_Text_LeonardDefeat:
	.string "Je, je… Pues he perdido…$"

SSTidalLowerDeck_Text_LeonardPostBattle:
	.string "¡Somos los HERMANOS FREGONA!\pEl mayor echa jabón en el suelo\ny el joven fregotea por todas partes.$"
	.string ""
	.string ""

