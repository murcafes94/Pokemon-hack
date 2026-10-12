FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COZMO: Oh…\nNo debería haberme dejado\lamedrentar por el EQUIPO MAGMA y\lrevelar dónde hay METEORITOS…\pEse METEORITO de la CASCADA METEORO…\nYa nunca lo recuperaré…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "¡Eh!\n¿Cómo?\pEse objeto…\p¿Es posible…?\p¿Es el METEORITO que el EQUIPO MAGMA\nrobó en la CASCADA METEORO?\pPor favor, ¿puedo…?\pNo quiero quitártelo por la cara…\n¿Qué te parece cambiarlo por esta MT?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COZMO: Esta MT es un símbolo\nde la enorme gratitud que siento.\l¡No dejes de usarla!$"
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COZMO: ¡No puedo creerlo!\n¡Es genial, maravilloso y estupendo!\p¡Será de una enorme ayuda\nen mi investigación!$"
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COZMO: Anda ya… ¿No?…\nMe siento profundamente abatido…$"
	.string ""

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COZMO: Por favor, ¿me darías\nese METEORITO?\pNo quiero quitártelo por la cara…\n¿Qué te parece cambiarlo por esta MT?$"
	.string ""
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "El PROF. COZMO fue a la CASCADA\nMETEORO, en la RUTA 114, con algunos\lmiembros del EQUIPO MAGMA.$"
	.string ""
	.string ""

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Pobre PROF. COZMO…\nEstá tan depre… Me da una pena…$"
	.string ""

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Mira al PROF. COZMO…\n¡Está tan feliz! ¡Da gusto verle!$"
	.string ""

