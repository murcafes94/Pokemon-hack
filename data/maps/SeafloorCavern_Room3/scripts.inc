SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "¡Ja, ja, ja, ja!\p¿Cómo has podido llegar hasta aquí\nsin un submarino?\l¡Estoy impresionada!\p¡Pero ya has cotilleado bastante!\p¡Y quiero tomarme la revancha por lo que\npasó en el INSTITUTO METEOROLÓGICO!\p¡Te voy a dar una buena tunda!\n¡Ya te puedes ir preparando!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "Ja, ja, ja, ja…\pAy…$"
	.string ""

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "¡Ja, ja, ja, ja!\n¡Qué fuerte eres!\pLástima que no seas miembro\ndel EQUIPO AQUA.\pPodrías haber disfrutado\ndel maravilloso mundo que el JEFE\lnos ha prometido…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "Para hacer realidad nuestros sueños,\nnecesitamos el poder de los POKéMON.\p¡Pero siempre hay algún entrometido\nque usa el poder de los POKéMON\lpara darnos la lata, incluso aquí!\p¡La vida podría ser mucho más\nfácil sin plastas como tú!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "¡Argh!$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "Mira, nosotros no nos cuestionamos\nlas razones del mandamás.\pPero aquí estás tú, mequetrefe,\nbuscando pelea con el JEFE.\pVa a resultar…\nque tienes agallas…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

