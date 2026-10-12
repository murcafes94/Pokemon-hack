VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "Pensar que estoy cada vez más cerca\nde la LIGA POKéMON…\pMe entra miedo escénico…$"
	.string ""
	.string ""

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "No me he dado ni cuenta…$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "La LIGA POKéMON vuelve a estar\nlejos, lejos… Qué depresión…$"
	.string ""

VictoryRoad_B1F_Text_ShannonIntro:
	.string "Para ganar en la LIGA POKéMON, debes\ncontar con la confianza de tus POKéMON.$"
	.string ""
	.string ""

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "Se nota que vuestra relación se basa\nen la mutua confianza.$"
	.string ""

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Cuanto más tiempo pasan juntos,\nmás crece la confianza entre POKéMON\ly ENTRENADORES.$"
	.string ""

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Éste no es el objetivo final, sólo\nun paso más hacia la LIGA POKéMON.$"
	.string ""

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "¡Tú avanzas rápido!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "¡Seguro que lo haces muy bien!\n¡Tus POKéMON parecen emocionados!$"
	.string ""

VictoryRoad_B1F_Text_MitchellIntro:
	.string "¡Mis POKéMON provocan una\nadmiración galáctica!$"
	.string ""

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "Nunca había conocido a nadie igual.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "De ti y de tus POKéMON emana\nun poder cósmico sin igual,\lincluso cuando no lucháis.$"
	.string ""
	.string ""

VictoryRoad_B1F_Text_HalleIntro:
	.string "¡Eh, tranqui, no te mosquees!\n¡Vamos a luchar con calma!$"
	.string ""

VictoryRoad_B1F_Text_HalleDefeat:
	.string "¡Guau!\n¡Ha sido magnífico!$"
	.string ""

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Estamos en la CALLE VICTORIA.\pPero en el fondo no es tan distinta\nde cualquier otra ruta.\p¡Intenta disfrutar de todo\nlo que te queda por ver!$"
	.string ""
	.string ""
	.string ""
	.string ""

