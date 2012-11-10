' Das DummyUIOwner-Objekt wird zwischen TRiAS und das eigentliche 
' UIOwner-Objekt geschaltet:

Function WrapUIOwner (OriginalOwner As DToolBarUIOwner) As DToolBarUIOwner

' anlegen des Objektes und verketten mit dem eigentlichen Objekt
Dim Wrapper As DummyUIOwner 

	Set Wrapper = New TRSABiS.DummyUIOwner
	Set Wrapper.TargetUIOwner = OriginalOwner

' Das Wrapperobjekt kann in 2 Modi arbeiten:
' - Normal: alle Aufrufe aus TRiAS heraus in das Wrapperobjekt werden
'           einfach an das originale UIOwner-Objekt weitergeleitet. Dieser Mode 
'           ist aktiviert, wenn nichts anderes vorgegeben wird.
	Wrapper.DebugMode = False		' Normal arbeiten

' - Debug:  es werden lediglich die Funktionsaufrufe 'FireCommand' und
'           'SetToolBarUIOwnerSite' an das originale UIOwner-Objekt durchgereicht
'           Die Aufrufe von 'UpdateUI' aktivieren den Button immer und 
'           'GetDescription' liefert immer eine leere Zeichenkette.
	Wrapper.DebugMode = True		' im Debugmode arbeiten

' Liefern des verpackten UIOwnerobjektes
	Set WrapUIOwner = Wrapper

End Function


Sub UnwrapUIOwner (WrappedUIOwner As DToolBarUIOwner)

' Am Schluß sollte die Property TargetUIOwner wieder zurückgesetzt werden
Dim Wrapper As TRSABiS.DummyUIOwner

	Set Wrapper = WrappedUIOwner
	Set Wrapper.TargetUIOwner = Nothing		' verpacktes Objekt freigeben
	Set WrappedUIOwner = Nothing			' Objekt selbst freigeben

End Sub
