RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Buenos días. Estás en DEVON S.A.\pSomos los orgullosos fabricantes\nde miles de objetos y medicinas\lque hacen la vida más fácil.$"
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "Uno de nuestros científicos se ha\ndejado robar un paquete de lo más\limportante.$"
	.string ""

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "Eh, esas DEPORTIVAS las hemos\nfabricado nosotros.\p¡Siempre es un placer ver a uno\nde nuestros clientes!$"
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "Ese paquete que han robado…\pes muy importante, cierto, pero no es\nalgo que pueda usar cualquiera.\pEn mi opinión, ese ladrón no era\nmuy listo que digamos…$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "Parece que alguien ha recuperado\nlas PIEZAS DEVON que robaron.$"
	.string ""

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "Lo siento, sólo el personal autorizado\npuede entrar aquí.$"
	.string ""

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "¿Cómo hemos podido ser tan tontos…?\n¡¿Cómo nos hemos dejado robar?!$"
	.string ""

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "¡Anda, hola!\n¡Tenerte aquí es siempre un placer!$"
	.string ""

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "En la urna de cristal se exponen\nmuestras de rocas y metales.\pHay un cartel con algo escrito…\p“DEVON S.A. se dedicaba en sus\ninicios a extraer rocas de canteras.”\p“También producía hierro a partir de\nlas limaduras que había en la arena.”\p“A pesar de tan humildes orígenes,\nDEVON logró crecer como empresa.”\p“DEVON fabrica en la actualidad una\namplia gama de productos industriales.”$"
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

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "En la urna de cristal se exponen\nprototipos y productos de prueba.\pHay un cartel con algo escrito…\p“Además de productos industriales,\nDEVON comercializa artículos varios\le incluso productos farmacéuticos.”\p“Desde hace poco, DEVON también vende\nartículos para ENTRENADORES POKéMON,\lcomo POKé BALLS y POKéNAVEGADORES.”$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

