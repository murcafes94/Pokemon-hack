SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "Es una cama.\nVoy a descansar un poco.$"
	.string ""

SSTidalRooms_Text_ColtonIntro:
	.string "A veces suelo ir a CIUDAD CALAGUA.\pMe lo paso genial participando\nen CONCURSOS POKéMON.$"
	.string ""
	.string ""

SSTidalRooms_Text_ColtonDefeat:
	.string "¡Qué combate tan bueno!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Yo es que me emociono sólo imaginando\nlos tipos de POKéMON a los que me\lenfrentaré en el siguiente CONCURSO…$"
	.string ""
	.string ""

SSTidalRooms_Text_MicahIntro:
	.string "¿Tus amigos son fuertes?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Sí, de hecho son muy fuertes…$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Los amigos suelen ser personas,\npero los POKéMON también pueden\lser muy buenos amigos…$"
	.string ""

SSTidalRooms_Text_ThomasIntro:
	.string "Joven…\n¿Has llamado a la puerta?$"
	.string ""

SSTidalRooms_Text_ThomasDefeat:
	.string "Se ha de aceptar la derrota\ncon deportividad y caballerosidad.$"
	.string ""

SSTidalRooms_Text_ThomasPostBattle:
	.string "El lema de cualquier CABALLERO que se\nprecie es: “Nunca perder la calma”.$"
	.string ""

SSTidalRooms_Text_JedIntro:
	.string "JOEL: Me da un poco de vergüenza,\npero… ¡vas a ver nuestro dúo de lucha!$"
	.string ""

SSTidalRooms_Text_JedDefeat:
	.string "JOEL: Ay…$"

SSTidalRooms_Text_JedPostBattle:
	.string "JOEL: Es la primera vez que nuestro\ndúo de lucha pierde…\l¡Debes de ser excepcional!$"
	.string ""
	.string ""

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JOEL: ¿Sólo tienes un POKéMON?\n¿Y no es un rollo patatero?$"
	.string ""

SSTidalRooms_Text_LeaIntro:
	.string "LIZ: Me da un poco de cosa, pero…\n¡vas a ver nuestro dúo de lucha!$"
	.string ""

SSTidalRooms_Text_LeaDefeat:
	.string "LIZ: Oh, no…$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LIZ: ¡No me lo puedo creer!\nNuestro dúo de lucha derrotado…\l¡Debes de ser excepcional!$"
	.string ""
	.string ""

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LIZ: Me encanta luchar…,\npero ni siquiera tienes dos POKéMON…$"
	.string ""

SSTidalRooms_Text_GarretIntro:
	.string "Llegas justo a tiempo, o sea.\pMe estaba aburriendo como una ostra,\nde verdad. ¡Haz algo para entretenerme!$"
	.string ""
	.string ""

SSTidalRooms_Text_GarretDefeat:
	.string "Esto no mola para nada, o sea…$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Le voy a decir a papi que me compre\nun yate que he visto, que es ideal.\l¡Sólo para mí y mis POKéMON!$"
	.string ""
	.string ""

SSTidalRooms_Text_NaomiIntro:
	.string "Oh, qué cosita tan mona que eres…\n¿Quieres tomar leche con galletas?\l¿O prefieres luchar un ratito?$"
	.string ""
	.string ""

SSTidalRooms_Text_NaomiDefeat:
	.string "Ya sabía yo que a ti te va la marcha…$"
	.string ""

SSTidalRooms_Text_NaomiPostBattle:
	.string "Relajarse en un crucero de lujo\nno está nada mal…\pAunque dar vueltas a HOENN\nen un ferry también tiene su encanto.$"
	.string ""
	.string ""
	.string ""

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "Oh… Hola… ¡Yo no estoy haciendo nada\nraro! Esto… ¡Toma esto! ¡Gratis!\pEh… En serio… ¡Yo no se lo he birlado\na nadie! ¡Nunca jamás haría algo así!\l¡Puedes usarlo sin problemas!$"
	.string ""
	.string ""
	.string ""
	.string ""

SSTidalRooms_Text_ExplainSnatch:
	.string "ROBO se apodera del movimiento\ndel rival para poder usarlo en su lugar.$"
	.string ""
	.string ""

