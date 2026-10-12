AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Los barcos de este tipo son poco\ncomunes, así que estoy de inspección.\pMmmm…\nParece que hay muchos camarotes…$"
	.string ""
	.string ""
	.string ""

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "¿Qué ha podido impulsarte a venir\nhasta aquí? ¡Será la curiosidad!$"
	.string ""

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "La fuerza es otra de tus cualidades…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "¿Ves al hombre de ahí al lado?\pDice que está de turismo,\npero yo no me lo creo.$"
	.string ""
	.string ""

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "¡Tú sí que sabes entrenar POKéMON!\n¡Será un honor registrarte!$"
	.string ""

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "¿Qué ha podido impulsarte a venir\nhasta aquí? ¡Será la curiosidad!$"
	.string ""

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "No es normal ser tan fuerte.$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "¡Ese picaruelo no es trigo limpio!\n¡Actúa de forma muy sospechosa!$"
	.string ""

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "¡Aaaah!\n¡Me han encontrado! Pero ¿eh?$"
	.string ""

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "¡Tú no eres mi madre!$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Mi madre se ha enfadado, así que me\nhe escondido. No digas que estoy aquí.$"
	.string ""

