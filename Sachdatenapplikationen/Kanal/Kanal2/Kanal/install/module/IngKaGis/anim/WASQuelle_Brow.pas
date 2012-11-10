unit WASQuelle_Brow;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdGridWin, Menus, StdCtrls, Buttons, DBCtrls, ExtCtrls, Grids, DBGrids,
  DBTables, defines;

type
  TFWASQuelle_Brow = class(TF)
  private
    { Private-Deklarationen }
    slSelect: TStringlist; { SQL strings für die Selektion }
  public
    { Public-Deklarationen }
    procedure Init(ltTyp: TltTyp; qry: TQuery);
  end;

var
  FWASQuelle_Brow: TFWASQuelle_Brow;

implementation

{$R *.DFM}
Uses    stdutil
              , dbUtil
              , Haupt_Util
              , DMDBWasser
              , haupt
              IniFiles
              ;

procedure TFWASQuelle_Brow.Init(ltTyp: TltTyp; qry: TQuery);
begin
  ltWindowTyp := ltTyp;
  inherited;
  {dlg('Init haltung');}
  cmbSort.items.add('Name ');            slSort.Add('WQ.NAME ASCENDING');
  cmbSort.items.add('Name invers');      slSort.Add('WQ.NAME DESCENDING');
  cmbSort.itemindex :=0;

  DBG.DataSource := DMWasser.DSQuelle;
  DBN.DataSource := DMWasser.DSQuelle;
end;

end.
