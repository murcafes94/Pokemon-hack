AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "FITO: ¡Estábamos buscando tesoros\ny nos encontramos con un combate!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "FITO: A pesar de luchar a dúo,\nhemos perdido…$"
	.string ""

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "FITO: No encontramos ni una baratija…\n¿Se habrá llevado ya alguien el tesoro?$"
	.string ""

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "FITO: Pero si no tienes dos POKéMON…\nAsí no ganas ni en sueños…$"
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "LUCI: ¡Anda! Buscábamos tesoros\ny nos encontramos con un combate…$"
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "LUCI: ¡Guau, qué fuerte eres!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "LUCI: Me pregunto dónde habrán\nescondido el tesoro…\p¡Si lo encuentro, ya sé en qué\nme lo voy a gastar!$"
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "LUCI: ¿No tienes dos POKéMON?\n¡Pues lo dejamos para otro día!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "LUCI: ¡Ay, me pones de los nervios!\n¡Por eso mismo te voy a registrar!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "FITO: Todavía estamos buscando\ntesoros por aquí.\pEntretanto, nuestros POKéMON\nhan mejorado. ¿Quieres verlo?$"
	.string ""
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "FITO: Nada, sigues siendo tan fuerte\ncomo siempre.$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "FITO: No encontramos ningún tesoro,\nperdemos en los combates POKéMON…\pYo me voy a casa… Bueno, quiero irme,\npero no creo que ella me deje…$"
	.string ""
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "FITO: Pero si no tienes dos POKéMON…\nAsí no ganas ni en sueños…$"
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "LUCI: ¡Hola de nuevo!\pYa se ve que tú tampoco has dejado\nde buscar el tesoro.\p¿Qué te parece si luchamos\ny quien pierda deja de buscar?$"
	.string ""
	.string ""
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "LUCI: Oh, perdimos otra vez…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "LUCI: Entrenaremos mejor a nuestros\nPOKéMON.\p¡Pero no nos iremos hasta\nencontrar algún tesoro!$"
	.string ""
	.string ""

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "LUCI: ¿No tienes dos POKéMON?\n¡Pues lo dejamos para otro día!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "No se me da bien nadar,\n¡pero luchar es otra cosa!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Ay, ay, ay…\nEsto no ha salido bien…$"
	.string ""

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Andar descalza por este barco\nno es muy higiénico.$"
	.string ""

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Fuerza y compasión…\n¡Todo ENTRENADOR debe poseer ambas!$"
	.string ""

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Hay algo en ti que deslumbra.$"
	.string ""

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "Por cierto, he visto algo que\nbrillaba en uno de los camarotes.$"
	.string ""
