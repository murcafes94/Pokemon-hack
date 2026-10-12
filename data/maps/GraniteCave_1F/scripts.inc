GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Oye, tú.\nAquí dentro está muy oscuro.\lNo va a ser fácil explorar esto.\pEse tipo que vino antes…\nMÁXIMO se llamaba…\pÉl sabía cómo usar DESTELLO, así\nque no ha debido de tener problemas…\pPero nosotros, los MONTAÑEROS,\nestamos siempre dispuestos a echar\luna mano… ¡o dos!\pAsí que toma, es para ti.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

GraniteCave_1F_Text_ExplainFlash:
	.string "Enseña el movimiento de MO DESTELLO\na un POKéMON y úsalo.\pPodrás alumbrar incluso las cuevas\noscuras como boca de lobo.\pPero, para usarlo, necesitas la MEDALLA\ndel GIMNASIO de AZULIZA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

