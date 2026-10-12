MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "¿Qué he hecho yo para merecer\neste puesto de guardia?\p¡Tengo las orejas ardiendo!$"
	.string ""
	.string ""

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "El calor me da flojera…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "¿Te parece raro que llevemos capuchas\nen un volcán lleno de lava como éste?$"
	.string ""

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "Nos unimos al EQUIPO MAGMA para ayudar\na nuestro líder a cumplir su visión.\pMe da igual si eres del EQUIPO AQUA\no sólo estás de paso por aquí.\p¡Nadie interfiere en nuestros planes\ny se sale con la suya!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "¡Oh, no!\n¡Esto no es de recibo!$"
	.string ""

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "Escúchame bien.\n¡El EQUIPO MAGMA tiene razón!\pNo hagas ni caso al EQUIPO AQUA.\n¡Mienten más que hablan!$"
	.string ""
	.string ""
	.string ""

