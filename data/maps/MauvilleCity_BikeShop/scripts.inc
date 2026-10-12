MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Bueno, bueno, bueno, ¿a quién tenemos\naquí? ¡Una personita con muchos bríos!\p¿Mi nombre? Me llaman ANACLETO y soy\nel propietario de esta tienda de bicis.$"
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "ANACLETO: Esas DEPORTIVAS\nestán que dan asquito…\p¿Vienes de muy lejos?$"
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "ANACLETO: ¿De veras?\pEntonces supongo que no necesitas\nninguna BICI…$"
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "ANACLETO: Ajá, ajá, entiendo…\nSí, sí, ya veo…\pAsí que has venido nada menos\nque desde VILLA RAÍZ…\p¡Impresionante!\n¡Está en el quinto pino!\pSi tuvieras una de mis BICIS, podrías\nir a cualquier sitio en un periquete\lmientras el viento acaricia tu rostro.\pYa sé: ¡te voy a dar una BICI!\pPero espera un segundo…\pNo te he dicho que hay dos tipos\nde BICIS…\pLa BICI CARRERA y la BICI ACROBÁTICA.\pLa BICI CARRERA es para aquellos a los\nque les gusta poner cara de velocidad.\pLa BICI ACROBÁTICA es para aquellos\na los que les gusta hacer virguerías.\pSoy la mar de majo, así que puedes\nelegir la que más te mole.\p¿Cuál te llevas?$"
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
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} eligió la BICI CARRERA.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} eligió la BICI ACROBÁTICA.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "ANACLETO: Si de repente te apetece\ncambiar de BICI, ven a verme.$"
	.string ""

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "ANACLETO: ¡Hola!\n¿Vienes a cambiar de BICI?$"
	.string ""

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "ANACLETO: ¡No hay problema!\nTe la cambio en un momentín.$"
	.string ""

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER} cambió la BICI CARRERA \npor la BICI ACROBÁTICA.$"
	.string ""

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER} cambió la BICI ACROBÁTICA\npor la BICI CARRERA.$"
	.string ""

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "ANACLETO: Bien, bien.\nMe alegro de que te guste.$"
	.string ""

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "¿Eh? ¿Qué le ha pasado a la BICI\nque te he dado?\pAh, ya, la has guardado en tu PC.\pBueno, pues sácala de ahí\ny te la cambiaré encantado.\p¡Espero que cuando viajes el viento\nsiempre te venga de espalda!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Trabajar aquí me está enseñando\nun montón sobre BICIS.\pSi quieres saber todos los secretos\nde tu BICI, echa un vistazo\la los manuales que hay ahí detrás.$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Es un manual sobre la BICI CARRERA.\p¿Qué capítulo quieres leer?$"
	.string ""

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "La BICI se mueve en la dirección\nque eliges en el + Panel de Control.\pIrá cogiendo velocidad poco a poco.\pPara parar, suelta el + Panel de\nControl. La BICI perderá velocidad\lgradualmente hasta detenerse.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "La BICI CARRERA es muy rápida,\npero tarda un poco en detenerse.\pDoblar las esquinas puede resultar\ncomplicado.\pSuelta el + Panel de Control justo\nantes de llegar a la esquina para\lreducir la velocidad.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "Por toda la región de HOENN hay\npequeñas pendientes arenosas.\pLa consistencia de la arena dificulta\nla ascensión de la pendiente.\pSin embargo, si tienes una BICI\nCARRERA, puedes subir sin problemas.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Es un manual sobre la BICI ACROBÁTICA.\p¿Qué capítulo quieres leer?$"
	.string ""

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Pulsa el Botón B mientras estás en la\nBICI para elevar la rueda delantera.\pUsa el + Panel de Control para dar\nvueltas con la rueda levantada.\pEsta técnica se llama “el caballito”.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Mantén pulsado el Botón B mientras\nla BICI está parada y empezará a dar\lsaltos en el sitio.\pEsta técnica se llama “saltitos”.\pSi a continuación usas el + Panel de\nControl, puedes moverte dando saltos.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""

MauvilleCity_BikeShop_Text_Jumps:
	.string "Pulsa el Botón B y el + Panel de Control\nal mismo tiempo para saltar.\pPulsa el + Panel de Control hacia los\nlados para dar un salto lateral.\pPúlsalo hacia arriba o abajo para que\nla BICI cambie de dirección durante\lel salto.\p¿Quieres leer otro capítulo?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

