MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "MÁXIMO: Anda, {PLAYER}{KUN}.\nMe sorprende que me hayas encontrado.\pDime… ¿Tú crees que las rocas\nme encantan?\pPues que sepas que no.\pYa nos enfrentamos en el CENTRO\nESPACIAL de CIUDAD ALGARIA.\pDeberías saber de sobra que soy muy,\npero que muy bueno.\p¡Tú lo has querido, {PLAYER}{KUN},\nsi buscas pelea, espérate lo peor!$"
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

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Vaya…\nPues sí que has mejorado…$"
	.string ""

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "MÁXIMO: Ahora que lo pienso, lo supe\ndesde que nos encontramos en la\lCUEVA GRANITO de PUEBLO AZULIZA.\pYa sabía yo que acabarías por hacerte\ncon el CAMPEONATO.\pMis predicciones nunca fallan.\p¿Y ahora qué te depara el futuro?\pMmmm…\nMmmm…\pJe, je, je, ni yo lo sé.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

