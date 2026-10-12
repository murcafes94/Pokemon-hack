MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "Aquí es donde los amantes de los\nDRAGONES entrenamos.\pA veces viene el CAMPEÓN de visita.\n¿Ves como somos algo especial?$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "¡Uf!\n¡No esperaba que fueras tan fuerte!$"
	.string ""

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "Te aguarda un camino largo y difícil.\p¿Cuándo lograré llegar triunfante\nhasta el final con mis POKéMON?$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "Quiero saber más sobre tus habilidades.\nDéjame registrarte en mi POKéNAV.$"
	.string ""

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "Desde que nos conocimos, hemos\nentrenado duro para ser los mejores.\p¡Veamos cuánto hemos mejorado!$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "¡Uf!\n¡No esperaba que fueras tan fuerte!$"
	.string ""

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "Se ve que has estado entrenando\nmucho con tus POKéMON.\p¡Pero yo también puedo mejorar!$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "JULI: Siempre hemos luchado a dúo.\nJuntos somos más fuertes.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "JULI: Oh…\nHemos perdido, querida.$"
	.string ""

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "JULI: Llevamos cincuenta años casados.\pY ahora que lo pienso… Todavía\nno he vencido a mi mujer en combate.$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "JULI: ¡Vaya, vaya! ¡Qué joven eres!\p¿Quieres desafiarnos? Pues entonces\ntendrás que volver con más POKéMON.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "JULI: Dime, si surgiera la oportunidad,\n¿volverías a enfrentarte a nosotros?$"
	.string ""

MeteorFalls_1F_2R_Text_JayIntro:
	.string "NELA: Llevamos cincuenta años casados.\pEl vínculo que nos une como pareja\nes fuerte como un roble.$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "NELA: Oh…\nHemos perdido, querido.$"
	.string ""

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "NELA: Cincuenta años de matrimonio…\pCada vez que discutíamos,\nlo resolvíamos con un combate POKéMON.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "NELA: ¡Vaya, vaya! ¡Qué joven eres!\p¿Quieres desafiarnos? Pues entonces\ntendrás que volver con más POKéMON.$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "JULI: Siempre hemos luchado a dúo.\nJuntos somos más fuertes.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "JULI: Oh…\nHemos perdido, querida.$"
	.string ""

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "JULI: Llevamos cincuenta años casados.\pY ahora que lo pienso… Mi mujer y yo\nhemos combatido día sí y día no.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "JULI: ¡Vaya, vaya! ¡Qué joven eres!\p¿Quieres desafiarnos? Pues entonces\ntendrás que volver con más POKéMON.$"
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "NELA: Llevamos cincuenta años casados.\pNos hemos apoyado el uno al otro\nen las duras y en las maduras.$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "NELA: Oh…\nHemos perdido, querido.$"
	.string ""

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "NELA: Cincuenta años de matrimonio…\nHan pasado tantas cosas…\pEspero que siempre seamos\ntan felices como hasta ahora.$"
	.string ""
	.string ""
	.string ""

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "NELA: ¡Vaya, vaya! ¡Qué joven eres!\p¿Quieres desafiarnos? Pues entonces\ntendrás que volver con más POKéMON.$"
	.string ""
	.string ""
	.string ""

