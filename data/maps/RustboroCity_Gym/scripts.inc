RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "Eh, ¿qué tal vamos?\p¡Escucha algo que te va a interesar!\n¿Vas camino del CAMPEONATO?\pYo no soy ENTRENADOR, pero te puedo\ndar un par de buenos consejos.\p¡Así me gusta! ¡Te voy a decir cómo\nganar el CAMPEONATO POKéMON!\pUn ENTRENADOR tiene que reunir\nMEDALLAS de GIMNASIO, ¿no?\p¡Pero ganar a los LÍDERES no es\npan comido!\p¡Y ahí entro yo!\nPuedo asesorarte como nadie.\pPETRA, la LÍDER del GIMNASIO,\nusa POKéMON de tipo ROCA.\pEl tipo ROCA es muy resistente, pero no\ntiene ninguna oportunidad si se usan\lmovimientos de tipo AGUA o PLANTA.\pSi derrotas a la LÍDER, ven a verme.\pVenga, ¡valor y al toro!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "¡Guau, vaya pedazo de victoria!\n¡Seguro que ha sido por todo lo que\lte he animado desde aquí!\p¡Genial!\nConsulta tu FICHA de ENTRENADOR.\pLa MEDALLA PIEDRA que has conseguido\ndebería figurar ahí.\pEn otras palabras…\p¡Has dado el primer paso que te llevará\na la cima!\p¡Tiene que ser superemocionante!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_JoshIntro:
	.string "A los ENTRENADORES no debes tomarnos\na la ligera… ¡Ahora verás por qué!$"
	.string ""

RustboroCity_Gym_Text_JoshDefeat:
	.string "Me has dejado a cuadros…$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "¡Todavía no has visto ni una pizca\ndel terrible poder del tipo ROCA!$"
	.string ""

RustboroCity_Gym_Text_TommyIntro:
	.string "¡Si no puedes vencerme a mí, ya puedes\nolvidarte de derrotar a PETRA!$"
	.string ""

RustboroCity_Gym_Text_TommyDefeat:
	.string "Vaya, se diría que tienes potencial…$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "Pero PETRA es mucho más fuerte\nque yo de aquí a Lima.\p¡Mejor no te confíes!$"
	.string ""
	.string ""

RustboroCity_Gym_Text_MarcIntro:
	.string "Ya sé que estamos en medio de una\nciudad, pero no te servirá de nada.\pMis POKéMON ROCA no se andan\ncon chiquitas. ¡Échate a temblar!$"
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_MarcDefeat:
	.string "¡Por todos los peñascos!\n¡Tú sí que no te andas con chiquitas!$"
	.string ""

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Nuestra LÍDER te dará tu merecido.\pA pesar de su juventud, escogió el\ntipo ROCA y eso demuestra carácter.$"
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Hola, soy PETRA, la LÍDER del\nGIMNASIO POKéMON de CIUDAD FÉRRICA.\pMe convertí en LÍDER para poder\naplicar lo que había aprendido en la\lESCUELA de ENTRENADORES POKéMON.\p¿Me harías el favor de enseñarme tus\nPOKéMON y tus técnicas de combate?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "Pues…\nhe perdido…\pParece que aún no he aprendido\nbastante…\pQué se le va a hacer.\pSegún las reglas de la LIGA POKéMON,\nlos ENTRENADORES deben recibir\lesto si derrotan a un LÍDER.\pTe entrego la MEDALLA PIEDRA oficial\nde la LIGA POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{PLAYER} recibió la MEDALLA PIEDRA\nde PETRA.$"
	.string ""

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "La MEDALLA PIEDRA potencia el poder\nde ATAQUE de tus POKéMON.\pTambién les permite usar la MO CORTE\nfuera del combate.\pAdemás, quiero darte esto.$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "La MT39 contiene TUMBA ROCAS.\pNo sólo inflige daño al lanzar rocas\na tu rival, sino que también reduce\lla VELOCIDAD de éste.\pSi usas una MT, puedes enseñar\nese movimiento a un POKéMON.\p¡Pero recuerda que sólo la podrás\nusar una vez y ya está!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Ya que eres tan fuerte, deberías\ndesafiar a otros LÍDERES.\pPero antes lucha contra muchos\nENTRENADORES para ganar experiencia.$"
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON de CIUDAD FÉRRICA$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON de CIUDAD FÉRRICA\pNUEVOS ENTRENADORES CERTIFICADOS:\n{PLAYER}$"
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "¡Bip, bip!\pPETRA: ¡Hola, {PLAYER}!\nAquí PETRA, de CIUDAD FÉRRICA.\pMe ha dicho MARCIAL que estás\nescalando puestos en la jerarquía\lde ENTRENADORES a ojos vistas.\pPero, la verdad, no quiero pensar\nque no puedo vencerte…\pEn el GIMNASIO nos entrenamos\na fondo para cuando vuelvas.\p¡Estamos deseando desafiarte!\n¡No nos hagas esperar mucho!\p¡Clic!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "Acabas de registrar a PETRA,\nla LÍDER de GIMNASIO, en el POKéNAV.$"
	.string ""

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "PETRA: Me alegra volver a verte.\nComo sabes, soy PETRA, la LÍDER\lde este GIMNASIO.\pSeguro que hemos adquirido mucha\nexperiencia desde la última vez.\pAsí que habrá que comprobar todo lo\nque hemos mejorado… ¡A luchar!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grrr…\nHe perdido otra vez…$"
	.string ""

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "PETRA: Todavía tengo mucho que\naprender de los combates POKéMON.\p¡Saber eso me da aún más ánimos\npara seguir entrenándome y mejorar!$"
	.string ""
	.string ""
	.string ""

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "PETRA: Me alegra volver a verte.\nComo sabes, soy PETRA, la LÍDER\lde este GIMNASIO.\pSeguro que hemos adquirido mucha\nexperiencia desde la última vez.\pAsí que habrá que comprobar todo lo\nque hemos mejorado…\pOh, no…\n¿Sólo llevas un POKéMON contigo?\pPues necesitas al menos otro más.\nSi no, no podremos luchar.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
