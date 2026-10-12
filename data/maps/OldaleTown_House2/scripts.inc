OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "Cuando los POKéMON luchan,\nsuben de nivel y se hacen más fuertes.$"
	.string ""

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Si los POKéMON que tienes se vuelven\nmás fuertes, podrás viajar más lejos.$"
	.string ""
	.string ""

