unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Memo1: TMemo;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form1: TForm1;
  vTrias: OleVariant;
  nID: Integer;

implementation

{$R *.DFM}
uses KanalKopplung_TLB, math;

procedure TForm1.Button1Click(Sender: TObject);
begin
  Button1.enabled := FALSE;
  vTrias :=  CoKoppelmodul.Create;
  vTrias.StarteKopplung;
  vTrias.ZeigeTRiAS(TRUE);

  Button2.enabled := TRUE;
  Button3.enabled := TRUE;
end;

function CalcTriasWinkel(c: string; dAblGKR, dAblGKH, dZulGKR, dZulGKH: double): double;
begin
  try
    try
      // Winkel zwischen zwei Punkten errechnen
      Result := ArcTan2( (dZulGKH - dAblGKH) ,
                       (dZulGKR - dAblGKR));
    except
      on E:Exception do begin
        Result := pi/2;
      end;
    end;
    // auf Triaswinkel normalisieren
    if (Result >= 0.0) and (Result < pi/2) then begin

    end else if (Result >= pi/2) and (Result < pi) then begin
      Result := result + pi;
    end else if (Result >= pi) and (Result < (pi*3/2)) then begin
      Result := result - pi;
    end else if (Result >= (pi*3/2)) and (Result < 2*pi) then begin

    end else begin
      Form1.memo1.Lines.add('???'+FloatToStr(Result));
    end;
    Result := Result * -90.0 / (pi/2);

    Form1.memo1.Lines.add(c+FloatToStr(Result));
  except
    on E:Exception do begin
      Form1.memo1.Lines.add(E.Message);
    end;
  end;

end;


procedure Linie(x1, y1, x2, y2: double);
var
  vX, vY, vZ: OleVariant;
   n: Integer;
begin

  inc(nID);

  // Linie aus zwei Punkten
  vX := VarArrayCreate([0,1], varDouble);
  vY := VarArrayCreate([0,1], varDouble);
  vZ := VarArrayCreate([0,1], varDouble);

  // Linie in den sichtbaren Bereich schieben
{  x1:= x1 + 3530000;
  y1:= y1 + 5730000;
  x2:= x2 + 3530000;
  y2:= y2 + 5730000;
}
  // Variant füllen
  vX[0] := x1;
  vY[0] := y1;
  vZ[0] := 0.0;
  vX[1] := x2;
  vY[1] := y2;
  vZ[1] := 0.0;

  // Linie zeichen
  vTrias.ErzeugeLinie(
                      vX,
                      vY,
                      vZ,
                      intToStr(nID),
                      'klasse'
  );

end;

procedure textOut(x, y, w: double; c: string);
var
   n: Integer;
begin
     // eindeutige ID
    inc(nID);

    // Text in den sichtbaren bereich schieben
//    x:= x + 3530000;
//    y:= y + 5730000;

    // Textausgabe
    n := vTrias.ErzeugeText(
                       x,
                       y,
                       0.0,
                       1,
                       w,
                       'Text_'+c,
                       'text'+intToStr(nID),
                       'klasse');
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  i: Integer;
  d: double;
  dZulGKR, dZulGKH, dAblGKR, dAblGKH: double;
  dx, dy: double;
begin

  vTrias.StartGeometryTransaction(1);

  dAblGKR := 2551970.0;
  dAblGKH := 5601633.0;
  dZulGKR := 2552007.0;
  dZulGKH := 5601635.0;
  dx := (dAblGKR - dZulGKR ) / 2 + dZulGKR ;
  dy := (dAblGKH - dZulGKH ) / 2 + dZulGKH ;

  // 45 Gradlinie nach links oben
  Linie  (dAblGKR, dAblGKH, dZulGKR, dZulGKH);
  TextOut(dAblGKR, dAblGKH, 0, 'Ablauf');
  TextOut(dZulGKR, dZulGKH, 0, 'Zulauf');
  TextOut(dx , dy,  CalcTriasWinkel('Test',dAblGKR, dAblGKH, dZulGKR, dZulGKH) ,'Testhaltung');

  dAblGKR := 2551266.0;
  dAblGKH := 5602041.0;
  dZulGKR := 2551255.0;
  dZulGKH := 5602091.0;
  dx := (dAblGKR - dZulGKR ) / 2 + dZulGKR ;
  dy := (dAblGKH - dZulGKH ) / 2 + dZulGKH ;

  // 45 Gradlinie nach links oben
  Linie  (dAblGKR, dAblGKH, dZulGKR, dZulGKH);
  TextOut(dAblGKR, dAblGKH, 0, 'Ablauf');
  TextOut(dZulGKR, dZulGKH, 0, 'Zulauf');
  TextOut(dx , dy,  CalcTriasWinkel('Test',dAblGKR, dAblGKH, dZulGKR, dZulGKH) ,'Testhaltung');

{
  // Nullpunkt
  TextOut(0, 0, 0, 'koor 00');

  // 45 Gradlinie nach rechts oben
  Linie  (0, 0, 10.0, 10.0);
  TextOut(10.0, 10.0, 0, 'koor 10');
  TextOut(5.0, 5.0, CalcTriasWinkel('45.0',0, 0, 10.0, 10.0)  ,'rechtsoben');

  // 0 Gradlinie
  Linie  (0, 0, 10.0, 0.0);
  TextOut(10.0, 0.0, 0, 'koor 10 0');
  TextOut(5.0, 0.0, CalcTriasWinkel('0 Grad', 0, 0, 10.0, 0.0) ,'waagerecht');

  // 45 Gradlinie nach rechts unten
  Linie  (0, 0, 10.0, -10.0);
  TextOut(10.0, -10.0, 0, 'koor 10-10');
  TextOut(5.0, -5.0, CalcTriasWinkel('-45',0, 0, 10.0, -10.0) ,'rechtsunten');

  // 45 Gradlinie nach links unten
  Linie  (0, 0, -10.0, -10.0);
  TextOut(-10.0, -10.0, 0, 'koor -10-10');
  TextOut(-5.0, -5.0, CalcTriasWinkel('-45',0, 0, -10.0, -10.0) ,'linksunten');

  // 45 Gradlinie nach links oben
  Linie  (0, 0, -10.0, 10.0);
  TextOut(-10.0, 10.0, 0, 'koor -10 10');
  TextOut(-5.0, 5.0,  CalcTriasWinkel('-45',0, 0, -10.0, 10.0) ,'linksoben');
}
  vTrias.EndGeometryTransaction;

end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  try
    if not varisempty(vTrias) then begin
      vTrias.BeendeKopplung;
      vTrias := unassigned;
    end;
  finally
    close;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  nID:=0;
end;

procedure TForm1.Button4Click(Sender: TObject);
var
  dAblGKR, dAblGKH, dZulGKR, dZulGKH: double;
  dWinkel: double;
  c: string;
begin
  CalcTriasWinkel('   0 Grad',  0.0,  0.0, 10.0,  0.0);
  CalcTriasWinkel('  45 Grad',  0.0,  0.0, 10.0, 10.0);
  CalcTriasWinkel('  90 Grad',  0.0,  0.0,  0.0, 10.0);
  CalcTriasWinkel(' 135 Grad',  0.0,  0.0,-10.0, 10.0);
  CalcTriasWinkel(' 180 Grad',  0.0,  0.0,-10.0,  0.0);
  CalcTriasWinkel(' 225 Grad',  0.0,  0.0,-10.0,-10.0);
  CalcTriasWinkel(' 270 Grad',  0.0,  0.0,  0.0,-10.0);
  CalcTriasWinkel(' 315 Grad',  0.0,  0.0, 10.0,-10.0);
  CalcTriasWinkel(' 360 Grad',  0.0,  0.0, 10.0,  0.0);


end;

end.
