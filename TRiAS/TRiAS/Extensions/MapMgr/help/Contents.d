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

#include "MapCommon.d"
#include "../MapCtrl/MMFKSAnh/help/contents.d"
#include "../MapCtrl/MMArcInf/help/contents.d"
#include "../MapCtrl/MMRefer/help/contents.d"
