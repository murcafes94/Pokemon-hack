ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "¡Hey, hola!\nQué sonrisa tan bonita tienes…\p¿Sabes? Mi hobby es coleccionar los\nperfiles de los ENTRENADORES POKéMON.$"
	.string ""
	.string ""
	.string ""

ProfileMan_Text_MayISeeYourProfile:
	.string "¿Qué te parece?\n¿Puedo ver tu perfil?$"
	.string ""

ProfileMan_Text_EasyChatExplanation:
	.string "Para crear tu perfil, debes unir\ncuatro palabras o locuciones.\pPara que te hagas una idea, te voy\na mostrar un ejemplo de perfil.\pPuedes cambiar los cuatro elementos\npor otras palabras que se ajusten\lmejor a tu personalidad.\pHay un montón de locuciones que\npuedes usar.\pEstán agrupadas por categorías,\npara que sea más fácil encontrarlas.\pPrimero elige una categoría para\nver todas las opciones disponibles.\pDespués elige la palabra o locución\nque te convenga.\pRepite esto hasta tener cuatro y\nhabrás creado tu propio perfil.$"
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

ProfileMan_Text_LetsSeeItThen:
	.string "¡Genial! ¡Gracias!\n¡Estoy deseando verlo!$"
	.string ""

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "¿No? ¿En serio?\pPensaba que alguien como tú tendría\nun perfil estupendo…$"
	.string ""
	.string ""

ProfileMan_Text_NotIntoItRightNow:
	.string "¿Y eso? ¿No te apetece?\p¡Bueno, pues hazlo cuando te\nvenga mejor!$"
	.string ""

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "¡Hey, hola!\nQué sonrisa tan bonita tienes…$"
	.string ""

ProfileMan_Text_MayISeeYourNewProfile:
	.string "¿Puedo ver tu nuevo perfil?$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "¡Sí! ¡Gracias!\pEspero que sea aún mejor que el perfil\nque me enseñaste la otra vez.$"
	.string ""
	.string ""

ProfileMan_Text_LikeProfileWayItIs:
	.string "Ah, te gusta tu perfil tal como es…\pNo te culpo, es un gran perfil\ntal como está ahora.$"
	.string ""
	.string ""

ProfileMan_Text_FantasticProfile:
	.string "¡Fantástico!\p¡Tu perfil es maravilloso!\nDice todo sobre ti.\pVaya, cualquiera que lo oiga caerá\nrendido a tus pies.\p¡Gracias!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
ProfileMan_Text_YouKnowSecretSaying:
	.string "Oh?\nYou know the secret saying!\pThat means you’re now a fellow member\nof the MYSTERY EVENT CLUB!$"
	.string ""
	.string ""
	.string ""
