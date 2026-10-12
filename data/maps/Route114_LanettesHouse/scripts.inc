Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "AREDIA: ¡Anda! ¡{PLAYER}{KUN}!\pPerdona el desorden, es que estoy\nen medio de una investigación vital\ly no tengo tiempo para nada…\pQué vergüenza… No le digas a nadie\nlo desastre que soy. Mira, te daré\lesto en agradecimiento…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "¿Quieres algún consejo sobre el Sistema\nde Almacenamiento de POKéMON?\pAhí va: organiza las CAJAS para que\npuedas encontrar rápido cada POKéMON.$"
	.string ""
	.string ""
	.string ""

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Son notas de investigación de AREDIA.\nContienen información sobre las CAJAS.\p“Diseñar las CAJAS para que\nalberguen 30 POKéMON cada una.\pTodo ENTRENADOR debería poder\nalmacenar 420 POKéMON en el PC.”\p¿Sigo leyendo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "“Añadir un sistema de marcado que\nfacilite la organización de los POKéMON.\pHacer posible el cambio de nombres y\ndiseños de papel pintado de las CAJAS\lpara agradar a los POKéMON guardados.”\p¿Sigo leyendo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "“Cuando se guarde un POKéMON,\nirá a la última CAJA inspeccionada.\pSi ésta está llena, el POKéMON se\nalmacenará en la siguiente CAJA.\pEs decir, al examinar una CAJA, ésta\npasará a ser la CAJA predeterminada\la la que se envíen los POKéMON.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} cerró el cuaderno.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Alguien ha enviado un correo\nelectrónico al PC…\p“¡Hola!\pTu Sistema de Almacenamiento\nparece mucho mejor que el mío.\pTiene un montón de características que\nlo hacen más útil y divertido de usar.\pMe enorgullece ser parte del equipo\nque ha desarrollado este sistema.\pEspero que tu trabajo mejore aún más\nlos Sistemas de Almacenamiento.\pUn abrazo,\pBILL”$"
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

