MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "¡No es nada personal, pero\ntengo órdenes que cumplir!$"
	.string ""

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "Vale, he perdido, pero…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "¡Hemos desenterrado lo más grande!\n¡Y la ESFERA AZUL es nuestra!\pLo único que tiene que hacer el jefe\nes… Jo, jo, jo… ¡Jua, jua, jua!$"
	.string ""
	.string ""
	.string ""

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "El calor me machaca. Va a resultar que\ndebería haberme unido al EQUIPO AQUA…$"
	.string ""

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "Está claro que el EQUIPO MAGMA\nno es para mí…$"
	.string ""

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "¿No crees que este sitio ganaría\npuntos si hubiera mar?$"
	.string ""

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "A veces hay temblores de tierra.\p¿Será cosa del volcán?\n¿O será GROU…?\p¡Huy!\n¡Casi meto la pata!$"
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "¡Luchas con mucha energía!\n¡Eres como un volcán!$"
	.string ""

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "Esta vez has ganado de casualidad,\npero no importa lo más mínimo.\p¡El sueño del EQUIPO MAGMA\npronto se hará realidad!$"
	.string ""
	.string ""
	.string ""

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "Uno del grupo está hecho polvo porque\nha perdido el SIGNO MAGMA.\pUn momento…\n¿Ahora lo tienes tú?$"
	.string ""
	.string ""
	.string ""

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "No puedo creerlo…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "No sé por qué tengo la sensación\nde que nuestro plan no va a salir bien…$"
	.string ""

