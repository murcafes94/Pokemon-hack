VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "He entrenado con toda mi familia,\ntoda enterita. ¡No voy a perder!$"
	.string ""
	.string ""

VictoryRoad_B2F_Text_VitoDefeat:
	.string "¡¿Mejor que mi familia?!\n¡¿Cómo puede ser?!$"
	.string ""

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Logré superar a toda mi familia.\nNunca había perdido…\pVaya palo…\nMe voy a casa a entrenar más.$"
	.string ""
	.string ""
	.string ""

VictoryRoad_B2F_Text_OwenIntro:
	.string "Me han dicho que por aquí había\nuna personita que da mucha guerra.\l¿Eres tú?$"
	.string ""

VictoryRoad_B2F_Text_OwenDefeat:
	.string "¡No hay que fiarse de tu juventud,\nestá claro!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Y, según los rumores, vienes\nde CIUDAD PETALIA, ¿no?$"
	.string ""

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Yo creo que tanta lucha ya debe\nde haberte agotado…$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "¡Pues no!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "Tanto CALLE VICTORIA como la LIGA\nPOKéMON son desafíos largos y duros.\l¡Procura no fatigarte demasiado!$"
	.string ""
	.string ""

VictoryRoad_B2F_Text_JulieIntro:
	.string "No deberías dormirte en los laureles\nsólo porque tienes un montón\lde MEDALLAS de GIMNASIO.\p¡Siempre puedes encontrar a alguien\nque sea mejor que tú!$"
	.string ""
	.string ""
	.string ""

VictoryRoad_B2F_Text_JulieDefeat:
	.string "¡Eres mejor que yo!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Mira todas tus MEDALLAS y acuérdate\nde los ENTRENADORES contra los que\lte has enfrentado.$"
	.string ""

VictoryRoad_B2F_Text_FelixIntro:
	.string "He llegado hasta aquí, pero tanta\ntensión me destroza el estómago…$"
	.string ""

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Ayyyy…\nQué dolor…$"
	.string ""

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "No puedo evitar ponerme tenso al saber\nque me acerco a la LIGA POKéMON.\pCuriosamente, es la única forma\nde controlar los nervios.$"
	.string ""
	.string ""

VictoryRoad_B2F_Text_DianneIntro:
	.string "En esta cueva encontrarás\nlo mejor de lo mejor.\pHasta ahora, ¿qué te parece?$"
	.string ""
	.string ""

VictoryRoad_B2F_Text_DianneDefeat:
	.string "¡Esto no me afecta lo más mínimo!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "¡Tienes agallas y eso me gusta!\n¡Sigue así!$"
	.string ""

