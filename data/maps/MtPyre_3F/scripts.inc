MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "¡El fresco aire de la montaña\nha potenciado mis poderes psíquicos!\pAlguien tan pequeño como tú…\nNo tienes ni medio movimiento…$"
	.string ""
	.string ""
	.string ""

MtPyre_3F_Text_WilliamDefeat:
	.string "Qué vergüenza más grande…$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Quizás todavía pueda potenciar\nmis poderes psíquicos una pizquita…$"
	.string ""

MtPyre_3F_Text_KaylaIntro:
	.string "¡Ja, ja, ja, ja!\pÉste no es lugar para críos…\n¡y menos aún para ti!$"
	.string ""
	.string ""

MtPyre_3F_Text_KaylaDefeat:
	.string "Es evidente que he perdido…$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Está claro que tengo que entrenarme\nmucho más…\pNo debo flaquear si quiero alcanzar\nla cima.\p¡Yo puedo!$"
	.string ""
	.string ""
	.string ""
	.string ""

MtPyre_3F_Text_GabrielleIntro:
	.string "¿Por qué has venido hasta aquí?$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "¡Ha sido impresionante!\nTienes cualidades muy especiales.$"
	.string ""

MtPyre_3F_Text_GabriellePostBattle:
	.string "Los POKéMON que ya no están aquí,\nlos POKéMON que te acompañan,\plos POKéMON que conocerás\nen el futuro…\pTodos merecen nuestro cariño.\nNo lo olvides nunca.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtPyre_3F_Text_GabrielleRegister:
	.string "Me gustaría volver a ver a tus POKéMON\ncuando hayan crecido un poco…\pDéjame ver tu POKéNAV, por favor.$"
	.string ""
	.string ""

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Ah, si eres tú…\p¿Has venido a enseñarme cómo\nhan crecido tus POKéMON?$"
	.string ""
	.string ""

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "¡Es impresionante!\nTienes cualidades muy especiales.$"
	.string ""

MtPyre_3F_Text_GabriellePostRematch:
	.string "Los POKéMON que ya no están aquí,\nlos POKéMON que te acompañan,\plos POKéMON que conocerás\nen el futuro…\pTodos merecen nuestro cariño.\nVeo que no lo has olvidado.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

