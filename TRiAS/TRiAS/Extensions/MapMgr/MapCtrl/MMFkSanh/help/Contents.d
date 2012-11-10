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
