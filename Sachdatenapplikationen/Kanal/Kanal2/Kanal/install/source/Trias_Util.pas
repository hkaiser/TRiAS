unit Trias_Util;

interface
  function StartTrias: boolean;
  function BeendeTrias: boolean;
  procedure ZeigeTrias;
  function ZeichneSchaechte(lAlle: Boolean): boolean;
  function ZeichneHaltungen(lAlle: Boolean): boolean;

var
  vTrias: OleVariant;

const
  Text_Links = 0;
  Text_Mitte = 1;
  Text_Rechts = 2;

implementation

uses sysutils, forms,  stdutil, KanalKopplung_Tlb, dmdbBestand;

function StartTrias: boolean;
begin
  Result := TRUE;
  try
    vTrias := CoKoppelmodul.Create;
    vTrias.StarteKopplung;
  except
    on E:Exception do begin
      Dlg(E.Message);
      Result := FALSE;
    end;
  end;
end;

procedure ZeigeTrias;
begin
  if not VarIsEmpty(vTrias) then begin
    vTrias.ZeigeTrias(TRUE);
  end;
end;

function BeendeTrias: boolean;
begin
  Result := TRUE;
  try
    if not VarIsEmpty(vTrias) then begin
      vTrias.Beendekopplung;
      vTrias := unassigned;
    end;
  except
    on E:Exception do begin
      Dlg(E.Message);
      Result := FALSE;
    end;
  end;
end;

function ZeichneSchaechte(lAlle: Boolean): boolean;

begin
  vTrias.StartGeometryTransaction(10);
  dmBestand.QrySchacht.first;
  while not dmBestand.QrySchacht.eof do begin
    vTrias.ErzeugeKreis(    dmBestand.QryDeckelGKR.AsFloat,
                            dmBestand.QryDeckelGKH.AsFloat,
                            0.625,
                            'SchachtDeckel'+dmBestand.QryDeckelID.AsString,
                            'klasse');
    vTrias.ErzeugeText(     dmBestand.QryDeckelGKR.AsFloat + 1.0,
                            dmBestand.QryDeckelGKH.AsFloat + 1.0,
                            Text_Links,
                            0,
                            dmBestand.QrySchachtBezeich.AsString,
                            'DeckelText'+dmBestand.QryDeckelID.AsString,
                            'klasse');

    dmBestand.QrySchacht.next;
  end;
  vTrias.EndGeometryTransaction;
end;
function ZeichneHaltungen(lAlle: Boolean): boolean;
var
  vPktX, vPktY, vPktZ: OleVariant;
  n:Integer;
begin
  try
    try
      vTrias.StartGeometryTransaction(10);
//      vTrias.SetzeFont('Courier');

      dmBestand.QryHaltung.first;
      n := 0;
      // Linie aus zwei Punkten
      vPktX := VarArrayCreate([0,1], varDouble);
      vPktY := VarArrayCreate([0,1], varDouble);
      vPktZ := VarArrayCreate([0,1], varDouble);

      while not dmBestand.QryHaltung.eof do begin
        if (dmBestand.QryZulaufGKR.AsFloat > 0.0 ) and
           (dmBestand.QryZulaufGKH.AsFloat > 0.0 ) and
           (dmBestand.QryAblaufGKR.AsFloat > 0.0 ) and
           (dmBestand.QryAblaufGKH.AsFloat > 0.0 ) then begin
          vPktX[0] := dmBestand.QryZulaufGKR.AsFloat;
          vPktY[0] := dmBestand.QryZulaufGKH.AsFloat;
          vPktZ[0] := 0.0;
          vPktX[1] := dmBestand.QryAblaufGKR.AsFloat;
          vPktY[1] := dmBestand.QryAblaufGKH.AsFloat;
          vPktZ[1] := 0.0;
          inc(n);
          if vTrias.ErzeugeLinie( vPktX,
                                  vPktY,
                                  vPktZ,
                                  'Haltung'+dmBestand.QryHaltungID.AsString,
                                  'klasse') <> 0 then begin
                                Dlg('Fehler');
            Application.Processmessages;
          end;

          // Zeichne Stutzen
       {
        dmBestand.QryStutzen.first;
        while not dmBestand.QryStutzen.eof do begin
          vTrias.ErzeugeSymbol(
                               'Stutzen'+dmBestand.QryStutzenID.AsString);
          dmBestand.QryStutzen.Next;
        end;
        }
{
    vTrias.ErzeugeText(     dmBestand.QryDeckelGKR.AsFloat + 1.0,
                            dmBestand.QryDeckelGKH.AsFloat + 1.0,
                            1,
                            0,
                            dmBestand.QrySchachtBezeich.AsString,
                            'DeckelText'+dmBestand.QryDeckelID.AsString,
                            'klasse');
}

          dmBestand.QryHaltung.next;
        end;  
      end;
    except
      on E:Exception do begin
        Dlg(E.Message);
      end;
    end;

  finally
    vTrias.EndGeometryTransaction;
  end;
end;

end.
