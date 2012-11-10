Dieses Projekt dient zum Erzeugen der Geomedia-Objektheader (*.tlh)

- Include - Pfad
  Unter 'Project->Settings->Preprocessor->Include Paths'
  ist der Pfad zur aktuellen Geomedia-Installation einzutragen
  Beispiel: 
  - 3 Versionen sind installiert:
    c:/Programme/GeoMedia/Geomedia1
	c:/Programme/GeoMedia/Geomedia2
	c:/Programme/GeoMedia/GeomediaPro
  - GeomediaPro soll benutzt werden
    -> Pfadeintrag 'c:/Programme/GeoMedia/GeomediaPro'
  - die Typelibrary-Header werden jetzt aus
    c:/Programme/GeoMedia/GeomediaPro/program/*.tlb
	genommen

- aktuell müssen die Bibliotheken von Geomedia-Pro genutzt werden
  da 'GMGeomTransform.tlb' nicht mehr existiert (ist jetzt in 'PClient.tlb')
