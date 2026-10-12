MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "¡Chubidubidú!\pAlgunos me llaman el “MACHACARROCAS”,\npero me parece que no es respetuoso.\pMerezco más consideración. Algo así\ncomo el “MAESTRO GOLPE ROCA”.\p¡Chubidubidú!\pGuau, tus POKéMON parecen bastante\nfuertes.\p¡Así me gusta! ¡Como premio te doy\nesta MÁQUINA OCULTA!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Esta MO contiene GOLPE ROCA.\pSi te encuentras con una gran roca\nbloqueando el camino…,\pusa el movimiento de esta MO\ny destrózala para abrirte paso.\p¡Sí, señor! ¡Hay que romper rocas\nporque lo digo yo! ¡Chubidubidú!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "A veces, al romper una roca,\npuedes encontrarte un POKéMON.\p¡Chubidubidú!$"
	.string ""
	.string ""

