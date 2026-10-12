SeafloorCavern_Room1_MapScripts::
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_1, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_2, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro:
	.string "¡No queremos enanos por aquí!\n¡Vete a casita con mamá!$"
	.string ""

SeafloorCavern_Room1_Text_Grunt1Defeat:
	.string "Aaaah, quiero irme a casa…$"

SeafloorCavern_Room1_Text_Grunt1PostBattle:
	.string "Quiero que me asciendan para poder\nmandar a los SOLDADOS…$"
	.string ""

SeafloorCavern_Room1_Text_Grunt2Intro:
	.string "Ese submarino es enanísimo…\nMe duele todo de estar ahí encogido…$"
	.string ""

SeafloorCavern_Room1_Text_Grunt2Defeat:
	.string "¡Me duele aún más perder!$"

SeafloorCavern_Room1_Text_Grunt2PostBattle:
	.string "Ese submarino que robamos\nes lo peor: ¡no se cabe dentro!$"
	.string ""
	.string ""

