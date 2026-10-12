Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Mi hermano mayor es el FOSILMANÍACO.\nLe enseñas un fósil y se vuelve loco…\pTambién le pirra cavar agujeros…\nÉl mismo cavó esta cueva que ves.\pTe voy a dar esto para que puedas\nEXCAVAR agujeros como mi hermano.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Si haces que un POKéMON use EXCAVAR\nen una cueva, vuelves a la entrada.$"
	.string ""

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "La vitrina de exhibición contiene\nrocas con formas extrañas.$"
	.string ""

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "“La composición de los estratos”…\n“Cómo erosiona la lluvia”…\l“Piedras, rocas y suelos”…\pEstá repleto de libros…$"
	.string ""
	.string ""
	.string ""

