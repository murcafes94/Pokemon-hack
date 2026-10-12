FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "¿Qué pasa, qué pasa?\pHe visto a un tipo muy sospechoso\nmerodeando por el LABORATORIO del\lPROF. COZMO…$"
	.string ""
	.string ""
	.string ""

FallarborTown_Text_RegionKnownForMeteors:
	.string "Esta región es conocida por sus\nlluvias de meteoritos.\pDicen que la CASCADA METEORO se creó\nhace siglos, a causa de un meteorito…$"
	.string ""
	.string ""
	.string ""

FallarborTown_Text_MyPreciousAzurill:
	.string "¡Mira! ¡Pero mira bien!\n¡Éste es mi precioso AZURILL!\p¿A que es la cosita más mona,\nsuave y blandita del mundo?$"
	.string ""
	.string ""

FallarborTown_Text_Azurill:
	.string "AZURILL: Azu, azuuuu…$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "¿Ya has desafiado a CANDELA, la\nLÍDER del GIMNASIO de LAVACALDA?\pSu abuelo era muy famoso. Perteneció\nal ALTO MANDO de la LIGA POKéMON.\pNo me sorprende ni una pizca que\nCANDELA también se haya convertido\len una gran ENTRENADORA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FallarborTown_Text_BattleTentSign:
	.string "TIENDA de BATALLA de PUEBLO PARDAL\n“¡El punto de encuentro\lde los grandes equipos!”$"
	.string ""

FallarborTown_Text_TownSign:
	.string "PUEBLO PARDAL\n“Una comunidad de granjas y jardines.”$"
	.string ""

FallarborTown_Text_MoveTutorSign:
	.string "CASA del TUTOR de MOVIMIENTOS\n“Enseña movimientos a tus POKéMON.”$"
	.string ""

