BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "¡Ésta es la TORRE BATALLA!\n¡Nada como una buena racha\lpara demostrar lo que vales!$"
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "¡Éste es el PALACIO BATALLA!\n¡No pierdas de vista a tus POKéMON!$"
	.string ""

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "¡Éste es el DOJO BATALLA!\n¡Hazte con un buen equipo!$"
	.string ""

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "¡Ésta es la PIRÁMIDE BATALLA!\n¡Te espera la EXPEDICIÓN de COMBATES!$"
	.string ""

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "¡HALL de las CLASIFICACIONES!\n¡Apúntate los mejores récords!$"
	.string ""

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "CENTRO del SERVICIO de CANJE\n¡Canjea tus PUNTOS de BATALLA!$"
	.string ""

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "¡Guau!\n¡Es gigantesca!\pSólo con ver la TORRE BATALLA,\nuno sabe que es un lugar especial.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "¡Mi gran sueño es conquistar el FRENTE\nde BATALLA y la LIGA POKéMON!\pY, si consigo hacerlo realidad…,\ple preguntaré a MIMI, mi vecina,\nsi quiere que seamos amigos.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "¡La PIRÁMIDE BATALLA es muy dura!\n¡Nunca podré llegar arriba del todo!\pAunque siempre puedo tratar de llegar\nescalando por fuera…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "Me crezco en las tinieblas…\nSí… ¿Hay algo que sea digno de mí?\lNada, salvo la PIRÁMIDE BATALLA…\p¿Acaso hay algo mejor que perderse\nentre las tinieblas y la desesperación?$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "No he dormido nada esta semana,\n¡pero ya tengo el equipo invencible!\p¡Voy a hacer historia\nen el DOJO BATALLA!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "¿Te ha traído a ti también el tal TRETO?\nQué tipo más raro, ¿no te parece?\pEs como si supiese de verdad elegir\na los mejores ENTRENADORES, pero…\pNunca lo he visto combatir por sí mismo.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "¡ZIGG!\n¡Confío en ti, chiquitín!\p¡Y mi pequeño ZIGG tendrá la gominola\nque más le guste si gana!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON parece perdido…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "La gente dice que soy un metomentodo,\npero es que no puedo evitarlo…\p¡Tienes la gorra torcida!\n¡Mira qué de basura hay en el suelo!\l¡Huy, es hora de cenar!\pNo sé si podré soportar quedarme\nsólo mirando el PALACIO BATALLA…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "Aunque no lo parezca ahora, en mi época\nllegué a ganar a un LÍDER de GIMNASIO.\pQuién sabe, si me lo propusiera, quizás\npodría volver a saborear la gloria.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "Soy el más rápido con mi BICI.\n¡Igualito que cuando combato!\p¡He ganado algunos combates\nen menos que canta un gallo!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "Soy mucho mejor que mi padre\nentrenando POKéMON.$"
	.string ""

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "¡Venga, hija mía!\n¡Vete y gana unos combates por papá!\pEres igualita a tu madre,\n¡contigo no va a poder nadie!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "No ha sido fácil llegar hasta aquí,\npero había oído que había una belleza\ldespampanante en el DOJO BATALLA.\p¿Y sabes lo que me he encontrado\nen realidad?\p¡Una banda de “artistas marciales”\nsudados, malolientes y salvajes!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "A veces veo entrar ahí a un anciano\nque tiene pinta de ser muy importante.\p¡Menudos POKéMON que lleva!…\pPero, a pesar de todo, parece\nser un tipo agradable.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "¿La conoces? ¿Conoces la leyenda\nde la PIRÁMIDE BATALLA?\pCuando un ENTRENADOR armado de valor\nllegue a la cima dorada, un hombre entre\llos hombres saldrá a su encuentro.\p¿No conocías esta leyenda?…\p¡Pues claro que no!\n¡Me la acabo de inventar!\p¿Y qué significa?, me dirás…\pBueno, eso, ¡no puedo decírtelo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "¡Madre mía!\n¡Y yo que no había perdido nunca antes!\p¡Pero esta vez me han tratado\nsin contemplaciones!\p¡Y encima van y me dicen que no\nvalgo para nada! ¡Madre mía!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "Este pobre se topó con un ENTRENADOR\nque lo hizo trizas en la TORRE BATALLA.\pMira cómo lo han dejado…\pNo lo olvides si alguna vez decides\nentrar en la TORRE BATALLA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "¡Sí! ¡Por fin he conseguido suficientes\nPUNTOS de BATALLA!\p¡Creo que voy a canjearlos por\nun MUÑECO de peluche gigante!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "¡Guay, sí!\n¡El HALL de las CLASIFICACIONES!\pYo quiero pasar a la historia como\nun gran campeón y que graben\laquí mi nombre con letras de oro.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "Contigo a mi lado,\nla victoria está más que asegurada.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "¡Ay, pichoncito, eres maravilloso!\p¡Estoy deseando empezar a luchar!\p¡Venga, vamos corriendo a una de esas\nsalas de COMBATES MÚLTIPLES!\pCuando entremos juntos en el SALÓN\nBATALLA, dejaremos a todos atrás\lcon el poder de nuestro amor.\p¡Irán cayendo uno a uno\ncomo piezas de dominó!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "El FRENTE de BATALLA no es sólo\npara ENTRENADORES fuertes.\pParece que aquí hay también gente\ncon habilidades especiales.\pEse TRETO…\pPuede que haya construido este lugar\npensando en hacer algo aún más grande…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Por favor, ¿serías tan amable?\n¿Tienes buena vista?\pPor ahí abajo hay un árbol viejo\ny, aunque tengo la vista cansada,\lpara mí que se está meneando…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Por favor, ¿serías tan amable?\n¿Tienes buena memoria?\pEs que tengo la sensación de que ahí\nabajo había antes un árbol viejo…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "¡Yo! ¡Yo! ¡Yo!…\n¡Lo he visto!\p¡Era una especie de POKéMON pegajoso\ny con una cola muy larga!\p¡Estaba escondido debajo de esa piedra,\ny no dejaba de mirarme! ¡Ay, qué repelús!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
