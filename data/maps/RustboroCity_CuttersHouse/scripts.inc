RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "Esa expresión decidida…\nEsa manera de caminar…\lEsos POKéMON tan bien entrenados…\pSin duda tú sabes entrenar POKéMON.\pNo, espera, no digas nada.\nMe basta con mirarte…\pEstoy seguro de que puedes\ndar buen uso a esta MO.\pNada de falsa modestia…\nAnda, toma.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "Esta MO es CORTE.\pUn movimiento de MO es aquel que un\nPOKéMON puede usar fuera del combate.\pCualquier POKéMON que haya aprendido\nCORTE puede derribar árboles si su\lENTRENADOR tiene la MEDALLA PIEDRA.\pY, al contrario de lo que ocurre\ncon las MT, las MO se pueden usar\lmás de una vez.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "Mi padre colaboró en las obras de\nexpansión de CIUDAD FÉRRICA.\pHizo que sus POKéMON usaran CORTE\npara abrir claros donde construir.$"
	.string ""
	.string ""
	.string ""

