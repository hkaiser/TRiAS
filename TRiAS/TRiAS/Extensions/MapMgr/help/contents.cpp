#line 1 ".\\help\\Contents.d"
/*
@doc
@contents1 Inhaltsverzeichnis |
@subindex Rasterdatenformate
@subindex Rasterdaten als Hintergrundbild

@normal Diese Hilfedatei wurde erzeugt am: <date>

@subindex Über diese Hilfedatei

***********************************************************************
@contents2 Rasterdatenformate |
@index topic | PICT_COMMON
***********************************************************************
@contents2 Rasterdaten als Hintergrundbild |
@head1 Allgemeines |
@index topic | MAP_COMMON
@head1 zur Verfügung stehende Importmodule |
@index topic | MODULE
***********************************************************************
@contents2 Über diese Hilfedatei | 
Copyright<csign> 1991-1998 <company>, #<copyright> V<version>
@doc PICT_COMMON
@topic Bilddateitypen |
Für Bilddateien sind im wesentlichen die folgenden Kriterien kennzeichnend:
@head1 Farbtiefe |
Die Farbtiefe gibt an wieviel Bit verwendet werden um einen Bildpunkt
abzuspeichern. Üblich sind die folgenden Werte:
<nl>1 Bit pro Pixel (max. 2 Farben, resp. schwarz/weiß)
<nl>4 Bit pro Pixel (max. 16 Farben)
<nl>8 Bit pro Pixel (max. 256 Farben)
<nl>24 Bit pro Pixel (max. 16 Mio. Farben)
<nl>
@ex Palettenbild mit 256 Farben |
@normal <bmp \./PictTypePal256\.bmp>
@ex Schwarz / weiß Bild |
@normal <bmp \./PictTypeBW\.bmp>
@head1 Dateiformat |
Das Dateiformat definiert die Art und Weise wie die Bilddaten abgespeichert
werden. Dazu gehören unter anderem:
<nl>Organisation der abgelegten Daten
<nl>Kompression der Daten
<nl>ggf. zusätzliche Informationen (Bildname, Bildnummer usw.)
@normal Das Dateiformat ist im allgemeinen mit einer bestimmten Dateierweiterung
assoziiert; z.B. haben Bilddaten im Windows-Bitmap Format i.a. die Endung '.bmp',
Bilddaten im Tiff-Format die Endung '.tif'.
@tip Wenn eine Bilddatei in einem bestimmten Format vorliegt kann im allgemeinen
nicht auf Eigenschaften wie Farbtiefe, Kompression usw. geschlossen werden. Um
diese Eigenschaften zu ermitteln sind entsprechende Programme notwendig.
@topic derzeit unterstützte Bilddateitypen |
Derzeit werden von TRiAS<rtm> die folgenden Rasterdatenformate unterstützt:
<nl>Tiff 1 Bit pro Pixel, unkomprimiert, G3 und G4-komprimiert
<nl>Tiff 4 und 8 Bit pro Pixel, unkomprimiert, RLE-komprimiert
<nl>Windows-Bitmap 1,4,8 Bit pro Pixel, unkomprimiert, RLE-komprimiert
*/

#line 1 ".\\help\\MapCommon.d"
/*
@doc MAP_COMMON
@topic Generelle Aufgabenstellung |
Beim Hinterlegen von Rasterdaten in einem Geoinformationssystem steht allgemein
die Aufgabe eine Bilddatei zu georefernzieren und anhand dieser Referenzierung
im GIS darzustellen. Als Georeferenzierung verstehen wir dabei die Angabe
einer Vorschrift wie für einen beliebigen Punkt in der Rasterdatei die zugehörige
Koordinate in einem gegebenen Koordinatensystem ermittelt werden kann.
<nl>Allgemein reicht für die Georeferenzierung die Angabe der
Abbildungsvorschrift für die Rasterpunkte sowie eine bestimmte Anzahl von
Referenzpunkten (i.a. vier) aus.
@ex Referenzpunkte |
@normal <bmp MapRefPoints\.bmp>
*/
#line 58 ".\\help\\Contents.d"
#line 1 ".\\help\\../MapCtrl/MMFKSAnh/help/contents.d"
/*
@doc MODULE
@topic Flurkarten des Landesvermessungsamtes Sachsen Anhalt |
@normal Das Landesvermessungsamt Sachsen Anhalt stellt georeferenzierte Flurkarten
als TIFF-Dateien bereit. Die Referenzierungsinformationen sind
im Image-Description-Tag (Tag270) enthalten, z.B. wie folgt:
@ex Referenzierungsinformationen von Flurkarten des Landesvermessungsamtes Sachsen Anhalt |
{ Embeddings:
  { uor_min: ( 4506983.130286242        , 5721761.652502531        ) }
  { uor_max: ( 4509358.564827944        , 5724693.781623119        ) }
  { ControlPoints:
    { PointPair:
      { File: ( 13028.3378148349         , 311.7172243694131        ) }
      { World: ( 4508647.134              , 5724653.965              ) }
    }
    { PointPair:
      { File: ( 18357.6007892361         , 19043.38804123749        ) }
      { World: ( 4509327.474              , 5722261.728              ) }
    }
    { PointPair:
      { File: ( 6181.439594400465        , 22439.17084217877        ) }
      { World: ( 4507772.705              , 5721828.034              ) }
    }
    { PointPair:
      { File: ( 943.8719738908815        , 3670.657934435269        ) }
      { World: ( 4507103.539              , 5724225.003              ) }
    }
  }
}
@normal Diese Struktur stellt alle notwendigen Informationen für das Einpassen der Rasterdatei
bereit so daß weitere Bearbeitungsschritte nicht notwendig sind.
@tip Neben den eigentlichen Referenzpunkten (uor_min bzw. uor_max) werden weitere Kontrollpunkte
(typischerweise vier) mitgeliefert. Diese Punkte werden vom Importmodul ausgewertet und in TRiAS<rtm>
importiert. Die Kontrollpunkte sollten stets mit markanten Punkten im Rasterbild deckungsgleich sein.
*/
#line 59 ".\\help\\Contents.d"
#line 1 ".\\help\\../MapCtrl/MMArcInf/help/contents.d"
/*
@doc MODULE
@topic Arc-Info Rasterdaten |
@normal Arc-Info benutzt zur Referenzierung von Rasterdaten eine sogenannte World
Datei. Typischerweise besitzt diese Datei die Endung .tfw.
@ex Aufbau einer Arc-Info - World-Datei |
12.390
0
0
-12.390
4456789.3456
5678901.2345
@tip Wenn Arc-Info Rasterdaten als Rasterkartentyp ausgewählt wurde, werden Sie
im Anschluß an die Auswahl der Rasterdatei aufgefordert die zugeordnete World-Datei
anzugeben. Typischerweise sollte die World-Datei in demselben Verzeichnis wie die
Rasterdatei liegen und beide Namen (bis auf die Erweiterung) gleich sein.
*/
#line 60 ".\\help\\Contents.d"
#line 1 ".\\help\\../MapCtrl/MMRefer/help/contents.d"
/*
@doc MODULE
@topic Karten mit bekannten Eckkoordinaten |
@normal Für den Import dieses Dateityps müssen die Koordinaten zweier diagonal gegenüberliegender
Eckpunkte der Bilddatei bekannt sein.
<bmp \.\./MapCtrl/MMRefer/help/PPgMMRefer\.bmp>
*/
#line 61 ".\\help\\Contents.d"
