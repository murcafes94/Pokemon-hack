DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "La vida en una islita como ésta, en paz\ny armonía con los POKéMON y tu familia,\lda para hablar largo y tendido.$"
	.string ""
	.string ""

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Yo soy de CIUDAD PORTUAL, pero\nme vine a vivir aquí cuando me casé.\pEl tiempo pasa despacio en esta isla,\npero, tras el estrés de vivir en un gran\lpuerto, sienta bien esta tranquilidad.$"
	.string ""
	.string ""
	.string ""
	.string ""

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Zigzaaaa!$"

