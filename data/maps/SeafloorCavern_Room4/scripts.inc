SeafloorCavern_Room4_MapScripts::
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_4, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro:
	.string "¿Quién eres?\n¿De dónde vienes?$"
	.string ""

SeafloorCavern_Room4_Text_Grunt3Defeat:
	.string "¿He perdido?$"

SeafloorCavern_Room4_Text_Grunt3PostBattle:
	.string "¡No consigo salir de aquí!\pMe estoy empezando a poner nervioso…$"
	.string ""

SeafloorCavern_Room4_Text_Grunt4Intro:
	.string "¿Quién eres?\n¿Adónde te crees que vas?$"
	.string ""

SeafloorCavern_Room4_Text_Grunt4Defeat:
	.string "¡Me has ganado!$"

SeafloorCavern_Room4_Text_Grunt4PostBattle:
	.string "¡Mi colega se olvidó el mapa\nen ese submarino!\p¡Hay que ser inútil!$"
	.string ""
	.string ""

