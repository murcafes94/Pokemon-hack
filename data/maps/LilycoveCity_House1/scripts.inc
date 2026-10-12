LilycoveCity_House1_MapScripts::
	.byte 0

LilycoveCity_House1_EventScript_ExpertM::
	msgbox LilycoveCity_House1_Text_PokemonPartnersNotTools, MSGBOX_NPC
	end

LilycoveCity_House1_EventScript_Kecleon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_NORMAL
	msgbox LilycoveCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_House1_Text_PokemonPartnersNotTools:
	.string "Los POKéMON son amigos de la gente,\nno sus esclavos o algo así.\pPor desgracia parece que hay gente\nque es incapaz de entender esto…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_House1_Text_Kecleon:
	.string "KECLEON: ¿Kecle?$"

