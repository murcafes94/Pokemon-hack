SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "Escúchame bien si quieres aprender\nalgo muy interesante.\pDicen que hay unas antiguas ruinas\ncerca de aquí, en el mar.\pEs posible que alberguen tesoros\nque sólo esperan a ser descubiertos.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "Fabulosos tesoros submarinos…\pQué bonito sería que existieran\nde verdad, pero, aunque no fuera así,\lme gustaría poder dar un paseo bajo\lel agua en compañía de mi POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""

SootopolisCity_House4_Text_Azumarill:
	.string "AZUMARILL: ¡Mariiiii!$"

