Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Nunca antes había visto a nadie que\nusara los POKéMON con tanto arte.\pNo te ofendas, pero mi hijo es\nmás fuerte que tú.\pHa participado incluso en el desafío\nde la LIGA POKéMON. Que lo sepas…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Usamos VESTIDURA para que nuestros\nPOKéMON mejoren aún más durante\lel entrenamiento.\pYa que has vencido a toda la familia, no\ncreo que la necesites, pero me gustaría\ldarte nuestra VESTIDURA igualmente.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "Cuando se trata de combates POKéMON,\ntendemos a tomárnoslo muy en serio…$"
	.string ""

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mamá es más fuerte que papá.\pYo soy más fuerte que mamá.\p¡Y la abuelita es más fuerte que yo!\pPero mi hermano mayor es aún\nmás fuerte que la abuelita.$"
	.string ""
	.string ""
	.string ""
	.string ""

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "No cabe duda de que eres fuerte.\pPero, si tuvieras que luchar contra mi\nnieto, llorarías pidiendo clemencia.\pEs mucho más fuerte que cualquier\notro ENTRENADOR que conozcamos.\pAhora debe de estar enfrentándose al\nCAMPEÓN de la LIGA POKéMON…\pConociendo a mi nieto…, ¡puede que\nya sea el nuevo CAMPEÓN y todo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Mi nieto debe de estar enfrentándose\nal CAMPEÓN de la LIGA POKéMON…\pConociendo a mi nieto…, ¡puede que\nya sea el nuevo CAMPEÓN y todo!$"
	.string ""
	.string ""
	.string ""

